/**
 * @file websocket_client.c
 * @brief WebSocket client implementation using libwebsockets for FlexRIC
 */

#include "websocket_client.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define MAX_PAYLOAD_SIZE 4096
#define MAX_QUEUED_MESSAGES 32

/**
 * @struct websocket_message
 * @brief A queued message
 */
typedef struct
{
    char *data;
    size_t len;
} websocket_message_t;

/**
 * @struct websocket_client
 * @brief Internal WebSocket client data
 */
struct websocket_client
{
    websocket_client_config_t config;
    struct lws_context *context;
    struct lws *wsi;
    char rx_buffer[MAX_PAYLOAD_SIZE + LWS_PRE];
    unsigned int rx_buffer_len;

    // Message queue
    websocket_message_t message_queue[MAX_QUEUED_MESSAGES];
    int message_queue_count;
    int message_queue_index;

    // Status tracking
    websocket_status_t status;
    time_t last_connect_attempt;

    // Callbacks
    websocket_message_callback_t message_cb;
    websocket_connection_callback_t connection_cb;
    void *user_data;
};

// Forward declarations for internal functions
static int callback_websocket(struct lws *wsi, enum lws_callback_reasons reason,
                              void *user, void *in, size_t len);
static void queue_message(websocket_client_t *client, const char *message, size_t len);
static void clear_message_queue(websocket_client_t *client);
static void update_client_status(websocket_client_t *client, websocket_status_t status);

// Protocol definition
static struct lws_protocols protocols[] = {
    {
        "flexric-protocol",
        callback_websocket,
        0, // per_session_data_size
        MAX_PAYLOAD_SIZE,
        0,    // id
        NULL, // user
        0     // tx_packet_size
    },
    {NULL, NULL, 0, 0, 0, NULL, 0} // terminator
};

/**
 * libwebsockets callback handler
 */
static int callback_websocket(struct lws *wsi, enum lws_callback_reasons reason,
                              void *user, void *in, size_t len)
{
    struct lws_vhost *vhost = lws_get_vhost(wsi);
    websocket_client_t *client = NULL;

    if (vhost)
    {
        client = (websocket_client_t *)lws_wsi_user(wsi);
    }

    if (!client)
    {
        return 0;
    }

    switch (reason)
    {
    case LWS_CALLBACK_CLIENT_ESTABLISHED:
        update_client_status(client, WS_STATUS_CONNECTED);
        lws_callback_on_writable(wsi);
        break;

    case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
    {
        const char *error_msg = in ? (char *)in : "Unknown error";
        fprintf(stderr, "WebSocket connection error: %s\n", error_msg);
        client->wsi = NULL;
        update_client_status(client, WS_STATUS_DISCONNECTED);
    }
    break;

    case LWS_CALLBACK_CLIENT_CLOSED:
        client->wsi = NULL;
        update_client_status(client, WS_STATUS_DISCONNECTED);
        break;

    case LWS_CALLBACK_CLIENT_RECEIVE:
        if (len + client->rx_buffer_len > sizeof(client->rx_buffer) - LWS_PRE - 1)
        {
            fprintf(stderr, "WebSocket receive buffer overflow\n");
            break;
        }

        memcpy(client->rx_buffer + LWS_PRE + client->rx_buffer_len, in, len);
        client->rx_buffer_len += len;
        client->rx_buffer[LWS_PRE + client->rx_buffer_len] = '\0';

        if (lws_is_final_fragment(wsi))
        {
            if (client->message_cb)
            {
                client->message_cb(client,
                                   (const char *)(client->rx_buffer + LWS_PRE),
                                   client->rx_buffer_len,
                                   client->user_data);
            }
            client->rx_buffer_len = 0;
        }
        break;

    case LWS_CALLBACK_CLIENT_WRITEABLE:
        if (client->message_queue_count > 0)
        {
            websocket_message_t *msg = &client->message_queue[client->message_queue_index];

            if (msg->data && msg->len > 0)
            {
                unsigned char *buf = (unsigned char *)msg->data;
                int n = lws_write(wsi, buf + LWS_PRE, msg->len, LWS_WRITE_TEXT);

                if (n < (int)msg->len)
                {
                    fprintf(stderr, "WebSocket write error\n");
                }

                free(msg->data);
                msg->data = NULL;
                msg->len = 0;

                client->message_queue_index = (client->message_queue_index + 1) % MAX_QUEUED_MESSAGES;
                client->message_queue_count--;

                if (client->message_queue_count > 0)
                {
                    lws_callback_on_writable(wsi);
                }
            }
        }
        break;

    default:
        break;
    }

    return 0;
}

/**
 * Update client status and invoke callback if necessary
 */
static void update_client_status(websocket_client_t *client, websocket_status_t status)
{
    if (client->status != status)
    {
        client->status = status;

        if (client->connection_cb)
        {
            client->connection_cb(client, status, client->user_data);
        }
    }
}

/**
 * Queue a message for sending
 */
static void queue_message(websocket_client_t *client, const char *message, size_t len)
{
    if (client->message_queue_count >= MAX_QUEUED_MESSAGES)
    {
        fprintf(stderr, "WebSocket message queue full, dropping message\n");
        return;
    }

    // Allocate buffer with room for LWS_PRE
    unsigned char *buf = (unsigned char *)malloc(LWS_PRE + len + 1);
    if (!buf)
    {
        fprintf(stderr, "Failed to allocate message buffer\n");
        return;
    }

    // Copy message after LWS_PRE offset
    memcpy(buf + LWS_PRE, message, len);
    buf[LWS_PRE + len] = '\0';

    // Add to queue
    int index = (client->message_queue_index + client->message_queue_count) % MAX_QUEUED_MESSAGES;
    client->message_queue[index].data = (char *)buf;
    client->message_queue[index].len = len;
    client->message_queue_count++;

    // Request a writable callback if connected
    if (client->wsi && client->status == WS_STATUS_CONNECTED)
    {
        lws_callback_on_writable(client->wsi);
    }
}

/**
 * Clear message queue
 */
static void clear_message_queue(websocket_client_t *client)
{
    for (int i = 0; i < MAX_QUEUED_MESSAGES; i++)
    {
        if (client->message_queue[i].data)
        {
            free(client->message_queue[i].data);
            client->message_queue[i].data = NULL;
            client->message_queue[i].len = 0;
        }
    }

    client->message_queue_count = 0;
    client->message_queue_index = 0;
}

/**
 * Initialize a WebSocket client
 */
websocket_client_t *websocket_client_init(
    const websocket_client_config_t *config,
    websocket_message_callback_t message_cb,
    websocket_connection_callback_t connection_cb,
    void *user_data)
{
    assert(config != NULL);

    websocket_client_t *client = (websocket_client_t *)calloc(1, sizeof(websocket_client_t));
    if (!client)
    {
        fprintf(stderr, "Failed to allocate memory for WebSocket client\n");
        return NULL;
    }

    // Copy configuration
    client->config = *config;
    client->message_cb = message_cb;
    client->connection_cb = connection_cb;
    client->user_data = user_data;
    client->status = WS_STATUS_DISCONNECTED;

    return client;
}

/**
 * Free a WebSocket client
 */
void websocket_client_free(websocket_client_t *client)
{
    if (!client)
    {
        return;
    }

    websocket_client_disconnect(client);

    if (client->context)
    {
        lws_context_destroy(client->context);
        client->context = NULL;
    }

    clear_message_queue(client);
    free(client);
}

/**
 * Connect to the WebSocket server
 */
bool websocket_client_connect(websocket_client_t *client)
{
    assert(client != NULL);

    // Already connected or connecting
    if (client->status != WS_STATUS_DISCONNECTED)
    {
        return true;
    }

    // Create context if needed
    if (!client->context)
    {
        struct lws_context_creation_info info;
        memset(&info, 0, sizeof(info));

        info.port = CONTEXT_PORT_NO_LISTEN;
        info.protocols = protocols;
        info.gid = -1;
        info.uid = -1;

        if (client->config.use_ssl)
        {
            info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
        }

        client->context = lws_create_context(&info);
        if (!client->context)
        {
            fprintf(stderr, "Failed to create WebSocket context\n");
            return false;
        }

        // Set wsi user data
        
        // Store client pointer for callbacks
        struct lws_vhost *vhost = lws_create_vhost(client->context, &info);
        if (!vhost)
        {
            fprintf(stderr, "Failed to create WebSocket vhost\n");
            lws_context_destroy(client->context);
            client->context = NULL;
            return false;
        }
        
        if (vhost)
        {
            printf("Setting vhost user data\n");
            //  lws_set_vhost_user(vhost, client);
            //  lws_set_vhost_user(vhost, client);
        }
    }

    // Create connection
    struct lws_client_connect_info conn_info;
    memset(&conn_info, 0, sizeof(conn_info));

    conn_info.context = client->context;
    conn_info.address = client->config.host;
    conn_info.port = client->config.port;
    conn_info.path = client->config.path;
    conn_info.host = lws_canonical_hostname(client->context);
    conn_info.origin = "origin";
    conn_info.protocol = protocols[0].name;

    if (client->config.use_ssl)
    {
        conn_info.ssl_connection = LCCSCF_USE_SSL;

        if (client->config.skip_cert_verify)
        {
            conn_info.ssl_connection |= LCCSCF_ALLOW_SELFSIGNED |
                                        LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;
        }
    }

    client->wsi = lws_client_connect_via_info(&conn_info);
    if (!client->wsi)
    {
        fprintf(stderr, "Failed to connect to WebSocket server\n");
        return false;
    }

    // Set client user data
    lws_set_wsi_user(client->wsi, client);

    update_client_status(client, WS_STATUS_CONNECTING);
    client->last_connect_attempt = time(NULL);

    return true;
}

/**
 * Disconnect from the WebSocket server
 */
void websocket_client_disconnect(websocket_client_t *client)
{
    assert(client != NULL);

    if (client->wsi)
    {
        lws_set_timeout(client->wsi, PENDING_TIMEOUT_CLOSE_SEND, LWS_TO_KILL_ASYNC);
        client->wsi = NULL;
    }

    update_client_status(client, WS_STATUS_DISCONNECTED);
}

/**
 * Get current connection status
 */
websocket_status_t websocket_client_get_status(websocket_client_t *client)
{
    assert(client != NULL);
    return client->status;
}

/**
 * Send a text message
 */
bool websocket_client_send(websocket_client_t *client, const char *message)
{
    assert(client != NULL);
    assert(message != NULL);

    size_t len = strlen(message);
    if (len == 0)
    {
        return false;
    }

    queue_message(client, message, len);
    return true;
}

/**
 * Send a JSON object
 */
bool websocket_client_send_json(websocket_client_t *client, json_object *json)
{
    assert(client != NULL);
    assert(json != NULL);

    const char *str = json_object_to_json_string(json);
    if (!str)
    {
        return false;
    }

    return websocket_client_send(client, str);
}

/**
 * Service the WebSocket connection
 */
bool websocket_client_service(websocket_client_t *client, int timeout_ms)
{
    assert(client != NULL);

    if (!client->context)
    {
        return false;
    }

    // Handle reconnection if enabled
    if (client->status == WS_STATUS_DISCONNECTED &&
        client->config.reconnect_interval > 0)
    {

        time_t now = time(NULL);
        if (now - client->last_connect_attempt >= client->config.reconnect_interval)
        {
            websocket_client_connect(client);
        }
    }

    return lws_service(client->context, timeout_ms) >= 0;
}

/**
 * Run the WebSocket event loop
 */
void websocket_client_run(websocket_client_t *client, volatile int *stop_flag)
{
    assert(client != NULL);
    assert(stop_flag != NULL);

    while (!*stop_flag)
    {
        websocket_client_service(client, 100);
    }
}
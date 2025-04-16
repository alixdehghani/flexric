#include "sm_uetrace.h"
#include "../src/util/time_now_us.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <signal.h>
// #include <unistd.h>
// #include <pthread.h>

// Global variables
static websocket_client_t *client = NULL;
// static pthread_t ws_thread = 0;
// static int ws_thread_running = 0;

// Add to global variables section
static int message_count = 0;
static uetrace_stats_t **metrics_array = NULL;
static int *metrics_lengths = NULL; // Store the length of each metrics array
static has_websocket_works_normal = true;

// Configuration

static http_client_t *uetrace_http_client = NULL;
static uint8_t sector_num = 0;
static char *backend_addr = NULL;
static char *websocket_path = NULL;

#define MAX_MESSAGES 10
#define WSS_SERVER_PORT 443

/**
 * WebSocket message callback
 */
void handle_uetrace_ws_message(websocket_client_t *client, const char *message, size_t len, void *user_data)
{
    // printf("Received message (%zu bytes): %s\n", len, message);

    // Initialize arrays if not done yet
    if (metrics_array == NULL)
    {
        metrics_array = (uetrace_stats_t **)calloc(MAX_MESSAGES, sizeof(uetrace_stats_t *));
        metrics_lengths = (int *)calloc(MAX_MESSAGES, sizeof(int));
        if (metrics_array == NULL || metrics_lengths == NULL)
        {
            fprintf(stderr, "Failed to allocate metrics array\n");
            has_websocket_works_normal = false;
            return;
        }
    }

    // Parse the JSON string
    json_object *root = json_parse_string(message);
    if (root == NULL)
    {
        fprintf(stderr, "Failed to parse JSON\n");
        has_websocket_works_normal = false;
        return;
    }

    // Verify it's an array
    if (!json_object_is_type(root, json_type_array))
    {
        fprintf(stderr, "JSON is not an array\n");
        has_websocket_works_normal = false;
        json_object_put(root);
        return;
    }

    // Process each object in the array
    int array_len = json_object_array_length(root);
    printf("Found %d network metric entries in message %d\n", array_len, message_count + 1);

    // Store metrics from this message in the array if we haven't reached the limit
    if (message_count < MAX_MESSAGES)
    {
        // Allocate memory for this message's metrics
        metrics_array[message_count] = (uetrace_stats_t *)calloc(array_len, sizeof(uetrace_stats_t));
        metrics_lengths[message_count] = array_len;

        // Process and store metrics for this message
        for (int i = 0; i < array_len; i++)
        {
            json_object *metrics = json_object_array_get_idx(root, i);

            if (!json_object_is_type(metrics, json_type_object))
            {
                fprintf(stderr, "Array element %d is not an object\n", i);
                continue;
            }

            uetrace_stats_t *rb = &metrics_array[message_count][i];

            // Extract each metric value
            rb->bsr = json_get_double(metrics, "bsr");
            rb->dl_bler = json_get_double(metrics, "dl_bler");
            rb->dl_cqi = json_get_double(metrics, "dl_cqi");
            rb->dl_mcs = json_get_double(metrics, "dl_mcs");
            rb->dl_pmi = json_get_double(metrics, "dl_pmi");
            rb->dl_rate = json_get_double(metrics, "dl_rate");
            rb->dl_ri = json_get_double(metrics, "dl_ri");
            rb->phr = json_get_double(metrics, "phr");
            rb->rnti = json_get_int(metrics, "rnti");
            rb->snr = json_get_double(metrics, "snr");
            rb->snr_pucch = json_get_double(metrics, "snr_pucch");
            rb->ul_bler = json_get_double(metrics, "ul_bler");
            rb->ul_mcs = json_get_double(metrics, "ul_mcs");
            rb->ul_rate = json_get_double(metrics, "ul_rate");

            // Debug print
            // printf("Stored metrics for message %d, entry %d, RNTI: %d, BSR: %f, dl_bler: %f, ul_bler: %f\n",
            //        message_count + 1, i + 1, rb->rnti, rb->bsr, rb->dl_bler, rb->ul_bler);
        }

        printf("Processed message %d of %d\n", message_count, MAX_MESSAGES);
    }
    message_count++;

    json_object_put(root);
}

/**
 * WebSocket connection status callback
 */
void handle_uetrace_ws_connection_change(websocket_client_t *client, websocket_status_t status, void *user_data)
{
    switch (status)
    {
    case WS_STATUS_CONNECTED:
        printf("WebSocket connection established\n");
        // Send initial commands after connection
        send_uetrace_subscription_command(client);
        break;

    case WS_STATUS_CONNECTING:
        printf("WebSocket connecting...\n");
        break;

    case WS_STATUS_DISCONNECTED:
        printf("WebSocket disconnected\n");
        break;
    }
}

/**
 * Example: Create and send a subscription command
 */
void send_uetrace_subscription_command(websocket_client_t *client)
{
    // Create command object
    json_object *cmd = json_create_object();
    json_add_string(cmd, "message", "metrics_start");
    json_add_string(cmd, "sector", "sector-1");
    json_add_string(cmd, "token", "devtmptoken");

    // Send command
    printf("Sending subscription command\n");
    websocket_client_send_json(client, cmd);

    // Free resources
    json_object_put(cmd);
}

void send_uetrace_unsubscription_command(websocket_client_t *client)
{
    // Create command object
    json_object *cmd = json_create_object();
    json_add_string(cmd, "message", "metrics_stop");
    json_add_string(cmd, "sector", "sector-1");
    json_add_string(cmd, "token", "devtmptoken");

    // Send command
    printf("Sending unsubscription command\n");
    websocket_client_send_json(client, cmd);

    // Free resources
    json_object_put(cmd);
}

// void *uetrace_websocket_thread_function(void *arg)
// {
//     websocket_client_t *ws_client = (websocket_client_t *)arg;
//     time_t last_metrics_time = 0;
//     int loop_count = 0;

//     printf("WebSocket service thread started\n");

//     while (ws_thread_running)
//     {
//         // Service the WebSocket
//         websocket_client_service(ws_client, 100);

//         // Send metrics every 10 seconds if connected
//         time_t now = time(NULL);
//         if (now - last_metrics_time >= 10 && websocket_client_get_status(ws_client) == WS_STATUS_CONNECTED)
//         {
//             last_metrics_time = now;

//             // Manually interrupt after the third loop if needed
//             loop_count++;
//             if (loop_count == 3)
//             {
//                 printf("Sending unsubscription command after third loop\n");
//                 send_uetrace_unsubscription_command(ws_client);
//                 // Don't set interrupted here as it would affect the main thread
//                 // Instead, we can just break out of the loop
//                 // break;
//             }
//         }
//     }

//     printf("WebSocket service thread exiting\n");
//     free_uetrace_sm();
//     return NULL;
// }

void init_uetrace_sm(void)
{
}
/**
 * Free the metrics array
 */
void free_metrics_array()
{
    if (metrics_array != NULL)
    {
        for (int i = 0; i < MAX_MESSAGES; i++)
        {
            if (metrics_array[i] != NULL)
            {
                free(metrics_array[i]);
                metrics_array[i] = NULL;
            }
        }
    }
}

void free_uetrace_sm(void)
{

    printf("Shutting down uetrace service model...\n");

    // Stop WebSocket thread if it's running
    // if (ws_thread_running)
    // {
    //     ws_thread_running = 0;

    //     // Send unsubscription command if connected
    //     if (client && websocket_client_get_status(client) == WS_STATUS_CONNECTED)
    //     {
    //         send_uetrace_unsubscription_command(client);
    //     }

    //     // Wait for thread to finish
    //     if (ws_thread != 0)
    //     {
    //         pthread_join(ws_thread, NULL);
    //         ws_thread = 0;
    //     }
    // }

    // Free WebSocket client
    free_metrics_array();
    if (client)
    {
        send_uetrace_unsubscription_command(client);
        websocket_client_free(client);
        client = NULL;
    }
    has_websocket_works_normal = true;

    printf("uetrace service model shutdown complete\n");
}

void set_uetrace_http_client(http_client_t *client)
{
    uetrace_http_client = client;
}

void set_uetrace_num_of_sector(uint8_t num)
{
    sector_num = num;
}

void set_uetrace_backend_host_addr(char *addr)
{
    backend_addr = addr;
}

void set_uetrace_backend_websocket_path(char *addr)
{
    websocket_path = addr;
}

bool read_uetrace_sm(void *data)
{
    assert(data != NULL);
    uetrace_ind_data_t *uetrace = (uetrace_ind_data_t *)data;
    assert(uetrace != NULL);
    srand(time(0));
    uetrace_ind_msg_t *ind_msg = &uetrace->msg;

    printf("FlexRIC WebSocket for getting uetrace\n");
    printf("========================\n\n");
    // Create WebSocket client configuration
    websocket_client_config_t config = {
        .host = backend_addr,
        .port = WSS_SERVER_PORT,
        .path = websocket_path,
        .use_ssl = true,
        .skip_cert_verify = true,
        .reconnect_interval = 5 // Reconnect every 5 seconds
    };

    // Initialize WebSocket client
    client = websocket_client_init(&config, handle_uetrace_ws_message, handle_uetrace_ws_connection_change, NULL);
    if (!client)
    {
        fprintf(stderr, "Failed to initialize WebSocket client\n");
        has_websocket_works_normal = false;
        return false;
    }

    printf("Connecting to WSS server at %s:%d%s\n",
           config.host, config.port, config.path);

    // Connect to server
    if (!websocket_client_connect(client))
    {
        fprintf(stderr, "Failed to connect to WebSocket server\n");
        has_websocket_works_normal = false;
        websocket_client_free(client);
        return false;
    }

    printf("Connection initiated...\n");
    // Reset counters
    message_count = 0;
    // Create and start the WebSocket service thread
    // ws_thread_running = 1;
    // if (pthread_create(&ws_thread, NULL, uetrace_websocket_thread_function, client) != 0)
    // {
    //     fprintf(stderr, "Failed to create WebSocket service thread\n");
    //     websocket_client_free(client);
    //     client = NULL;
    //     return;
    // }

    // The function returns immediately, allowing the application to continue
    // printf("WebSocket client initialized in async mode\n");

    while (message_count < MAX_MESSAGES && has_websocket_works_normal == true)
    {
        // Service the WebSocket
        websocket_client_service(client, 100);
        usleep(10000); // 10ms
    }
    if (has_websocket_works_normal == true)
    {
        int allItems = 0;
        for (int i = 0; i < MAX_MESSAGES; i++)
        {
            allItems += metrics_lengths[i];
        }
        ind_msg->len = allItems;
        if (ind_msg->len > 0)
        {
            ind_msg->rb = calloc(ind_msg->len, sizeof(uetrace_stats_t));
            assert(ind_msg->rb != NULL);
        }
        int counters = 0;
        for (int i = 0; i < MAX_MESSAGES; i++)
        {
            for (int j = 0; j < metrics_lengths[i]; j++)
            {
                uetrace_stats_t *rb = &ind_msg->rb[counters];
                rb->bsr = metrics_array[i][j].bsr;
                rb->dl_bler = metrics_array[i][j].dl_bler;
                rb->dl_cqi = metrics_array[i][j].dl_cqi;
                rb->dl_mcs = metrics_array[i][j].dl_mcs;
                rb->dl_pmi = metrics_array[i][j].dl_pmi;
                rb->dl_rate = metrics_array[i][j].dl_rate;
                rb->dl_ri = metrics_array[i][j].rnti;
                rb->phr = metrics_array[i][j].phr;
                rb->rnti = metrics_array[i][j].rnti;
                rb->snr = metrics_array[i][j].snr;
                rb->snr_pucch = metrics_array[i][j].snr_pucch;
                rb->ul_bler = metrics_array[i][j].ul_bler;
                rb->ul_mcs = metrics_array[i][j].ul_mcs;
                rb->ul_rate = metrics_array[i][j].ul_rate;
                counters++;
            }
        }
    }
    ind_msg->tstamp = time_now_us();

    // Clean up
    free_uetrace_sm();

    return true;
}

void read_uetrace_setup_sm(void *data)
{
    assert(data != NULL);
    //  assert(data->type == uetrace_AGENT_IF_E2_SETUP_ANS_V0 );
    assert(0 != 0 && "Not supported");
}

sm_ag_if_ans_t write_ctrl_uetrace_sm(void const *data)
{
    (void)data;
    assert(0 != 0 && "Not supported");
}
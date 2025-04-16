/**
 * @file websocket_client.h
 * @brief WebSocket client interface for FlexRIC
 */

 #ifndef WEBSOCKET_CLIENT_H
 #define WEBSOCKET_CLIENT_H
 
 #include <libwebsockets.h>
 #include <stdbool.h>
 #include <json-c/json.h>
 
 /**
  * @struct websocket_client_config_t
  * @brief Configuration for WebSocket client
  */
 typedef struct {
     const char *host;         /**< Server hostname */
     int port;                 /**< Server port */
     const char *path;         /**< WebSocket endpoint path */
     bool use_ssl;             /**< Whether to use secure WebSocket (WSS) */
     bool skip_cert_verify;    /**< Whether to skip SSL certificate verification */
     int reconnect_interval;   /**< Reconnection interval in seconds (0 to disable) */
 } websocket_client_config_t;
 
 /**
  * @struct websocket_client_t
  * @brief WebSocket client handle (opaque)
  */
 typedef struct websocket_client websocket_client_t;
 
 /**
  * @enum websocket_status_t
  * @brief Status of the WebSocket connection
  */
 typedef enum {
     WS_STATUS_DISCONNECTED,  /**< Not connected */
     WS_STATUS_CONNECTING,    /**< Connection in progress */
     WS_STATUS_CONNECTED      /**< Successfully connected */
 } websocket_status_t;
 
 /**
  * @typedef websocket_message_callback_t
  * @brief Callback function for received messages
  * @param client The client instance
  * @param message The received message
  * @param len Length of the message
  * @param user_data User data provided during initialization
  */
 typedef void (*websocket_message_callback_t)(
     websocket_client_t *client, 
     const char *message, 
     size_t len, 
     void *user_data
 );
 
 /**
  * @typedef websocket_connection_callback_t
  * @brief Callback function for connection status changes
  * @param client The client instance
  * @param status New connection status
  * @param user_data User data provided during initialization
  */
 typedef void (*websocket_connection_callback_t)(
     websocket_client_t *client, 
     websocket_status_t status, 
     void *user_data
 );
 
 /**
  * @brief Initialize a WebSocket client
  * @param config Client configuration
  * @param message_cb Callback for received messages (can be NULL)
  * @param connection_cb Callback for connection status changes (can be NULL)
  * @param user_data User data to pass to callbacks
  * @return Initialized client or NULL on failure
  */
 websocket_client_t* websocket_client_init(
     const websocket_client_config_t *config,
     websocket_message_callback_t message_cb,
     websocket_connection_callback_t connection_cb,
     void *user_data
 );
 
 /**
  * @brief Free a WebSocket client
  * @param client Client to free
  */
 void websocket_client_free(websocket_client_t *client);
 
 /**
  * @brief Connect to the WebSocket server
  * @param client Initialized client
  * @return true on success, false on failure
  */
 bool websocket_client_connect(websocket_client_t *client);
 
 /**
  * @brief Disconnect from the WebSocket server
  * @param client Connected client
  */
 void websocket_client_disconnect(websocket_client_t *client);
 
 /**
  * @brief Get current connection status
  * @param client Client to check
  * @return Current status
  */
 websocket_status_t websocket_client_get_status(websocket_client_t *client);
 
 /**
  * @brief Send a text message
  * @param client Connected client
  * @param message Message to send
  * @return true on success, false on failure
  */
 bool websocket_client_send(websocket_client_t *client, const char *message);
 
 /**
  * @brief Send a JSON object
  * @param client Connected client
  * @param json JSON object to send
  * @return true on success, false on failure
  */
 bool websocket_client_send_json(websocket_client_t *client, json_object *json);
 
 /**
  * @brief Service the WebSocket connection (process events)
  * @param client Client to service
  * @param timeout_ms Maximum time to wait in milliseconds
  * @return true if events were processed, false on timeout or error
  */
 bool websocket_client_service(websocket_client_t *client, int timeout_ms);
 
 /**
  * @brief Run the WebSocket event loop in the current thread
  * @param client Client to run
  * @param stop_flag Pointer to a flag that will stop the loop when set to non-zero
  */
 void websocket_client_run(websocket_client_t *client, volatile int *stop_flag);
 
 #endif /* WEBSOCKET_CLIENT_H */
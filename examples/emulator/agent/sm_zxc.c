#include "sm_zxc.h"
#include "../src/util/time_now_us.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

// Global variables
static volatile int interrupted = 0;
static websocket_client_t *client = NULL;

// Configuration
#define WSS_SERVER_HOST "192.168.80.222"
#define WSS_SERVER_PORT 443
#define WSS_SERVER_PATH "/ws"



/**
 * Signal handler for clean shutdown
 */
void handle_zxc_signal(int sig) {
    interrupted = 1;
}

/**
 * WebSocket message callback
 */
void handle_zxc_message(websocket_client_t *client, const char *message, size_t len, void *user_data) {
    printf("Received message (%zu bytes): %s\n", len, message);

     // Parse the JSON string
     json_object* root = json_parse_string(message);
     if (root == NULL) {
         fprintf(stderr, "Failed to parse JSON\n");
         return;
     }
     
     // Verify it's an array
     if (!json_object_is_type(root, json_type_array)) {
         fprintf(stderr, "JSON is not an array\n");
         json_object_put(root);
         return;
     }
     
     // Process each object in the array
     int array_len = json_object_array_length(root);
     printf("Found %d network metric entries\n", array_len);
     
     for (int i = 0; i < array_len; i++) {
         json_object* metrics = json_object_array_get_idx(root, i);
         
         if (!json_object_is_type(metrics, json_type_object)) {
             fprintf(stderr, "Array element %d is not an object\n", i);
             continue;
         }
         
         printf("\nNetwork Metrics Entry #%d:\n", i+1);
         printf("---------------------------\n");
         
         // Get each metric value using the wrapper functions
         int bsr = json_get_int(metrics, "bsr");
         int dl_bler = json_get_int(metrics, "dl_bler");
         int dl_cqi = json_get_int(metrics, "dl_cqi");
         int dl_mcs = json_get_int(metrics, "dl_mcs");
         int dl_pmi = json_get_int(metrics, "dl_pmi");
         int dl_rate = json_get_int(metrics, "dl_rate");
         int dl_ri = json_get_int(metrics, "dl_ri");
         int phr = json_get_int(metrics, "phr");
         int rnti = json_get_int(metrics, "rnti");
         int snr = json_get_int(metrics, "snr");
         int snr_pucch = json_get_int(metrics, "snr_pucch");
         int ul_bler = json_get_int(metrics, "ul_bler");
         int ul_mcs = json_get_int(metrics, "ul_mcs");
         int ul_rate = json_get_int(metrics, "ul_rate");
         
         // Print all metrics
         printf("BSR: %d\n", bsr);
         printf("DL BLER: %d%%\n", dl_bler);
         printf("DL CQI: %d\n", dl_cqi);
         printf("DL MCS: %d\n", dl_mcs);
         printf("DL PMI: %d\n", dl_pmi);
         printf("DL Rate: %d bps\n", dl_rate);
         printf("DL RI: %d\n", dl_ri);
         printf("PHR: %d dB\n", phr);
         printf("RNTI: %d\n", rnti);
         printf("SNR: %d dB\n", snr);
         printf("SNR PUCCH: %d dB\n", snr_pucch);
         printf("UL BLER: %d%%\n", ul_bler);
         printf("UL MCS: %d\n", ul_mcs);
         printf("UL Rate: %d bps\n", ul_rate);
     }
     
     // Clean up
     json_object_put(root);
    
    // Parse JSON response
    // json_object *json = json_parse_string(message);
    // if (!json) {
    //     fprintf(stderr, "Failed to parse JSON response\n");
    //     return;
    // }
    
    // Extract message type
    // const char *msg_type = json_get_array(json, "type");

    // const char *msg_type = json_get_string(json, "type");
    // if (msg_type) {
    //     printf("Message type: %s\n", msg_type);
        
    //     // Handle different message types
    //     if (strcmp(msg_type, "event") == 0) {
    //         json_object *data = json_get_object(json, "data");
    //         if (data) {
    //             const char *event_type = json_get_string(data, "event");
    //             printf("Event: %s\n", event_type);
                
    //             // Handle specific events as needed
    //         }
    //     } else if (strcmp(msg_type, "response") == 0) {
    //         int status = json_get_int(json, "status");
    //         printf("Response status: %d\n", status);
            
    //         // Handle response data
    //         json_object *data = json_get_object(json, "data");
    //         if (data) {
    //             // Process response data
    //             printf("Response data: %s\n", json_to_string(data));
    //         }
    //     }
    // }
    
    // json_object_put(json);
}

/**
 * WebSocket connection status callback
 */
void handle_zxc_connection_change(websocket_client_t *client, websocket_status_t status, void *user_data) {
    switch (status) {
        case WS_STATUS_CONNECTED:
            printf("WebSocket connection established\n");
            // Send initial commands after connection
            send_zxc_subscription_command(client);
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
void send_zxc_subscription_command(websocket_client_t *client) {
    // // Create subscription payload
    // json_object *payload = json_create_object();
    // json_add_string(payload, "action", "subscribe");
    // json_add_string(payload, "channel", "metrics");
    
    // // Create filter object
    // json_object *filter = json_create_object();
    // json_add_string(filter, "node_id", "gnb-001");
    // json_add_string(filter, "metric_type", "performance");
    
    // // Add filter to payload
    // json_add_object(payload, "filter", filter);
    
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

void send_zxc_unsubscription_command(websocket_client_t *client) {    
    // Create command object
    json_object *cmd = json_create_object();
    json_add_string(cmd, "message", "metrics_stop");
    json_add_string(cmd, "sector", "sector-1");
    json_add_string(cmd, "token	", "devtmptoken");
    
    // Send command
    printf("Sending unsubscription command\n");
    websocket_client_send_json(client, cmd);
    
    // Free resources
    json_object_put(cmd);
}

/**
 * Example: Create and send a metrics command
 */
void send_zxc_metrics_command(websocket_client_t *client) {
    // Create metrics payload
    json_object *payload = json_create_object();
    json_add_string(payload, "action", "report");
    
    // Create metrics object
    json_object *metrics = json_create_object();
    json_add_string(metrics, "ric_id", "flexric-001");
    json_add_string(metrics, "timestamp", "2025-04-07T12:00:00Z");
    json_add_double(metrics, "cpu_usage", 23.5);
    json_add_int(metrics, "active_nodes", 3);
    
    // Add metrics to payload
    json_add_object(payload, "metrics", metrics);
    
    // Create command object
    json_object *cmd = json_create_object();
    json_add_string(cmd, "type", "event");
    json_add_object(cmd, "data", payload);
    
    // Send command
    printf("Sending metrics command\n");
    websocket_client_send_json(client, cmd);
    
    // Free resources
    json_object_put(cmd);
}


void init_zxc_sm(void)
{
    // Set up signal handler
    signal(SIGINT, handle_zxc_signal);
    
    printf("FlexRIC WebSocket Example\n");
    printf("========================\n\n");
     // Create WebSocket client configuration
     websocket_client_config_t config = {
        .host = WSS_SERVER_HOST,
        .port = WSS_SERVER_PORT,
        .path = WSS_SERVER_PATH,
        .use_ssl = true,
        .skip_cert_verify = true,
        .reconnect_interval = 5  // Reconnect every 5 seconds
    };
    
    // Initialize WebSocket client
    client = websocket_client_init(&config, handle_zxc_message, handle_zxc_connection_change, NULL);
    if (!client) {
        fprintf(stderr, "Failed to initialize WebSocket client\n");
        return 1;
    }
    
    printf("Connecting to WSS server at %s:%d%s\n", 
           config.host, config.port, config.path);
    
    // Connect to server
    if (!websocket_client_connect(client)) {
        fprintf(stderr, "Failed to connect to WebSocket server\n");
        websocket_client_free(client);
        return 1;
    }
    
    printf("Connection initiated...\n");
    
    // Main loop
    time_t last_metrics_time = 0;
    int loop_count = 0;
    while (!interrupted) {
        // Service the WebSocket
        websocket_client_service(client, 100);
        
        // Send metrics every 10 seconds if connected
        time_t now = time(NULL);
        if (now - last_metrics_time >= 10 && websocket_client_get_status(client) == WS_STATUS_CONNECTED) {
            // send_zxc_metrics_command(client);
            last_metrics_time = now;
            // Manually interrupt after the third loop
            loop_count++;
            if (loop_count == 3) {
                printf("Manually interrupting after third loop\n");
                send_zxc_unsubscription_command(client);
                interrupted = 1;
            }
        }

    }
    
    printf("Shutting down...\n");
    
    // Clean up
    websocket_client_free(client);
}

void free_zxc_sm(void)
{
  // No allocation needed
}


bool read_zxc_sm(void* data)
{
  return true;
}

void read_zxc_setup_sm(void* data)
{
  assert(data != NULL);
//  assert(data->type == zxc_AGENT_IF_E2_SETUP_ANS_V0 );
  assert(0 !=0 && "Not supported");
}


sm_ag_if_ans_t write_ctrl_zxc_sm(void const* data)
{

  assert(data != NULL);

  sm_ag_if_ans_t ans = {.type = CTRL_OUTCOME_SM_AG_IF_ANS_V0 };
  return ans;
}


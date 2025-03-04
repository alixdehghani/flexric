/**
 * @file http_json_example.c
 * @brief Example application using HTTP client and JSON parser for FlexRIC
 *
 * This example demonstrates how to:
 * 1. Fetch data from a REST API
 * 2. Parse JSON responses
 * 3. Create JSON objects
 * 4. Post JSON data
 * 5. Use both libraries together in a FlexRIC-related context
 */

 #include "http_client.h"
 #include "json_parser.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 
 // URLs for the example (replace with real endpoints in actual use)
 #define API_GET_URL "https://jsonplaceholder.typicode.com/todos/1"
 #define API_POST_URL "https://jsonplaceholder.typicode.com/posts"
 
 // Function prototypes
 void fetch_and_display_data(http_client_t* client);
 void create_and_post_data(http_client_t* client);
 void simulate_ric_metrics_report(http_client_t* client);
 
 int main(int argc, char* argv[]) {
     printf("FlexRIC HTTP/JSON Example\n");
     printf("=========================\n\n");
     
     // Initialize the HTTP client
     http_client_t* client = http_client_init();
     if (!client) {
         fprintf(stderr, "Failed to initialize HTTP client\n");
         return 1;
     }
     
     printf("HTTP client initialized successfully\n\n");
     
     // Run the examples
     printf("Example 1: Fetching and displaying data\n");
     printf("---------------------------------------\n");
     fetch_and_display_data(client);
     printf("\n");
     
     printf("Example 2: Creating and posting data\n");
     printf("-----------------------------------\n");
     create_and_post_data(client);
     printf("\n");
     
     printf("Example 3: Simulating RIC metrics reporting\n");
     printf("------------------------------------------\n");
     simulate_ric_metrics_report(client);
     printf("\n");
     
     // Clean up
     http_client_free(client);
     printf("HTTP client cleaned up\n");
     
     return 0;
 }
 
 /**
  * Example 1: Fetch data from an API and display it
  */
 void fetch_and_display_data(http_client_t* client) {
     // Make GET request
     printf("Fetching data from %s\n", API_GET_URL);
     http_result_t result = http_get(client, API_GET_URL);
     
     if (!result.success) {
         fprintf(stderr, "HTTP request failed with status code %ld\n", result.status_code);
         return;
     }
     
     printf("Received %zu bytes of data\n", result.size);
     printf("Raw response: %s\n", result.data);
     
     // Parse the JSON
     json_object* json = json_parse_string(result.data);
     if (!json) {
         fprintf(stderr, "Failed to parse JSON response\n");
         http_result_free(&result);
         return;
     }
     
     // Extract and display data
     printf("\nParsed JSON data:\n");
     printf("  User ID: %d\n", json_get_int(json, "userId"));
     printf("  ID: %d\n", json_get_int(json, "id"));
     printf("  Title: %s\n", json_get_string(json, "title"));
     printf("  Completed: %s\n", json_get_bool(json, "completed") ? "true" : "false");
     
     // Clean up
     json_object_put(json);
     http_result_free(&result);
 }
 
 /**
  * Example 2: Create JSON data and post it to an API
  */
 void create_and_post_data(http_client_t* client) {
     // Create a JSON object
     json_object* post = json_create_object();
     json_add_int(post, "userId", 1);
     json_add_string(post, "title", "FlexRIC HTTP/JSON Example");
     json_add_string(post, "body", "This is a test post from the FlexRIC HTTP/JSON example application.");
     
     // Convert to string and display
     const char* json_str = json_to_string(post);
     printf("Created JSON object:\n%s\n", json_str);
     
     // Post the data
     printf("\nPosting data to %s\n", API_POST_URL);
     http_result_t result = http_post(client, API_POST_URL, json_str, "application/json");
     
     if (!result.success) {
         fprintf(stderr, "HTTP POST failed with status code %ld\n", result.status_code);
         json_object_put(post);
         return;
     }
     
     printf("POST successful\n");
     printf("Response: %s\n", result.data);
     
     // Parse the response
     json_object* response = json_parse_string(result.data);
     if (response) {
         printf("\nServer assigned ID: %d\n", json_get_int(response, "id"));
         json_object_put(response);
     }
     
     // Clean up
     json_object_put(post);
     http_result_free(&result);
 }
 
 /**
  * Example 3: Simulate sending RIC metrics to a monitoring system
  */
 void simulate_ric_metrics_report(http_client_t* client) {
     // Create the main metrics object
     json_object* metrics = json_create_object();
     
     // Add RIC identity information
     json_add_string(metrics, "ric_id", "flexric-001");
     json_add_string(metrics, "version", "0.0.1");
     json_add_string(metrics, "timestamp", "2025-03-03T12:00:00Z");
     
     // Create and add E2 nodes array
     json_object* e2_nodes = json_create_array();
     
     // Add first E2 node
     json_object* node1 = json_create_object();
     json_add_string(node1, "id", "gnb-001");
     json_add_string(node1, "connection_status", "connected");
     json_add_int(node1, "uptime_seconds", 3600);
     
     // Add second E2 node
     json_object* node2 = json_create_object();
     json_add_string(node2, "id", "gnb-002");
     json_add_string(node2, "connection_status", "connected");
     json_add_int(node2, "uptime_seconds", 1800);
     
     // Add third E2 node (disconnected)
     json_object* node3 = json_create_object();
     json_add_string(node3, "id", "gnb-003");
     json_add_string(node3, "connection_status", "disconnected");
     json_add_int(node3, "uptime_seconds", 0);
     
     // Add nodes to array
     json_array_add_object(e2_nodes, node1);
     json_array_add_object(e2_nodes, node2);
     json_array_add_object(e2_nodes, node3);
     
     // Add the nodes array to the metrics object
     json_add_object(metrics, "e2_nodes", e2_nodes);
     
     // Add performance metrics
     json_object* performance = json_create_object();
     json_add_int(performance, "active_subscriptions", 12);
     json_add_int(performance, "messages_processed", 15240);
     json_add_double(performance, "avg_response_time_ms", 4.3);
     json_add_int(performance, "memory_usage_kb", 134576);
     json_add_double(performance, "cpu_usage_percent", 23.5);
     
     // Add performance metrics to main object
     json_add_object(metrics, "performance", performance);
     
     // Convert to string
     const char* metrics_json = json_to_string(metrics);
     printf("RIC Metrics Report:\n%s\n", metrics_json);
     
     // In a real application, you would send this to a monitoring system
     printf("\nIn a real application, these metrics would be sent to a monitoring service.\n");
     printf("Example: POST to https://monitoring.example.com/api/ric/metrics\n");
     
     // Simulate posting (this would use a real endpoint in production)
     // http_result_t result = http_post(client, "https://monitoring.example.com/api/ric/metrics", 
     //                                 metrics_json, "application/json");
     
     // Clean up
     json_object_put(metrics);
     // Don't forget to free result with http_result_free(&result) in real code
 }
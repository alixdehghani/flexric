/**
 * @file http_client.c
 * @brief HTTP client implementation using libcurl for FlexRIC
 */

 #include "http_client.h"
 #include <stdlib.h>
 #include <string.h>
 #include <assert.h>
 
 struct http_response {
     char* data;
     size_t size;
 };
 
 static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
     size_t realsize = size * nmemb;
     struct http_response* resp = (struct http_response*)userp;
     
     char* ptr = realloc(resp->data, resp->size + realsize + 1);
     if(!ptr) {
         /* out of memory */
         fprintf(stderr, "Failed to allocate memory for HTTP response\n");
         return 0;
     }
     
     resp->data = ptr;
     memcpy(&(resp->data[resp->size]), contents, realsize);
     resp->size += realsize;
     resp->data[resp->size] = 0;
     
     return realsize;
 }
 
 http_client_t* http_client_init() {
     http_client_t* client = (http_client_t*)malloc(sizeof(http_client_t));
     if (client == NULL) {
         fprintf(stderr, "Failed to allocate memory for HTTP client\n");
         return NULL;
     }
     
     client->curl = curl_easy_init();
     if (client->curl == NULL) {
         fprintf(stderr, "Failed to initialize curl\n");
         free(client);
         return NULL;
     }
     
     /* Default settings */
     curl_easy_setopt(client->curl, CURLOPT_TIMEOUT, 10L); /* 10 seconds timeout */
     curl_easy_setopt(client->curl, CURLOPT_FOLLOWLOCATION, 1L); /* follow redirects */
     curl_easy_setopt(client->curl, CURLOPT_WRITEFUNCTION, write_callback);
     
     return client;
 }
 
 void http_client_free(http_client_t* client) {
     if (client != NULL) {
         if (client->curl != NULL) {
             curl_easy_cleanup(client->curl);
         }
         free(client);
     }
 }
 
 http_result_t http_get(http_client_t* client, const char* url) {
     assert(client != NULL);
     assert(url != NULL);
     
     http_result_t result = {0};
     struct http_response response = {0};
     
     response.data = malloc(1);
     response.size = 0;
     
     curl_easy_setopt(client->curl, CURLOPT_URL, url);
     curl_easy_setopt(client->curl, CURLOPT_HTTPGET, 1L);
     curl_easy_setopt(client->curl, CURLOPT_WRITEDATA, (void*)&response);
     
     CURLcode res = curl_easy_perform(client->curl);
     
     if (res != CURLE_OK) {
         fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
         result.success = false;
         result.data = NULL;
         free(response.data);
     } else {
         long response_code;
         curl_easy_getinfo(client->curl, CURLINFO_RESPONSE_CODE, &response_code);
         
         result.success = (response_code >= 200 && response_code < 300);
         result.status_code = response_code;
         result.data = response.data;
         result.size = response.size;
     }
     
     return result;
 }
 
 http_result_t http_post(http_client_t* client, const char* url, const char* data, const char* content_type) {
     assert(client != NULL);
     assert(url != NULL);
     assert(data != NULL);
     
     http_result_t result = {0};
     struct http_response response = {0};
     
     response.data = malloc(1);
     response.size = 0;
     
     struct curl_slist* headers = NULL;
     if (content_type != NULL) {
         char content_type_header[128];
         snprintf(content_type_header, sizeof(content_type_header), "Content-Type: %s", content_type);
         headers = curl_slist_append(headers, content_type_header);
     }
     
     curl_easy_setopt(client->curl, CURLOPT_URL, url);
     curl_easy_setopt(client->curl, CURLOPT_POST, 1L);
     curl_easy_setopt(client->curl, CURLOPT_POSTFIELDS, data);
     curl_easy_setopt(client->curl, CURLOPT_HTTPHEADER, headers);
     curl_easy_setopt(client->curl, CURLOPT_WRITEDATA, (void*)&response);
     
     CURLcode res = curl_easy_perform(client->curl);
     
     if (headers != NULL) {
         curl_slist_free_all(headers);
     }
     
     if (res != CURLE_OK) {
         fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
         result.success = false;
         result.data = NULL;
         free(response.data);
     } else {
         long response_code;
         curl_easy_getinfo(client->curl, CURLINFO_RESPONSE_CODE, &response_code);
         
         result.success = (response_code >= 200 && response_code < 300);
         result.status_code = response_code;
         result.data = response.data;
         result.size = response.size;
     }
     
     return result;
 }
 
 void http_result_free(http_result_t* result) {
     if (result != NULL && result->data != NULL) {
         free(result->data);
         result->data = NULL;
         result->size = 0;
     }
 }
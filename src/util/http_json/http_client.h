/**
 * @file http_client.h
 * @brief HTTP client interface for FlexRIC using libcurl
 */

 #ifndef HTTP_CLIENT_H
 #define HTTP_CLIENT_H
 
 #include <curl/curl.h>
 #include <stdbool.h>
 #include <stdio.h>
 
 /**
  * @struct http_client_t
  * @brief HTTP client handle
  */
 typedef struct {
     CURL* curl;  /**< curl handle */
 } http_client_t;
 
 /**
  * @struct http_result_t
  * @brief HTTP response result
  */
 typedef struct {
     bool success;      /**< true if request was successful */
     long status_code;  /**< HTTP status code */
     char* data;        /**< response data */
     size_t size;       /**< size of response data */
 } http_result_t;
 
 /**
  * @brief Initialize an HTTP client
  * @return Initialized client or NULL on failure
  */
 http_client_t* http_client_init();
 
 /**
  * @brief Free an HTTP client
  * @param client Client to free
  */
 void http_client_free(http_client_t* client);
 
 /**
  * @brief Perform an HTTP GET request
  * @param client Initialized client
  * @param url URL to get
  * @return Response result
  */
 http_result_t http_get(http_client_t* client, const char* url);
 
 /**
  * @brief Perform an HTTP POST request
  * @param client Initialized client
  * @param url URL to post to
  * @param data Data to post
  * @param content_type Content type or NULL for default
  * @return Response result
  */
 http_result_t http_post(http_client_t* client, const char* url, const char* data, const char* content_type);
 
 /**
  * @brief Free the result data from an HTTP request
  * @param result Result to free
  */
 void http_result_free(http_result_t* result);
 
 #endif /* HTTP_CLIENT_H */
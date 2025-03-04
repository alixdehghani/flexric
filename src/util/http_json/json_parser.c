/**
 * @file json_parser.c
 * @brief JSON parser implementation using json-c for FlexRIC
 */

 #include "json_parser.h"
 #include <string.h>
 #include <assert.h>
 
 json_object* json_parse_string(const char* str) {
     assert(str != NULL);
     
     json_object* obj = json_tokener_parse(str);
     if (obj == NULL) {
         fprintf(stderr, "Failed to parse JSON string\n");
     }
     
     return obj;
 }
 
 json_object* json_create_object() {
     return json_object_new_object();
 }
 
 json_object* json_create_array() {
     return json_object_new_array();
 }
 
 void json_add_string(json_object* obj, const char* key, const char* value) {
     assert(obj != NULL);
     assert(key != NULL);
     assert(value != NULL);
     
     json_object_object_add(obj, key, json_object_new_string(value));
 }
 
 void json_add_int(json_object* obj, const char* key, int value) {
     assert(obj != NULL);
     assert(key != NULL);
     
     json_object_object_add(obj, key, json_object_new_int(value));
 }
 
 void json_add_double(json_object* obj, const char* key, double value) {
     assert(obj != NULL);
     assert(key != NULL);
     
     json_object_object_add(obj, key, json_object_new_double(value));
 }
 
 void json_add_bool(json_object* obj, const char* key, bool value) {
     assert(obj != NULL);
     assert(key != NULL);
     
     json_object_object_add(obj, key, json_object_new_boolean(value));
 }
 
 void json_add_object(json_object* obj, const char* key, json_object* value) {
     assert(obj != NULL);
     assert(key != NULL);
     assert(value != NULL);
     
     json_object_object_add(obj, key, value);
 }
 
 void json_array_add_string(json_object* array, const char* value) {
     assert(array != NULL);
     assert(value != NULL);
     
     json_object_array_add(array, json_object_new_string(value));
 }
 
 void json_array_add_int(json_object* array, int value) {
     assert(array != NULL);
     
     json_object_array_add(array, json_object_new_int(value));
 }
 
 void json_array_add_double(json_object* array, double value) {
     assert(array != NULL);
     
     json_object_array_add(array, json_object_new_double(value));
 }
 
 void json_array_add_bool(json_object* array, bool value) {
     assert(array != NULL);
     
     json_object_array_add(array, json_object_new_boolean(value));
 }
 
 void json_array_add_object(json_object* array, json_object* value) {
     assert(array != NULL);
     assert(value != NULL);
     
     json_object_array_add(array, value);
 }
 
 const char* json_get_string(json_object* obj, const char* key) {
     assert(obj != NULL);
     assert(key != NULL);
     
     json_object* value;
     if (!json_object_object_get_ex(obj, key, &value)) {
         fprintf(stderr, "Key '%s' not found in JSON object\n", key);
         return NULL;
     }
     
     if (!json_object_is_type(value, json_type_string)) {
         fprintf(stderr, "Value for key '%s' is not a string\n", key);
         return NULL;
     }
     
     return json_object_get_string(value);
 }
 
 int json_get_int(json_object* obj, const char* key) {
     assert(obj != NULL);
     assert(key != NULL);
     
     json_object* value;
     if (!json_object_object_get_ex(obj, key, &value)) {
         fprintf(stderr, "Key '%s' not found in JSON object\n", key);
         return 0;
     }
     
     if (!json_object_is_type(value, json_type_int)) {
         fprintf(stderr, "Value for key '%s' is not an integer\n", key);
         return 0;
     }
     
     return json_object_get_int(value);
 }
 
 double json_get_double(json_object* obj, const char* key) {
     assert(obj != NULL);
     assert(key != NULL);
     
     json_object* value;
     if (!json_object_object_get_ex(obj, key, &value)) {
         fprintf(stderr, "Key '%s' not found in JSON object\n", key);
         return 0.0;
     }
     
     if (!json_object_is_type(value, json_type_double)) {
         fprintf(stderr, "Value for key '%s' is not a double\n", key);
         return 0.0;
     }
     
     return json_object_get_double(value);
 }
 
 bool json_get_bool(json_object* obj, const char* key) {
     assert(obj != NULL);
     assert(key != NULL);
     
     json_object* value;
     if (!json_object_object_get_ex(obj, key, &value)) {
         fprintf(stderr, "Key '%s' not found in JSON object\n", key);
         return false;
     }
     
     if (!json_object_is_type(value, json_type_boolean)) {
         fprintf(stderr, "Value for key '%s' is not a boolean\n", key);
         return false;
     }
     
     return json_object_get_boolean(value);
 }
 
 json_object* json_get_object(json_object* obj, const char* key) {
     assert(obj != NULL);
     assert(key != NULL);
     
     json_object* value;
     if (!json_object_object_get_ex(obj, key, &value)) {
         fprintf(stderr, "Key '%s' not found in JSON object\n", key);
         return NULL;
     }
     
     if (!json_object_is_type(value, json_type_object)) {
         fprintf(stderr, "Value for key '%s' is not an object\n", key);
         return NULL;
     }
     
     return value;
 }
 
 json_object* json_get_array(json_object* obj, const char* key) {
     assert(obj != NULL);
     assert(key != NULL);
     
     json_object* value;
     if (!json_object_object_get_ex(obj, key, &value)) {
         fprintf(stderr, "Key '%s' not found in JSON object\n", key);
         return NULL;
     }
     
     if (!json_object_is_type(value, json_type_array)) {
         fprintf(stderr, "Value for key '%s' is not an array\n", key);
         return NULL;
     }
     
     return value;
 }
 
 const char* json_to_string(json_object* obj) {
     assert(obj != NULL);
     
     return json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY);
 }
//  </antArtifact>
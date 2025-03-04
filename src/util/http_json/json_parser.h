/**
 * @file json_parser.h
 * @brief JSON parser interface for FlexRIC using json-c
 */

 #ifndef JSON_PARSER_H
 #define JSON_PARSER_H
 
 #include <json-c/json.h>
 #include <stdbool.h>
 #include <stdio.h>
 
 /**
  * @brief Parse a JSON string into a json-c object
  * @param str String to parse
  * @return Parsed JSON object or NULL on failure
  */
 json_object* json_parse_string(const char* str);
 
 /**
  * @brief Create a new JSON object
  * @return New JSON object
  */
 json_object* json_create_object();
 
 /**
  * @brief Create a new JSON array
  * @return New JSON array
  */
 json_object* json_create_array();
 
 /**
  * @brief Add a string to a JSON object
  * @param obj JSON object
  * @param key Key
  * @param value String value
  */
 void json_add_string(json_object* obj, const char* key, const char* value);
 
 /**
  * @brief Add an integer to a JSON object
  * @param obj JSON object
  * @param key Key
  * @param value Integer value
  */
 void json_add_int(json_object* obj, const char* key, int value);
 
 /**
  * @brief Add a double to a JSON object
  * @param obj JSON object
  * @param key Key
  * @param value Double value
  */
 void json_add_double(json_object* obj, const char* key, double value);
 
 /**
  * @brief Add a boolean to a JSON object
  * @param obj JSON object
  * @param key Key
  * @param value Boolean value
  */
 void json_add_bool(json_object* obj, const char* key, bool value);
 
 /**
  * @brief Add an object to a JSON object
  * @param obj JSON object
  * @param key Key
  * @param value Object value
  */
 void json_add_object(json_object* obj, const char* key, json_object* value);
 
 /**
  * @brief Add a string to a JSON array
  * @param array JSON array
  * @param value String value
  */
 void json_array_add_string(json_object* array, const char* value);
 
 /**
  * @brief Add an integer to a JSON array
  * @param array JSON array
  * @param value Integer value
  */
 void json_array_add_int(json_object* array, int value);
 
 /**
  * @brief Add a double to a JSON array
  * @param array JSON array
  * @param value Double value
  */
 void json_array_add_double(json_object* array, double value);
 
 /**
  * @brief Add a boolean to a JSON array
  * @param array JSON array
  * @param value Boolean value
  */
 void json_array_add_bool(json_object* array, bool value);
 
 /**
  * @brief Add an object to a JSON array
  * @param array JSON array
  * @param value Object value
  */
 void json_array_add_object(json_object* array, json_object* value);
 
 /**
  * @brief Get a string from a JSON object
  * @param obj JSON object
  * @param key Key
  * @return String value or NULL if not found or wrong type
  */
 const char* json_get_string(json_object* obj, const char* key);
 
 /**
  * @brief Get an integer from a JSON object
  * @param obj JSON object
  * @param key Key
  * @return Integer value or 0 if not found or wrong type
  */
 int json_get_int(json_object* obj, const char* key);
 
 /**
  * @brief Get a double from a JSON object
  * @param obj JSON object
  * @param key Key
  * @return Double value or 0.0 if not found or wrong type
  */
 double json_get_double(json_object* obj, const char* key);
 
 /**
  * @brief Get a boolean from a JSON object
  * @param obj JSON object
  * @param key Key
  * @return Boolean value or false if not found or wrong type
  */
 bool json_get_bool(json_object* obj, const char* key);
 
 /**
  * @brief Get an object from a JSON object
  * @param obj JSON object
  * @param key Key
  * @return Object value or NULL if not found or wrong type
  */
 json_object* json_get_object(json_object* obj, const char* key);
 
 /**
  * @brief Get an array from a JSON object
  * @param obj JSON object
  * @param key Key
  * @return Array value or NULL if not found or wrong type
  */
 json_object* json_get_array(json_object* obj, const char* key);
 
 /**
  * @brief Convert a JSON object to a string
  * @param obj JSON object
  * @return String representation of the JSON object
  */
 const char* json_to_string(json_object* obj);
 
 #endif /* JSON_PARSER_H */
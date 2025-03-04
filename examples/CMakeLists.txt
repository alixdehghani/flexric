add_subdirectory(emulator)
add_subdirectory(ric)
add_subdirectory(xApp)


# Add HTTP JSON example if curl and json-c are enabled
if(USE_CURL_JSON)
  add_subdirectory(http_json_example)
endif()
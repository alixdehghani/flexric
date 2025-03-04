add_library(http_json_obj OBJECT
            http_client.c
            json_parser.c)

target_include_directories(http_json_obj PRIVATE ${CURL_INCLUDE_DIRS} ${JSON-C_INCLUDE_DIRS})
target_compile_options(http_json_obj PRIVATE -fPIC -fvisibility=hidden)
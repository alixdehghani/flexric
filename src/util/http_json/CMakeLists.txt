
# Find curl and json-c libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(CURL REQUIRED libcurl)
pkg_check_modules(JSON-C REQUIRED json-c)

# Add include directories
include_directories(${CURL_INCLUDE_DIRS} ${JSON-C_INCLUDE_DIRS} )

# Print found libraries (optional)
message(STATUS "Found CURL: ${CURL_LIBRARIES}")
message(STATUS "Found JSON-C: ${JSON-C_LIBRARIES}")

add_library(http_json_obj OBJECT
            http_client.c
            json_parser.c)

target_include_directories(http_json_obj PRIVATE ${CURL_INCLUDE_DIRS} ${JSON-C_INCLUDE_DIRS})
target_compile_options(http_json_obj PRIVATE -fPIC -fvisibility=hidden)
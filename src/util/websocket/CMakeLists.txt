# WebSocket Client Library

# Find required libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBWEBSOCKETS REQUIRED libwebsockets)
pkg_check_modules(JSON-C REQUIRED json-c)

# Print found libraries (optional)
message(STATUS "Found LIBWEBSOCKETS: ${LIBWEBSOCKETS_LIBRARIES}")
message(STATUS "Found JSON-C: ${JSON-C_LIBRARIES}")

# Add include directories
include_directories(
  ${LIBWEBSOCKETS_INCLUDE_DIRS}
  ${JSON-C_INCLUDE_DIRS}
)

# Create the WebSocket client library
add_library(websocket_client_obj OBJECT
            websocket_client.c)

target_include_directories(websocket_client_obj PRIVATE 
                          ${LIBWEBSOCKETS_INCLUDE_DIRS} 
                          ${JSON-C_INCLUDE_DIRS})
                          
target_compile_options(websocket_client_obj PRIVATE -fPIC -fvisibility=hidden)

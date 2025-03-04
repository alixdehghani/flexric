# HTTP JSON Example

# Include directories
include_directories(
  ${CMAKE_SOURCE_DIR}/src/util/http_json
  ${CURL_INCLUDE_DIRS}
  ${JSON-C_INCLUDE_DIRS}
)

# Create the example executable
add_executable(http_json_example 
               http_json_example.c)

# Link the required libraries
target_link_libraries(http_json_example
                      ${CURL_LIBRARIES}
                      ${JSON-C_LIBRARIES}
                      $<TARGET_OBJECTS:http_json_obj>)

# Installation option
install(TARGETS http_json_example DESTINATION ${CMAKE_INSTALL_BINDIR})

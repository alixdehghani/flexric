  # Include directories
  include_directories(
    ${CMAKE_SOURCE_DIR}/src/util/http_json
    ${CURL_INCLUDE_DIRS}
    ${JSON-C_INCLUDE_DIRS}
  )

  target_link_libraries(
                      ${CURL_LIBRARIES}
                      ${JSON-C_LIBRARIES}
                      $<TARGET_OBJECTS:http_json_obj>
                      )
install(TARGETS http_json_example DESTINATION ${CMAKE_INSTALL_BINDIR})

add_subdirectory(agent)
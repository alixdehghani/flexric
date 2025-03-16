set(SM_ENCODING_ENB_CONF "PLAIN" CACHE STRING "The ENB_CONF SM encoding to use")
set_property(CACHE SM_ENCODING_ENB_CONF PROPERTY STRINGS "PLAIN" "ASN" "FLATBUFFERS")
message(STATUS "Selected ENB_CONF SM_ENCODING: ${SM_ENCODING_ENB_CONF}")


if(SM_ENCODING_ENB_CONF  STREQUAL "PLAIN")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR} )
  add_executable(test_enb_conf_sm
                      main.c 
                      ../../rnd/fill_rnd_data_enb_conf.c
                      ../../../src/util/time_now_us.c
              )
elseif(SM_ENCODING_ENB_CONF STREQUAL "ASN")
  message(FATAL_ERROR "Not implemented ASN encoding")

elseif(SM_ENCODING_ENB_CONF STREQUAL "FLATBUFFERS")
  message(FATAL_ERROR "Not implemented ASN encoding")

endif()

target_compile_definitions(test_enb_conf_sm PUBLIC ${SM_ENCODING_ENB_CONF})
target_link_libraries(test_enb_conf_sm PUBLIC enb_conf_sm_static -pthread)

enable_testing()
add_test(Unit_test_ENB_CONF test_enb_conf_sm)

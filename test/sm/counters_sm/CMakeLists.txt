set(SM_ENCODING_COUNTERS "PLAIN" CACHE STRING "The COUNTERS SM encoding to use")
set_property(CACHE SM_ENCODING_COUNTERS PROPERTY STRINGS "PLAIN" "ASN" "FLATBUFFERS")
message(STATUS "Selected COUNTERS SM_ENCODING: ${SM_ENCODING_COUNTERS}")


if(SM_ENCODING_COUNTERS  STREQUAL "PLAIN")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR} )
  add_executable(test_counters_sm
                      main.c 
                      ../../rnd/fill_rnd_data_counters.c
                      ../../../src/util/time_now_us.c
              )
elseif(SM_ENCODING_COUNTERS STREQUAL "ASN")
  message(FATAL_ERROR "Not implemented ASN encoding")

elseif(SM_ENCODING_COUNTERS STREQUAL "FLATBUFFERS")
  message(FATAL_ERROR "Not implemented ASN encoding")

endif()

target_compile_definitions(test_counters_sm PUBLIC ${SM_ENCODING_COUNTERS})
target_link_libraries(test_counters_sm PUBLIC counters_sm_static -pthread)

enable_testing()
add_test(Unit_test_COUNTERS test_counters_sm)

set(SM_ENCODING_RR "PLAIN" CACHE STRING "The RR SM encoding to use")
set_property(CACHE SM_ENCODING_RR PROPERTY STRINGS "PLAIN" "ASN" "FLATBUFFERS")
message(STATUS "Selected RR SM_ENCODING: ${SM_ENCODING_RR}")


if(SM_ENCODING_RR  STREQUAL "PLAIN")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR} )
  add_executable(test_rr_sm
                      main.c 
                      ../../rnd/fill_rnd_data_rr.c
                      ../../../src/util/time_now_us.c
              )
elseif(SM_ENCODING_RR STREQUAL "ASN")
  message(FATAL_ERROR "Not implemented ASN encoding")

elseif(SM_ENCODING_RR STREQUAL "FLATBUFFERS")
  message(FATAL_ERROR "Not implemented ASN encoding")

endif()

target_compile_definitions(test_rr_sm PUBLIC ${SM_ENCODING_RR})
target_link_libraries(test_rr_sm PUBLIC rr_sm_static -pthread)

enable_testing()
add_test(Unit_test_RR test_rr_sm)

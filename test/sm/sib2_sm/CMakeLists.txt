set(SM_ENCODING_SIB2 "PLAIN" CACHE STRING "The SIB2 SM encoding to use")
set_property(CACHE SM_ENCODING_SIB2 PROPERTY STRINGS "PLAIN" "ASN" "FLATBUFFERS")
message(STATUS "Selected SIB2 SM_ENCODING: ${SM_ENCODING_SIB2}")


if(SM_ENCODING_SIB2  STREQUAL "PLAIN")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR} )
  add_executable(test_sib2_sm
                      main.c 
                      ../../rnd/fill_rnd_data_sib2.c
                      ../../../src/util/time_now_us.c
              )
elseif(SM_ENCODING_SIB2 STREQUAL "ASN")
  message(FATAL_ERROR "Not implemented ASN encoding")

elseif(SM_ENCODING_SIB2 STREQUAL "FLATBUFFERS")
  message(FATAL_ERROR "Not implemented ASN encoding")

endif()

target_compile_definitions(test_sib2_sm PUBLIC ${SM_ENCODING_SIB2})
target_link_libraries(test_sib2_sm PUBLIC sib2_sm_static -pthread)

enable_testing()
add_test(Unit_test_SIB2 test_sib2_sm)

set(SM_ENCODING_SIB1 "PLAIN" CACHE STRING "The SIB1 SM encoding to use")
set_property(CACHE SM_ENCODING_SIB1 PROPERTY STRINGS "PLAIN" "ASN" "FLATBUFFERS")
message(STATUS "Selected SIB1 SM_ENCODING: ${SM_ENCODING_SIB1}")


if(SM_ENCODING_SIB1  STREQUAL "PLAIN")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR} )
  add_executable(test_sib1_sm
                      main.c 
                      ../../rnd/fill_rnd_data_sib1.c
                      ../../../src/util/time_now_us.c
              )
elseif(SM_ENCODING_SIB1 STREQUAL "ASN")
  message(FATAL_ERROR "Not implemented ASN encoding")

elseif(SM_ENCODING_SIB1 STREQUAL "FLATBUFFERS")
  message(FATAL_ERROR "Not implemented ASN encoding")

endif()

target_compile_definitions(test_sib1_sm PUBLIC ${SM_ENCODING_SIB1})
target_link_libraries(test_sib1_sm PUBLIC sib1_sm_static -pthread)

enable_testing()
add_test(Unit_test_SIB1 test_sib1_sm)

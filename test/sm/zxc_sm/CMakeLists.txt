set(SM_ENCODING_ZXC "PLAIN" CACHE STRING "The ZXC SM encoding to use")
set_property(CACHE SM_ENCODING_ZXC PROPERTY STRINGS "PLAIN" "ASN" "FLATBUFFERS")
message(STATUS "Selected ZXC SM_ENCODING: ${SM_ENCODING_ZXC}")


if(SM_ENCODING_ZXC  STREQUAL "PLAIN")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR} )
  add_executable(test_zxc_sm
                      main.c 
                      ../../rnd/fill_rnd_data_zxc.c
                      ../../../src/util/time_now_us.c
              )
elseif(SM_ENCODING_ZXC STREQUAL "ASN")
  message(FATAL_ERROR "Not implemented ASN encoding")

elseif(SM_ENCODING_ZXC STREQUAL "FLATBUFFERS")
  message(FATAL_ERROR "Not implemented ASN encoding")

endif()

target_compile_definitions(test_zxc_sm PUBLIC ${SM_ENCODING_ZXC})
target_link_libraries(test_zxc_sm PUBLIC zxc_sm_static -pthread)

enable_testing()
add_test(Unit_test_ZXC test_zxc_sm)

set(SM_ENCODING_UETRACE "PLAIN" CACHE STRING "The UETRACE SM encoding to use")
set_property(CACHE SM_ENCODING_UETRACE PROPERTY STRINGS "PLAIN" "ASN" "FLATBUFFERS")
message(STATUS "Selected UETRACE SM_ENCODING: ${SM_ENCODING_UETRACE}")


if(SM_ENCODING_UETRACE  STREQUAL "PLAIN")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR} )
  add_executable(test_uetrace_sm
                      main.c 
                      ../../rnd/fill_rnd_data_uetrace.c
                      ../../../src/util/time_now_us.c
              )
elseif(SM_ENCODING_UETRACE STREQUAL "ASN")
  message(FATAL_ERROR "Not implemented ASN encoding")

elseif(SM_ENCODING_UETRACE STREQUAL "FLATBUFFERS")
  message(FATAL_ERROR "Not implemented ASN encoding")

endif()

target_compile_definitions(test_uetrace_sm PUBLIC ${SM_ENCODING_UETRACE})
target_link_libraries(test_uetrace_sm PUBLIC uetrace_sm_static -pthread)

enable_testing()
add_test(Unit_test_UETRACE test_uetrace_sm)

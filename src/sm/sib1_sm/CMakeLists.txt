cmake_minimum_required(VERSION 3.15) # setting this is required
project(sib1_sm)            # this sets the project name

set(SM_ENCODING_SIB1_SRC
                      ../sm_proc_data.c 
                      sib1_sm_agent.c 
                      sib1_sm_ric.c 
                     ../../util/byte_array.c 
                     ../../util/alg_ds/alg/defer.c 
                     ../../util/alg_ds/alg/eq_float.c 
                     ../../util/alg_ds/ds/seq_container/seq_arr.c 
                     ../../util/alg_ds/ds/seq_container/seq_ring.c 
                     ../../util/alg_ds/ds/assoc_container/assoc_rb_tree.c
                     ../../util/alg_ds/ds/assoc_container/bimap.c
                      ie/sib1_data_ie.c 
                      )


if(SM_ENCODING_SIB1 STREQUAL "PLAIN")
  set(SM_ENCODING_SIB1_SRC_PLAIN 
    # This dependency sucks!
    $<TARGET_OBJECTS:e2ap_ran_func_obj>
    ${SM_ENCODING_SIB1_SRC}
    enc/sib1_enc_plain.c 
    dec/sib1_dec_plain.c 
    )

  # Shared
  add_library(sib1_sm SHARED ${SM_ENCODING_SIB1_SRC_PLAIN} )
  target_compile_options(sib1_sm PRIVATE -fPIC -fvisibility=hidden)

  # Static
  add_library(sib1_sm_static STATIC ${SM_ENCODING_SIB1_SRC_PLAIN}) 

elseif(SM_ENCODING_SIB1 STREQUAL "ASN" )
  message(FATAL_ERROR "SIB1 SM ASN not implemented")
elseif(SM_ENCODING_SIB1 STREQUAL "FLATBUFFERS" )
  message(FATAL_ERROR "SIB1 SM FB not implemented")
else()
  message(FATAL_ERROR "Unknown SM encoding type ")
endif()

target_compile_definitions(sib1_sm PUBLIC ${SM_ENCODING_SIB1} ${E2AP_VERSION}  ${KPM_VERSION}  )
target_compile_definitions(sib1_sm_static PUBLIC ${SM_ENCODING_SIB1} ${E2AP_VERSION}  ${KPM_VERSION}  )


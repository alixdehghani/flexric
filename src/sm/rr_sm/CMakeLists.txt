cmake_minimum_required(VERSION 3.15) # setting this is required
project(rr_sm)            # this sets the project name

set(SM_ENCODING_RR_SRC
                      ../sm_proc_data.c 
                      rr_sm_agent.c 
                      rr_sm_ric.c 
                     ../../util/byte_array.c 
                     ../../util/alg_ds/alg/defer.c 
                     ../../util/alg_ds/alg/eq_float.c 
                     ../../util/alg_ds/ds/seq_container/seq_arr.c 
                     ../../util/alg_ds/ds/seq_container/seq_ring.c 
                     ../../util/alg_ds/ds/assoc_container/assoc_rb_tree.c
                     ../../util/alg_ds/ds/assoc_container/bimap.c
                      ie/rr_data_ie.c 
                      )


if(SM_ENCODING_RR STREQUAL "PLAIN")
  set(SM_ENCODING_RR_SRC_PLAIN 
    # This dependency sucks!
    $<TARGET_OBJECTS:e2ap_ran_func_obj>
    ${SM_ENCODING_RR_SRC}
    enc/rr_enc_plain.c 
    dec/rr_dec_plain.c 
    )

  # Shared
  add_library(rr_sm SHARED ${SM_ENCODING_RR_SRC_PLAIN} )
  target_compile_options(rr_sm PRIVATE -fPIC -fvisibility=hidden)

  # Static
  add_library(rr_sm_static STATIC ${SM_ENCODING_RR_SRC_PLAIN}) 

elseif(SM_ENCODING_RR STREQUAL "ASN" )
  message(FATAL_ERROR "RR SM ASN not implemented")
elseif(SM_ENCODING_RR STREQUAL "FLATBUFFERS" )
  message(FATAL_ERROR "RR SM FB not implemented")
else()
  message(FATAL_ERROR "Unknown SM encoding type ")
endif()

target_compile_definitions(rr_sm PUBLIC ${SM_ENCODING_RR} ${E2AP_VERSION}  ${KPM_VERSION}  )
target_compile_definitions(rr_sm_static PUBLIC ${SM_ENCODING_RR} ${E2AP_VERSION}  ${KPM_VERSION}  )


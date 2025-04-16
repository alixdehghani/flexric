add_executable(xapp_enb_ctrl
  enb_ctrl.c
  ../../../../src/util/alg_ds/alg/defer.c
  )

add_executable(xapp_sib1_ctrl
  sib1_ctrl.c
  ../../../../src/util/alg_ds/alg/defer.c
  )

  add_executable(xapp_rr_ctrl
  rr_ctrl.c
  ../../../../src/util/alg_ds/alg/defer.c
  )

  add_executable(xapp_ind_ctrl
  ind_ctrl.c
  ../../../../src/util/alg_ds/alg/defer.c
  )

 target_link_libraries(xapp_sib1_ctrl
 						PUBLIC
 						e42_xapp
 						-pthread
 						-lsctp
 						-ldl
 						)

 target_link_libraries(xapp_rr_ctrl
 						PUBLIC
 						e42_xapp
 						-pthread
 						-lsctp
 						-ldl
 						)
					
 target_link_libraries(xapp_enb_ctrl
 						PUBLIC
 						e42_xapp
 						-pthread
 						-lsctp
 						-ldl
 						)

target_link_libraries(xapp_ind_ctrl
 						PUBLIC
 						e42_xapp
 						-pthread
 						-lsctp
 						-ldl
 						)




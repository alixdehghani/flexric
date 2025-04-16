add_executable(xapp_kpm_moni 
		xapp_kpm_moni.c
                ../../../../src/util/alg_ds/alg/defer.c
              )

 target_link_libraries(xapp_kpm_moni
                      PUBLIC
                      e42_xapp
                      -pthread
                      -lsctp
                      -ldl
                      )

add_executable(xapp_get_enb_conf 
		xapp_get_enb_conf.c
                ../../../../src/util/alg_ds/alg/defer.c
              )

 target_link_libraries(xapp_get_enb_conf
                      PUBLIC
                      e42_xapp
                      -pthread
                      -lsctp
                      -ldl
                      )

add_executable(xapp_get_rr 
		xapp_get_rr.c
                ../../../../src/util/alg_ds/alg/defer.c
              )

 target_link_libraries(xapp_get_rr
                      PUBLIC
                      e42_xapp
                      -pthread
                      -lsctp
                      -ldl
                      )


add_executable(xapp_get_counters 
		xapp_get_counters.c
                ../../../../src/util/alg_ds/alg/defer.c
              )

 target_link_libraries(xapp_get_counters
                      PUBLIC
                      e42_xapp
                      -pthread
                      -lsctp
                      -ldl
                      )

add_executable(xapp_get_sib2 
    xapp_get_sib2.c
                ../../../../src/util/alg_ds/alg/defer.c
              )
                  
  target_link_libraries(xapp_get_sib2
                       PUBLIC
                       e42_xapp
                       -pthread
                       -lsctp
                       -ldl
                       )

add_executable(xapp_get_uetrace 
    xapp_get_uetrace.c
                ../../../../src/util/alg_ds/alg/defer.c
              )
                  
  target_link_libraries(xapp_get_uetrace
                       PUBLIC
                       e42_xapp
                       -pthread
                       -lsctp
                       -ldl
                       )

add_executable(xapp_get_sib1 
		xapp_get_sib1.c
                ../../../../src/util/alg_ds/alg/defer.c
              )

 target_link_libraries(xapp_get_sib1
                      PUBLIC
                      e42_xapp
                      -pthread
                      -lsctp
                      -ldl
                      )


add_executable(xapp_rc_moni 
               xapp_rc_moni.c
               ../../../../src/util/alg_ds/alg/defer.c
              )
                  
target_link_libraries(xapp_rc_moni
                     PUBLIC
                     e42_xapp
                     -pthread
                     -lsctp
                     -ldl
                     )

/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

 #include "../../../../src/xApp/e42_xapp_api.h"
 #include "../../../../src/util/alg_ds/alg/defer.h"
 #include "../../../../src/util/time_now_us.h"
 
 #include <pthread.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <signal.h>
 #include <time.h>
 #include <unistd.h>
 
 // static uint64_t cnt_mac;
 
 // static void sm_cb_mac(sm_ag_if_rd_t const *rd)
 // {
 //   assert(rd != NULL);
 //   assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
 //   assert(rd->ind.type == MAC_STATS_V0);
 
 //   int64_t now = time_now_us();
 //   if (cnt_mac % 1024 == 0)
 //     printf("MAC ind_msg latency = %ld μs\n", now - rd->ind.mac.msg.tstamp);
 //   cnt_mac++;
 // }
 
 // static uint64_t cnt_rlc;
 
 // static uint64_t cnt_zxc;
 static uint64_t cnt_sib2;
 // static uint64_t cnt_enb_conf;
  
 
 // SIB2 !
 static void sm_cb_sib2(sm_ag_if_rd_t const *rd)
 {
   assert(rd != NULL);
   assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
 
   assert(rd->ind.type == SIB2_STATS_V0);
   for (int i = 0; i < rd->ind.sib2.msg.len; i++)
   {
     sib2_stats_t* rb = &rd->ind.sib2.msg.rb[i];
     printf("default_paging_cycle: %d\n", rb->default_paging_cycle);
     printf("delta_pucch_shift: %d\n", rb->delta_pucch_shift);
     printf("t311: %d\n", rb->t311);
     printf("delta_preamble_msg3: %d\n", rb->delta_preamble_msg3);
     printf("n_cs_an: %d\n", rb->n_cs_an);
    //  printf("system_info_value_tag: %d\n", rb->system_info_value_tag);
    //  printf("si_mapping_info: %d\n", rb->sched_info_si_mapping_info_1);
    //  printf("si_periodicity: %d\n", rb->sched_info_si_periodicity_1);
   }
   
   if(!rd->ind.sib2.msg.len == 0)
   {
     
   }
 
   int64_t now = time_now_us();
 
   if (cnt_sib2 % 1024 == 0){
     printf("SIB2 ind_msg latency = %ld μs\n", now - rd->ind.sib2.msg.tstamp);
     cnt_sib2++;
     return;
   }
 }
 
 
 int main(int argc, char *argv[])
 {
   fr_args_t args = init_fr_args(argc, argv);
 
   // Init the xApp
   init_xapp_api(&args);
   sleep(1);
 
   e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
   defer({ free_e2_node_arr_xapp(&nodes); });
 
   assert(nodes.len > 0);
 
   printf("Connected E2 nodes = %d\n", nodes.len);
 
   // SIB2 indication
   const char *i_2 = "1_ms";
   sm_ans_xapp_t *sib2_handle = NULL;
   
   if (nodes.len > 0)
   {
     sib2_handle = calloc(nodes.len, sizeof(sm_ans_xapp_t));
     assert(sib2_handle != NULL);
   }
 
   for (int i = 0; i < nodes.len; i++)
   {
     e2_node_connected_xapp_t *n = &nodes.n[i];
     for (size_t j = 0; j < n->len_rf; j++)
       printf("Registered node %d ran func id = %d \n ", i, n->rf[j].id);
 
     if (n->id.type == ngran_gNB || n->id.type == ngran_eNB)
     {
       // MAC Control is not yet implemented in OAI RAN
       
 
       sib2_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 154, (void *)i_2, sm_cb_sib2);
       assert(sib2_handle[i].success == true);
 
       // enb_conf_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 150, (void *)i_1, sm_cb_enb_conf);
       // assert(enb_conf_handle[i].success == true);
     }
     else if (n->id.type == ngran_gNB_CU || n->id.type == ngran_gNB_CUUP)
     {
       // pdcp_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 144, (void *)i_2, sm_cb_pdcp);
       // assert(pdcp_handle[i].success == true);
 
       // gtp_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 148, (void *)i_3, sm_cb_gtp);
       // assert(gtp_handle[i].success == true);
     }
     else if (n->id.type == ngran_gNB_DU)
     {
       // mac_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 142, (void *)i_0, sm_cb_mac);
       // assert(mac_handle[i].success == true);
 
       // rlc_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 143, (void *)i_1, sm_cb_rlc);
       // assert(rlc_handle[i].success == true);
 
     }
   }
 
   sleep(5);
 
   for (int i = 0; i < nodes.len; ++i)
   {
     
     if (sib2_handle[i].u.handle != 0)
       rm_report_sm_xapp_api(sib2_handle[i].u.handle);
     
   }
 
   if (nodes.len > 0)
   {
     
     free(sib2_handle);
     
   }
 
   // Stop the xApp
   while (try_stop_xapp_api() == false)
     usleep(1000);
 
   printf("Test xApp run SUCCESSFULLY\n");
 }
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
 static uint64_t cnt_sib1;
 // static uint64_t cnt_enb_conf;
  
 
 // SIB1 !
 static void sm_cb_sib1(sm_ag_if_rd_t const *rd)
 {
   assert(rd != NULL);
   assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
 
   assert(rd->ind.type == SIB1_STATS_V0);
   for (int i = 0; i < rd->ind.counters.msg.len; i++)
   {
     sib1_stats_t* rb = &rd->ind.sib1.msg.rb[i];
     printf("cell_barred: %s\n", rb->cell_barred);
     printf("intra_freq_reselection: %s\n", rb->intra_freq_reselection);
     printf("p_max: %d\n", rb->p_max);
     printf("q_rx_lev_min: %d\n", rb->q_rx_lev_min);
     printf("si_window_length: %d\n", rb->si_window_length);
     printf("system_info_value_tag: %d\n", rb->system_info_value_tag);
     printf("si_mapping_info: %s\n", rb->sched_info_si_mapping_info_1);
     printf("si_periodicity: %d\n", rb->sched_info_si_periodicity_1);
   }
   
   if(!rd->ind.sib1.msg.len == 0)
   {
     
   }
 
   int64_t now = time_now_us();
 
   if (cnt_sib1 % 1024 == 0)
     printf("SIB1 ind_msg latency = %ld μs\n", now - rd->ind.sib1.msg.tstamp);
    
     cnt_sib1++;
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
 
   // SIB1 indication
   const char *i_2 = "1_ms";
   sm_ans_xapp_t *sib1_handle = NULL;
   
   if (nodes.len > 0)
   {
     sib1_handle = calloc(nodes.len, sizeof(sm_ans_xapp_t));
     assert(sib1_handle != NULL);
   }
 
   for (int i = 0; i < nodes.len; i++)
   {
     e2_node_connected_xapp_t *n = &nodes.n[i];
     for (size_t j = 0; j < n->len_rf; j++)
       printf("Registered node %d ran func id = %d \n ", i, n->rf[j].id);
 
     if (n->id.type == ngran_gNB || n->id.type == ngran_eNB)
     {
       // MAC Control is not yet implemented in OAI RAN
       
 
       sib1_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 153, (void *)i_2, sm_cb_sib1);
       assert(sib1_handle[i].success == true);
 
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
     
     if (sib1_handle[i].u.handle != 0)
       rm_report_sm_xapp_api(sib1_handle[i].u.handle);
     
   }
 
   if (nodes.len > 0)
   {
     
     free(sib1_handle);
     
   }
 
   // Stop the xApp
   while (try_stop_xapp_api() == false)
     usleep(1000);
 
   printf("Test xApp run SUCCESSFULLY\n");
 }
 
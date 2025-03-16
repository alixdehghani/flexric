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

// #include "fill_rnd_data_zxc.h"
// #include "../../src/util/time_now_us.h"

// #include <assert.h>
// #include <stdlib.h>
// #include <time.h>
// #include <stdio.h>
// #include <string.h>

// void fill_zxc_ind_data(zxc_ind_data_t* ind)
// {
  
  
//   assert(ind != NULL);

//   srand(time(0));

//   int const mod = 1024;

//   zxc_ind_msg_t* ind_msg = &ind->msg;

//   ind_msg->tstamp = time_now_us();

//   ind_msg->len = 1;
//   if(ind_msg->len > 0 ){
//     ind_msg->rb = calloc(ind_msg->len, sizeof(zxc_radio_bearer_stats_t) );
//     assert(ind_msg->rb != NULL);
//   }

//   ind_msg->pci = 123;
//   ind_msg->len_str = 12; // Length of "Hello World" + 1 for null terminator
//   ind_msg->str = calloc(ind_msg->len_str, sizeof(char));
//   assert(ind_msg->str != NULL);
//   snprintf(ind_msg->str, ind_msg->len_str, "Hello World");

//   // for(uint32_t i = 0; i < ind_msg->len; ++i){
//     zxc_radio_bearer_stats_t* rb = &ind_msg->rb[0];

//     // strncpy(rb->cell_id, "wel", 4);  // Copy "wel" (3 chars + \0), fits in 4 bytes
// // OR
// // memcpy(rb->test_char, "wel", 4); // Same effect, copies exactly 4 bytes
//     sprintf(rb->bbu_addr , "fre");
//     sprintf(rb->cell_id, "fre");
//     sprintf(rb->enb_id , "fre");
//     sprintf(rb->geran_ci , "fre");
//     sprintf(rb->geran_lac , "fre");
//     sprintf(rb->gtp_bind_addr , "fre");
//     sprintf(rb->mcc , "fre");
//     sprintf(rb->mme_addr , "fre");
//     sprintf(rb->mnc , "fre");
//     sprintf(rb->n_prb , "fre");
//     sprintf(rb->name , "fre");
//     sprintf(rb->nof_ports , "fre");
//     sprintf(rb->p_a , "fre");
//     sprintf(rb->phy_cell_id , "fre");
//     sprintf(rb->rru_addr , "fre");
//     sprintf(rb->s1c_bind_addr , "fre");
//     sprintf(rb->sec1_pci , "fre");
//     sprintf(rb->sec1_x2_bind_addr , "fre");
//     sprintf(rb->sec2_pci , "fre");
//     sprintf(rb->sec2_x2_bind_addr , "fre");
//     sprintf(rb->sec3_x2_bind_addr , "fre");
//     sprintf(rb->sector_id , "fre");
//     sprintf(rb->tac , "fre");
//     sprintf(rb->tm , "fre");
//     snprintf(rb->ws_port , sizeof(rb->ws_port),"fre");

//   }
// // }


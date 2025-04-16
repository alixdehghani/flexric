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

#ifndef SIB2_DATA_INFORMATION_ELEMENTS_H
#define SIB2_DATA_INFORMATION_ELEMENTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 9 Information Elements (IE) , RIC Event Trigger Definition, RIC Action Definition, RIC Indication Header, RIC Indication Message, RIC Call Process ID, RIC Control Header, RIC Control Message, RIC Control Outcome and RAN Function Definition defined by ORAN-WG3.E2SM-v01.00.00 at Section 5
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

typedef struct {
  uint32_t ms;
  uint32_t init_ms;
  uint32_t interval_ms;
} sib2_event_trigger_t;

void free_sib2_event_trigger(sib2_event_trigger_t* src); 

sib2_event_trigger_t cp_sib2_event_trigger( sib2_event_trigger_t* src);

bool eq_sib2_event_trigger(sib2_event_trigger_t* m0, sib2_event_trigger_t* m1);



//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;  
} sib2_action_def_t;

void free_sib2_action_def(sib2_action_def_t* src); 

sib2_action_def_t cp_sib2_action_def(sib2_action_def_t* src);

bool eq_sib2_action_def(sib2_event_trigger_t* m0,  sib2_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} sib2_ind_hdr_t;

void free_sib2_ind_hdr(sib2_ind_hdr_t* src); 

sib2_ind_hdr_t cp_sib2_ind_hdr(sib2_ind_hdr_t const* src);

bool eq_sib2_ind_hdr(sib2_ind_hdr_t* m0, sib2_ind_hdr_t* m1);


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct {
  
  int additional_spectrum_emission;
  int ul_bw_present;
  int ul_carrier_freq_present;
  int modification_period_coeff;
  int default_paging_cycle;
  char nB[5];
  int p_b;
  int rs_power;
  int high_speed_flag;
  int prach_config_index;
  int prach_freq_offset;
  int zero_correlation_zone_config;
  int root_sequence_index;
  int delta_pucch_shift;
  int n1_pucch_an;
  int n_cs_an;
  int n_rb_cqi;
  int enable_64_qam;
  char hopping_mode[30];
  int n_sb;
  int pusch_hopping_offset;
  int cyclic_shift;
  int group_assignment_pusch;
  int group_hopping_enabled;
  int sequence_hopping_enabled;
  int mac_con_res_timer;
  int max_harq_msg3_tx;
  int num_ra_preambles;
  int preamble_init_rx_target_pwr;
  int preamble_trans_max;
  int pwr_ramping_step;
  int ra_resp_win_size;
  char ul_cp_length [15];
  double alpha;
  int format_1;
  int format_1b;
  int format_2;
  int format_2a;
  int format_2b;
  int delta_preamble_msg3;
  int p0_nominal_pucch;
  int p0_nominal_pusch;
  char time_alignment_timer [20];
  int n310;
  int n311;
  int t300;
  int t301;
  int t310;
  int t311;



} sib2_stats_t;

typedef struct {
  sib2_stats_t* rb; 
  uint32_t len;

  int64_t tstamp;
} sib2_ind_msg_t;

void free_sib2_ind_msg(sib2_ind_msg_t* src); 

sib2_ind_msg_t cp_sib2_ind_msg(sib2_ind_msg_t const* src);

bool eq_sib2_ind_msg(sib2_ind_msg_t* m0, sib2_ind_msg_t* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} sib2_call_proc_id_t;

void free_sib2_call_proc_id( sib2_call_proc_id_t* src); 

sib2_call_proc_id_t cp_sib2_call_proc_id( sib2_call_proc_id_t* src);

bool eq_sib2_call_proc_id(sib2_call_proc_id_t* m0, sib2_call_proc_id_t* m1);



//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////


typedef struct {
  uint32_t dummy;
} sib2_ctrl_hdr_t;

void free_sib2_ctrl_hdr( sib2_ctrl_hdr_t* src); 

sib2_ctrl_hdr_t cp_sib2_ctrl_hdr(sib2_ctrl_hdr_t* src);

bool eq_sib2_ctrl_hdr(sib2_ctrl_hdr_t* m0, sib2_ctrl_hdr_t* m1);



//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


typedef struct {
  uint32_t action;
} sib2_ctrl_msg_t;

void free_sib2_ctrl_msg( sib2_ctrl_msg_t* src); 

sib2_ctrl_msg_t cp_sib2_ctrl_msg(sib2_ctrl_msg_t* src);

bool eq_sib2_ctrl_msg(sib2_ctrl_msg_t* m0, sib2_ctrl_msg_t* m1);



//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  SIB2_CTRL_OUT_OK,

  SIB2_CTRL_OUT_END
} sib2_ctrl_out_e;


typedef struct {
  sib2_ctrl_out_e ans;
} sib2_ctrl_out_t;

void free_sib2_ctrl_out(sib2_ctrl_out_t* src); 

sib2_ctrl_out_t cp_sib2_ctrl_out(sib2_ctrl_out_t* src);

bool eq_sib2_ctrl_out(sib2_ctrl_out_t* m0, sib2_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint8_t* buf;
  size_t len;
} sib2_func_def_t;

void free_sib2_func_def( sib2_func_def_t* src); 

sib2_func_def_t cp_sib2_func_def(sib2_func_def_t const* src);

bool eq_sib2_func_def(sib2_func_def_t const* m0, sib2_func_def_t const* m1);

/////////////////////////////////////////////////
//////////////////////////////////////////////////
/////////////////////////////////////////////////


/*
 * O-RAN defined 5 Procedures: RIC Subscription, RIC Indication, RIC Control, E2 Setup and RIC Service Update 
 * */


///////////////
/// RIC Subscription
///////////////

typedef struct{
  sib2_event_trigger_t et; 
  sib2_action_def_t* ad;
} sib2_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  sib2_ind_hdr_t hdr;
  sib2_ind_msg_t msg;
  sib2_call_proc_id_t* proc_id;
} sib2_ind_data_t;

void free_sib2_ind_data(sib2_ind_data_t* ind);

sib2_ind_data_t cp_sib2_ind_data(sib2_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  sib2_ctrl_hdr_t hdr;
  sib2_ctrl_msg_t msg;
} sib2_ctrl_req_data_t;

typedef struct{
  sib2_ctrl_out_t* out;
} sib2_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  sib2_func_def_t func_def;
} sib2_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  sib2_func_def_t func_def;
} sib2_ric_service_update_t;


#ifdef __cplusplus
}
#endif

#endif


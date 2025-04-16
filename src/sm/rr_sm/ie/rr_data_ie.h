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

#ifndef RR_DATA_INFORMATION_ELEMENTS_H
#define RR_DATA_INFORMATION_ELEMENTS_H

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
} rr_event_trigger_t;

void free_rr_event_trigger(rr_event_trigger_t* src); 

rr_event_trigger_t cp_rr_event_trigger( rr_event_trigger_t* src);

bool eq_rr_event_trigger(rr_event_trigger_t* m0, rr_event_trigger_t* m1);



//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;  
} rr_action_def_t;

void free_rr_action_def(rr_action_def_t* src); 

rr_action_def_t cp_rr_action_def(rr_action_def_t* src);

bool eq_rr_action_def(rr_event_trigger_t* m0,  rr_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} rr_ind_hdr_t;

void free_rr_ind_hdr(rr_ind_hdr_t* src); 

rr_ind_hdr_t cp_rr_ind_hdr(rr_ind_hdr_t const* src);

bool eq_rr_ind_hdr(rr_ind_hdr_t* m0, rr_ind_hdr_t* m1);


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct {
  
  char dl_pathloss_change[10];
  int periodic_phr_timer;
  int prohibit_phr_timer;
  int time_alignment_timer;
  int max_harq_tx;
  int periodic_bsr_timer;
  int retx_bsr_timer;
  char mode[15];
  int cqi_report_cnfg_nof_prb;
  int cqi_report_cnfg_period;
  int simultaneousAckCQI;
  char cqi_report_cnfg_subframe[155];
  char duration[10];
  char resources[5];
  int beta_offset_ack_idx;
  int beta_offset_cqi_idx;
  int beta_offset_ri_idx;
  int dsr_trans_max;
  int sched_request_cnfg_nof_prb;
  int sched_request_cnfg_period;
  char sched_request_cnfg_subframe[155];

} rr_stats_t;

typedef struct {
  rr_stats_t* rb; 
  uint32_t len;

  int64_t tstamp;
} rr_ind_msg_t;

void free_rr_ind_msg(rr_ind_msg_t* src); 

rr_ind_msg_t cp_rr_ind_msg(rr_ind_msg_t const* src);

bool eq_rr_ind_msg(rr_ind_msg_t* m0, rr_ind_msg_t* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} rr_call_proc_id_t;

void free_rr_call_proc_id( rr_call_proc_id_t* src); 

rr_call_proc_id_t cp_rr_call_proc_id( rr_call_proc_id_t* src);

bool eq_rr_call_proc_id(rr_call_proc_id_t* m0, rr_call_proc_id_t* m1);



//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////


typedef struct {
  uint32_t dummy;
} rr_ctrl_hdr_t;

void free_rr_ctrl_hdr( rr_ctrl_hdr_t* src); 

rr_ctrl_hdr_t cp_rr_ctrl_hdr(rr_ctrl_hdr_t* src);

bool eq_rr_ctrl_hdr(rr_ctrl_hdr_t* m0, rr_ctrl_hdr_t* m1);



//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


typedef struct {
  uint32_t action;
  uint32_t len;
  rr_stats_t* rr_rb;
} rr_ctrl_msg_t;

void free_rr_ctrl_msg( rr_ctrl_msg_t* src); 

rr_ctrl_msg_t cp_rr_ctrl_msg(rr_ctrl_msg_t* src);

bool eq_rr_ctrl_msg(rr_ctrl_msg_t* m0, rr_ctrl_msg_t* m1);



//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  RR_CTRL_OUT_OK,

  RR_CTRL_OUT_END
} rr_ctrl_out_e;


typedef struct {
  rr_ctrl_out_e ans;
} rr_ctrl_out_t;

void free_rr_ctrl_out(rr_ctrl_out_t* src); 

rr_ctrl_out_t cp_rr_ctrl_out(rr_ctrl_out_t* src);

bool eq_rr_ctrl_out(rr_ctrl_out_t* m0, rr_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint8_t* buf;
  size_t len;
} rr_func_def_t;

void free_rr_func_def( rr_func_def_t* src); 

rr_func_def_t cp_rr_func_def(rr_func_def_t const* src);

bool eq_rr_func_def(rr_func_def_t const* m0, rr_func_def_t const* m1);

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
  rr_event_trigger_t et; 
  rr_action_def_t* ad;
} rr_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  rr_ind_hdr_t hdr;
  rr_ind_msg_t msg;
  rr_call_proc_id_t* proc_id;
} rr_ind_data_t;

void free_rr_ind_data(rr_ind_data_t* ind);

rr_ind_data_t cp_rr_ind_data(rr_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  rr_ctrl_hdr_t hdr;
  rr_ctrl_msg_t msg;
} rr_ctrl_req_data_t;

typedef struct{
  rr_ctrl_out_t* out;
} rr_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  rr_func_def_t func_def;
} rr_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  rr_func_def_t func_def;
} rr_ric_service_update_t;


#ifdef __cplusplus
}
#endif

#endif


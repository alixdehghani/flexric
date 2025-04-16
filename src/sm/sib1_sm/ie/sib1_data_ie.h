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

#ifndef SIB1_DATA_INFORMATION_ELEMENTS_H
#define SIB1_DATA_INFORMATION_ELEMENTS_H

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
} sib1_event_trigger_t;

void free_sib1_event_trigger(sib1_event_trigger_t* src); 

sib1_event_trigger_t cp_sib1_event_trigger( sib1_event_trigger_t* src);

bool eq_sib1_event_trigger(sib1_event_trigger_t* m0, sib1_event_trigger_t* m1);



//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;  
} sib1_action_def_t;

void free_sib1_action_def(sib1_action_def_t* src); 

sib1_action_def_t cp_sib1_action_def(sib1_action_def_t* src);

bool eq_sib1_action_def(sib1_event_trigger_t* m0,  sib1_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} sib1_ind_hdr_t;

void free_sib1_ind_hdr(sib1_ind_hdr_t* src); 

sib1_ind_hdr_t cp_sib1_ind_hdr(sib1_ind_hdr_t const* src);

bool eq_sib1_ind_hdr(sib1_ind_hdr_t* m0, sib1_ind_hdr_t* m1);


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct {

  char cell_barred [12];
  char intra_freq_reselection [12];
  int p_max;
  int q_rx_lev_min;
  int si_window_length;
  int system_info_value_tag;
  char sched_info_si_mapping_info_1 [20];
  int sched_info_si_periodicity_1;
  char sched_info_si_mapping_info_2 [20];
  int sched_info_si_periodicity_2;
  char sched_info_si_mapping_info_3 [20];
  int sched_info_si_periodicity_3;
  char sched_info_si_mapping_info_4 [20];
  int sched_info_si_periodicity_4;
  char sched_info_si_mapping_info_5 [20];
  int sched_info_si_periodicity_5;
  char sched_info_si_mapping_info_6 [20];
  int sched_info_si_periodicity_6;
  char sched_info_si_mapping_info_7 [20];
  int sched_info_si_periodicity_7;
  char sched_info_si_mapping_info_8 [20];
  int sched_info_si_periodicity_8;


} sib1_stats_t;

typedef struct {
  sib1_stats_t* rb; 
  uint32_t len;

  int64_t tstamp;
} sib1_ind_msg_t;

void free_sib1_ind_msg(sib1_ind_msg_t* src); 

sib1_ind_msg_t cp_sib1_ind_msg(sib1_ind_msg_t const* src);

bool eq_sib1_ind_msg(sib1_ind_msg_t* m0, sib1_ind_msg_t* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} sib1_call_proc_id_t;

void free_sib1_call_proc_id( sib1_call_proc_id_t* src); 

sib1_call_proc_id_t cp_sib1_call_proc_id( sib1_call_proc_id_t* src);

bool eq_sib1_call_proc_id(sib1_call_proc_id_t* m0, sib1_call_proc_id_t* m1);



//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////


typedef struct {
  uint32_t dummy;
} sib1_ctrl_hdr_t;

void free_sib1_ctrl_hdr( sib1_ctrl_hdr_t* src); 

sib1_ctrl_hdr_t cp_sib1_ctrl_hdr(sib1_ctrl_hdr_t* src);

bool eq_sib1_ctrl_hdr(sib1_ctrl_hdr_t* m0, sib1_ctrl_hdr_t* m1);



//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


typedef struct {
  uint32_t action;
  uint32_t len;
  sib1_stats_t* sib1_rb;
} sib1_ctrl_msg_t;

void free_sib1_ctrl_msg( sib1_ctrl_msg_t* src); 

sib1_ctrl_msg_t cp_sib1_ctrl_msg(sib1_ctrl_msg_t* src);

bool eq_sib1_ctrl_msg(sib1_ctrl_msg_t* m0, sib1_ctrl_msg_t* m1);



//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  SIB1_CTRL_OUT_OK,

  SIB1_CTRL_OUT_END
} sib1_ctrl_out_e;


typedef struct {
  sib1_ctrl_out_e ans;
} sib1_ctrl_out_t;

void free_sib1_ctrl_out(sib1_ctrl_out_t* src); 

sib1_ctrl_out_t cp_sib1_ctrl_out(sib1_ctrl_out_t* src);

bool eq_sib1_ctrl_out(sib1_ctrl_out_t* m0, sib1_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint8_t* buf;
  size_t len;
} sib1_func_def_t;

void free_sib1_func_def( sib1_func_def_t* src); 

sib1_func_def_t cp_sib1_func_def(sib1_func_def_t const* src);

bool eq_sib1_func_def(sib1_func_def_t const* m0, sib1_func_def_t const* m1);

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
  sib1_event_trigger_t et; 
  sib1_action_def_t* ad;
} sib1_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  sib1_ind_hdr_t hdr;
  sib1_ind_msg_t msg;
  sib1_call_proc_id_t* proc_id;
} sib1_ind_data_t;

void free_sib1_ind_data(sib1_ind_data_t* ind);

sib1_ind_data_t cp_sib1_ind_data(sib1_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  sib1_ctrl_hdr_t hdr;
  sib1_ctrl_msg_t msg;
} sib1_ctrl_req_data_t;

typedef struct{
  sib1_ctrl_out_t* out;
} sib1_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  sib1_func_def_t func_def;
} sib1_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  sib1_func_def_t func_def;
} sib1_ric_service_update_t;


#ifdef __cplusplus
}
#endif

#endif


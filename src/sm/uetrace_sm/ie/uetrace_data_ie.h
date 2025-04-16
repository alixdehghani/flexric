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

#ifndef UETRACE_DATA_INFORMATION_ELEMENTS_H
#define UETRACE_DATA_INFORMATION_ELEMENTS_H

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
  uint32_t interval_ms;
  uint32_t init_ms;
} uetrace_event_trigger_t;

void free_uetrace_event_trigger(uetrace_event_trigger_t* src); 

uetrace_event_trigger_t cp_uetrace_event_trigger( uetrace_event_trigger_t* src);

bool eq_uetrace_event_trigger(uetrace_event_trigger_t* m0, uetrace_event_trigger_t* m1);



//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;  
} uetrace_action_def_t;

void free_uetrace_action_def(uetrace_action_def_t* src); 

uetrace_action_def_t cp_uetrace_action_def(uetrace_action_def_t* src);

bool eq_uetrace_action_def(uetrace_event_trigger_t* m0,  uetrace_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} uetrace_ind_hdr_t;

void free_uetrace_ind_hdr(uetrace_ind_hdr_t* src); 

uetrace_ind_hdr_t cp_uetrace_ind_hdr(uetrace_ind_hdr_t const* src);

bool eq_uetrace_ind_hdr(uetrace_ind_hdr_t* m0, uetrace_ind_hdr_t* m1);


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct {
  int rnti;
  double bsr;
  double dl_bler;
  double dl_cqi;
  double dl_mcs;
  double dl_pmi;
  double dl_rate;
  double dl_ri;
  double phr;
  double snr_pucch;
  double ul_bler;
  double ul_mcs;
  double ul_rate;
  double snr;

} uetrace_stats_t;

typedef struct {
  uetrace_stats_t* rb; 
  uint32_t len;

  int64_t tstamp;
} uetrace_ind_msg_t;

void free_uetrace_ind_msg(uetrace_ind_msg_t* src); 

uetrace_ind_msg_t cp_uetrace_ind_msg(uetrace_ind_msg_t const* src);

bool eq_uetrace_ind_msg(uetrace_ind_msg_t* m0, uetrace_ind_msg_t* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} uetrace_call_proc_id_t;

void free_uetrace_call_proc_id( uetrace_call_proc_id_t* src); 

uetrace_call_proc_id_t cp_uetrace_call_proc_id( uetrace_call_proc_id_t* src);

bool eq_uetrace_call_proc_id(uetrace_call_proc_id_t* m0, uetrace_call_proc_id_t* m1);



//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////


typedef struct {
  uint32_t dummy;
} uetrace_ctrl_hdr_t;

void free_uetrace_ctrl_hdr( uetrace_ctrl_hdr_t* src); 

uetrace_ctrl_hdr_t cp_uetrace_ctrl_hdr(uetrace_ctrl_hdr_t* src);

bool eq_uetrace_ctrl_hdr(uetrace_ctrl_hdr_t* m0, uetrace_ctrl_hdr_t* m1);



//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


typedef struct {
  uint32_t action;
} uetrace_ctrl_msg_t;

void free_uetrace_ctrl_msg( uetrace_ctrl_msg_t* src); 

uetrace_ctrl_msg_t cp_uetrace_ctrl_msg(uetrace_ctrl_msg_t* src);

bool eq_uetrace_ctrl_msg(uetrace_ctrl_msg_t* m0, uetrace_ctrl_msg_t* m1);



//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  UETRACE_CTRL_OUT_OK,

  UETRACE_CTRL_OUT_END
} uetrace_ctrl_out_e;


typedef struct {
  uetrace_ctrl_out_e ans;
} uetrace_ctrl_out_t;

void free_uetrace_ctrl_out(uetrace_ctrl_out_t* src); 

uetrace_ctrl_out_t cp_uetrace_ctrl_out(uetrace_ctrl_out_t* src);

bool eq_uetrace_ctrl_out(uetrace_ctrl_out_t* m0, uetrace_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint8_t* buf;
  size_t len;
} uetrace_func_def_t;

void free_uetrace_func_def( uetrace_func_def_t* src); 

uetrace_func_def_t cp_uetrace_func_def(uetrace_func_def_t const* src);

bool eq_uetrace_func_def(uetrace_func_def_t const* m0, uetrace_func_def_t const* m1);

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
  uetrace_event_trigger_t et; 
  uetrace_action_def_t* ad;
} uetrace_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  uetrace_ind_hdr_t hdr;
  uetrace_ind_msg_t msg;
  uetrace_call_proc_id_t* proc_id;
} uetrace_ind_data_t;

void free_uetrace_ind_data(uetrace_ind_data_t* ind);

uetrace_ind_data_t cp_uetrace_ind_data(uetrace_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  uetrace_ctrl_hdr_t hdr;
  uetrace_ctrl_msg_t msg;
} uetrace_ctrl_req_data_t;

typedef struct{
  uetrace_ctrl_out_t* out;
} uetrace_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  uetrace_func_def_t func_def;
} uetrace_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  uetrace_func_def_t func_def;
} uetrace_ric_service_update_t;


#ifdef __cplusplus
}
#endif

#endif


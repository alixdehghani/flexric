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

#ifndef COUNTERS_DATA_INFORMATION_ELEMENTS_H
#define COUNTERS_DATA_INFORMATION_ELEMENTS_H

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
} counters_event_trigger_t;

void free_counters_event_trigger(counters_event_trigger_t* src); 

counters_event_trigger_t cp_counters_event_trigger( counters_event_trigger_t* src);

bool eq_counters_event_trigger(counters_event_trigger_t* m0, counters_event_trigger_t* m1);



//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;  
} counters_action_def_t;

void free_counters_action_def(counters_action_def_t* src); 

counters_action_def_t cp_counters_action_def(counters_action_def_t* src);

bool eq_counters_action_def(counters_event_trigger_t* m0,  counters_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} counters_ind_hdr_t;

void free_counters_ind_hdr(counters_ind_hdr_t* src); 

counters_ind_hdr_t cp_counters_ind_hdr(counters_ind_hdr_t const* src);

bool eq_counters_ind_hdr(counters_ind_hdr_t* m0, counters_ind_hdr_t* m1);


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct {
  uint8_t sector_number;
  uint64_t time_stamp;
  double dl_bitrate;
  double dl_errors;
  double dl_nas_transport;
  double dl_tx;
  double dl_use_avg;
  double dl_use_max;
  double dl_use_min;
  double dl_use_online;
  double nof_pdcp_pak;
  double nof_fail_pdcp_pak;
  double dl_nof_volte_pak;
  double dl_nof_fail_volte_pak;
  double dl_trafic_volte;
  double erab_count_avg;
  double erab_count_max;
  double erab_count_min;
  double erab_modify_request;
  double erab_modify_response;
  double erab_release_command;
  double erab_release_response;
  double erab_setup_request;
  double erab_setup_response;
  double volte_erab_attempts;
  double number_of_rach;
  double number_of_rar;
  double max_time_adv;
  double call_duration;
  double rrc_connection_reconfiguration;
  double rrc_connection_reconfiguration_complete;
  double rrc_connection_reestablishment;
  double rrc_connection_reestablishment_reject;
  double rrc_connection_reestablishment_request;
  double rrc_connection_reconfiguration_modify_bearer;
  double rrc_connection_reconfiguration_new_bearer;
  double rrc_connection_reconfiguration_rem_bearer;
  double rrc_connection_reconfiguration_handover;
  double rrc_connection_reconfiguration_mac_ce;
  double rrc_connection_reject;
  double rrc_connection_release;
  double rrc_connection_request;
  double rrc_connection_setup;
  double rrc_connection_setup_complete;
  double rrc_dl_information_transfer;
  double rrc_security_mode_command;
  double rrc_security_mode_complete;
  double rrc_security_mode_failure;
  double rrc_ue_capability_enquiry;
  double rrc_ue_capability_information;
  double rrc_ul_information_transfer;
  double csfb_attempt;
  double csfb_success;
  double srvcc_attempt;
  double srvcc_success;
  double volte_qci1_attempts;
  double success_volte_establishment_qci1;
  double csfb_geran_attempt;
  double csfb_umts_attempt;
  double handover_success_inter_sec;
  double handover_request_inter_sec;
  double s1_setup_failure;
  double s1_setup_request;
  double s1_setup_response;
  double handover_request;
  double handover_request_acknowledge;
  double handover_send_notify;
  double handover_success;
  double handover_failure;
  double ue_context_modify_response;
  double handover_success_volte;
  double ue_context_modify_failure;
  double ue_context_modify_request;
  double ue_context_release_command;
  double ue_context_release_complete;
  double ue_context_release_request;
  double ue_context_setup_complete;
  double ue_count_avg;
  double ue_count_max;
  double ue_count_min;
  double ue_count_online;
  double initial_context_setup_request;
  double initial_context_setup_failure;
  double initial_context_setup_response;
  double initial_ue_message;
  double mme_status_transfer;
  double ul_bitrate;
  double ul_errors;
  double ul_nas_transport;
  double ul_tx;
  double ul_use_avg;
  double ul_use_max;
  double ul_use_min;
  double ul_use_online;
  double ul_interference;
  double ul_trafic_volte;

} counters_stats_t;

typedef struct {
  counters_stats_t* rb; 
  uint32_t len;

  int64_t tstamp;
} counters_ind_msg_t;

void free_counters_ind_msg(counters_ind_msg_t* src); 

counters_ind_msg_t cp_counters_ind_msg(counters_ind_msg_t const* src);

bool eq_counters_ind_msg(counters_ind_msg_t* m0, counters_ind_msg_t* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} counters_call_proc_id_t;

void free_counters_call_proc_id( counters_call_proc_id_t* src); 

counters_call_proc_id_t cp_counters_call_proc_id( counters_call_proc_id_t* src);

bool eq_counters_call_proc_id(counters_call_proc_id_t* m0, counters_call_proc_id_t* m1);



//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////


typedef struct {
  uint32_t dummy;
} counters_ctrl_hdr_t;

void free_counters_ctrl_hdr( counters_ctrl_hdr_t* src); 

counters_ctrl_hdr_t cp_counters_ctrl_hdr(counters_ctrl_hdr_t* src);

bool eq_counters_ctrl_hdr(counters_ctrl_hdr_t* m0, counters_ctrl_hdr_t* m1);



//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


typedef struct {
  uint32_t action;
} counters_ctrl_msg_t;

void free_counters_ctrl_msg( counters_ctrl_msg_t* src); 

counters_ctrl_msg_t cp_counters_ctrl_msg(counters_ctrl_msg_t* src);

bool eq_counters_ctrl_msg(counters_ctrl_msg_t* m0, counters_ctrl_msg_t* m1);



//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  COUNTERS_CTRL_OUT_OK,

  COUNTERS_CTRL_OUT_END
} counters_ctrl_out_e;


typedef struct {
  counters_ctrl_out_e ans;
} counters_ctrl_out_t;

void free_counters_ctrl_out(counters_ctrl_out_t* src); 

counters_ctrl_out_t cp_counters_ctrl_out(counters_ctrl_out_t* src);

bool eq_counters_ctrl_out(counters_ctrl_out_t* m0, counters_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint8_t* buf;
  size_t len;
} counters_func_def_t;

void free_counters_func_def( counters_func_def_t* src); 

counters_func_def_t cp_counters_func_def(counters_func_def_t const* src);

bool eq_counters_func_def(counters_func_def_t const* m0, counters_func_def_t const* m1);

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
  counters_event_trigger_t et; 
  counters_action_def_t* ad;
} counters_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  counters_ind_hdr_t hdr;
  counters_ind_msg_t msg;
  counters_call_proc_id_t* proc_id;
} counters_ind_data_t;

void free_counters_ind_data(counters_ind_data_t* ind);

counters_ind_data_t cp_counters_ind_data(counters_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  counters_ctrl_hdr_t hdr;
  counters_ctrl_msg_t msg;
} counters_ctrl_req_data_t;

typedef struct{
  counters_ctrl_out_t* out;
} counters_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  counters_func_def_t func_def;
} counters_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  counters_func_def_t func_def;
} counters_ric_service_update_t;


#ifdef __cplusplus
}
#endif

#endif


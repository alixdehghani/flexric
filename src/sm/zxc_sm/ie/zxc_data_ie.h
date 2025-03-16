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

#ifndef ZXC_DATA_INFORMATION_ELEMENTS_H
#define ZXC_DATA_INFORMATION_ELEMENTS_H

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
} zxc_event_trigger_t;

void free_zxc_event_trigger(zxc_event_trigger_t* src); 

zxc_event_trigger_t cp_zxc_event_trigger( zxc_event_trigger_t* src);

bool eq_zxc_event_trigger(zxc_event_trigger_t* m0, zxc_event_trigger_t* m1);



//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;  
} zxc_action_def_t;

void free_zxc_action_def(zxc_action_def_t* src); 

zxc_action_def_t cp_zxc_action_def(zxc_action_def_t* src);

bool eq_zxc_action_def(zxc_event_trigger_t* m0,  zxc_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} zxc_ind_hdr_t;

void free_zxc_ind_hdr(zxc_ind_hdr_t* src); 

zxc_ind_hdr_t cp_zxc_ind_hdr(zxc_ind_hdr_t const* src);

bool eq_zxc_ind_hdr(zxc_ind_hdr_t* m0, zxc_ind_hdr_t* m1);


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct {

  char bbu_addr [20];
  char cell_id [20];
  char enb_id [20];
  char geran_ci [20];
  char geran_lac [20];
  char gtp_bind_addr [20];
  char mcc [20];
  char mme_addr [20];
  char mnc [20];
  char n_prb [20];
  char name [20];
  char nof_ports [20];
  char p_a [20];
  char phy_cell_id [20];
  char rru_addr [20];
  char s1c_bind_addr [20];
  char sec1_pci [20];
  char sec1_x2_bind_addr [20];
  char sec2_pci [20];
  char sec2_x2_bind_addr [20];
  char sec3_x2_bind_addr [20];
  char sector_id [20];
  char tac [20];
  char tm [20];
  char ws_port [20];

} zxc_radio_bearer_stats_t;

typedef struct {
  zxc_radio_bearer_stats_t* rb; 
  uint32_t len;
  // char* str;
  // uint32_t len_str;
  // uint32_t pci;
  int64_t tstamp;
} zxc_ind_msg_t;

void free_zxc_ind_msg(zxc_ind_msg_t* src); 

zxc_ind_msg_t cp_zxc_ind_msg(zxc_ind_msg_t const* src);

bool eq_zxc_ind_msg(zxc_ind_msg_t* m0, zxc_ind_msg_t* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} zxc_call_proc_id_t;

void free_zxc_call_proc_id( zxc_call_proc_id_t* src); 

zxc_call_proc_id_t cp_zxc_call_proc_id( zxc_call_proc_id_t* src);

bool eq_zxc_call_proc_id(zxc_call_proc_id_t* m0, zxc_call_proc_id_t* m1);



//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////


typedef struct {
  uint32_t dummy;
} zxc_ctrl_hdr_t;

void free_zxc_ctrl_hdr( zxc_ctrl_hdr_t* src); 

zxc_ctrl_hdr_t cp_zxc_ctrl_hdr(zxc_ctrl_hdr_t* src);

bool eq_zxc_ctrl_hdr(zxc_ctrl_hdr_t* m0, zxc_ctrl_hdr_t* m1);



//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


typedef struct {
  zxc_radio_bearer_stats_t* rb; 
  uint32_t len;
} zxc_ctrl_msg_t;

void free_zxc_ctrl_msg( zxc_ctrl_msg_t* src); 

zxc_ctrl_msg_t cp_zxc_ctrl_msg(zxc_ctrl_msg_t* src);

bool eq_zxc_ctrl_msg(zxc_ctrl_msg_t* m0, zxc_ctrl_msg_t* m1);



//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  ZXC_CTRL_OUT_OK,

  ZXC_CTRL_OUT_END
} zxc_ctrl_out_e;


typedef struct {
  zxc_ctrl_out_e ans;
} zxc_ctrl_out_t;

void free_zxc_ctrl_out(zxc_ctrl_out_t* src); 

zxc_ctrl_out_t cp_zxc_ctrl_out(zxc_ctrl_out_t* src);

bool eq_zxc_ctrl_out(zxc_ctrl_out_t* m0, zxc_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint8_t* buf;
  size_t len;
} zxc_func_def_t;

void free_zxc_func_def( zxc_func_def_t* src); 

zxc_func_def_t cp_zxc_func_def(zxc_func_def_t const* src);

bool eq_zxc_func_def(zxc_func_def_t const* m0, zxc_func_def_t const* m1);

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
  zxc_event_trigger_t et; 
  zxc_action_def_t* ad;
} zxc_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  zxc_ind_hdr_t hdr;
  zxc_ind_msg_t msg;
  zxc_call_proc_id_t* proc_id;
} zxc_ind_data_t;

void free_zxc_ind_data(zxc_ind_data_t* ind);

zxc_ind_data_t cp_zxc_ind_data(zxc_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  zxc_ctrl_hdr_t hdr;
  zxc_ctrl_msg_t msg;
} zxc_ctrl_req_data_t;

typedef struct{
  zxc_ctrl_out_t* out;
} zxc_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  zxc_func_def_t func_def;
} zxc_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  zxc_func_def_t func_def;
} zxc_ric_service_update_t;


#ifdef __cplusplus
}
#endif

#endif


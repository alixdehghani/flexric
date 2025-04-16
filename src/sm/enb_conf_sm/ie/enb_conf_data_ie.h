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

#ifndef ENB_CONF_DATA_INFORMATION_ELEMENTS_H
#define ENB_CONF_DATA_INFORMATION_ELEMENTS_H

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
} enb_conf_event_trigger_t;

void free_enb_conf_event_trigger(enb_conf_event_trigger_t* src); 

enb_conf_event_trigger_t cp_enb_conf_event_trigger( enb_conf_event_trigger_t* src);

bool eq_enb_conf_event_trigger(enb_conf_event_trigger_t* m0, enb_conf_event_trigger_t* m1);



//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;  
} enb_conf_action_def_t;

void free_enb_conf_action_def(enb_conf_action_def_t* src); 

enb_conf_action_def_t cp_enb_conf_action_def(enb_conf_action_def_t* src);

bool eq_enb_conf_action_def(enb_conf_event_trigger_t* m0,  enb_conf_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} enb_conf_ind_hdr_t;

void free_enb_conf_ind_hdr(enb_conf_ind_hdr_t* src); 

enb_conf_ind_hdr_t cp_enb_conf_ind_hdr(enb_conf_ind_hdr_t const* src);

bool eq_enb_conf_ind_hdr(enb_conf_ind_hdr_t* m0, enb_conf_ind_hdr_t* m1);


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct {
  // enb
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

  //enb_files
  char drb_config[50];
  char mbms_sib_config[50];
  char rr_config[50];
  char sib_config[50];
  
  // expert
  char accept_handover_ratio[20];
  char agc_energy_b2x0[20];
  char alpha[20];
  char bi[20];
  char bi_flag[20];
  char csfb_geran_list[100];
  char eea_pref_list[20];
  char eia_pref_list[20];
  char enable_mbsfn[20];
  char geran_csfb_flag[20];
  char handover_drb_id[20];
  char link_failure_nof_err[20];
  char m1u_if_addr[20];
  char m1u_multiaddr[20];
  char mbms_file[20];
  char metrics_addr[20];
  char metrics_period_secs[20];
  char metrics_port[20];
  char nof_phy_threads[20];
  char packet_size[20];
  char pusch_max_its[20];
  char radio_unit[20];
  char rrc_connected[20];
  char rrc_inactivity_timer[20];
  char snr_pucch[20];
  char snr_pusch[20];

  // gui
  char enable_gui[20];

  // log
  char all_hex_limit[20];
  char all_level[20];
  char file_max_size[20];
  char filename_log[20];

  //pcap
  char enable_pcap[20];
  char filename_pcap[20];

  // rf
  char dl_earfcn[20];
  char rx_gain[20];
  char tx_gain[20];

  // scheduler
  char nof_ctrl_symbols[20];
  char pdsch_max_mcs1[20];
  char pdsch_max_mcs2[20];
  char pusch_max_mcs[20];

} enb_conf_stats_t;

typedef struct {
  enb_conf_stats_t* rb; 
  uint32_t len;

  int64_t tstamp;
} enb_conf_ind_msg_t;

void free_enb_conf_ind_msg(enb_conf_ind_msg_t* src); 

enb_conf_ind_msg_t cp_enb_conf_ind_msg(enb_conf_ind_msg_t const* src);

bool eq_enb_conf_ind_msg(enb_conf_ind_msg_t* m0, enb_conf_ind_msg_t* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} enb_conf_call_proc_id_t;

void free_enb_conf_call_proc_id( enb_conf_call_proc_id_t* src); 

enb_conf_call_proc_id_t cp_enb_conf_call_proc_id( enb_conf_call_proc_id_t* src);

bool eq_enb_conf_call_proc_id(enb_conf_call_proc_id_t* m0, enb_conf_call_proc_id_t* m1);



//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////


typedef struct {
  uint32_t dummy;
} enb_conf_ctrl_hdr_t;

void free_enb_conf_ctrl_hdr( enb_conf_ctrl_hdr_t* src); 

enb_conf_ctrl_hdr_t cp_enb_conf_ctrl_hdr(enb_conf_ctrl_hdr_t* src);

bool eq_enb_conf_ctrl_hdr(enb_conf_ctrl_hdr_t* m0, enb_conf_ctrl_hdr_t* m1);



//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


typedef struct {
  uint32_t len;
  enb_conf_stats_t* enb_rb;
} enb_conf_ctrl_msg_t;

void free_enb_conf_ctrl_msg( enb_conf_ctrl_msg_t* src); 

enb_conf_ctrl_msg_t cp_enb_conf_ctrl_msg(enb_conf_ctrl_msg_t* src);

bool eq_enb_conf_ctrl_msg(enb_conf_ctrl_msg_t* m0, enb_conf_ctrl_msg_t* m1);



//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  ENB_CONF_CTRL_OUT_OK,

  ENB_CONF_CTRL_OUT_END
} enb_conf_ctrl_out_e;


typedef struct {
  enb_conf_ctrl_out_e ans;
} enb_conf_ctrl_out_t;

void free_enb_conf_ctrl_out(enb_conf_ctrl_out_t* src); 

enb_conf_ctrl_out_t cp_enb_conf_ctrl_out(enb_conf_ctrl_out_t* src);

bool eq_enb_conf_ctrl_out(enb_conf_ctrl_out_t* m0, enb_conf_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint8_t* buf;
  size_t len;
} enb_conf_func_def_t;

void free_enb_conf_func_def( enb_conf_func_def_t* src); 

enb_conf_func_def_t cp_enb_conf_func_def(enb_conf_func_def_t const* src);

bool eq_enb_conf_func_def(enb_conf_func_def_t const* m0, enb_conf_func_def_t const* m1);

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
  enb_conf_event_trigger_t et; 
  enb_conf_action_def_t* ad;
} enb_conf_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  enb_conf_ind_hdr_t hdr;
  enb_conf_ind_msg_t msg;
  enb_conf_call_proc_id_t* proc_id;
} enb_conf_ind_data_t;

void free_enb_conf_ind_data(enb_conf_ind_data_t* ind);

enb_conf_ind_data_t cp_enb_conf_ind_data(enb_conf_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  enb_conf_ctrl_hdr_t hdr;
  enb_conf_ctrl_msg_t msg;
} enb_conf_ctrl_req_data_t;

typedef struct{
  enb_conf_ctrl_out_t* out;
} enb_conf_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  enb_conf_func_def_t func_def;
} enb_conf_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  enb_conf_func_def_t func_def;
} enb_conf_ric_service_update_t;


#ifdef __cplusplus
}
#endif

#endif


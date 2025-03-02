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
  /* PDU stats */
  /* TX */
  uint32_t txpdu_pkts;         /* aggregated number of transmitted ZXC PDUs */
  uint32_t txpdu_bytes;        /* aggregated amount of transmitted bytes in ZXC PDUs */
  uint32_t txpdu_wt_ms;        /* TODO: aggregated head-of-line tx packet waiting time to be transmitted (i.e. send to the MAC layer) */
  uint32_t txpdu_dd_pkts;      /* aggregated number of dropped or discarded tx packets by ZXC */
  uint32_t txpdu_dd_bytes;     /* aggregated amount of bytes dropped or discarded tx packets by ZXC */
  uint32_t txpdu_retx_pkts;    /* aggregated number of tx pdus/pkts to be re-transmitted (only applicable to ZXC AM) */
  uint32_t txpdu_retx_bytes;   /* aggregated amount of bytes to be re-transmitted (only applicable to ZXC AM) */
  uint32_t txpdu_segmented;    /* aggregated number of segmentations */
  uint32_t txpdu_status_pkts;  /* aggregated number of tx status pdus/pkts (only applicable to ZXC AM) */
  uint32_t txpdu_status_bytes; /* aggregated amount of tx status bytes  (only applicable to ZXC AM) */
  uint32_t txbuf_occ_bytes;    /* (IMPLEMENTED) transmitting bytes currently in buffer */
  uint32_t txbuf_occ_pkts;     /* TODO: current tx buffer occupancy in terms of number of packets (average: NOT IMPLEMENTED) */

  /* txbuf_wd_ms: the time window for which the txbuf  occupancy value is obtained - NOT IMPLEMENTED */

  /* RX */
  uint32_t rxpdu_pkts;         /* aggregated number of received ZXC PDUs */
  uint32_t rxpdu_bytes;        /* amount of bytes received by the ZXC */
  uint32_t rxpdu_dup_pkts;     /* aggregated number of duplicate packets */
  uint32_t rxpdu_dup_bytes;    /* aggregated amount of duplicated bytes */
  uint32_t rxpdu_dd_pkts;      /* aggregated number of rx packets dropped or discarded by ZXC */
  uint32_t rxpdu_dd_bytes;     /* aggregated amount of rx bytes dropped or discarded by ZXC */
  uint32_t rxpdu_ow_pkts;      /* aggregated number of out of window received ZXC pdu */
  uint32_t rxpdu_ow_bytes;     /* aggregated number of out of window bytes received ZXC pdu */
  uint32_t rxpdu_status_pkts;  /* aggregated number of rx status pdus/pkts (only applicable to ZXC AM) */
  uint32_t rxpdu_status_bytes; /* aggregated amount of rx status bytes  (only applicable to ZXC AM) */
  /* rxpdu_rotout_ms: flag indicating rx reordering  timeout in ms - NOT IMPLEMENTED */
  /* rxpdu_potout_ms: flag indicating the poll retransmit time out in ms - NOT IMPLEMENTED */
  /* rxpdu_sptout_ms: flag indicating status prohibit timeout in ms - NOT IMPLEMENTED */
  uint32_t rxbuf_occ_bytes;    /* (IMPLEMENTED) received bytes currently in buffer */
  uint32_t rxbuf_occ_pkts;     /* TODO: current rx buffer occupancy in terms of number of packets (average: NOT IMPLEMENTED) */


  /* SDU stats */
  /* TX */
  uint32_t txsdu_pkts;         /* number of SDUs delivered */
  uint64_t txsdu_bytes;        /* (UPDATED) number of SDUs bytes successfully transmitted so far (counter) */
  /* Average time for an SDU to be passed to MAC:
   * Actually measures the time it takes for THE FULL SDU to be passed to MAC FOR THE FIRST TIME.
   * Since the MAC schedules in advance, it does not measure the time of
   * transmission over the air, just the time to reach the MAC layer.
   * => to control it, 'txsdu_hol_waittime' that measures the current HOL-delay is added.
   */
  double txsdu_avg_time_to_tx; /* (100ms-windowed) per-packet sojourn (SDU to PDU) in microseconds */
  uint32_t txsdu_wt_us;        /* HOL delay of the current radio bearer, in microseconds */


  /* RX */
  uint32_t rxsdu_pkts;         /* number of SDUs received */
  uint64_t rxsdu_bytes;        /* (UPDATED) number of SDUs bytes arrived so far (counter) */
  uint32_t rxsdu_dd_pkts;      /* number of dropped or discarded SDUs */
  uint32_t rxsdu_dd_bytes;     /* number of bytes of SDUs dropped or discarded */

  uint32_t rnti;
  uint8_t mode;               /* 0: ZXC AM, 1: ZXC UM, 2: ZXC TM */
  uint8_t rbid;
  uint8_t zxc_data_t; 

} zxc_radio_bearer_stats_t;

typedef struct {
  zxc_radio_bearer_stats_t* rb; 
  uint32_t len;
  char* str;
  uint32_t len_str;
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
  uint32_t action;
  uint32_t action2;
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


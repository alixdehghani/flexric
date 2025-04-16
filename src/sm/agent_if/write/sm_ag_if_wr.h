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


#ifndef E2AP_SM_WR_IF_H
#define E2AP_SM_WR_IF_H 

#include "subscribe_timer.h"
#include "../../pdcp_sm/ie/pdcp_data_ie.h"
#include "../../rlc_sm/ie/rlc_data_ie.h"
#include "../../zxc_sm/ie/zxc_data_ie.h"
#include "../../sib1_sm/ie/sib1_data_ie.h"
#include "../../sib2_sm/ie/sib2_data_ie.h"
#include "../../rr_sm/ie/rr_data_ie.h"
#include "../../uetrace_sm/ie/uetrace_data_ie.h"
#include "../../counters_sm/ie/counters_data_ie.h"
#include "../../mac_sm/ie/mac_data_ie.h"
#include "../../slice_sm/ie/slice_data_ie.h"
#include "../../tc_sm/ie/tc_data_ie.h"
#include "../../gtp_sm/ie/gtp_data_ie.h"
#include "../../kpm_sm/kpm_data_ie_wrapper.h"
#include "../../rc_sm/ie/rc_data_ie.h"
#include "../../enb_conf_sm/ie/enb_conf_data_ie.h"

//////////////////////
//////////////////////
// Control
//////////////////////
//////////////////////


typedef enum{
  MAC_CTRL_REQ_V0 = 0,
  RLC_CTRL_REQ_V0 = 1,
  ZXC_CTRL_REQ_V0 = 2,
  PDCP_CTRL_REQ_V0 = 3,
  SLICE_CTRL_REQ_V0 = 4,
  TC_CTRL_REQ_V0 = 5,
  GTP_CTRL_REQ_V0 = 6,
  ENB_CONF_CTRL_REQ_V0 = 7,
  RAN_CONTROL_CTRL_V1_03 = 8, 
  COUNTERS_CTRL_REQ_V0 = 9,
  SIB1_CTRL_REQ_V0 = 10,
  SIB2_CTRL_REQ_V0 = 11,
  UETRACE_CTRL_REQ_V0 = 12,
  RR_CTRL_REQ_V0 = 13,
  SM_AGENT_IF_WRITE_CTRL_V0_END = 14,
} sm_ag_if_ctrl_e;

typedef struct{
  sm_ag_if_ctrl_e type;
  union{
    mac_ctrl_req_data_t mac_ctrl;
    rlc_ctrl_req_data_t rlc_ctrl;
    zxc_ctrl_req_data_t zxc_ctrl;
    pdcp_ctrl_req_data_t pdcp_req_ctrl;
    slice_ctrl_req_data_t slice_req_ctrl;
    tc_ctrl_req_data_t tc_req_ctrl;
    gtp_ctrl_req_data_t gtp_ctrl;
    rc_ctrl_req_data_t rc_ctrl;
    enb_conf_ctrl_req_data_t enb_conf_ctrl;
    counters_ctrl_req_data_t counters_ctrl;
    sib1_ctrl_req_data_t sib1_ctrl;
    sib2_ctrl_req_data_t sib2_ctrl;
    rr_ctrl_req_data_t rr_ctrl;
    uetrace_ctrl_req_data_t uetrace_ctrl;
  };
}  sm_ag_if_wr_ctrl_t;


//////////////////////
//////////////////////
// Subscription 
//////////////////////
//////////////////////

typedef enum{
  MAC_SUBS_V0 = 0, 
  RLC_SUBS_V0, 
  ZXC_SUBS_V0,
  PDCP_SUBS_V0, 
  SLICE_SUBS_V0, 
  TC_SUBS_V0, 
  GTP_SUBS_V0, 
  KPM_SUBS_V3_0,
  ENB_CONF_SUBS_V0, 
  COUNTERS_SUBS_V0,
  SIB1_SUBS_V0,
  SIB2_SUBS_V0,
  UETRACE_SUBS_V0,
  RR_SUBS_V0,
  RAN_CTRL_SUBS_V1_03, 
  SM_AGENT_IF_WRITE_SUBS_V0_END,
} sm_ag_if_subs_e;

typedef struct{ 
  uint32_t ric_req_id;
  rc_sub_data_t rc;
} wr_rc_sub_data_t;


typedef struct{
  sm_ag_if_subs_e type;
  union{
    mac_sub_data_t mac;
    rlc_sub_data_t rlc;
    zxc_sub_data_t zxc;
    pdcp_sub_data_t pdcp;
    slice_sub_data_t slice;
    tc_sub_data_t tc;
    gtp_sub_data_t gtp;
    kpm_sub_data_t kpm;
    enb_conf_sub_data_t enb_conf;
    counters_sub_data_t counters;
    sib1_sub_data_t sib1;
    sib2_sub_data_t sib2;
    rr_sub_data_t rr;
    uetrace_sub_data_t uetrace;
    wr_rc_sub_data_t wr_rc;
  };
} sm_ag_if_wr_subs_t;


//////////////////////
//////////////////////
// Write interface 
//////////////////////
//////////////////////

typedef enum{
 CONTROL_SM_AG_IF_WR,
 SUBSCRIPTION_SM_AG_IF_WR,
 END_SM_AG_IF_WR,
} sm_ag_if_wr_e; 

typedef struct {
  sm_ag_if_wr_e type;
  union{
    sm_ag_if_wr_ctrl_t ctrl;
    sm_ag_if_wr_subs_t subs;
  }; 
} sm_ag_if_wr_t;

#endif

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


#ifndef SM_READ_INTERFACE_H
#define SM_READ_INTERFACE_H

// Interface between the SM and the agent/server. 
// The SM can call the functions here defined and implemented on the RAN/server to read data.

#include "../../mac_sm/ie/mac_data_ie.h"
#include "../../rlc_sm/ie/rlc_data_ie.h"
#include "../../zxc_sm/ie/zxc_data_ie.h"
#include "../../counters_sm/ie/counters_data_ie.h"
#include "../../enb_conf_sm/ie/enb_conf_data_ie.h"
#include "../../sib1_sm/ie/sib1_data_ie.h"
#include "../../rr_sm/ie/rr_data_ie.h"
#include "../../uetrace_sm/ie/uetrace_data_ie.h"
#include "../../sib2_sm/ie/sib2_data_ie.h"
#include "../../pdcp_sm/ie/pdcp_data_ie.h"
#include "../../slice_sm/ie/slice_data_ie.h"
#include "../../tc_sm/ie/tc_data_ie.h"
#include "../../gtp_sm/ie/gtp_data_ie.h"
#include "../../rc_sm/ie/rc_data_ie.h"
#include "../../kpm_sm/kpm_data_ie_wrapper.h"

#include "../write/subscribe_timer.h"

////////////////////
// Indication Message 
////////////////////

// Do not change the order!
typedef enum{
  MAC_STATS_V0 = 0,
  RLC_STATS_V0,
  ZXC_STATS_V0,
  SIB1_STATS_V0,
  SIB2_STATS_V0,
  RR_STATS_V0,
  UETRACE_STATS_V0,
  COUNTERS_STATS_V0,
  ENB_CONF_STATS_V0,
  PDCP_STATS_V0,
  SLICE_STATS_V0,
  TC_STATS_V0,
  GTP_STATS_V0, 
  KPM_STATS_V3_0, 
  RAN_CTRL_STATS_V1_03,
  SM_AGENT_IF_READ_V0_END,
} sm_ag_if_rd_ind_e;

typedef struct{
  kpm_ind_data_t ind;
  // Non-owning pointer
  kpm_act_def_t const* act_def;
} kpm_rd_ind_data_t;

typedef struct{
  rc_ind_data_t ind;
  // Non-owning pointer
  e2sm_rc_action_def_t const* act_def;
  uint32_t ric_id;
} rc_rd_ind_data_t;

// ToDo: Change it for pointers, to break the dependencies
typedef struct{
  sm_ag_if_rd_ind_e type;
// Do not change the order!
  union {
    mac_ind_data_t mac;
    rlc_ind_data_t rlc;
    pdcp_ind_data_t pdcp;
    slice_ind_data_t slice;
    tc_ind_data_t tc;
    gtp_ind_data_t gtp;
    kpm_rd_ind_data_t kpm;
    rc_rd_ind_data_t rc;
    zxc_ind_data_t zxc;
    enb_conf_ind_data_t enb_conf;
    counters_ind_data_t counters;
    sib1_ind_data_t sib1;
    sib2_ind_data_t sib2;
    rr_ind_data_t rr;
    uetrace_ind_data_t uetrace;
  };
} sm_ag_if_rd_ind_t;

void free_sm_ag_if_rd_ind(sm_ag_if_rd_ind_t* d);

sm_ag_if_rd_ind_t cp_sm_ag_if_rd_ind(sm_ag_if_rd_ind_t const* d);

////////////////////
// E2 Setup 
////////////////////

typedef enum{
  MAC_AGENT_IF_E2_SETUP_ANS_V0 = 0,
  RLC_AGENT_IF_E2_SETUP_ANS_V0,
  ZXC_AGENT_IF_E2_SETUP_ANS_V0,
  PDCP_AGENT_IF_E2_SETUP_ANS_V0,
  SLICE_AGENT_IF_E2_SETUP_ANS_V0,
  TC_AGENT_IF_E2_SETUP_ANS_V0,
  GTP_AGENT_IF_E2_SETUP_ANS_V0,
  KPM_V3_0_AGENT_IF_E2_SETUP_ANS_V0,
  RAN_CTRL_V1_3_AGENT_IF_E2_SETUP_ANS_V0,
  ENB_CONF_AGENT_IF_E2_SETUP_ANS_V0,
  COUNTERS_AGENT_IF_E2_SETUP_ANS_V0,
  SIB1_AGENT_IF_E2_SETUP_ANS_V0,
  SIB2_AGENT_IF_E2_SETUP_ANS_V0,
  RR_AGENT_IF_E2_SETUP_ANS_V0,
  UETRACE_AGENT_IF_E2_SETUP_ANS_V0,
  SM_AGENT_IF_E2_SETUP_ANS_V0_END,
} sm_ag_if_rd_e2setup_e;

typedef struct{
  sm_ag_if_rd_e2setup_e type;
  union {
    mac_e2_setup_data_t mac;
    rlc_e2_setup_data_t rlc;
    pdcp_e2_setup_data_t pdcp;
    slice_e2_setup_data_t slice;
    tc_e2_setup_data_t tc;
    gtp_e2_setup_data_t gtp;
    kpm_e2_setup_t kpm;
    rc_e2_setup_t rc;
    zxc_e2_setup_data_t zxc;
    counters_e2_setup_data_t counters;
    enb_conf_e2_setup_data_t enb_conf;
    sib1_e2_setup_data_t sib1;
    sib2_e2_setup_data_t sib2;
    rr_e2_setup_data_t rr;
    uetrace_e2_setup_data_t uetrace;
    
  };
} sm_ag_if_rd_e2setup_t;

////////////////////
// RIC SERVICE UPDATE 
////////////////////

typedef enum{
  MAC_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  RLC_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  ZXC_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  COUNTERS_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  PDCP_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  SLICE_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  TC_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  GTP_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  KPM_V3_0_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  RAN_CTRL_V1_3_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  ENB_CONF_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  SIB1_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  SIB2_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  RR_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  UETRACE_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,

  SM_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0_END,
} sm_ag_if_rd_rsu_e;

typedef struct{
  sm_ag_if_rd_rsu_e type;
  union {
    mac_ric_service_update_t mac;
    rlc_ric_service_update_t rlc;
    zxc_ric_service_update_t zxc;
    pdcp_ric_service_update_t pdcp;
    slice_ric_service_update_t slice;
    tc_ric_service_update_t tc;
    gtp_ric_service_update_t gtp;
    kpm_ric_service_update_t kpm;
    rc_ric_service_update_t rc;
    enb_conf_ric_service_update_t enb_conf;
    counters_ric_service_update_t counters;
    sib1_ric_service_update_t sib1;
    sib2_ric_service_update_t sib2;
    rr_ric_service_update_t rr;
    uetrace_ric_service_update_t uetrace;
  };
} sm_ag_if_rd_rsu_t;


////////////////////////////////////////
// AGENT INTERFACE READ
////////////////////////////////////////

typedef enum{
  INDICATION_MSG_AGENT_IF_ANS_V0,
  E2_SETUP_AGENT_IF_ANS_V0,
  RIC_SERV_UPDATE_AGENT_IF_ANS_V0,
  
  END_AGENT_IF_ANS_V0,
}  sm_ag_if_rd_e;

typedef struct{
  sm_ag_if_rd_e type;
  union{
    sm_ag_if_rd_ind_t ind;
    sm_ag_if_rd_e2setup_t e2ap;
    sm_ag_if_rd_rsu_t rsu;
  };
} sm_ag_if_rd_t;

void free_sm_ag_if_rd(sm_ag_if_rd_t* src);

sm_ag_if_rd_t cp_sm_ag_if_rd(sm_ag_if_rd_t const* src);

#endif


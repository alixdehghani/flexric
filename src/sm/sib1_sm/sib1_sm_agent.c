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


#include "sib1_sm_agent.h"
#include "sib1_sm_id.h"
#include "enc/sib1_enc_generic.h"
#include "dec/sib1_dec_generic.h"
#include "../../util/alg_ds/alg/defer.h"


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{

  sm_agent_t base;

#ifdef ASN
  sib1_enc_asn_t enc;
#elif FLATBUFFERS 
  sib1_enc_fb_t enc;
#elif PLAIN
  sib1_enc_plain_t enc;
#else
  static_assert(false, "No encryption type selected");
#endif

} sm_sib1_agent_t;


// Function pointers provided by the RAN for the 
// 5 procedures, 
// subscription, indication, control, 
// E2 Setup and RIC Service Update. 
//
static
sm_ag_if_ans_subs_t on_subscription_sib1_sm_ag(sm_agent_t const* sm_agent, const sm_subs_data_t* data)
{
  assert(sm_agent != NULL);
  assert(data != NULL);

  sm_sib1_agent_t* sm = (sm_sib1_agent_t*)sm_agent;
 
  sib1_event_trigger_t ev = sib1_dec_event_trigger(&sm->enc, data->len_et, data->event_trigger);

  sm_ag_if_ans_subs_t ans = {.type = PERIODIC_SUBSCRIPTION_FLRC};
  ans.per.t.init_ms = ev.init_ms;
  ans.per.t.interval_ms = ev.interval_ms;
  ans.per.t.ms = ev.ms;
  return ans;
}

static
exp_ind_data_t on_indication_sib1_sm_ag(sm_agent_t const* sm_agent,void* act_def)
{
//  printf("on_indication SIB1 called \n");
  assert(sm_agent != NULL);
  assert(act_def == NULL && "Action Definition data not needed for this SM");
  sm_sib1_agent_t* sm = (sm_sib1_agent_t*)sm_agent;

  exp_ind_data_t ret = {.has_value = true};

  // Fill Indication Header
  sib1_ind_hdr_t hdr = {.dummy = 0 };
  byte_array_t ba_hdr = sib1_enc_ind_hdr(&sm->enc, &hdr );
  ret.data.ind_hdr = ba_hdr.buf;
  ret.data.len_hdr = ba_hdr.len;

  // Fill Indication Message 
  //sm_ag_if_rd_t rd_if = {.type = INDICATION_MSG_AGENT_IF_ANS_V0};
  //rd_if.ind.type = SIB1_STATS_V0;

  sib1_ind_data_t sib1 = {0};
 // Liberate the memory if previously allocated by the RAN. It sucks
  defer({ free_sib1_ind_hdr(&sib1.hdr) ;});
  defer({ free_sib1_ind_msg(&sib1.msg) ;});
  defer({ free_sib1_call_proc_id(sib1.proc_id);});

  if(sm->base.io.read_ind(&sib1) == false)
    return (exp_ind_data_t){.has_value = false};

  byte_array_t ba = sib1_enc_ind_msg(&sm->enc, &sib1.msg);
  ret.data.ind_msg = ba.buf;
  ret.data.len_msg = ba.len;

  // Fill Call Process ID
  ret.data.call_process_id = NULL;
  ret.data.len_cpid = 0;

  return ret;
}

static
 sm_ctrl_out_data_t on_control_sib1_sm_ag(sm_agent_t const* sm_agent, sm_ctrl_req_data_t const* data)
{
  assert(sm_agent != NULL);
  assert(data != NULL);
  sm_sib1_agent_t* sm = (sm_sib1_agent_t*) sm_agent;

  sib1_ctrl_hdr_t hdr = sib1_dec_ctrl_hdr(&sm->enc, data->len_hdr, data->ctrl_hdr);
  // assert(hdr.dummy == 0 && "Only dummy == 0 supported ");

  sib1_ctrl_msg_t msg = sib1_dec_ctrl_msg(&sm->enc, data->len_msg, data->ctrl_msg);
  // assert(msg.action == 42 && "Only action number 42 supported");

  //sm_ag_if_wr_t wr = {.type = CONTROL_SM_AG_IF_WR };
  //wr.ctrl.type = SIB1_CTRL_REQ_V0;

  sib1_ctrl_req_data_t sib1_ctrl = {0};

  sib1_ctrl.hdr.dummy = hdr.dummy; 
  sib1_ctrl.msg.len = msg.len;
  sib1_ctrl.msg.sib1_rb = msg.sib1_rb;

  sm->base.io.write_ctrl(&sib1_ctrl);

  // Answer from the E2 Node
  sm_ctrl_out_data_t ret = {0};
  ret.ctrl_out = NULL;
  ret.len_out = 0;

  printf("on_control called \n");
  return ret;
}

static
sm_e2_setup_data_t on_e2_setup_sib1_sm_ag(sm_agent_t const* sm_agent)
{
  assert(sm_agent != NULL);
  //printf("on_e2_setup called \n");
  sm_sib1_agent_t* sm = (sm_sib1_agent_t*)sm_agent;
  (void)sm;

  sm_e2_setup_data_t setup = {.len_rfd =0, .ran_fun_def = NULL  }; 

  // ToDo: in other SMs we should call the RAN to fulfill this data
  // as it represents the capabilities of the RAN Function

  size_t const sz = strnlen(SM_SIB1_STR, 256);
  assert(sz < 256 && "Buffer overeflow?");

  setup.len_rfd = sz;
  setup.ran_fun_def = calloc(1, sz);
  assert(setup.ran_fun_def != NULL);

  memcpy(setup.ran_fun_def, SM_SIB1_STR , sz);
  
  /*
  // RAN Function
  setup.rf.def = cp_str_to_ba(SM_SIB1_SHORT_NAME);
  setup.rf.id = SM_SIB1_ID;
  setup.rf.rev = SM_SIB1_REV;

  setup.rf.oid = calloc(1, sizeof(byte_array_t) );
  assert(setup.rf.oid != NULL && "Memory exhausted");

  *setup.rf.oid = cp_str_to_ba(SM_SIB1_OID);
*/

  return setup;
}

static
sm_ric_service_update_data_t on_ric_service_update_sib1_sm_ag(sm_agent_t const* sm_agent )
{
  assert(sm_agent != NULL);
  assert(0!=0 && "Not implemented");


  printf("on_ric_service_update called \n");
  sm_ric_service_update_data_t dst = {0}; 

  return dst;
}

static
void free_sib1_sm_ag(sm_agent_t* sm_agent)
{
  assert(sm_agent != NULL);
  sm_sib1_agent_t* sm = (sm_sib1_agent_t*)sm_agent;
  free(sm);
}



// General SM information

// Definition
static
char const* def_sib1_sm_ag(void)
{
  return SM_SIB1_STR;
}

// ID
static
uint16_t id_sib1_sm_ag(void)
{
  return SM_SIB1_ID; 
}

  // Revision
static
uint16_t rev_sib1_sm_ag (void)
{
  return SM_SIB1_REV;
}

// OID
static
char const* oid_sib1_sm_ag (void)
{
  return SM_SIB1_OID;
}



sm_agent_t* make_sib1_sm_agent(sm_io_ag_ran_t io)
{
  sm_sib1_agent_t* sm = calloc(1, sizeof(sm_sib1_agent_t));
  assert(sm != NULL && "Memory exhausted!!!");

//  *(uint16_t*)(&sm->base.ran_func_id) = SM_SIB1_ID; 

  // Read
  sm->base.io.read_ind = io.read_ind_tbl[SIB1_STATS_V0];
  sm->base.io.read_setup = io.read_setup_tbl[SIB1_AGENT_IF_E2_SETUP_ANS_V0];
 
  //Write
  sm->base.io.write_ctrl = io.write_ctrl_tbl[SIB1_CTRL_REQ_V0];
  sm->base.io.write_subs = io.write_subs_tbl[SIB1_SUBS_V0];

  sm->base.free_sm = free_sib1_sm_ag;
  sm->base.free_act_def = NULL; //free_act_def_sib1_sm_ag;

  // O-RAN E2SM 5 Procedures
  sm->base.proc.on_subscription = on_subscription_sib1_sm_ag;
  sm->base.proc.on_indication = on_indication_sib1_sm_ag;
  sm->base.proc.on_control = on_control_sib1_sm_ag;
  sm->base.proc.on_ric_service_update = on_ric_service_update_sib1_sm_ag;
  sm->base.proc.on_e2_setup = on_e2_setup_sib1_sm_ag;
  sm->base.handle = NULL;

  // General SM information
  sm->base.info.def = def_sib1_sm_ag;
  sm->base.info.id =  id_sib1_sm_ag;
  sm->base.info.rev = rev_sib1_sm_ag;
  sm->base.info.oid = oid_sib1_sm_ag;

//  assert(strlen(SM_SIB1_STR) < sizeof( sm->base.ran_func_name) );
//  memcpy(sm->base.ran_func_name, SM_SIB1_STR, strlen(SM_SIB1_STR)); 

  return &sm->base;
}

/*
uint16_t id_sib1_sm_agent(sm_agent_t const* sm_agent )
{
  assert(sm_agent != NULL);
  sm_sib1_agent_t* sm = (sm_sib1_agent_t*)sm_agent;
  return sm->base.ran_func_id;
}
*/


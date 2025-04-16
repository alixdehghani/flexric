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


#include "counters_data_ie.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

void free_counters_event_trigger(counters_event_trigger_t* src)
{
  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 
}

counters_event_trigger_t cp_counters_event_trigger( counters_event_trigger_t* src)
{
  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 

  counters_event_trigger_t et = {0};
  return et;
}

bool eq_counters_event_trigger(counters_event_trigger_t* m0, counters_event_trigger_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

void free_counters_action_def(counters_action_def_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
}

counters_action_def_t cp_counters_action_def(counters_action_def_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  counters_action_def_t ad = {0};
  return ad;
}

bool eq_counters_action_def(counters_event_trigger_t* m0,  counters_event_trigger_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////


void free_counters_ind_hdr(counters_ind_hdr_t* src)
{
  assert(src != NULL);
  (void)src;
}

counters_ind_hdr_t cp_counters_ind_hdr(counters_ind_hdr_t const* src)
{
  assert(src != NULL);
  counters_ind_hdr_t dst = {0}; 
  dst.dummy = src->dummy;
  return dst;
}

bool eq_counters_ind_hdr(counters_ind_hdr_t* m0, counters_ind_hdr_t* m1)
{
  assert(m0 != 0);
  assert(m1 != 0);

  if(m0->dummy != m1->dummy)
    return false;
  return true;
}






//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

void free_counters_ind_msg(counters_ind_msg_t* src)
{
  assert(src != NULL);

  if(src->len > 0){
    assert(src->rb != NULL);
    free(src->rb);
  }
}

counters_ind_msg_t cp_counters_ind_msg(counters_ind_msg_t const* src)
{
  assert(src != NULL);

  counters_ind_msg_t cp = {.len = src->len, .tstamp = src->tstamp}; 

  if(cp.len > 0){
    cp.rb = calloc(cp.len, sizeof(counters_stats_t));
    assert(cp.rb != NULL && "memory exhausted");
    memcpy(cp.rb, src->rb, sizeof(counters_stats_t)*cp.len);
  }

  return cp;
}

bool eq_counters_ind_msg(counters_ind_msg_t* m0, counters_ind_msg_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if(m0->tstamp != m1->tstamp ||
      m0->len != m1->len)
    return false;

  for(uint32_t i =0; i < m0->len; ++i){
 counters_stats_t const* rb0 = &m0->rb[i];
 counters_stats_t const* rb1 = &m1->rb[i];
 if(
     rb0->dl_bitrate != rb1->dl_bitrate ||
     rb0->dl_errors != rb1->dl_errors ||
     rb0->dl_nas_transport != rb1->dl_nas_transport ||
     rb0->dl_tx != rb1->dl_tx ||
     rb0->dl_use_avg != rb1->dl_use_avg ||
     rb0->dl_use_max != rb1->dl_use_max ||
     rb0->dl_use_min != rb1->dl_use_min ||
     rb0->dl_use_online != rb1->dl_use_online ||
     rb0->nof_pdcp_pak != rb1->nof_pdcp_pak ||
     rb0->nof_fail_pdcp_pak != rb1->nof_fail_pdcp_pak ||
     rb0->dl_nof_volte_pak != rb1->dl_nof_volte_pak ||
     rb0->dl_nof_fail_volte_pak != rb1->dl_nof_fail_volte_pak ||
     rb0->dl_trafic_volte != rb1->dl_trafic_volte ||
     rb0->erab_count_avg != rb1->erab_count_avg ||
     rb0->erab_count_max != rb1->erab_count_max ||
     rb0->erab_count_min != rb1->erab_count_min ||
     rb0->erab_modify_request != rb1->erab_modify_request ||
     rb0->erab_modify_response != rb1->erab_modify_response ||
     rb0->erab_release_command != rb1->erab_release_command ||
     rb0->erab_release_response != rb1->erab_release_response ||
     rb0->erab_setup_request != rb1->erab_setup_request ||
     rb0->erab_setup_response != rb1->erab_setup_response ||
     rb0->volte_erab_attempts != rb1->volte_erab_attempts ||
     rb0->number_of_rach != rb1->number_of_rach ||
     rb0->number_of_rar != rb1->number_of_rar ||
     rb0->max_time_adv != rb1->max_time_adv ||
     rb0->call_duration != rb1->call_duration ||
     rb0->rrc_connection_reconfiguration != rb1->rrc_connection_reconfiguration ||
     rb0->rrc_connection_reconfiguration_complete != rb1->rrc_connection_reconfiguration_complete ||
     rb0->rrc_connection_reestablishment != rb1->rrc_connection_reestablishment || 
     rb0->rrc_connection_reestablishment_reject != rb1->rrc_connection_reestablishment_reject   ||
     rb0->rrc_connection_reestablishment_request != rb1->rrc_connection_reestablishment_request ||  
     rb0->rrc_connection_reconfiguration_modify_bearer != rb1->rrc_connection_reconfiguration_modify_bearer  ||
     rb0->rrc_connection_reconfiguration_new_bearer != rb1->rrc_connection_reconfiguration_new_bearer ||
     rb0->rrc_connection_reconfiguration_rem_bearer != rb1->rrc_connection_reconfiguration_rem_bearer ||
     rb0->rrc_connection_reconfiguration_handover != rb1->rrc_connection_reconfiguration_handover ||
     rb0->rrc_connection_reconfiguration_mac_ce != rb1->rrc_connection_reconfiguration_mac_ce ||
     rb0->rrc_connection_reject != rb1->rrc_connection_reject ||
     rb0->rrc_connection_release != rb1->rrc_connection_release ||
     rb0->rrc_connection_request != rb1->rrc_connection_request ||
     rb0->rrc_connection_setup != rb1->rrc_connection_setup ||
     rb0->rrc_connection_setup_complete != rb1->rrc_connection_setup_complete ||
     rb0->rrc_dl_information_transfer != rb1->rrc_dl_information_transfer ||
     rb0->rrc_security_mode_command != rb1->rrc_security_mode_command ||
     rb0->rrc_security_mode_complete != rb1->rrc_security_mode_complete ||
     rb0->rrc_security_mode_failure != rb1->rrc_security_mode_failure ||
     rb0->rrc_ue_capability_enquiry != rb1->rrc_ue_capability_enquiry ||
     rb0->rrc_ue_capability_information != rb1->rrc_ue_capability_information ||
     rb0->rrc_ul_information_transfer != rb1->rrc_ul_information_transfer ||
     rb0->csfb_attempt != rb1->csfb_attempt ||
     rb0->csfb_success != rb1->csfb_success ||
     rb0->srvcc_attempt != rb1->srvcc_attempt ||
     rb0->srvcc_success != rb1->srvcc_success ||
     rb0->volte_qci1_attempts != rb1->volte_qci1_attempts ||
     rb0->success_volte_establishment_qci1 != rb1->success_volte_establishment_qci1 ||
     rb0->csfb_geran_attempt != rb1->csfb_geran_attempt ||
     rb0->csfb_umts_attempt != rb1->csfb_umts_attempt ||
     rb0->handover_success_inter_sec != rb1->handover_success_inter_sec ||
     rb0->handover_request_inter_sec != rb1->handover_request_inter_sec ||
     rb0->s1_setup_failure != rb1->s1_setup_failure ||
     rb0->s1_setup_request != rb1->s1_setup_request ||
     rb0->s1_setup_response != rb1->s1_setup_response ||
     rb0->handover_request != rb1->handover_request   ||
     rb0->handover_request_acknowledge != rb1->handover_request_acknowledge ||  
     rb0->handover_send_notify != rb1->handover_send_notify  ||
     rb0->handover_success != rb1->handover_success ||
     rb0->handover_failure != rb1->handover_failure ||
     rb0->ue_context_modify_response != rb1->ue_context_modify_response ||
     rb0->handover_success_volte != rb1->handover_success_volte ||
     rb0->ue_context_modify_failure != rb1->ue_context_modify_failure ||
     rb0->ue_context_modify_request != rb1->ue_context_modify_request ||
     rb0->ue_context_release_command != rb1->ue_context_release_command ||
     rb0->ue_context_release_complete != rb1->ue_context_release_complete ||
     rb0->ue_context_release_request != rb1->ue_context_release_request ||
     rb0->ue_context_setup_complete != rb1->ue_context_setup_complete ||
     rb0->ue_count_avg != rb1->ue_count_avg ||
     rb0->ue_count_max != rb1->ue_count_max ||
     rb0->ue_count_min != rb1->ue_count_min ||
     rb0->ue_count_online != rb1->ue_count_online ||
     rb0->initial_context_setup_request != rb1->initial_context_setup_request ||
     rb0->initial_context_setup_failure != rb1->initial_context_setup_failure ||
     rb0->initial_context_setup_response != rb1->initial_context_setup_response ||
     rb0->initial_ue_message != rb1->initial_ue_message ||
     rb0->mme_status_transfer != rb1->mme_status_transfer ||
     rb0->ul_bitrate != rb1->ul_bitrate ||
     rb0->ul_errors != rb1->ul_errors ||
     rb0->ul_nas_transport != rb1->ul_nas_transport ||
     rb0->ul_tx != rb1->ul_tx ||
     rb0->ul_use_avg != rb1->ul_use_avg ||
     rb0->ul_use_max != rb1->ul_use_max ||
     rb0->ul_use_min != rb1->ul_use_min ||
     rb0->ul_use_online != rb1->ul_use_online ||
     rb0->ul_interference != rb1->ul_interference ||
     rb0->ul_trafic_volte != rb1->ul_trafic_volte 
     )
  return false;
  }
    return true;
}

//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

void free_counters_call_proc_id(counters_call_proc_id_t* src)
{
  // Note that the src could be NULL
  free(src);
}

counters_call_proc_id_t cp_counters_call_proc_id( counters_call_proc_id_t* src)
{
  assert(src != NULL); 
  counters_call_proc_id_t dst = {0};

  dst.dummy = src->dummy;

  return dst;
}

bool eq_counters_call_proc_id(counters_call_proc_id_t* m0, counters_call_proc_id_t* m1)
{
  if(m0 == NULL && m1 == NULL)
    return true;
  if(m0 == NULL)
    return false;
  if(m1 == NULL)
    return false;

  if(m0->dummy != m1->dummy)
    return false;

  return true;
}


//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////

void free_counters_ctrl_hdr( counters_ctrl_hdr_t* src)
{

  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 
}

counters_ctrl_hdr_t cp_counters_ctrl_hdr(counters_ctrl_hdr_t* src)
{
  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 
  counters_ctrl_hdr_t ret = {0};
  return ret;
}

bool eq_counters_ctrl_hdr(counters_ctrl_hdr_t* m0, counters_ctrl_hdr_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


void free_counters_ctrl_msg( counters_ctrl_msg_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
}

counters_ctrl_msg_t cp_counters_ctrl_msg(counters_ctrl_msg_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  counters_ctrl_msg_t ret = {0};
  return ret;
}

bool eq_counters_ctrl_msg(counters_ctrl_msg_t* m0, counters_ctrl_msg_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

void free_counters_ctrl_out(counters_ctrl_out_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
}

counters_ctrl_out_t cp_counters_ctrl_out(counters_ctrl_out_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  counters_ctrl_out_t ret = {0}; 
  return ret;
}

bool eq_counters_ctrl_out(counters_ctrl_out_t* m0, counters_ctrl_out_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

void free_counters_func_def( counters_func_def_t* src)
{
  assert(src != NULL);
  free(src->buf);
}

counters_func_def_t cp_counters_func_def(counters_func_def_t const* src)
{
  assert(src != NULL);

  counters_func_def_t dst = {.len = src->len};
  if(src->len > 0){
    dst.buf = calloc(dst.len, sizeof(uint8_t)); 
    assert(dst.buf != NULL && "memory exhausted");
    memcpy(dst.buf, src->buf, dst.len);
  }

  return dst;
}

bool eq_counters_func_def(counters_func_def_t const* m0, counters_func_def_t const* m1)
{
  if(m0 == m1)
    return true;

  if(m0 == NULL || m1 == NULL)
    return false;

  if(m0->len != m1->len)
    return false;

  int rc = memcmp(m0, m1, m0->len);
  return rc == 0;
}


///////////////
// RIC Indication
///////////////

void free_counters_ind_data(counters_ind_data_t* ind)
{
  assert(ind != NULL);
  
  free_counters_ind_hdr(&ind->hdr);
  free_counters_ind_msg(&ind->msg);
  free_counters_call_proc_id(ind->proc_id); 
}

counters_ind_data_t cp_counters_ind_data(counters_ind_data_t const* src)
{
  assert(src != NULL);
  counters_ind_data_t dst = {0};

  dst.hdr = cp_counters_ind_hdr(&src->hdr);
  dst.msg = cp_counters_ind_msg(&src->msg);

  if(src->proc_id != NULL){
    dst.proc_id = malloc(sizeof(counters_call_proc_id_t));
    assert(dst.proc_id != NULL && "Memory exhausted");
    *dst.proc_id = cp_counters_call_proc_id(src->proc_id);
  }

  return dst;
}



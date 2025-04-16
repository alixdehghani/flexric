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


#include "uetrace_data_ie.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

void free_uetrace_event_trigger(uetrace_event_trigger_t* src)
{
  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 
}

uetrace_event_trigger_t cp_uetrace_event_trigger( uetrace_event_trigger_t* src)
{
  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 

  uetrace_event_trigger_t et = {0};
  return et;
}

bool eq_uetrace_event_trigger(uetrace_event_trigger_t* m0, uetrace_event_trigger_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

void free_uetrace_action_def(uetrace_action_def_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
}

uetrace_action_def_t cp_uetrace_action_def(uetrace_action_def_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  uetrace_action_def_t ad = {0};
  return ad;
}

bool eq_uetrace_action_def(uetrace_event_trigger_t* m0,  uetrace_event_trigger_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////


void free_uetrace_ind_hdr(uetrace_ind_hdr_t* src)
{
  assert(src != NULL);
  (void)src;
}

uetrace_ind_hdr_t cp_uetrace_ind_hdr(uetrace_ind_hdr_t const* src)
{
  assert(src != NULL);
  uetrace_ind_hdr_t dst = {0}; 
  dst.dummy = src->dummy;
  return dst;
}

bool eq_uetrace_ind_hdr(uetrace_ind_hdr_t* m0, uetrace_ind_hdr_t* m1)
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

void free_uetrace_ind_msg(uetrace_ind_msg_t* src)
{
  assert(src != NULL);

  if(src->len > 0){
    assert(src->rb != NULL);
    free(src->rb);
  }
}

uetrace_ind_msg_t cp_uetrace_ind_msg(uetrace_ind_msg_t const* src)
{
  assert(src != NULL);

  uetrace_ind_msg_t cp = {.len = src->len, .tstamp = src->tstamp}; 

  if(cp.len > 0){
    cp.rb = calloc(cp.len, sizeof(uetrace_stats_t));
    assert(cp.rb != NULL && "memory exhausted");
    memcpy(cp.rb, src->rb, sizeof(uetrace_stats_t)*cp.len);
  }

  return cp;
}

bool eq_uetrace_ind_msg(uetrace_ind_msg_t* m0, uetrace_ind_msg_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if(m0->tstamp != m1->tstamp ||
      m0->len != m1->len)
    return false;

  for(uint32_t i =0; i < m0->len; ++i){
 uetrace_stats_t const* rb0 = &m0->rb[i];
 uetrace_stats_t const* rb1 = &m1->rb[i];
 if(
     rb0->rnti != rb1->rnti   ||
     rb0->bsr != rb1->bsr ||  
     rb0->dl_bler != rb1->dl_bler  ||
     rb0->dl_cqi != rb1->dl_cqi ||
     rb0->dl_mcs != rb1->dl_mcs ||
     rb0->dl_pmi != rb1->dl_pmi ||
     rb0->dl_rate != rb1->dl_rate ||
     rb0->dl_ri != rb1->dl_ri ||
     rb0->phr != rb1->phr ||
     rb0->snr_pucch != rb1->snr_pucch ||
     rb0->ul_bler != rb1->ul_bler ||
     rb0->ul_mcs != rb1->ul_mcs ||
     rb0->ul_rate != rb1->ul_rate ||
     rb0->snr != rb1->snr
     )
  return false;
  }
    return true;
}

//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

void free_uetrace_call_proc_id(uetrace_call_proc_id_t* src)
{
  // Note that the src could be NULL
  free(src);
}

uetrace_call_proc_id_t cp_uetrace_call_proc_id( uetrace_call_proc_id_t* src)
{
  assert(src != NULL); 
  uetrace_call_proc_id_t dst = {0};

  dst.dummy = src->dummy;

  return dst;
}

bool eq_uetrace_call_proc_id(uetrace_call_proc_id_t* m0, uetrace_call_proc_id_t* m1)
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

void free_uetrace_ctrl_hdr( uetrace_ctrl_hdr_t* src)
{

  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 
}

uetrace_ctrl_hdr_t cp_uetrace_ctrl_hdr(uetrace_ctrl_hdr_t* src)
{
  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 
  uetrace_ctrl_hdr_t ret = {0};
  return ret;
}

bool eq_uetrace_ctrl_hdr(uetrace_ctrl_hdr_t* m0, uetrace_ctrl_hdr_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


void free_uetrace_ctrl_msg( uetrace_ctrl_msg_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
}

uetrace_ctrl_msg_t cp_uetrace_ctrl_msg(uetrace_ctrl_msg_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  uetrace_ctrl_msg_t ret = {0};
  return ret;
}

bool eq_uetrace_ctrl_msg(uetrace_ctrl_msg_t* m0, uetrace_ctrl_msg_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

void free_uetrace_ctrl_out(uetrace_ctrl_out_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
}

uetrace_ctrl_out_t cp_uetrace_ctrl_out(uetrace_ctrl_out_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  uetrace_ctrl_out_t ret = {0}; 
  return ret;
}

bool eq_uetrace_ctrl_out(uetrace_ctrl_out_t* m0, uetrace_ctrl_out_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

void free_uetrace_func_def( uetrace_func_def_t* src)
{
  assert(src != NULL);
  free(src->buf);
}

uetrace_func_def_t cp_uetrace_func_def(uetrace_func_def_t const* src)
{
  assert(src != NULL);

  uetrace_func_def_t dst = {.len = src->len};
  if(src->len > 0){
    dst.buf = calloc(dst.len, sizeof(uint8_t)); 
    assert(dst.buf != NULL && "memory exhausted");
    memcpy(dst.buf, src->buf, dst.len);
  }

  return dst;
}

bool eq_uetrace_func_def(uetrace_func_def_t const* m0, uetrace_func_def_t const* m1)
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

void free_uetrace_ind_data(uetrace_ind_data_t* ind)
{
  assert(ind != NULL);
  
  free_uetrace_ind_hdr(&ind->hdr);
  free_uetrace_ind_msg(&ind->msg);
  free_uetrace_call_proc_id(ind->proc_id); 
}

uetrace_ind_data_t cp_uetrace_ind_data(uetrace_ind_data_t const* src)
{
  assert(src != NULL);
  uetrace_ind_data_t dst = {0};

  dst.hdr = cp_uetrace_ind_hdr(&src->hdr);
  dst.msg = cp_uetrace_ind_msg(&src->msg);

  if(src->proc_id != NULL){
    dst.proc_id = malloc(sizeof(uetrace_call_proc_id_t));
    assert(dst.proc_id != NULL && "Memory exhausted");
    *dst.proc_id = cp_uetrace_call_proc_id(src->proc_id);
  }

  return dst;
}



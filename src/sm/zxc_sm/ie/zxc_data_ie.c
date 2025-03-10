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


#include "zxc_data_ie.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

void free_zxc_event_trigger(zxc_event_trigger_t* src)
{
  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 
}

zxc_event_trigger_t cp_zxc_event_trigger( zxc_event_trigger_t* src)
{
  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 

  zxc_event_trigger_t et = {0};
  return et;
}

bool eq_zxc_event_trigger(zxc_event_trigger_t* m0, zxc_event_trigger_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

void free_zxc_action_def(zxc_action_def_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
}

zxc_action_def_t cp_zxc_action_def(zxc_action_def_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  zxc_action_def_t ad = {0};
  return ad;
}

bool eq_zxc_action_def(zxc_event_trigger_t* m0,  zxc_event_trigger_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////


void free_zxc_ind_hdr(zxc_ind_hdr_t* src)
{
  assert(src != NULL);
  (void)src;
}

zxc_ind_hdr_t cp_zxc_ind_hdr(zxc_ind_hdr_t const* src)
{
  assert(src != NULL);
  zxc_ind_hdr_t dst = {0}; 
  dst.dummy = src->dummy;
  return dst;
}

bool eq_zxc_ind_hdr(zxc_ind_hdr_t* m0, zxc_ind_hdr_t* m1)
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

void free_zxc_ind_msg(zxc_ind_msg_t* src)
{
  assert(src != NULL);

  if(src->len > 0){
    assert(src->rb != NULL);
    free(src->rb);
  }
}

zxc_ind_msg_t cp_zxc_ind_msg(zxc_ind_msg_t const* src)
{
  assert(src != NULL);

  zxc_ind_msg_t cp = {.len = src->len, .tstamp = src->tstamp}; 

  if(cp.len > 0){
    cp.rb = calloc(cp.len, sizeof(zxc_radio_bearer_stats_t));
    assert(cp.rb != NULL && "memory exhausted");
    memcpy(cp.rb, src->rb, sizeof(zxc_radio_bearer_stats_t)*cp.len);
  }

  return cp;
}

bool eq_zxc_ind_msg(zxc_ind_msg_t* m0, zxc_ind_msg_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if(m0->tstamp != m1->tstamp ||
      m0->len != m1->len)
    return false;

  for(uint32_t i =0; i < m0->len; ++i){
 zxc_radio_bearer_stats_t const* rb0 = &m0->rb[i];
 zxc_radio_bearer_stats_t const* rb1 = &m1->rb[i];
 if(
     rb0->txpdu_pkts != rb1->txpdu_pkts   ||
     rb0->txpdu_bytes != rb1->txpdu_bytes ||  
     rb0->txpdu_wt_ms != rb1->txpdu_wt_ms  ||
     rb0->txpdu_dd_pkts != rb1->txpdu_dd_pkts ||
     rb0->txpdu_dd_bytes != rb1->txpdu_dd_bytes ||
     rb0->txpdu_retx_pkts != rb1->txpdu_retx_pkts ||
     rb0->txpdu_retx_bytes != rb1->txpdu_retx_bytes ||
     rb0->txpdu_segmented != rb1->txpdu_segmented ||
     rb0->txpdu_status_pkts != rb1->txpdu_status_pkts ||
     rb0->txpdu_status_bytes != rb1->txpdu_status_bytes ||
     rb0->txbuf_occ_bytes != rb1-> txbuf_occ_bytes ||
     rb0->txbuf_occ_pkts != rb1->txbuf_occ_pkts ||
     rb0->rxpdu_pkts != rb1->rxpdu_pkts ||
     rb0->rxpdu_bytes != rb1->rxpdu_bytes ||
     rb0->rxpdu_dup_pkts != rb1->rxpdu_dup_pkts ||
     rb0->rxpdu_dup_bytes != rb1->rxpdu_dup_bytes ||
     rb0->rxpdu_dd_pkts != rb1->rxpdu_dd_pkts ||
     rb0->rxpdu_dd_bytes != rb1->rxpdu_dd_bytes ||
     rb0->rxpdu_ow_pkts != rb1->rxpdu_ow_pkts ||
     rb0->rxpdu_ow_bytes != rb1->rxpdu_ow_bytes ||
     rb0->rxpdu_status_pkts != rb1->rxpdu_status_pkts ||
     rb0->rxpdu_status_bytes != rb1->rxpdu_status_bytes ||
     rb0->rxbuf_occ_bytes != rb1->rxbuf_occ_bytes ||
     rb0->rxbuf_occ_pkts != rb1->rxbuf_occ_pkts ||
     rb0->txsdu_pkts != rb1->txsdu_pkts ||
     rb0->txsdu_bytes != rb1->txsdu_bytes ||
     rb0->rxsdu_pkts != rb1->rxsdu_pkts ||
     rb0->rxsdu_bytes != rb1->rxsdu_bytes ||
     rb0->rxsdu_dd_pkts != rb1->rxsdu_dd_pkts ||
     rb0->rxsdu_dd_bytes != rb1->rxsdu_dd_bytes ||
     rb0->rnti != rb1->rnti ||
     rb0->mode != rb1->mode ||
     rb0->rbid != rb1->rbid 
     )
  return false;
  }
    return true;
}

//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

void free_zxc_call_proc_id(zxc_call_proc_id_t* src)
{
  // Note that the src could be NULL
  free(src);
}

zxc_call_proc_id_t cp_zxc_call_proc_id( zxc_call_proc_id_t* src)
{
  assert(src != NULL); 
  zxc_call_proc_id_t dst = {0};

  dst.dummy = src->dummy;

  return dst;
}

bool eq_zxc_call_proc_id(zxc_call_proc_id_t* m0, zxc_call_proc_id_t* m1)
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

void free_zxc_ctrl_hdr( zxc_ctrl_hdr_t* src)
{

  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 
}

zxc_ctrl_hdr_t cp_zxc_ctrl_hdr(zxc_ctrl_hdr_t* src)
{
  assert(src != NULL);
  assert(0!=0 && "Not implemented" ); 
  zxc_ctrl_hdr_t ret = {0};
  return ret;
}

bool eq_zxc_ctrl_hdr(zxc_ctrl_hdr_t* m0, zxc_ctrl_hdr_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


void free_zxc_ctrl_msg( zxc_ctrl_msg_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
}

zxc_ctrl_msg_t cp_zxc_ctrl_msg(zxc_ctrl_msg_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  zxc_ctrl_msg_t ret = {0};
  return ret;
}

bool eq_zxc_ctrl_msg(zxc_ctrl_msg_t* m0, zxc_ctrl_msg_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

void free_zxc_ctrl_out(zxc_ctrl_out_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
}

zxc_ctrl_out_t cp_zxc_ctrl_out(zxc_ctrl_out_t* src)
{
  assert(src != NULL);

  assert(0!=0 && "Not implemented" ); 
  zxc_ctrl_out_t ret = {0}; 
  return ret;
}

bool eq_zxc_ctrl_out(zxc_ctrl_out_t* m0, zxc_ctrl_out_t* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  assert(0!=0 && "Not implemented" ); 

  return true;
}


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

void free_zxc_func_def( zxc_func_def_t* src)
{
  assert(src != NULL);
  free(src->buf);
}

zxc_func_def_t cp_zxc_func_def(zxc_func_def_t const* src)
{
  assert(src != NULL);

  zxc_func_def_t dst = {.len = src->len};
  if(src->len > 0){
    dst.buf = calloc(dst.len, sizeof(uint8_t)); 
    assert(dst.buf != NULL && "memory exhausted");
    memcpy(dst.buf, src->buf, dst.len);
  }

  return dst;
}

bool eq_zxc_func_def(zxc_func_def_t const* m0, zxc_func_def_t const* m1)
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

void free_zxc_ind_data(zxc_ind_data_t* ind)
{
  assert(ind != NULL);
  
  free_zxc_ind_hdr(&ind->hdr);
  free_zxc_ind_msg(&ind->msg);
  free_zxc_call_proc_id(ind->proc_id); 
}

zxc_ind_data_t cp_zxc_ind_data(zxc_ind_data_t const* src)
{
  assert(src != NULL);
  zxc_ind_data_t dst = {0};

  dst.hdr = cp_zxc_ind_hdr(&src->hdr);
  dst.msg = cp_zxc_ind_msg(&src->msg);

  if(src->proc_id != NULL){
    dst.proc_id = malloc(sizeof(zxc_call_proc_id_t));
    assert(dst.proc_id != NULL && "Memory exhausted");
    *dst.proc_id = cp_zxc_call_proc_id(src->proc_id);
  }

  return dst;
}



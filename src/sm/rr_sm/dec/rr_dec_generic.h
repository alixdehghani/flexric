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


#ifndef RR_DECRYPTION_GENERIC
#define RR_DECRYPTION_GENERIC 

#include "rr_dec_asn.h"
#include "rr_dec_fb.h"
#include "rr_dec_plain.h"

/////////////////////////////////////////////////////////////////////
// 9 Information Elements that are interpreted by the SM according
// to ORAN-WG3.E2SM-v01.00.00 Technical Specification
/////////////////////////////////////////////////////////////////////


#define rr_dec_event_trigger(T,U,V) _Generic ((T), \
                           rr_enc_plain_t*: rr_dec_event_trigger_plain, \
                           rr_enc_asn_t*: rr_dec_event_trigger_asn,\
                           rr_enc_fb_t*: rr_dec_event_trigger_fb,\
                           default: rr_dec_event_trigger_plain) (U,V)

#define rr_dec_action_def(T,U,V) _Generic ((T), \
                           rr_enc_plain_t*: rr_dec_action_def_plain, \
                           rr_enc_asn_t*: rr_dec_action_def_asn, \
                           rr_enc_fb_t*: rr_dec_action_def_fb, \
                           default:  rr_dec_action_def_plain) (U,V)

#define rr_dec_ind_hdr(T,U,V) _Generic ((T), \
                           rr_enc_plain_t*: rr_dec_ind_hdr_plain , \
                           rr_enc_asn_t*: rr_dec_ind_hdr_asn, \
                           rr_enc_fb_t*: rr_dec_ind_hdr_fb, \
                           default:  rr_dec_ind_hdr_plain) (U,V)

#define rr_dec_ind_msg(T,U,V) _Generic ((T), \
                           rr_enc_plain_t*: rr_dec_ind_msg_plain , \
                           rr_enc_asn_t*: rr_dec_ind_msg_asn, \
                           rr_enc_fb_t*: rr_dec_ind_msg_fb, \
                           default:  rr_dec_ind_msg_plain) (U,V)

#define rr_dec_call_proc_id(T,U,V) _Generic ((T), \
                           rr_enc_plain_t*: rr_dec_call_proc_id_plain , \
                           rr_enc_asn_t*: rr_dec_call_proc_id_asn, \
                           rr_enc_fb_t*: rr_dec_call_proc_id_fb, \
                           default:  rr_dec_call_proc_id_plain) (U,V)

#define rr_dec_ctrl_hdr(T,U,V) _Generic ((T), \
                           rr_enc_plain_t*: rr_dec_ctrl_hdr_plain , \
                           rr_enc_asn_t*: rr_dec_ctrl_hdr_asn, \
                           rr_enc_fb_t*: rr_dec_ctrl_hdr_fb, \
                           default: rr_dec_ctrl_hdr_plain) (U,V)

#define rr_dec_ctrl_msg(T,U,V) _Generic ((T), \
                           rr_enc_plain_t*: rr_dec_ctrl_msg_plain , \
                           rr_enc_asn_t*: rr_dec_ctrl_msg_asn, \
                           rr_enc_fb_t*: rr_dec_ctrl_msg_fb, \
                           default:  rr_dec_ctrl_msg_plain) (U,V)

#define rr_dec_ctrl_out(T,U,V) _Generic ((T), \
                           rr_enc_plain_t*: rr_dec_ctrl_out_plain , \
                           rr_enc_asn_t*: rr_dec_ctrl_out_asn, \
                           rr_enc_fb_t*: rr_dec_ctrl_out_fb, \
                           default:  rr_dec_ctrl_out_plain) (U,V)

#define rr_dec_func_def(T,U,V) _Generic ((T), \
                           rr_enc_plain_t*: rr_dec_func_def_plain, \
                           rr_enc_asn_t*: rr_dec_func_def_asn, \
                           rr_enc_fb_t*:  rr_dec_func_def_fb, \
                           default:  rr_dec_func_def_plain) (U,V)

#endif


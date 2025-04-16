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


#ifndef SIB2_DECRYPTION_ASN_H
#define SIB2_DECRYPTION_ASN_H

#include <stddef.h>
#include "../ie/sib2_data_ie.h"


sib2_event_trigger_t sib2_dec_event_trigger_asn(size_t len, uint8_t const ev_tr[len]);

sib2_action_def_t sib2_dec_action_def_asn(size_t len, uint8_t const action_def[len]);

sib2_ind_hdr_t sib2_dec_ind_hdr_asn(size_t len, uint8_t const ind_hdr[len]); 

sib2_ind_msg_t sib2_dec_ind_msg_asn(size_t len, uint8_t const ind_msg[len]); 

sib2_call_proc_id_t sib2_dec_call_proc_id_asn(size_t len, uint8_t const call_proc_id[len]);

sib2_ctrl_hdr_t sib2_dec_ctrl_hdr_asn(size_t len, uint8_t const ctrl_hdr[len]); 

sib2_ctrl_msg_t sib2_dec_ctrl_msg_asn(size_t len, uint8_t const ctrl_msg[len]); 

sib2_ctrl_out_t sib2_dec_ctrl_out_asn(size_t len, uint8_t const ctrl_out[len]); 

sib2_func_def_t sib2_dec_func_def_asn(size_t len, uint8_t const func_def[len]);

#endif


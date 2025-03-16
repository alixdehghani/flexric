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



#ifndef ENB_CONF_ENCRYPTION_PLAIN_H
#define ENB_CONF_ENCRYPTION_PLAIN_H 

#include "../../../util/byte_array.h"
#include "../ie/enb_conf_data_ie.h"


// Used for static polymorphism. 
// View enb_conf_enc_generic file
typedef struct{

} enb_conf_enc_plain_t;


byte_array_t enb_conf_enc_event_trigger_plain(enb_conf_event_trigger_t const* event_trigger);

byte_array_t enb_conf_enc_action_def_plain(enb_conf_action_def_t const*);

byte_array_t enb_conf_enc_ind_hdr_plain(enb_conf_ind_hdr_t const*); 

byte_array_t enb_conf_enc_ind_msg_plain(enb_conf_ind_msg_t const*); 

byte_array_t enb_conf_enc_call_proc_id_plain(enb_conf_call_proc_id_t const*); 

byte_array_t enb_conf_enc_ctrl_hdr_plain(enb_conf_ctrl_hdr_t const*); 

byte_array_t enb_conf_enc_ctrl_msg_plain(enb_conf_ctrl_msg_t const*); 

byte_array_t enb_conf_enc_ctrl_out_plain(enb_conf_ctrl_out_t const*); 

byte_array_t enb_conf_enc_func_def_plain(enb_conf_func_def_t const*);

#endif


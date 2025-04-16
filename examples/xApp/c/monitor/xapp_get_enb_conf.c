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

#include "../../../../src/xApp/e42_xapp_api.h"
#include "../../../../src/util/alg_ds/alg/defer.h"
#include "../../../../src/util/time_now_us.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>



static uint64_t cnt_enb_conf;


// ENB CONFIG!
static void sm_cb_enb_conf(sm_ag_if_rd_t const *rd)
{
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);

  assert(rd->ind.type == ENB_CONF_STATS_V0);
  if(!rd->ind.enb_conf.msg.len == 0)
  {
    for (int i = 0; i < rd->ind.enb_conf.msg.len; i++)
    {
      printf("enb_id %s\n", rd->ind.enb_conf.msg.rb[i].enb_id);
    }
    
    
  }

  int64_t now = time_now_us();

  if (cnt_enb_conf % 1024 == 0)
    printf("ENB_CONF ind_msg latency = %ld μs\n", now - rd->ind.enb_conf.msg.tstamp);
  cnt_enb_conf++;
}



int main(int argc, char *argv[])
{
  fr_args_t args = init_fr_args(argc, argv);

  // Init the xApp
  init_xapp_api(&args);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });

  assert(nodes.len > 0);

  printf("Connected E2 nodes = %d\n", nodes.len);

  const char *i_1 = "1_ms";
  sm_ans_xapp_t *enb_conf_handle = NULL;

  if (nodes.len > 0)
  {
    enb_conf_handle = calloc(nodes.len, sizeof(sm_ans_xapp_t));
    assert(enb_conf_handle != NULL);
  }

  for (int i = 0; i < nodes.len; i++)
  {
    e2_node_connected_xapp_t *n = &nodes.n[i];
    for (size_t j = 0; j < n->len_rf; j++)
      printf("Registered node %d ran func id = %d \n ", i, n->rf[j].id);

    if (n->id.type == ngran_gNB || n->id.type == ngran_eNB)
    {
      enb_conf_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 150, (void *)i_1, sm_cb_enb_conf);
      assert(enb_conf_handle[i].success == true);
    }
    else if (n->id.type == ngran_gNB_CU || n->id.type == ngran_gNB_CUUP)
    {
      // assert(gtp_handle[i].success == true);
    }
    else if (n->id.type == ngran_gNB_DU)
    {
      // assert(rlc_handle[i].success == true);

    }
  }

  sleep(5);

  for (int i = 0; i < nodes.len; ++i)
  {
    // Remove the handle previously returned
    if (enb_conf_handle[i].u.handle != 0)
      rm_report_sm_xapp_api(enb_conf_handle[i].u.handle);
  }

  if (nodes.len > 0)
  {
    free(enb_conf_handle);
  }

  // Stop the xApp
  while (try_stop_xapp_api() == false)
    usleep(1000);

  printf("Test xApp run SUCCESSFULLY\n");
}

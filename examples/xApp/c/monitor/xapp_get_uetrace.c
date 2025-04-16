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

// static uint64_t cnt_mac;

// static void sm_cb_mac(sm_ag_if_rd_t const *rd)
// {
//   assert(rd != NULL);
//   assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
//   assert(rd->ind.type == MAC_STATS_V0);

//   int64_t now = time_now_us();
//   if (cnt_mac % 1024 == 0)
//     printf("MAC ind_msg latency = %ld μs\n", now - rd->ind.mac.msg.tstamp);
//   cnt_mac++;
// }

// static uint64_t cnt_rlc;

// static uint64_t cnt_zxc;
static uint64_t cnt_uetrace;
// static uint64_t cnt_enb_conf;

// UETRACE !
static void sm_cb_uetrace(sm_ag_if_rd_t const *rd)
{
    assert(rd != NULL);
    assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);

    assert(rd->ind.type == UETRACE_STATS_V0);
    printf("%-5s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "RNTI", "BSR", "DL_BLER", "DL_CQI", "DL_MCS", "DL_PMI", "DL_RATE", "DL_RI", "PHR", "SNR_PUCCH", "UL_BLER", "UL_MCS", "UL_RATE");
    for (int i = 0; i < rd->ind.counters.msg.len; i++)
    {
        uetrace_stats_t *rb = &rd->ind.uetrace.msg.rb[i];
        printf("%-5d %-10.2f %-10.2f %-10.2f %-10.2f %-10.2f %-10.2f %-10.2f %-10.2f %-10.2f %-10.2f %-10.2f %-10.2f\n", rb->rnti, rb->bsr, rb->dl_bler, rb->dl_cqi, rb->dl_mcs, rb->dl_pmi, rb->dl_rate, rb->dl_ri, rb->phr, rb->snr_pucch, rb->ul_bler, rb->ul_mcs, rb->ul_rate, rb->snr);
    }

    if (!rd->ind.uetrace.msg.len == 0)
    {
    }

    int64_t now = time_now_us();

    if (cnt_uetrace % 1024 == 0)
    {
        printf("uetrace ind_msg latency = %ld μs\n", now - rd->ind.uetrace.msg.tstamp);
        cnt_uetrace++;
    }
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

    // uetrace indication
    const char *i_2 = "1_ms";
    sm_ans_xapp_t *uetrace_handle = NULL;

    if (nodes.len > 0)
    {
        uetrace_handle = calloc(nodes.len, sizeof(sm_ans_xapp_t));
        assert(uetrace_handle != NULL);
    }

    for (int i = 0; i < nodes.len; i++)
    {
        e2_node_connected_xapp_t *n = &nodes.n[i];
        for (size_t j = 0; j < n->len_rf; j++)
            printf("Registered node %d ran func id = %d \n ", i, n->rf[j].id);

        if (n->id.type == ngran_gNB || n->id.type == ngran_eNB)
        {
            // MAC Control is not yet implemented in OAI RAN

            uetrace_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 155, (void *)i_2, sm_cb_uetrace);
            assert(uetrace_handle[i].success == true);

            // enb_conf_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 150, (void *)i_1, sm_cb_enb_conf);
            // assert(enb_conf_handle[i].success == true);
        }
        else if (n->id.type == ngran_gNB_CU || n->id.type == ngran_gNB_CUUP)
        {
            // pdcp_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 144, (void *)i_2, sm_cb_pdcp);
            // assert(pdcp_handle[i].success == true);

            // gtp_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 148, (void *)i_3, sm_cb_gtp);
            // assert(gtp_handle[i].success == true);
        }
        else if (n->id.type == ngran_gNB_DU)
        {
            // mac_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 142, (void *)i_0, sm_cb_mac);
            // assert(mac_handle[i].success == true);

            // rlc_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 143, (void *)i_1, sm_cb_rlc);
            // assert(rlc_handle[i].success == true);
        }
    }

    sleep(35);

    for (int i = 0; i < nodes.len; ++i)
    {

        if (uetrace_handle[i].u.handle != 0)
            rm_report_sm_xapp_api(uetrace_handle[i].u.handle);
    }

    if (nodes.len > 0)
    {

        free(uetrace_handle);
    }

    // Stop the xApp
    while (try_stop_xapp_api() == false)
        usleep(1000);

    printf("Test xApp run SUCCESSFULLY\n");
}

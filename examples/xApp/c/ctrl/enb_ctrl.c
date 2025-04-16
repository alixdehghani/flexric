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
#include "../../../../src/xApp/db/sqlite3/sqlite3.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>




static int callback_enb_conf(void *data, int argc, char **argv, char **azColName) {
  enb_conf_stats_t *rb = (enb_conf_stats_t *)data;
  for (int i = 0; i < argc; i++) {
      if (strcmp(azColName[i], "bbu_addr") == 0) strcpy(rb->bbu_addr, argv[i]);
      if (strcmp(azColName[i], "cell_id") == 0) strcpy(rb->cell_id, argv[i]);
      if (strcmp(azColName[i], "enb_id") == 0) strcpy(rb->enb_id, argv[i]);
      if (strcmp(azColName[i], "geran_ci") == 0) strcpy(rb->geran_ci, argv[i]);
      if (strcmp(azColName[i], "geran_lac") == 0) strcpy(rb->geran_lac, argv[i]);
      if (strcmp(azColName[i], "gtp_bind_addr") == 0) strcpy(rb->gtp_bind_addr, argv[i]);
      if (strcmp(azColName[i], "mcc") == 0) strcpy(rb->mcc, argv[i]);
      if (strcmp(azColName[i], "mme_addr") == 0) strcpy(rb->mme_addr, argv[i]);
      if (strcmp(azColName[i], "mnc") == 0) strcpy(rb->mnc, argv[i]);
      if (strcmp(azColName[i], "n_prb") == 0) strcpy(rb->n_prb, argv[i]);
      if (strcmp(azColName[i], "name") == 0) strcpy(rb->name, argv[i]);
      if (strcmp(azColName[i], "nof_ports") == 0) strcpy(rb->nof_ports, argv[i]);
      if (strcmp(azColName[i], "p_a") == 0) strcpy(rb->p_a, argv[i]);
      if (strcmp(azColName[i], "phy_cell_id") == 0) strcpy(rb->phy_cell_id, argv[i]);
      if (strcmp(azColName[i], "rru_addr") == 0) strcpy(rb->rru_addr, argv[i]);
      if (strcmp(azColName[i], "s1c_bind_addr") == 0) strcpy(rb->s1c_bind_addr, argv[i]);
      if (strcmp(azColName[i], "sec1_pci") == 0) strcpy(rb->sec1_pci, argv[i]);
      if (strcmp(azColName[i], "sec1_x2_bind_addr") == 0) strcpy(rb->sec1_x2_bind_addr, argv[i]);
      if (strcmp(azColName[i], "sec2_pci") == 0) strcpy(rb->sec2_pci, argv[i]);
      if (strcmp(azColName[i], "sec2_x2_bind_addr") == 0) strcpy(rb->sec2_x2_bind_addr, argv[i]);
      if (strcmp(azColName[i], "sec3_x2_bind_addr") == 0) strcpy(rb->sec3_x2_bind_addr, argv[i]);
      if (strcmp(azColName[i], "sector_id") == 0) strcpy(rb->sector_id, argv[i]);
      if (strcmp(azColName[i], "tac") == 0) strcpy(rb->tac, argv[i]);
      if (strcmp(azColName[i], "tm") == 0) strcpy(rb->tm, argv[i]);
      if (strcmp(azColName[i], "ws_port") == 0) strcpy(rb->ws_port, argv[i]);
      if (strcmp(azColName[i], "drb_config") == 0) strcpy(rb->drb_config, argv[i]);
      if (strcmp(azColName[i], "mbms_sib_config") == 0) strcpy(rb->mbms_sib_config, argv[i]);
      if (strcmp(azColName[i], "rr_config") == 0) strcpy(rb->rr_config, argv[i]);
      if (strcmp(azColName[i], "sib_config") == 0) strcpy(rb->sib_config, argv[i]);
      if (strcmp(azColName[i], "accept_handover_ratio") == 0) strcpy(rb->accept_handover_ratio, argv[i]);
      if (strcmp(azColName[i], "agc_energy_b2x0") == 0) strcpy(rb->agc_energy_b2x0, argv[i]);
      if (strcmp(azColName[i], "alpha") == 0) strcpy(rb->alpha, argv[i]);
      if (strcmp(azColName[i], "bi") == 0) strcpy(rb->bi, argv[i]);
      if (strcmp(azColName[i], "bi_flag") == 0) strcpy(rb->bi_flag, argv[i]);
      if (strcmp(azColName[i], "csfb_geran_list") == 0) strcpy(rb->csfb_geran_list, argv[i]);
      if (strcmp(azColName[i], "eea_pref_list") == 0) strcpy(rb->eea_pref_list, argv[i]);
      if (strcmp(azColName[i], "eia_pref_list") == 0) strcpy(rb->eia_pref_list, argv[i]);
      if (strcmp(azColName[i], "enable_mbsfn") == 0) strcpy(rb->enable_mbsfn, argv[i]);
      if (strcmp(azColName[i], "geran_csfb_flag") == 0) strcpy(rb->geran_csfb_flag, argv[i]);
      if (strcmp(azColName[i], "handover_drb_id") == 0) strcpy(rb->handover_drb_id, argv[i]);
      if (strcmp(azColName[i], "link_failure_nof_err") == 0) strcpy(rb->link_failure_nof_err, argv[i]);
      if (strcmp(azColName[i], "m1u_if_addr") == 0) strcpy(rb->m1u_if_addr, argv[i]);
      if (strcmp(azColName[i], "m1u_multiaddr") == 0) strcpy(rb->m1u_multiaddr, argv[i]);
      if (strcmp(azColName[i], "mbms_file") == 0) strcpy(rb->mbms_file, argv[i]);
      if (strcmp(azColName[i], "metrics_addr") == 0) strcpy(rb->metrics_addr, argv[i]);
      if (strcmp(azColName[i], "metrics_period_secs") == 0) strcpy(rb->metrics_period_secs, argv[i]);
      if (strcmp(azColName[i], "metrics_port") == 0) strcpy(rb->metrics_port, argv[i]);
      if (strcmp(azColName[i], "nof_phy_threads") == 0) strcpy(rb->nof_phy_threads, argv[i]);
      if (strcmp(azColName[i], "packet_size") == 0) strcpy(rb->packet_size, argv[i]);
      if (strcmp(azColName[i], "pusch_max_its") == 0) strcpy(rb->pusch_max_its, argv[i]);
      if (strcmp(azColName[i], "radio_unit") == 0) strcpy(rb->radio_unit, argv[i]);
      if (strcmp(azColName[i], "rrc_connected") == 0) strcpy(rb->rrc_connected, argv[i]);
      if (strcmp(azColName[i], "rrc_inactivity_timer") == 0) strcpy(rb->rrc_inactivity_timer, argv[i]);
      if (strcmp(azColName[i], "snr_pucch") == 0) strcpy(rb->snr_pucch, argv[i]);
      if (strcmp(azColName[i], "snr_pusch") == 0) strcpy(rb->snr_pusch, argv[i]);
      if (strcmp(azColName[i], "enable_gui") == 0) strcpy(rb->enable_gui, argv[i]);
      if (strcmp(azColName[i], "all_hex_limit") == 0) strcpy(rb->all_hex_limit, argv[i]);
      if (strcmp(azColName[i], "all_level") == 0) strcpy(rb->all_level, argv[i]);
      if (strcmp(azColName[i], "file_max_size") == 0) strcpy(rb->file_max_size, argv[i]);
      if (strcmp(azColName[i], "filename_log") == 0) strcpy(rb->filename_log, argv[i]);
      if (strcmp(azColName[i], "enable_pcap") == 0) strcpy(rb->enable_pcap, argv[i]);
      if (strcmp(azColName[i], "filename_pcap") == 0) strcpy(rb->filename_pcap, argv[i]);
      if (strcmp(azColName[i], "dl_earfcn") == 0) strcpy(rb->dl_earfcn, argv[i]);
      if (strcmp(azColName[i], "rx_gain") == 0) strcpy(rb->rx_gain, argv[i]);
      if (strcmp(azColName[i], "tx_gain") == 0) strcpy(rb->tx_gain, argv[i]);
      if (strcmp(azColName[i], "nof_ctrl_symbols") == 0) strcpy(rb->nof_ctrl_symbols, argv[i]);
      if (strcmp(azColName[i], "pdsch_max_mcs1") == 0) strcpy(rb->pdsch_max_mcs1, argv[i]);
      if (strcmp(azColName[i], "pdsch_max_mcs2") == 0) strcpy(rb->pdsch_max_mcs2, argv[i]);
      if (strcmp(azColName[i], "pusch_max_mcs") == 0) strcpy(rb->pusch_max_mcs, argv[i]);

  }
  return 0;
}

void fill_rb_from_db_enb_conf(enb_conf_stats_t *rb, const char *addr_db) {
  sqlite3 *db;
  char *err_msg = 0;
  
  // sqlite address should change 
  int rc = sqlite3_open(addr_db, &db);

  if (rc != SQLITE_OK) {
      fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));

      sqlite3_close(db);
      return;
  }

  const char *sql = "SELECT * FROM ENB_CONF LIMIT 1";

  rc = sqlite3_exec(db, sql, callback_enb_conf, rb, &err_msg);

  if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to select data: %s\n", err_msg);
      sqlite3_free(err_msg);
  }

  sqlite3_close(db);
}


int main(int argc, char *argv[])
{
  fr_args_t args = init_fr_args(argc, argv);

  char *addr_db = 0;
  if (asprintf(&addr_db, "%s%s", get_conf_db_dir(&args), get_conf_db_name(&args)) == -1) {
    // Handle error
    perror("asprintf");
    return 1;
}
  printf("[xApp]: DB filename = %s\n", addr_db);

  //Init the xApp
  init_xapp_api(&args);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });

  assert(nodes.len > 0);

  printf("Connected E2 nodes = %d\n", nodes.len);

  for (int i = 0; i < nodes.len; i++) {
    e2_node_connected_xapp_t* n = &nodes.n[i];

    for (size_t j = 0; j < n->len_rf; j++)
      printf("Registered node %d ran func id = %d \n ", i, n->rf[j].id);

    if(n->id.type == ngran_gNB || n->id.type == ngran_gNB_DU || n->id.type == ngran_eNB){

        enb_conf_stats_t enb_rb;
        fill_rb_from_db_enb_conf(&enb_rb, &addr_db);
      enb_conf_ctrl_req_data_t wr_enb = {.hdr.dummy = 124, .msg.len = 1, .msg.enb_rb = &enb_rb};
      sm_ans_xapp_t const a = control_sm_xapp_api(&nodes.n[i].id, 150, &wr_enb);
      assert(a.success == true);
     } else {
       printf("Cannot send MAC ctrl to if the E2 Node is not a GNB or DU\n");
    }
  }

 //Stop the xApp
  while(try_stop_xapp_api() == false)
    usleep(1000);

  printf("Test xApp run SUCCESSFULLY\n");
}


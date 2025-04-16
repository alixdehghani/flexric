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

#include "sqlite3_wrapper.h"
#include "../../../util/time_now_us.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

static
void create_table(sqlite3* db, char* sql)
{
  char* err_msg = NULL;
  int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
  assert(rc == SQLITE_OK && "Error while creating the DB. Check the err_msg string for further info" );
}

static
void create_mac_ue_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_mac = "DROP TABLE IF EXISTS MAC_UE;"
  "CREATE TABLE MAC_UE(tstamp INT CHECK(tstamp > 0)," 
                       "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"
                       "mcc INT,"
                       "mnc INT,"
                       "mnc_digit_len INT,"
                       "nb_id INT,"
                       "cu_du_id TEXT,"
                       "frame INT,"
                       "slot INT,"
                       "dl_aggr_tbs INT CHECK(dl_aggr_tbs  >= 0 AND dl_aggr_tbs < 18446744073709551615),"
                       "ul_aggr_tbs INT CHECK(ul_aggr_tbs  >= 0 AND ul_aggr_tbs < 18446744073709551615),"
                       "dl_aggr_bytes_sdus  INT CHECK(dl_aggr_bytes_sdus  >= 0 AND dl_aggr_bytes_sdus < 18446744073709551615),"
                       "ul_aggr_bytes_sdus INT CHECK(ul_aggr_bytes_sdus >= 0 AND ul_aggr_bytes_sdus < 18446744073709551615),"
                       "dl_curr_tbs INT CHECK(dl_curr_tbs >= 0 AND dl_curr_tbs < 18446744073709551615),"
                       "ul_curr_tbs INT CHECK(ul_curr_tbs >= 0 AND ul_curr_tbs < 18446744073709551615),"
                       "dl_sched_rb INT CHECK(dl_sched_rb >= 0 AND dl_sched_rb < 18446744073709551615),"
                       "ul_sched_rb INT CHECK(ul_sched_rb >= 0 AND ul_sched_rb < 18446744073709551615),"
                       "pusch_snr REAL CHECK(pusch_snr == NULL OR (pusch_snr >= 0 AND pusch_snr < 4294967296)),"
                       "pucch_snr REAL CHECK(pucch_snr == NULL OR (pucch_snr >= 0 AND pucch_snr < 4294967296)) ,"
                       "rnti INT  CHECK(rnti  >= 0 AND rnti < 4294967296 ),"
                       "dl_aggr_prb INT  CHECK(dl_aggr_prb >= 0 AND dl_aggr_prb < 4294967296 ),"
                       "ul_aggr_prb INT  CHECK(ul_aggr_prb >= 0 AND ul_aggr_prb < 4294967296 ),"
                       "dl_aggr_sdus INT  CHECK(dl_aggr_sdus >= 0 AND dl_aggr_sdus < 4294967296 ),"
                       "ul_aggr_sdus INT  CHECK(ul_aggr_sdus >= 0 AND ul_aggr_sdus < 4294967296 ),"
                       "dl_aggr_retx_prb  INT  CHECK(dl_aggr_retx_prb >= 0 AND dl_aggr_retx_prb < 4294967296 ),"
                       "ul_aggr_retx_prb  INT  CHECK(ul_aggr_retx_prb >= 0 AND ul_aggr_retx_prb < 4294967296 ),"
                       "wb_cqi INT  CHECK(wb_cqi >= 0 AND wb_cqi < 256 ),"
                       "dl_mcs1 INT  CHECK(dl_mcs1>= 0 AND dl_mcs1 < 256),"
                       "ul_mcs1  INT CHECK(ul_mcs1 >= 0 AND ul_mcs1 < 256),"
                       "dl_mcs2  INT CHECK(dl_mcs2 >= 0 AND dl_mcs2 < 256),"
                       "ul_mcs2 INT CHECK(ul_mcs2 >= 0 AND ul_mcs2 < 256),"
                       "phr INT CHECK(phr >= -128 AND  phr < 128),"
                       "bsr INT CHECK(bsr >= 0 AND  bsr < 4294967296),"
                       "dl_bler REAL CHECK(dl_bler  >= 0 AND dl_bler < 4294967296),"
                       "ul_bler REAL CHECK(ul_bler  >= 0 AND ul_bler < 4294967296),"
                       "dl_num_harq INT CHECK(dl_num_harq >= 0 AND  dl_num_harq < 5),"
                       "dl_harq_round0 INT CHECK(dl_harq_round0 >= 0 AND  dl_harq_round0 < 4294967296),"
                       "dl_harq_round1 INT CHECK(dl_harq_round1 >= 0 AND  dl_harq_round1 < 4294967296),"
                       "dl_harq_round2 INT CHECK(dl_harq_round2 >= 0 AND  dl_harq_round2 < 4294967296),"
                       "dl_harq_round3 INT CHECK(dl_harq_round3 >= 0 AND  dl_harq_round3 < 4294967296),"
                       "dlsch_errors INT CHECK(dlsch_errors >= 0 AND  dlsch_errors < 4294967296),"
                       "ul_num_harq INT CHECK(ul_num_harq >= 0 AND  ul_num_harq < 5),"
                       "ul_harq_round0 INT CHECK(ul_harq_round0 >= 0 AND  ul_harq_round0 < 4294967296),"
                       "ul_harq_round1 INT CHECK(ul_harq_round1 >= 0 AND  ul_harq_round1 < 4294967296),"
                       "ul_harq_round2 INT CHECK(ul_harq_round2 >= 0 AND  ul_harq_round2 < 4294967296),"
                       "ul_harq_round3 INT CHECK(ul_harq_round3 >= 0 AND  ul_harq_round3 < 4294967296),"
                       "ulsch_errors INT CHECK(ulsch_errors >= 0 AND  ulsch_errors < 4294967296)"
                       ");";

  create_table(db, sql_mac);
}

static
void create_rlc_bearer_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_rlc = "DROP TABLE IF EXISTS RLC_bearer;"
  "CREATE TABLE RLC_bearer(tstamp INT CHECK(tstamp > 0)," 
                            "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"
                            "mcc INT,"
                            "mnc INT,"
                            "mnc_digit_len INT,"
                            "nb_id INT,"
                            "cu_du_id TEXT,"
                            "txpdu_pkts INT CHECK(txpdu_pkts >= 0 AND txpdu_pkts < 4294967296)," // 1 << 32 = 4294967296 
                            "txpdu_bytes INT CHECK(txpdu_bytes >= 0 AND  txpdu_bytes < 4294967296 ),"\
                            "txpdu_wt_ms  INT CHECK(txpdu_wt_ms  >= 0 AND  txpdu_wt_ms  < 4294967296 ),"\
                            "txpdu_dd_pkts INT CHECK(txpdu_dd_pkts >= 0 AND  txpdu_dd_pkts < 4294967296 ) ,"\
                            "txpdu_dd_bytes INT  CHECK(txpdu_dd_bytes >= 0 AND  txpdu_dd_bytes < 4294967296 ),"\
                            "txpdu_retx_pkts INT CHECK(txpdu_retx_pkts >= 0 AND  txpdu_retx_pkts < 4294967296 ) ,"\
                            "txpdu_retx_bytes INT  CHECK(txpdu_retx_bytes >= 0 AND  txpdu_retx_bytes < 4294967296 ),"\
                            "txpdu_segmented INT  CHECK(txpdu_segmented >= 0 AND  txpdu_segmented < 4294967296 ),"\
                            "txpdu_status_pkts INT  CHECK(txpdu_status_pkts >= 0 AND  txpdu_status_pkts < 4294967296 ),"\
                            "txpdu_status_bytes INT  CHECK(txpdu_status_bytes >= 0 AND  txpdu_status_bytes < 4294967296 ),"\
                            "txbuf_occ_bytes INT  CHECK(txbuf_occ_bytes >= 0 AND  txbuf_occ_bytes < 4294967296 ),"\
                            "txbuf_occ_pkts INT  CHECK(txbuf_occ_pkts >= 0 AND  txbuf_occ_pkts < 4294967296 ),"\
                            "rxpdu_pkts INT  CHECK(rxpdu_pkts >= 0 AND  rxpdu_pkts < 4294967296 ),"\
                            "rxpdu_bytes INT  CHECK(rxpdu_bytes >= 0 AND  rxpdu_bytes < 4294967296 ),"\
                            "rxpdu_dup_pkts INT CHECK(rxpdu_dup_pkts >= 0 AND  rxpdu_dup_pkts < 4294967296 ),"\
                            "rxpdu_dup_bytes INT CHECK(rxpdu_dup_bytes >= 0 AND  rxpdu_dup_bytes < 4294967296 ),"\
                            "rxpdu_dd_pkts INT CHECK(rxpdu_dd_pkts >= 0 AND  rxpdu_dd_pkts < 4294967296 ),"\
                            "rxpdu_dd_bytes INT CHECK(rxpdu_dd_bytes >= 0 AND  rxpdu_dd_bytes < 4294967296 ),"\
                            "rxpdu_ow_pkts INT CHECK(rxpdu_ow_pkts >= 0 AND  rxpdu_ow_pkts < 4294967296 ),"\
                            "rxpdu_ow_bytes INT CHECK(rxpdu_ow_bytes >= 0 AND  rxpdu_ow_bytes < 4294967296 ),"\
                            "rxpdu_status_pkts INT CHECK(rxpdu_status_pkts >= 0 AND  rxpdu_status_pkts < 4294967296 ),"\
                            "rxpdu_status_bytes INT CHECK(rxpdu_status_bytes >= 0 AND  rxpdu_status_bytes < 4294967296 ),"\
                            "rxbuf_occ_bytes INT CHECK(rxbuf_occ_bytes >= 0 AND  rxbuf_occ_bytes < 4294967296 ),"\
                            "rxbuf_occ_pkts INT CHECK(rxbuf_occ_pkts >= 0 AND  rxbuf_occ_pkts < 4294967296 ),"\
                            "txsdu_pkts INT CHECK(txsdu_pkts >= 0 AND  txsdu_pkts < 4294967296 ),"\
                            "txsdu_bytes INT CHECK(txsdu_bytes >= 0 AND  txsdu_bytes < 4294967296 ),"\
                            "txsdu_avg_time_to_tx REAL CHECK(txsdu_avg_time_to_tx >= 0 AND  txsdu_avg_time_to_tx < 4294967296 ),"\
                            "txsdu_wt_us INT CHECK(txsdu_wt_us >= 0 AND  txsdu_wt_us < 4294967296 ),"\
                            "rxsdu_pkts INT CHECK(rxsdu_pkts >= 0 AND  rxsdu_pkts < 4294967296 ),"\
                            "rxsdu_bytes INT CHECK(rxsdu_bytes >= 0 AND  rxsdu_bytes < 4294967296 ),"\
                            "rxsdu_dd_pkts INT CHECK(rxsdu_dd_pkts >= 0 AND  rxsdu_dd_pkts < 4294967296 ),"\
                            "rxsdu_dd_bytes INT CHECK(rxsdu_dd_bytes >= 0 AND  rxsdu_dd_bytes < 4294967296 ),"\
                            "rnti INT CHECK(rnti >= 0 AND  rnti < 4294967296 ),"\
                            "mode INT CHECK(mode >= 0 AND  mode < 3),"\
                            "rbid INT CHECK(rbid >= 0 AND  rbid < 16)"
                            ");";

  create_table(db, sql_rlc);
}

static
void create_zxc_bearer_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_zxc = "DROP TABLE IF EXISTS ZXC_bearer;"
  "CREATE TABLE ZXC_bearer(tstamp INT CHECK(tstamp > 0)," 
                            "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"
                            "mcc INT,"
                            "mnc INT,"
                            "mnc_digit_len INT,"
                            "nb_id INT,"
                            "cu_du_id TEXT,"
                            "bbu_addr TEXT,"\
                            "cell_id TEXT,"\
                            "enb_id TEXT,"\
                            "geran_ci TEXT,"\
                            "geran_lac TEXT,"\
                            "gtp_bind_addr TEXT,"\
                            "mcc_1 TEXT,"\
                            "mme_addr TEXT,"\
                            "mnc_1 TEXT,"\
                            "n_prb TEXT,"\
                            "name TEXT,"\
                            "nof_ports TEXT,"\
                            "p_a TEXT,"\
                            "phy_cell_id TEXT,"\
                            "rru_addr TEXT,"\
                            "s1c_bind_addr TEXT,"\
                            "sec1_pci TEXT,"\
                            "sec1_x2_bind_addr TEXT,"\
                            "sec2_pci TEXT,"\
                            "sec2_x2_bind_addr TEXT,"\
                            "sec3_x2_bind_addr TEXT,"\
                            "sector_id TEXT,"\
                            "tac TEXT,"\
                            "tm TEXT,"\
                            "ws_port TEXT"
                            ");";
                            

  create_table(db, sql_zxc);
}
void create_sib1_bearer_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_sib1 =  "CREATE TABLE IF NOT EXISTS SIB1(tstamp INT CHECK(tstamp > 0)," 
                            "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"
                            "mcc INT,"
                            "mnc INT,"
                            "mnc_digit_len INT,"
                            "nb_id INT,"
                            "cu_du_id TEXT,"
                            "cell_barred TEXT,"
                            "intra_freq_reselection TEXT,"
                            "p_max INT,"
                            "q_rx_lev_min INT,"
                            "si_window_length INT,"
                            "system_info_value_tag INT,"
                            "sched_info_si_mapping_info_1 TEXT,"
                            "sched_info_si_periodicity_1 INT,"
                            "sched_info_si_mapping_info_2 TEXT,"
                            "sched_info_si_periodicity_2 INT,"
                            "sched_info_si_mapping_info_3 TEXT,"
                            "sched_info_si_periodicity_3 INT,"
                            "sched_info_si_mapping_info_4 TEXT,"
                            "sched_info_si_periodicity_4 INT,"
                            "sched_info_si_mapping_info_5 TEXT,"
                            "sched_info_si_periodicity_5 INT,"
                            "sched_info_si_mapping_info_6 TEXT,"
                            "sched_info_si_periodicity_6 INT,"
                            "sched_info_si_mapping_info_7 TEXT,"
                            "sched_info_si_periodicity_7 INT,"
                            "sched_info_si_mapping_info_8 TEXT,"
                            "sched_info_si_periodicity_8 INT"                                                      
                            ");";
                            

  create_table(db, sql_sib1);
}
void create_rr_bearer_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_rr =  "CREATE TABLE IF NOT EXISTS RR(tstamp INT CHECK(tstamp > 0)," 
                            "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"
                            "mcc INT,"
                            "mnc INT,"
                            "mnc_digit_len INT,"
                            "nb_id INT,"
                            "cu_du_id TEXT,"
                            "dl_pathloss_change TEXT,"
                            "periodic_phr_timer INT,"
                            "prohibit_phr_timer INT,"
                            "time_alignment_timer INT,"
                            "max_harq_tx INT,"
                            "periodic_bsr_timer INT,"
                            "retx_bsr_timer INT,"
                            "mode TEXT,"
                            "cqi_report_cnfg_nof_prb INT,"
                            "cqi_report_cnfg_period INT,"
                            "simultaneousAckCQI INT,"
                            "cqi_report_cnfg_subframe TEXT,"
                            "duration TEXT,"
                            "resources TEXT,"
                            "beta_offset_ack_idx INT,"
                            "beta_offset_cqi_idx INT,"
                            "beta_offset_ri_idx INT,"
                            "dsr_trans_max INT,"
                            "sched_request_cnfg_nof_prb INT,"
                            "sched_request_cnfg_period INT,"
                            "sched_request_cnfg_subframe TEXT"
                            ");";
                            

  create_table(db, sql_rr);
}
void create_uetrace_bearer_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_uetrace =  "CREATE TABLE IF NOT EXISTS UETRACE(tstamp INT CHECK(tstamp > 0)," 
                            "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"
                            "mcc INT,"
                            "mnc INT,"
                            "mnc_digit_len INT,"
                            "nb_id INT,"
                            "cu_du_id TEXT,"
                            "rnti INT,"
                            "bsr REAL,"
                            "dl_bler REAL,"
                            "dl_cqi REAL,"
                            "dl_mcs REAL,"
                            "dl_pmi REAL,"
                            "dl_rate REAL,"
                            "dl_ri REAL,"
                            "phr REAL,"
                            "snr_pucch REAL,"
                            "ul_bler REAL,"
                            "ul_mcs REAL,"
                            "ul_rate REAL,"
                            "snr REAL"
                            ");";
                            

  create_table(db, sql_uetrace);
}
void create_sib2_bearer_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_sib2 =  "CREATE TABLE IF NOT EXISTS SIB2(tstamp INT CHECK(tstamp > 0)," 
                            "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"
                            "mcc INT,"
                            "mnc INT,"
                            "mnc_digit_len INT,"
                            "nb_id INT,"
                            "cu_du_id TEXT,"
                            "additional_spectrum_emission INT,"
                            "ul_bw_present INT,"
                            "ul_carrier_freq_present INT,"
                            "modification_period_coeff INT,"
                            "default_paging_cycle INT,"
                            "nB TEXT,"
                            "p_b INT,"
                            "rs_power INT,"
                            "high_speed_flag INT,"
                            "prach_config_index INT,"
                            "prach_freq_offset INT,"
                            "zero_correlation_zone_config INT,"
                            "root_sequence_index INT,"
                            "delta_pucch_shift INT,"
                            "n1_pucch_an INT,"
                            "n_cs_an INT,"
                            "n_rb_cqi INT,"
                            "enable_64_qam INT,"
                            "hopping_mode TEXT,"
                            "n_sb INT,"
                            "pusch_hopping_offset INT,"
                            "cyclic_shift INT,"
                            "group_assignment_pusch INT,"
                            "group_hopping_enabled INT,"
                            "sequence_hopping_enabled INT,"
                            "mac_con_res_timer INT,"
                            "max_harq_msg3_tx INT,"
                            "num_ra_preambles INT,"
                            "preamble_init_rx_target_pwr INT,"
                            "preamble_trans_max INT,"
                            "pwr_ramping_step INT,"
                            "ra_resp_win_size INT,"
                            "ul_cp_length TEXT,"
                            "alpha REAL,"
                            "format_1 INT,"
                            "format_1b INT,"
                            "format_2 INT,"
                            "format_2a INT,"
                            "format_2b INT,"
                            "delta_preamble_msg3 INT,"
                            "p0_nominal_pucch INT,"
                            "p0_nominal_pusch INT,"
                            "time_alignment_timer TEXT,"
                            "n310 INT,"
                            "n311 INT,"
                            "t300 INT,"
                            "t301 INT,"
                            "t310 INT,"
                            "t311 INT"                                                
                            ");";
                            

  create_table(db, sql_sib2);
}
static
void create_enb_conf_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_enb_conf =  "CREATE TABLE IF NOT EXISTS ENB_CONF(tstamp INT CHECK(tstamp > 0)," 
                            "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"
                            "mcc INT,"
                            "mnc INT,"
                            "mnc_digit_len INT,"
                            "nb_id INT,"
                            "cu_du_id TEXT,"
                            "bbu_addr TEXT,"\
                            "cell_id TEXT,"\
                            "enb_id TEXT,"\
                            "geran_ci TEXT,"\
                            "geran_lac TEXT,"\
                            "gtp_bind_addr TEXT,"\
                            "mcc_1 TEXT,"\
                            "mme_addr TEXT,"\
                            "mnc_1 TEXT,"\
                            "n_prb TEXT,"\
                            "name TEXT,"\
                            "nof_ports TEXT,"\
                            "p_a TEXT,"\
                            "phy_cell_id TEXT,"\
                            "rru_addr TEXT,"\
                            "s1c_bind_addr TEXT,"\
                            "sec1_pci TEXT,"\
                            "sec1_x2_bind_addr TEXT,"\
                            "sec2_pci TEXT,"\
                            "sec2_x2_bind_addr TEXT,"\
                            "sec3_x2_bind_addr TEXT,"\
                            "sector_id TEXT,"\
                            "tac TEXT,"\
                            "tm TEXT,"\
                            "ws_port TEXT,"\
                            "drb_config TEXT,"\
                            "mbms_sib_config TEXT,"\
                            "rr_config TEXT,"\
                            "sib_config TEXT,"\
                            "accept_handover_ratio TEXT,"\
                            "agc_energy_b2x0 TEXT,"\
                            "alpha TEXT,"\
                            "bi TEXT,"\
                            "bi_flag TEXT,"\
                            "csfb_geran_list TEXT,"\
                            "eea_pref_list TEXT,"\
                            "eia_pref_list TEXT,"\
                            "enable_mbsfn TEXT,"\
                            "geran_csfb_flag TEXT,"\
                            "handover_drb_id TEXT,"\
                            "link_failure_nof_err TEXT,"\
                            "m1u_if_addr TEXT,"\
                            "m1u_multiaddr TEXT,"\
                            "mbms_file TEXT,"\
                            "metrics_addr TEXT,"\
                            "metrics_period_secs TEXT,"\
                            "metrics_port TEXT,"\
                            "nof_phy_threads TEXT,"\
                            "packet_size TEXT,"\
                            "pusch_max_its TEXT,"\
                            "radio_unit TEXT,"\
                            "rrc_connected TEXT,"\
                            "rrc_inactivity_timer TEXT,"\
                            "snr_pucch TEXT,"\
                            "snr_pusch TEXT,"\
                            "enable_gui TEXT,"\
                            "all_hex_limit TEXT,"\
                            "all_level TEXT,"\
                            "file_max_size TEXT,"\
                            "filename_log TEXT,"\
                            "enable_pcap TEXT,"\
                            "filename_pcap TEXT,"\
                            "dl_earfcn TEXT,"\
                            "rx_gain TEXT,"\
                            "tx_gain TEXT,"\
                            "nof_ctrl_symbols TEXT,"\
                            "pdsch_max_mcs1 TEXT,"\
                            "pdsch_max_mcs2 TEXT,"\
                            "pusch_max_mcs TEXT"
                            ");";
                            

  create_table(db, sql_enb_conf);
}
static
void create_counters_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_counters =  "CREATE TABLE IF NOT EXISTS COUNTERS(tstamp INT CHECK(tstamp > 0)," 
                            "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"
                            "mcc INT,"
                            "mnc INT,"
                            "mnc_digit_len INT,"
                            "nb_id INT,"
                            "cu_du_id TEXT,"
                            "sector_number INT,"\
                            "time_stamp INT,"\
                            "dl_bitrate REAL,"\
                            "dl_errors REAL,"\
                            "dl_nas_transport REAL,"\
                            "dl_tx REAL,"\
                            "dl_use_avg REAL,"\
                            "dl_use_max REAL,"\
                            "dl_use_min REAL,"\
                            "dl_use_online REAL,"\
                            "nof_pdcp_pak REAL,"\
                            "nof_fail_pdcp_pak REAL,"\
                            "dl_nof_volte_pak REAL,"\
                            "dl_nof_fail_volte_pak REAL,"\
                            "dl_trafic_volte REAL,"\
                            "erab_count_avg REAL,"\
                            "erab_count_max REAL,"\
                            "erab_count_min REAL,"\
                            "erab_modify_request REAL,"\
                            "erab_modify_response REAL,"\
                            "erab_release_command REAL,"\
                            "erab_release_response REAL,"\
                            "erab_setup_request REAL,"\
                            "erab_setup_response REAL,"\
                            "volte_erab_attempts REAL,"\
                            "number_of_rach REAL,"\
                            "number_of_rar REAL,"\                            
                            "max_time_adv REAL,"\
                            "call_duration REAL,"\
                            "rrc_connection_reconfiguration REAL,"\
                            "rrc_connection_reconfiguration_complete REAL,"\
                            "rrc_connection_reestablishment REAL,"\
                            "rrc_connection_reestablishment_reject REAL,"\
                            "rrc_connection_reestablishment_request REAL,"\
                            "rrc_connection_reconfiguration_modify_bearer REAL,"\
                            "rrc_connection_reconfiguration_new_bearer REAL,"\
                            "rrc_connection_reconfiguration_rem_bearer REAL,"\
                            "rrc_connection_reconfiguration_handover REAL,"\
                            "rrc_connection_reconfiguration_mac_ce REAL,"\
                            "rrc_connection_reject REAL,"\
                            "rrc_connection_release REAL,"\
                            "rrc_connection_request REAL,"\
                            "rrc_connection_setup REAL,"\
                            "rrc_connection_setup_complete REAL,"\
                            "rrc_dl_information_transfer REAL,"\
                            "rrc_security_mode_command REAL,"\
                            "rrc_security_mode_complete REAL,"\
                            "rrc_security_mode_failure REAL,"\
                            "rrc_ue_capability_enquiry REAL,"\
                            "rrc_ue_capability_information REAL,"\
                            "rrc_ul_information_transfer REAL,"\
                            "csfb_attempt REAL,"\
                            "csfb_success REAL,"\
                            "srvcc_attempt REAL,"\
                            "srvcc_success REAL,"\
                            "volte_qci1_attempts REAL,"\
                            "success_volte_establishment_qci1 REAL,"\
                            "csfb_geran_attempt REAL,"\
                            "csfb_umts_attempt REAL,"\
                            "handover_success_inter_sec REAL,"\
                            "handover_request_inter_sec REAL,"\
                            "s1_setup_failure REAL,"\
                            "s1_setup_request REAL,"\
                            "s1_setup_response REAL,"\
                            "handover_request REAL,"\
                            "handover_request_acknowledge REAL,"\
                            "handover_send_notify REAL,"\
                            "handover_success REAL,"\
                            "handover_failure REAL,"\
                            "ue_context_modify_response REAL,"\
                            "handover_success_volte REAL,"\
                            "ue_context_modify_failure REAL,"\
                            "ue_context_modify_request REAL,"\
                            "ue_context_release_command REAL,"\
                            "ue_context_release_complete REAL,"\
                            "ue_context_release_request REAL,"\
                            "ue_context_setup_complete REAL,"\
                            "ue_count_avg REAL,"\
                            "ue_count_max REAL,"\
                            "ue_count_min REAL,"\
                            "ue_count_online REAL,"\
                            "initial_context_setup_request REAL,"\
                            "initial_context_setup_failure REAL,"\
                            "initial_context_setup_response REAL,"\
                            "initial_ue_message REAL,"\
                            "mme_status_transfer REAL,"\
                            "ul_bitrate REAL,"\
                            "ul_errors REAL,"\
                            "ul_nas_transport REAL,"\
                            "ul_tx REAL,"\
                            "ul_use_avg REAL,"\
                            "ul_use_max REAL,"\
                            "ul_use_min REAL,"\
                            "ul_use_online REAL,"\
                            "ul_interference REAL,"\
                            "ul_trafic_volte REAL"
                            ");";
                            

  create_table(db, sql_counters);
}
static
void create_pdcp_bearer_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_pdcp = "DROP TABLE IF EXISTS PDCP_bearer;"
  "CREATE TABLE PDCP_bearer(tstamp INT CHECK(tstamp > 0)," 
                       "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node <= 10),"
                       "mcc INT,"
                       "mnc INT,"
                       "mnc_digit_len INT,"
                       "nb_id INT,"
                       "cu_du_id TEXT,"
                       "txpdu_pkts INT CHECK(txpdu_pkts  >= 0 AND txpdu_pkts  < 4294967296),"
                       "txpdu_bytes INT CHECK(txpdu_bytes >=0 AND txpdu_bytes < 4294967296 ),"
                       "txpdu_sn INT CHECK(txpdu_sn >=0 AND txpdu_sn < 4294967296 ),"
                       "rxpdu_pkts INT CHECK(rxpdu_pkts >=0 AND rxpdu_pkts < 4294967296 ),"
                       "rxpdu_bytes INT CHECK(rxpdu_bytes >=0 AND rxpdu_bytes < 4294967296 ),"
                       "rxpdu_sn  INT CHECK(rxpdu_sn  >= 0 AND rxpdu_sn  < 4294967296 ) ,"
                       "rxpdu_oo_pkts INT  CHECK(rxpdu_oo_pkts >= 0 AND rxpdu_oo_pkts < 4294967296 ),"
                       "rxpdu_oo_bytes INT  CHECK(rxpdu_oo_bytes >= 0 AND rxpdu_oo_bytes < 4294967296 ),"
                       "rxpdu_dd_pkts INT  CHECK(rxpdu_dd_pkts >= 0 AND rxpdu_dd_pkts < 4294967296 ),"
                       "rxpdu_dd_bytes INT  CHECK(rxpdu_dd_bytes >= 0 AND rxpdu_dd_bytes < 4294967296 ),"
                       "rxpdu_ro_count INT  CHECK(rxpdu_ro_count >= 0 AND rxpdu_ro_count < 4294967296 ),"
                       "txsdu_pkts INT  CHECK(txsdu_pkts >= 0 AND txsdu_pkts < 4294967296 ),"
                       "txsdu_bytes INT  CHECK(txsdu_bytes >= 0 AND txsdu_bytes <4294967296 ),"
                       "rxsdu_pkts INT  CHECK(rxsdu_pkts >= 0 AND rxsdu_pkts <4294967296),"
                       "rxsdu_bytes INT CHECK(rxsdu_bytes >= 0 AND rxsdu_bytes <4294967296),"
                       "rnti INT CHECK(rnti >= 0 AND rnti <4294967296),"
                       "mode INT CHECK(mode >= 0 AND mode < 4294967296),"
                       "rbid INT CHECK(rbid >= 0 AND rbid < 4294967296)" // −23 dB to +40 dB 
                       ");";
  create_table(db, sql_pdcp);
}

static
void create_slice_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_slice = "DROP TABLE IF EXISTS SLICE;"
                    "CREATE TABLE SLICE("\
                    "tstamp INT CHECK(tstamp > 0),"\
                    "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"\
                    "mcc INT,"\
                    "mnc INT,"\
                    "mnc_digit_len INT,"\
                    "nb_id INT,"\
                    "cu_du_id TEXT,"\
                    "len_slices INT CHECK(len_slices  >= 0 AND len_slices < 4),"\
                    "sched_name TEXT,"\
                    "id INT CHECK(id >=0 AND id < 4294967296),"\
                    "label TEXT,"\
                    "type TEXT,"\
                    "type_conf TEXT,"\
                    "sched TEXT,"\
                    "type_param0 REAL CHECK(type_param0 == NULL OR (type_param0 >= 0 AND type_param0 < 4294967296)),"\
                    "type_param1 REAL CHECK(type_param1 == NULL OR (type_param1 >= 0 AND type_param1 < 4294967296)),"\
                    "type_param2 REAL CHECK(type_param2 == NULL OR (type_param2 >= 0 AND type_param2 < 4294967296))"
                    ");";
  create_table(db, sql_slice);
}

static
void create_ue_slice_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_ue_slice = "DROP TABLE IF EXISTS UE_SLICE;"
                    "CREATE TABLE UE_SLICE("\
                    "tstamp INT CHECK(tstamp > 0),"\
                    "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"\
                    "mcc INT,"\
                    "mnc INT,"\
                    "mnc_digit_len INT,"\
                    "nb_id INT,"\
                    "cu_du_id TEXT,"\
                    "len_ue_slice INT CHECK(len_ue_slice  >= 0 AND len_ue_slice  < 4294967296),"\
                    "rnti INT CHECK(rnti == -1 OR (rnti >= 0 AND rnti < 65535)),"\
                    "dl_id INT CHECK(dl_id == -1 OR (dl_id >= 0 AND dl_id < 4294967296))"
                    ");";
  create_table(db, sql_ue_slice);
}

static
void create_gtp_table(sqlite3* db)
{
  assert(db != NULL);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_gtp = "DROP TABLE IF EXISTS GTP_NGUT;"
  "CREATE TABLE GTP_NGUT(tstamp INT CHECK(tstamp > 0)," 
                            "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node <= 10),"
                            "mcc INT,"
                            "mnc INT,"
                            "mnc_digit_len INT,"
                            "nb_id INT,"
                            "cu_du_id TEXT,"
                            "teidgnb INT ," // 1 << 32 = 4294967296 
                            "rnti INT ,"
                            "qfi  INT ,"
                            "teidupf INT "
                            ");";

  create_table(db, sql_gtp);
}
void create_kpm_table(sqlite3* db) 
{
  assert(db != NULL);

  char* sql_kpm_measRecord = "DROP TABLE IF EXISTS KPM_MeasRecord;"
  "CREATE TABLE KPM_MeasRecord(tstamp INT," 
                       "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"
                       "mcc INT,"
                       "mnc INT,"
                       "mnc_digit_len INT,"
                       "nb_id INT,"
                       "cu_du_id TEXT,"
                       "incompleteFlag INT,"
                       "val REAL CHECK(val >=0 AND val < 4294967296 )"
                       ");";
  create_table(db, sql_kpm_measRecord);

  // ToDo: PRIMARY KEY UNIQUE
  char* sql_kpm_labelInfo = "DROP TABLE IF EXISTS KPM_LabelInfo;"
  "CREATE TABLE KPM_LabelInfo(tstamp INT CHECK(tstamp > 0)," 
                       "ngran_node INT CHECK(ngran_node >= 0 AND ngran_node < 9),"
                       "mcc INT,"
                       "mnc INT,"
                       "mnc_digit_len INT,"
                       "nb_id INT,"
                       "cu_du_id TEXT,"
                       "MeasType TEXT,"
                       "noLabel INT CHECK(noLabel >=0 AND noLabel < 4294967296 ),"
                       "plmnID TEXT,"
                       "sST TEXT,"
                       "sD TEXT,"
                       "fiveQI  INT CHECK(fiveQI  >= 0 AND fiveQI  < 4294967296 ) ,"
                       "qFI INT  CHECK(qFI >= 0 AND qFI < 4294967296 ),"
                       "qCI INT  CHECK(qCI >= 0 AND qCI < 4294967296 ),"
                       "qCImax INT  CHECK(qCImax >= 0 AND qCImax < 4294967296 ),"
                       "qCImin INT  CHECK(qCImin >= 0 AND qCImin < 4294967296 ),"
                       "aRPmax INT  CHECK(aRPmax >= 0 AND aRPmax < 4294967296 ),"
                       "aRPmin INT  CHECK(aRPmin >= 0 AND aRPmin < 4294967296 ),"
                       "bitrateRange INT  CHECK(bitrateRange >= 0 AND bitrateRange <4294967296 ),"
                       "layerMU_MIMO INT  CHECK(layerMU_MIMO >= 0 AND layerMU_MIMO <4294967296),"
                       "sUM INT CHECK(sUM >= 0 AND sUM <4294967296),"
                       "distBinX INT CHECK(distBinX >= 0 AND distBinX <4294967296),"
                       "distBinY INT CHECK(distBinY >= 0 AND distBinY <4294967296),"
                       "distBinZ INT CHECK(distBinZ >= 0 AND distBinZ <4294967296),"
                       "preLabelOverride INT CHECK(preLabelOverride >= 0 AND preLabelOverride <4294967296),"
                       "startEndInd INT CHECK(startEndInd >= 0 AND startEndInd <4294967296),"
                       "min INT CHECK(min >= 0 AND min <4294967296),"
                       "max INT CHECK(max >= 0 AND max <4294967296),"
                       "avg INT CHECK(avg >= 0 AND avg < 4294967296)"
                       ");";
  create_table(db, sql_kpm_labelInfo);
}

static
void insert_db(sqlite3* db, char const* sql)
{
  assert(db != NULL);
  assert(sql != NULL);

  char* err_msg = NULL;
  int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
  // printf("%s\n", err_msg);
  assert(rc == SQLITE_OK && "Error while inserting into the DB. Check the err_msg string for further info");
}


static
int to_sql_string_mac_ue(global_e2_node_id_t const* id, mac_ue_stats_impl_t* stats, int64_t tstamp, char* out, size_t out_len)
{
  assert(stats != NULL);       
  assert(out != NULL);
  const size_t max = 1024;
  assert(out_len >= max);

  char* c_null = NULL;
  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int rc = snprintf(out, max, 
      "INSERT INTO MAC_UE VALUES("
      "%ld,"//tstamp
      "%d," //ngran_node  
      "%d," //mcc
      "%d," //mnc
      "%d," //mnc_digit_len   
      "%d," //nb_id 
      "'%s'," //cu_du_id
      "%d," //frame
      "%d," //slot
      "%lu,"//dl_aggr_tbs     
      "%lu,"//ul_aggr_tbs     
      "%lu," //dl_aggr_bytes_sdus   
      "%lu,"//ul_aggr_bytes_sdus       
      "%lu," //dl_curr_tbs
      "%lu," //ul_curr_tbs
      "%lu," //dl_sched_rb
      "%lu," //ul_sched_rb
      "%g,"// pusch_snr        
      "%g,"//  pucch_snr      
      "%u,"// rnti            
      "%u,"//dl_aggr_prb      
      "%u,"//  ul_aggr_prb    
      "%u,"//  dl_aggr_sdus   
      "%u,"//  ul_aggr_sdus   
      "%u,"// dl_aggr_retx_prb
      "%u,"// ul_aggr_retx_prb
      "%u,"// wb_cqi
      "%u,"// dl_mcs1
      "%u,"// ul_mcs1
      "%u,"// dl_mcs2         
      "%u,"// ul_mcs2         
      "%d,"// phr
      "%u,"// bsr
      "%f," // dl_bler
      "%f," // ul_bler
      "%d," // dl_num_harq
      "%u," // dl_harq[0]
      "%u," // dl_harq[1]
      "%u," // dl_harq[2]
      "%u," // dl_harq[3]
      "%u," // dlsch_errors
      "%d," // ul_num_harq
      "%u," // ul_harq[0]
      "%u," // ul_harq[1]
      "%u," // ul_harq[2]
      "%u," // ul_harq[3]
      "%u" // ulsch_errors
      ");"
      ,tstamp                
      ,id->type
      ,id->plmn.mcc
      ,id->plmn.mnc
      ,id->plmn.mnc_digit_len
      ,id->nb_id.nb_id 
      ,id->cu_du_id ? c_cu_du_id : c_null
      ,stats->frame
      ,stats->slot
      ,stats->dl_aggr_tbs    
      ,stats->ul_aggr_tbs    
      ,stats->dl_aggr_bytes_sdus      
      ,stats->ul_aggr_bytes_sdus      
      ,stats->dl_curr_tbs
      ,stats->ul_curr_tbs
      ,stats->dl_sched_rb
      ,stats->ul_sched_rb
      ,stats->pusch_snr      
      ,stats->pucch_snr      
      ,stats->rnti 
      ,stats->dl_aggr_prb    
      ,stats->ul_aggr_prb    
      ,stats->dl_aggr_sdus   
      ,stats->ul_aggr_sdus   
      ,stats->dl_aggr_retx_prb        
      ,stats->ul_aggr_retx_prb
      ,stats->wb_cqi         
      ,stats->dl_mcs1        
      ,stats->ul_mcs1        
      ,stats->dl_mcs2        
      ,stats->ul_mcs2        
      ,stats->phr            
      ,stats->bsr
      ,stats->dl_bler
      ,stats->ul_bler
      ,stats->dl_num_harq
      ,stats->dl_harq[0]
      ,stats->dl_harq[1]
      ,stats->dl_harq[2]
      ,stats->dl_harq[3]
      ,stats->dl_harq[4]
      ,stats->ul_num_harq
      ,stats->ul_harq[0]
      ,stats->ul_harq[1]
      ,stats->ul_harq[2]
      ,stats->ul_harq[3]
      ,stats->ul_harq[4]
      );
  assert(rc < (int)max && "Not enough space in the char array to write all the data");
  return rc;
}


static
int to_sql_string_rlc_rb(global_e2_node_id_t const* id,rlc_radio_bearer_stats_t* rlc, int64_t tstamp, char* out, size_t out_len)
{
  assert(rlc != NULL);
  assert(out != NULL);
  const size_t max = 1024;
  assert(out_len >= max);

  char* c_null = NULL;
  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int const rc = snprintf(out, max,
        "INSERT INTO RLC_bearer VALUES("
        "%ld,"// tstamp
        "%d," //ngran_node  
        "%d," //mcc
        "%d," //mnc
        "%d," //mnc_digit_len   
        "%d," //nb_id 
        "'%s'," //cu_du_id
        "%u," //rlc->txpdu_pkts
        "%u," //rlc->txpdu_bytes
        "%u," //rlc->txpdu_wt_ms 
        "%u," //rlc->txpdu_dd_pkts
        "%u," //rlc->txpdu_dd_bytes 
        "%u," //rlc->txpdu_retx_pkts
        "%u," //rlc->txpdu_retx_bytes
        "%u," //rlc->txpdu_segmented
        "%u," //rlc->txpdu_status_pkts
        "%u," //rlc->txpdu_status_bytes
        "%u," //rlc->txbuf_occ_bytes
        "%u," //rlc->txbuf_occ_pkts
        "%u," //rlc->rxpdu_pkts
        "%u," //rlc->rxpdu_bytes
        "%u," //rlc->rxpdu_dup_pkts
        "%u," //rlc->rxpdu_dup_bytes
        "%u," //rlc->rxpdu_dd_pkts
        "%u," //rlc->rxpdu_dd_bytes
        "%u," //rlc->rxpdu_ow_pkts
        "%u," //rlc->rxpdu_ow_bytes
        "%u," //rlc->rxpdu_status_pkts
        "%u," //rlc->rxpdu_status_bytes
        "%u," //rlc->rxbuf_occ_bytes
        "%u," //rlc->rxbuf_occ_pkts
        "%u," //rlc->txsdu_pkts
        "%lu," //rlc->txsdu_bytes
        "%.2f," //rlc->txsdu_avg_time_to_tx
        "%u," //rlc->txsdu_wt_us
        "%u," //rlc->rxsdu_pkts
        "%lu," //rlc->rxsdu_bytes
        "%u," //rlc->rxsdu_dd_pkts
        "%u," //rlc->rxsdu_dd_bytes
        "%u," //rlc->rnti
        "%u,"  //rlc->mode
        "%u"  //rlc->rbid 
        ");"
        , tstamp
        , id->type
        , id->plmn.mcc
        , id->plmn.mnc
        , id->plmn.mnc_digit_len
        , id->nb_id.nb_id 
        , id->cu_du_id ? c_cu_du_id : c_null
        , rlc->txpdu_pkts
        , rlc->txpdu_bytes
        , rlc->txpdu_wt_ms
        , rlc->txpdu_dd_pkts
        , rlc->txpdu_dd_bytes
        , rlc->txpdu_retx_pkts
        , rlc->txpdu_retx_bytes
        , rlc->txpdu_segmented
        , rlc->txpdu_status_pkts
        , rlc->txpdu_status_bytes
        , rlc->txbuf_occ_bytes
        , rlc->txbuf_occ_pkts
        , rlc->rxpdu_pkts
        , rlc->rxpdu_bytes
        , rlc->rxpdu_dup_pkts
        , rlc->rxpdu_dup_bytes
        , rlc->rxpdu_dd_pkts
        , rlc->rxpdu_dd_bytes
        , rlc->rxpdu_ow_pkts
        , rlc->rxpdu_ow_bytes
        , rlc->rxpdu_status_pkts
        , rlc->rxpdu_status_bytes
        , rlc->rxbuf_occ_bytes
        , rlc->rxbuf_occ_pkts
        , rlc->txsdu_pkts
        , rlc->txsdu_bytes
        , rlc->txsdu_avg_time_to_tx
        , rlc->txsdu_wt_us
        , rlc->rxsdu_pkts
        , rlc->rxsdu_bytes
        , rlc->rxsdu_dd_pkts
        , rlc->rxsdu_dd_bytes
        , rlc->rnti
        , rlc->mode
        , rlc->rbid
        );
  assert(rc < (int)max && "Not enough space in the char array to write all the data");
  return rc;
}

static
int to_sql_string_sib1_rb(global_e2_node_id_t const* id,sib1_stats_t* sib1, int64_t tstamp, char* out, size_t out_len)
{
  assert(sib1 != NULL);
  assert(out != NULL);
  const size_t max = 1024;
  assert(out_len >= max);

  char* c_null = NULL;
  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int const rc = snprintf(out, max,
        "INSERT INTO SIB1 VALUES("
        "%ld,"// tstamp
        "%d," //ngran_node  
        "%d," //mcc
        "%d," //mnc
        "%d," //mnc_digit_len   
        "%d," //nb_id 
        "'%s'," //cu_du_id
        "'%s',"
        "'%s'," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "'%s'," 
        "%d,"
        "'%s'," 
        "%d,"
        "'%s'," 
        "%d,"
        "'%s'," 
        "%d,"
        "'%s'," 
        "%d,"
        "'%s'," 
        "%d,"
        "'%s'," 
        "%d,"
        "'%s'," 
        "%d"
        ");"
        , tstamp
        , id->type
        , id->plmn.mcc
        , id->plmn.mnc
        , id->plmn.mnc_digit_len
        , id->nb_id.nb_id 
        , id->cu_du_id ? c_cu_du_id : c_null
        , sib1->cell_barred
        , sib1->intra_freq_reselection
        , sib1->p_max
        , sib1->q_rx_lev_min
        , sib1->si_window_length
        , sib1->system_info_value_tag 
        , sib1->sched_info_si_mapping_info_1
        , sib1->sched_info_si_periodicity_1
        , sib1->sched_info_si_mapping_info_2
        , sib1->sched_info_si_periodicity_2
        , sib1->sched_info_si_mapping_info_3
        , sib1->sched_info_si_periodicity_3
        , sib1->sched_info_si_mapping_info_4
        , sib1->sched_info_si_periodicity_4
        , sib1->sched_info_si_mapping_info_5
        , sib1->sched_info_si_periodicity_5
        , sib1->sched_info_si_mapping_info_6
        , sib1->sched_info_si_periodicity_6
        , sib1->sched_info_si_mapping_info_7
        , sib1->sched_info_si_periodicity_7
        , sib1->sched_info_si_mapping_info_8
        , sib1->sched_info_si_periodicity_8
        );
  assert(rc < (int)max && "Not enough space in the char array to write all the data");
  return rc;
}

static
int to_sql_string_rr_rb(global_e2_node_id_t const* id,rr_stats_t* rr, int64_t tstamp, char* out, size_t out_len)
{
  assert(rr != NULL);
  assert(out != NULL);
  const size_t max = 1024;
  assert(out_len >= max);

  char* c_null = NULL;
  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int const rc = snprintf(out, max,
        "INSERT INTO RR VALUES("
        "%ld,"// tstamp
        "%d," //ngran_node  
        "%d," //mcc
        "%d," //mnc
        "%d," //mnc_digit_len   
        "%d," //nb_id 
        "'%s'," //cu_du_id
        "'%s',"
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "'%s',"
        "%d," 
        "%d,"
        "%d," 
        "'%s',"
        "'%s'," 
        "'%s',"
        "%d," 
        "%d,"
        "%d," 
        "%d,"
        "%d," 
        "%d,"
        "'%s'" 
        ");"
        , tstamp
        , id->type
        , id->plmn.mcc
        , id->plmn.mnc
        , id->plmn.mnc_digit_len
        , id->nb_id.nb_id 
        , id->cu_du_id ? c_cu_du_id : c_null
        , rr->dl_pathloss_change
        , rr->periodic_phr_timer
        , rr->prohibit_phr_timer
        , rr->time_alignment_timer
        , rr->max_harq_tx
        , rr->periodic_bsr_timer 
        , rr->retx_bsr_timer
        , rr->mode
        , rr->cqi_report_cnfg_nof_prb
        , rr->cqi_report_cnfg_period
        , rr->simultaneousAckCQI
        , rr->cqi_report_cnfg_subframe
        , rr->duration
        , rr->resources
        , rr->beta_offset_ack_idx
        , rr->beta_offset_cqi_idx
        , rr->beta_offset_ri_idx
        , rr->dsr_trans_max
        , rr->sched_request_cnfg_nof_prb
        , rr->sched_request_cnfg_period
        , rr->sched_request_cnfg_subframe
        );
  assert(rc < (int)max && "Not enough space in the char array to write all the data");
  return rc;
}

static
int to_sql_string_uetrace_rb(global_e2_node_id_t const* id,uetrace_stats_t* uetrace, int64_t tstamp, char* out, size_t out_len)
{
  assert(uetrace != NULL);
  assert(out != NULL);
  const size_t max = 20480;
  assert(out_len >= max);

  char* c_null = NULL;
  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int const rc = snprintf(out, max,
        "INSERT INTO uetrace VALUES("
        "%ld,"// tstamp
        "%d," //ngran_node  
        "%d," //mcc
        "%d," //mnc
        "%d," //mnc_digit_len   
        "%d," //nb_id 
        "'%s'," //cu_du_id
        "%d,"
        "%f," 
        "%f," 
        "%f," 
        "%f," 
        "%f," 
        "%f," 
        "%f,"
        "%f," 
        "%f,"
        "%f," 
        "%f,"
        "%f," 
        "%f"
        ");"
        , tstamp
        , id->type
        , id->plmn.mcc
        , id->plmn.mnc
        , id->plmn.mnc_digit_len
        , id->nb_id.nb_id 
        , id->cu_du_id ? c_cu_du_id : c_null
        , uetrace->rnti
        , uetrace->bsr
        , uetrace->dl_bler
        , uetrace->dl_cqi
        , uetrace->dl_mcs
        , uetrace->dl_pmi
        , uetrace->dl_rate
        , uetrace->dl_ri
        , uetrace->phr
        , uetrace->snr_pucch
        , uetrace->ul_bler
        , uetrace->ul_mcs
        , uetrace->ul_rate
        , uetrace->snr
        );
  assert(rc < (int)max && "Not enough space in the char array to write all the data");
  return rc;
}

static
int to_sql_string_sib2_rb(global_e2_node_id_t const* id,sib2_stats_t* sib2, int64_t tstamp, char* out, size_t out_len)
{
  assert(sib2 != NULL);
  assert(out != NULL);
  const size_t max = 1024;
  assert(out_len >= max);

  char* c_null = NULL;
  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int const rc = snprintf(out, max,
        "INSERT INTO SIB2 VALUES("
        "%ld,"// tstamp
        "%d," //ngran_node  
        "%d," //mcc
        "%d," //mnc
        "%d," //mnc_digit_len   
        "%d," //nb_id 
        "'%s'," //cu_du_id
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d,"
        "'%s'," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "'%s'," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "'%s'," 
        "%f," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "'%s'," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d," 
        "%d" 
        ");"
        , tstamp
        , id->type
        , id->plmn.mcc
        , id->plmn.mnc
        , id->plmn.mnc_digit_len
        , id->nb_id.nb_id 
        , id->cu_du_id ? c_cu_du_id : c_null
        , sib2->additional_spectrum_emission
        , sib2->ul_bw_present
        , sib2->ul_carrier_freq_present
        , sib2->modification_period_coeff
        , sib2->default_paging_cycle
        , sib2->nB 
        , sib2->p_b
        , sib2->rs_power
        , sib2->high_speed_flag
        , sib2->prach_config_index
        , sib2->prach_freq_offset
        , sib2->zero_correlation_zone_config
        , sib2->root_sequence_index
        , sib2->delta_pucch_shift
        , sib2->n1_pucch_an
        , sib2->n_cs_an
        , sib2->n_rb_cqi
        , sib2->enable_64_qam
        , sib2->hopping_mode
        , sib2->n_sb
        , sib2->pusch_hopping_offset
        , sib2->cyclic_shift
        , sib2->group_assignment_pusch
        , sib2->group_hopping_enabled
        , sib2->sequence_hopping_enabled
        , sib2->mac_con_res_timer
        , sib2->max_harq_msg3_tx
        , sib2->num_ra_preambles
        , sib2->preamble_init_rx_target_pwr 
        , sib2->preamble_trans_max
        , sib2->pwr_ramping_step
        , sib2->ra_resp_win_size
        , sib2->ul_cp_length
        , sib2->alpha
        , sib2->format_1
        , sib2->format_1b
        , sib2->format_2
        , sib2->format_2a
        , sib2->format_2b
        , sib2->delta_preamble_msg3
        , sib2->p0_nominal_pucch
        , sib2->p0_nominal_pusch
        , sib2->time_alignment_timer
        , sib2->n310
        , sib2->n311
        , sib2->t300
        , sib2->t301
        , sib2->t310
        , sib2->t311
        );
  assert(rc < (int)max && "Not enough space in the char array to write all the data");
  return rc;
}

static
int to_sql_string_zxc_rb(global_e2_node_id_t const* id,zxc_radio_bearer_stats_t* zxc, int64_t tstamp, char* out, size_t out_len)
{
  assert(zxc != NULL);
  assert(out != NULL);
  const size_t max = 1024;
  assert(out_len >= max);

  char* c_null = NULL;
  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int const rc = snprintf(out, max,
        "INSERT INTO ZXC_bearer VALUES("
        "%ld,"// tstamp
        "%d," //ngran_node  
        "%d," //mcc
        "%d," //mnc
        "%d," //mnc_digit_len   
        "%d," //nb_id 
        "'%s'," //cu_du_id
        "'%s'," // zxc --> enb
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'" 
        ");"
        , tstamp
        , id->type
        , id->plmn.mcc
        , id->plmn.mnc
        , id->plmn.mnc_digit_len
        , id->nb_id.nb_id 
        , id->cu_du_id ? c_cu_du_id : c_null
        , zxc->bbu_addr
        , zxc->cell_id
        , zxc->enb_id
        , zxc->geran_ci
        , zxc->geran_lac
        , zxc->gtp_bind_addr
        , zxc->mcc
        , zxc->mme_addr
        , zxc->mnc
        , zxc->n_prb
        , zxc->name
        , zxc->nof_ports
        , zxc->p_a
        , zxc->phy_cell_id
        , zxc->rru_addr
        , zxc->s1c_bind_addr
        , zxc->sec1_pci
        , zxc->sec1_x2_bind_addr
        , zxc->sec2_pci
        , zxc->sec2_x2_bind_addr
        , zxc->sec3_x2_bind_addr
        , zxc->sector_id
        , zxc->tac
        , zxc->tm
        , zxc->ws_port
        );
  assert(rc < (int)max && "Not enough space in the char array to write all the data");
  return rc;
}

static
int to_sql_string_enb_conf_rb(global_e2_node_id_t const* id,enb_conf_stats_t* enb_conf, int64_t tstamp, char* out, size_t out_len)
{
  assert(enb_conf != NULL);
  assert(out != NULL);
  const size_t max = 1024;
  assert(out_len >= max);

  char* c_null = NULL;
  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int const rc = snprintf(out, max,
        "INSERT INTO ENB_CONF VALUES("
        "%ld,"// tstamp
        "%d," //ngran_node  
        "%d," //mcc
        "%d," //mnc
        "%d," //mnc_digit_len   
        "%d," //nb_id 
        "'%s'," //cu_du_id
        "'%s'," // enb_conf --> enb
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s'," 
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s',"
        "'%s'," 
        "'%s'" 
        ");"
        , tstamp
        , id->type
        , id->plmn.mcc
        , id->plmn.mnc
        , id->plmn.mnc_digit_len
        , id->nb_id.nb_id 
        , id->cu_du_id ? c_cu_du_id : c_null
        , enb_conf->bbu_addr
        , enb_conf->cell_id
        , enb_conf->enb_id
        , enb_conf->geran_ci
        , enb_conf->geran_lac
        , enb_conf->gtp_bind_addr
        , enb_conf->mcc
        , enb_conf->mme_addr
        , enb_conf->mnc
        , enb_conf->n_prb
        , enb_conf->name
        , enb_conf->nof_ports
        , enb_conf->p_a
        , enb_conf->phy_cell_id
        , enb_conf->rru_addr
        , enb_conf->s1c_bind_addr
        , enb_conf->sec1_pci
        , enb_conf->sec1_x2_bind_addr
        , enb_conf->sec2_pci
        , enb_conf->sec2_x2_bind_addr
        , enb_conf->sec3_x2_bind_addr
        , enb_conf->sector_id
        , enb_conf->tac
        , enb_conf->tm
        , enb_conf->ws_port
        , enb_conf->drb_config
        , enb_conf->mbms_sib_config
        , enb_conf->rr_config
        , enb_conf->sib_config
        , enb_conf->accept_handover_ratio
        , enb_conf->agc_energy_b2x0
        , enb_conf->alpha
        , enb_conf->bi
        , enb_conf->bi_flag
        , enb_conf->csfb_geran_list
        , enb_conf->eea_pref_list
        , enb_conf->eia_pref_list
        , enb_conf->enable_mbsfn
        , enb_conf->geran_csfb_flag
        , enb_conf->handover_drb_id
        , enb_conf->link_failure_nof_err
        , enb_conf->m1u_if_addr
        , enb_conf->m1u_multiaddr
        , enb_conf->mbms_file
        , enb_conf->metrics_addr
        , enb_conf->metrics_period_secs
        , enb_conf->metrics_port
        , enb_conf->nof_phy_threads
        , enb_conf->packet_size
        , enb_conf->pusch_max_its
        , enb_conf->radio_unit
        , enb_conf->rrc_connected
        , enb_conf->rrc_inactivity_timer
        , enb_conf->snr_pucch
        , enb_conf->snr_pusch
        , enb_conf->enable_gui
        , enb_conf->all_hex_limit
        , enb_conf->all_level
        , enb_conf->file_max_size
        , enb_conf->filename_log
        , enb_conf->enable_pcap
        , enb_conf->filename_pcap
        , enb_conf->dl_earfcn
        , enb_conf->rx_gain
        , enb_conf->tx_gain
        , enb_conf->nof_ctrl_symbols
        , enb_conf->pdsch_max_mcs1
        , enb_conf->pdsch_max_mcs2
        , enb_conf->pusch_max_mcs
        );
  assert(rc < (int)max && "Not enough space in the char array to write all the data");
  return rc;
}

static
int to_sql_string_counters_rb(global_e2_node_id_t const* id, counters_stats_t* counters, int64_t tstamp, char* out, size_t out_len)
{
  printf(" out_len = %d\n", out_len);
  assert(counters != NULL);
  assert(out != NULL);
  const size_t max = 2048;
  assert(out_len >= max);

  char* c_null = NULL;
  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int const rc = snprintf(out, max,
        "INSERT INTO COUNTERS VALUES("
        "%ld,"// tstamp
        "%d," //ngran_node  
        "%d," //mcc
        "%d," //mnc
        "%d," //mnc_digit_len   
        "%d," //nb_id 
        "'%s'," //cu_du_id
        "'%u',"
        "'%u',"
        "'%f'," // counters !
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"         
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f'," 
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f',"
        "'%f'," 
        "'%f'" 
        ");"
        , tstamp
        , id->type
        , id->plmn.mcc
        , id->plmn.mnc
        , id->plmn.mnc_digit_len
        , id->nb_id.nb_id 
        , id->cu_du_id ? c_cu_du_id : c_null
        , counters->sector_number
        , counters->time_stamp
        , counters->dl_bitrate
        , counters->dl_errors
        , counters->dl_nas_transport
        , counters->dl_tx
        , counters->dl_use_avg
        , counters->dl_use_max
        , counters->dl_use_min
        , counters->dl_use_online
        , counters->nof_pdcp_pak
        , counters->nof_fail_pdcp_pak
        , counters->dl_nof_volte_pak
        , counters->dl_nof_fail_volte_pak
        , counters->dl_trafic_volte
        , counters->erab_count_avg
        , counters->erab_count_max
        , counters->erab_count_min
        , counters->erab_modify_request
        , counters->erab_modify_response
        , counters->erab_release_command
        , counters->erab_release_response
        , counters->erab_setup_request
        , counters->erab_setup_response
        , counters->volte_erab_attempts
        , counters->number_of_rach
        , counters->number_of_rar
        , counters->max_time_adv
        , counters->call_duration
        , counters->rrc_connection_reconfiguration
        , counters->rrc_connection_reconfiguration_complete
        , counters->rrc_connection_reestablishment
        , counters->rrc_connection_reestablishment_reject
        , counters->rrc_connection_reestablishment_request
        , counters->rrc_connection_reconfiguration_modify_bearer
        , counters->rrc_connection_reconfiguration_new_bearer
        , counters->rrc_connection_reconfiguration_rem_bearer
        , counters->rrc_connection_reconfiguration_handover
        , counters->rrc_connection_reconfiguration_mac_ce
        , counters->rrc_connection_reject
        , counters->rrc_connection_release
        , counters->rrc_connection_request
        , counters->rrc_connection_setup
        , counters->rrc_connection_setup_complete
        , counters->rrc_dl_information_transfer
        , counters->rrc_security_mode_command
        , counters->rrc_security_mode_complete
        , counters->rrc_security_mode_failure
        , counters->rrc_ue_capability_enquiry
        , counters->rrc_ue_capability_information
        , counters->rrc_ul_information_transfer
        , counters->csfb_attempt
        , counters->csfb_success
        , counters->srvcc_attempt
        , counters->srvcc_success
        , counters->volte_qci1_attempts
        , counters->success_volte_establishment_qci1
        , counters->csfb_geran_attempt
        , counters->csfb_umts_attempt
        , counters->handover_success_inter_sec
        , counters->handover_request_inter_sec
        , counters->s1_setup_failure
        , counters->s1_setup_request
        , counters->s1_setup_response
        , counters->handover_request
        , counters->handover_request_acknowledge
        , counters->handover_send_notify
        , counters->handover_success
        , counters->handover_failure
        , counters->ue_context_modify_response
        , counters->handover_success_volte
        , counters->ue_context_modify_failure
        , counters->ue_context_modify_request
        , counters->ue_context_release_command
        , counters->ue_context_release_complete
        , counters->ue_context_release_request
        , counters->ue_context_setup_complete
        , counters->ue_count_avg
        , counters->ue_count_max
        , counters->ue_count_min
        , counters->ue_count_online
        , counters->initial_context_setup_request
        , counters->initial_context_setup_failure
        , counters->initial_context_setup_response
        , counters->initial_ue_message
        , counters->mme_status_transfer
        , counters->ul_bitrate
        , counters->ul_errors
        , counters->ul_nas_transport
        , counters->ul_tx
        , counters->ul_use_avg
        , counters->ul_use_max
        , counters->ul_use_min
        , counters->ul_use_online
        , counters->ul_interference
        , counters->ul_trafic_volte
        );
  assert(rc < (int)max && "Not enough space in the char array to write all the data");
  return rc;
}

static
int to_sql_string_pdcp_rb(global_e2_node_id_t const* id, pdcp_radio_bearer_stats_t* pdcp, int64_t tstamp, char* out, size_t out_len)
{                              
  assert(pdcp != NULL);        
  assert(out != NULL);
  const size_t max = 512;      
  assert(out_len >= max);

  char* c_null = NULL;
  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int rc = snprintf(out, out_len, 
      "INSERT INTO PDCP_bearer VALUES("
        "%ld," //tstamp         
        "%d," //ngran_node  
        "%d," //mcc
        "%d," //mnc
        "%d," //mnc_digit_len   
        "%d," //nb_id 
        "'%s'," //cu_du_id
        "%u," //txpdu_pkts       
        "%u," //txpdu_bytes     
        "%u," // txpdu_sn   
        "%u," //rxpdu_pkts      
        "%u," //rxpdu_bytes     
        "%u,"     //rxpdu_sn    
        "%u," //rxpdu_oo_pkts   
        "%u," //rxpdu_oo_bytes  
        "%u,"   //rxpdu_dd_pkts 
        "%u,"  //rxpdu_dd_bytes 
        "%u," //rxpdu_ro_count  
        "%u,"//txsdu_pkts
        "%u," //txsdu_bytes     
        "%u,"//rxsdu_pkts
        "%u," //rxsdu_bytes     
        "%u," //rnti            
        "%u," //mode            
        "%u" //rbid
        ");"
        , tstamp               
        , id->type
        , id->plmn.mcc
        , id->plmn.mnc
        , id->plmn.mnc_digit_len
        , id->nb_id.nb_id 
        , id->cu_du_id ? c_cu_du_id : c_null
        , pdcp->txpdu_pkts     
        , pdcp->txpdu_bytes    
        , pdcp->txpdu_sn       
        , pdcp->rxpdu_pkts     
        , pdcp->rxpdu_bytes    
        , pdcp->rxpdu_sn       
        , pdcp->rxpdu_oo_pkts  
        , pdcp->rxpdu_oo_bytes 
        , pdcp->rxpdu_dd_pkts  
        , pdcp->rxpdu_dd_bytes 
        , pdcp->rxpdu_ro_count 
        , pdcp->txsdu_pkts     
        , pdcp->txsdu_bytes    
        , pdcp->rxsdu_pkts     
        , pdcp->rxsdu_bytes    
        , pdcp->rnti           
        , pdcp->mode           
        , pdcp->rbid           
        );                     
  assert(rc < (int)max && "Not enough space in the char array to write all the data");
  return rc;
}

static
int to_sql_string_ue_slice_rb(global_e2_node_id_t const* id, ue_slice_conf_t const* ues, ue_slice_assoc_t const* u, int64_t tstamp, char* out, size_t out_len)
{
  assert(ues != NULL);
  assert(out != NULL);
  const size_t max = 512;
  assert(out_len >= max);

  char* c_null = NULL;
  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int rc = 0;
  if (u == NULL) {
    rc = snprintf(out, out_len,
                  "INSERT INTO UE_SLICE VALUES("
                  "%ld,"   // tstamp
                  "%d,"    // ngran_node
                  "%d,"    // mcc
                  "%d,"    // mnc
                  "%d,"    // mnc_digit_len
                  "%d,"    // nb_id
                  "'%s',"  // cu_du_id
                  "%d,"    // dl->len_ue_slices
                  "%d,"    // ues[i]->rnti
                  "%d"     // ues[i]->dl_id
                  ");"
                  , tstamp, id->type, id->plmn.mcc, id->plmn.mnc, id->plmn.mnc_digit_len, id->nb_id.nb_id
                  , id->cu_du_id ? c_cu_du_id : c_null
                  , ues->len_ue_slice, -1, -1);
    assert(rc < (int)max && "Not enough space in the char array to write all the data");
    return rc;
  }

  rc = snprintf(out, out_len,
                "INSERT INTO UE_SLICE VALUES("
                "%ld,"   // tstamp
                "%d,"    // ngran_node
                "%d,"    // mcc
                "%d,"    // mnc
                "%d,"    // mnc_digit_len
                "%d,"    // nb_id
                "'%s',"  // cu_du_id
                "%d,"    // dl->len_ue_slices
                "%d,"    // ues[i]->rnti
                "%d"     // ues[i]->dl_id
                ");"
                , tstamp, id->type, id->plmn.mcc, id->plmn.mnc, id->plmn.mnc_digit_len, id->nb_id.nb_id
                , id->cu_du_id ? c_cu_du_id : c_null
                , ues->len_ue_slice, u->rnti, u->dl_id);
  assert(rc < (int)max && "Not enough space in the char array to write all the data");
  return rc;
}

static
int to_sql_string_slice_rb(global_e2_node_id_t const* id, ul_dl_slice_conf_t const* slices, fr_slice_t const* s, int64_t tstamp, char* out, size_t out_len)
{
  assert(slices != NULL);
  assert(out != NULL);
  const size_t max = 1024;
  assert(out_len >= max);

  char* c_null = NULL;
  char sched_name[50];
  sched_name[0] = '\0';
  strncat(sched_name, slices->sched_name, slices->len_sched_name);

  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int rc = 0;
  if (s == NULL) {
    rc = snprintf(out, out_len,
                  "INSERT INTO SLICE VALUES("
                  "%ld,"   // tstamp
                  "%d,"    // ngran_node
                  "%d,"    // mcc
                  "%d,"    // mnc
                  "%d,"    // mnc_digit_len
                  "%d,"    // nb_id
                  "'%s',"  // cu_du_id
                  "%d,"    // dl->len_slices
                  "'%s',"  // dl->sched_name
                  "%u,"    // dl->slice[i].id
                  "'%s',"  // dl->slice[i].label
                  "'%s',"  // dl->slice[i]->params.type
                  "'%s',"  // dl->slice[i]->params.u.nvs.conf
                  "'%s',"  // dl->slice[i].sched
                  "%.2f,"  // dl->slice[i]->params.u.sta.pos_high/nvs.u.rate.u1.mbps_required/nvs.u.capacity.u.pct_reserved/edf.deadline
                  "%.2f,"  // dl->slice[i]->params.u.sta.pos_high/nvs.u.rate.u2.mbps_reference/edf.guaranteed_prbs
                  "%.2f"  // dl->slice[i]->params.u.edf.max_replenish
                  ");"
                  , tstamp, id->type, id->plmn.mcc, id->plmn.mnc, id->plmn.mnc_digit_len, id->nb_id.nb_id
                  , id->cu_du_id ? c_cu_du_id : c_null
                  , 0, sched_name, 0, c_null, c_null, c_null, c_null, 0.00, 0.00, 0.00);
    assert(rc < (int)max && "Not enough space in the char array to write all the data");
    return rc;
  }

  char label[50];
  label[0] = '\0';
  strncat(label, s->label, s->len_label);
  char params_type[10];
  params_type[0] = '\0';
  char params_type_conf[10];
  params_type_conf[0] = '\0';
  char sched[50];
  sched[0] = '\0';
  strncat(sched, s->sched, s->len_sched);
  if (s->params.type == SLICE_ALG_SM_V0_STATIC) {
    strcat(params_type, "STATIC");
    rc = snprintf(out, out_len,
                  "INSERT INTO SLICE VALUES("
                  "%ld,"   // tstamp
                  "%d,"    // ngran_node
                  "%d,"    // mcc
                  "%d,"    // mnc
                  "%d,"    // mnc_digit_len
                  "%d,"    // nb_id
                  "'%s',"  // cu_du_id
                  "%d,"    // dl->len_slices
                  "'%s',"  // dl->sched_name
                  "%u,"    // dl->slice[i].id
                  "'%s',"  // dl->slice[i].label
                  "'%s',"  // dl->slice[i]->params.type
                  "'%s',"  // dl->slice[i]->params.u.nvs.conf
                  "'%s',"  // dl->slice[i].sched
                  "%d,"    // dl->slice[i]->params.u.sta.pos_high/nvs.u.rate.u1.mbps_required/nvs.u.capacity.u.pct_reserved/edf.deadline
                  "%d,"    // dl->slice[i]->params.u.sta.pos_high/nvs.u.rate.u2.mbps_reference/edf.guaranteed_prbs
                  "%.2f"  // dl->slice[i]->params.u.edf.max_replenish
                  ");"
                  , tstamp, id->type, id->plmn.mcc, id->plmn.mnc, id->plmn.mnc_digit_len, id->nb_id.nb_id
                  , id->cu_du_id ? c_cu_du_id : c_null
                  , slices->len_slices, c_null
                  , s->id, label, params_type, c_null, sched
                  , s->params.u.sta.pos_low, s->params.u.sta.pos_high, 0.00);
  } else if (s->params.type == SLICE_ALG_SM_V0_NVS) {
    strcat(params_type, "NVS");
    if (s->params.u.nvs.conf == SLICE_SM_NVS_V0_RATE) {
      strcat(params_type_conf, "RATE");
      rc = snprintf(out, out_len,
                    "INSERT INTO SLICE VALUES("
                    "%ld,"   // tstamp
                    "%d,"    // ngran_node
                    "%d,"    // mcc
                    "%d,"    // mnc
                    "%d,"    // mnc_digit_len
                    "%d,"    // nb_id
                    "'%s',"  // cu_du_id
                    "%d,"    // dl->len_slices
                    "'%s',"  // dl->sched_name
                    "%u,"    // dl->slice[i].id
                    "'%s',"  // dl->slice[i].label
                    "'%s',"  // dl->slice[i]->params.type
                    "'%s',"  // dl->slice[i]->params.u.nvs.conf
                    "'%s',"  // dl->slice[i].sched
                    "%.2f,"  // dl->slice[i]->params.u.sta.pos_high/nvs.u.rate.u1.mbps_required/nvs.u.capacity.u.pct_reserved/edf.deadline
                    "%.2f,"  // dl->slice[i]->params.u.sta.pos_high/nvs.u.rate.u2.mbps_reference/edf.guaranteed_prbs
                    "%.2f"  // dl->slice[i]->params.u.edf.max_replenish
                    ");"
                    , tstamp, id->type, id->plmn.mcc, id->plmn.mnc, id->plmn.mnc_digit_len, id->nb_id.nb_id
                    , id->cu_du_id ? c_cu_du_id : c_null
                    , slices->len_slices, c_null
                    , s->id, label, params_type, params_type_conf, sched
                    , s->params.u.nvs.u.rate.u1.mbps_required, s->params.u.nvs.u.rate.u2.mbps_reference, 0.00);
      } else if (s->params.u.nvs.conf == SLICE_SM_NVS_V0_CAPACITY) {
        strcat(params_type_conf, "CAPACITY");
        rc = snprintf(out, out_len,
                      "INSERT INTO SLICE VALUES("
                      "%ld,"   // tstamp
                      "%d,"    // ngran_node
                      "%d,"    // mcc
                      "%d,"    // mnc
                      "%d,"    // mnc_digit_len
                      "%d,"    // nb_id
                      "'%s',"  // cu_du_id
                      "%d,"    // dl->len_slices
                      "'%s',"  // dl->sched_name
                      "%u,"    // dl->slice[i].id
                      "'%s',"  // dl->slice[i].label
                      "'%s',"  // dl->slice[i]->params.type
                      "'%s',"  // dl->slice[i]->params.u.nvs.conf
                      "'%s',"  // dl->slice[i].sched
                      "%.2f,"  // dl->slice[i]->params.u.sta.pos_high/nvs.u.rate.u1.mbps_required/nvs.u.capacity.u.pct_reserved/edf.deadline
                      "%.2f,"  // dl->slice[i]->params.u.sta.pos_high/nvs.u.rate.u2.mbps_reference/edf.guaranteed_prbs
                      "%.2f"  // dl->slice[i]->params.u.edf.max_replenish
                      ");"
                      , tstamp, id->type, id->plmn.mcc, id->plmn.mnc, id->plmn.mnc_digit_len, id->nb_id.nb_id
                      , id->cu_du_id ? c_cu_du_id : c_null
                      , slices->len_slices, c_null
                      , s->id, label, params_type, params_type_conf, sched
                      , s->params.u.nvs.u.capacity.u.pct_reserved, 0.00, 0.00);
      }
  } else if (s->params.type == SLICE_ALG_SM_V0_EDF) {
    strcat(params_type, "EDF");
    rc = snprintf(out, out_len,
                  "INSERT INTO SLICE VALUES("
                  "%ld,"   // tstamp
                  "%d,"    // ngran_node
                  "%d,"    // mcc
                  "%d,"    // mnc
                  "%d,"    // mnc_digit_len
                  "%d,"    // nb_id
                  "'%s',"  // cu_du_id
                  "%d,"    // dl->len_slices
                  "'%s',"  // dl->sched_name
                  "%u,"    // dl->slice[i].id
                  "'%s',"  // dl->slice[i].label
                  "'%s',"  // dl->slice[i]->params.type
                  "'%s',"  // dl->slice[i]->params.u.nvs.conf
                  "'%s',"  // dl->slice[i].sched
                  "%d,"  // dl->slice[i]->params.u.sta.pos_high/nvs.u.rate.u1.mbps_required/nvs.u.capacity.u.pct_reserved/edf.deadline
                  "%d,"  // dl->slice[i]->params.u.sta.pos_high/nvs.u.rate.u2.mbps_reference/edf.guaranteed_prbs
                  "%d"  // dl->slice[i]->params.u.edf.max_replenish
                  ");"
                  , tstamp, id->type, id->plmn.mcc, id->plmn.mnc, id->plmn.mnc_digit_len, id->nb_id.nb_id
                  , id->cu_du_id ? c_cu_du_id : c_null
                  , slices->len_slices, c_null
                  , s->id, label, params_type, c_null, sched
                  , s->params.u.edf.deadline
                  , s->params.u.edf.guaranteed_prbs
                  , s->params.u.edf.max_replenish);
  }
  assert(rc < (int) max && "Not enough space in the char array to write all the data");
  return rc;
}

static
int to_sql_string_gtp_NGUT(global_e2_node_id_t const* id,gtp_ngu_t_stats_t* gtp, int64_t tstamp, char* out, size_t out_len)
{
  assert(gtp != NULL);
  assert(out != NULL);
  const size_t max = 1024;
  assert(out_len >= max);

  char* c_null = NULL;
  char c_cu_du_id[26];
  if (id->cu_du_id) {
    int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
    assert(rc < (int) max && "Not enough space in the char array to write all the data");
  }

  int const rc = snprintf(out, max,
        "INSERT INTO GTP_NGUT VALUES("
        "%ld," //tstamp         
        "%d," //ngran_node  
        "%d," //mcc
        "%d," //mnc
        "%d," //mnc_digit_len   
        "%d," //nb_id 
        "'%s'," //cu_du_id
        "%u," //teidgnb    
        "%u," //rnti
        "%u," // qfi   
        "%u" //teidupf
        ");"
        , tstamp               
        , id->type
        , id->plmn.mcc
        , id->plmn.mnc
        , id->plmn.mnc_digit_len
        , id->nb_id.nb_id
        , id->cu_du_id ? c_cu_du_id : c_null
        , gtp->teidgnb
        , gtp->rnti   
        , gtp->qfi    
        , gtp->teidupf    
        );      
  assert(rc < (int)max && "Not enough space in the char array to write all the data");
  return rc;
}

// static
// void to_sql_string_kpm_measRecord(global_e2_node_id_t const* id,  
//                                  MeasDataItem_t* kpm_measData, 
//                                  MeasRecord_t* kpm_measRecord, 
//                                  uint32_t tstamp, 
//                                  char* out, 
//                                  size_t out_len)
// {
//   assert(kpm_measData != NULL);
//   assert(out != NULL);
//   const size_t max = 512;
//   assert(out_len >= max);

//   char* c_null = NULL;
//   char c_cu_du_id[26];
//   if (id->cu_du_id) {
//     int rc = snprintf(c_cu_du_id, 26, "%lu", *id->cu_du_id);
//     assert(rc < (int) max && "Not enough space in the char array to write all the data");
//   }

//   if (kpm_measRecord == NULL){
//     int const rc = snprintf(out, max,
//         "INSERT INTO KPM_MeasRecord VALUES("
//         "%u,"// tstamp
//         "%d," //ngran_node  
//         "%d," //mcc
//         "%d," //mnc
//         "%d," //mnc_digit_len   
//         "%d," //nb_id 
//         "'%s'," //cu_du_id
//         "%p,"  //kpm_measData->incompleteFlag
//         "NULL"  //kpm_measRecord->int_val
//         ");" 
//         , tstamp
//         , id->type
//         , id->plmn.mcc
//         , id->plmn.mnc
//         , id->plmn.mnc_digit_len
//         , id->nb_id
//         , id->cu_du_id ? c_cu_du_id : c_null
//         , (void *)kpm_measData->incompleteFlag
//         // , granulPeriod
//         );
//     assert(rc < (int)max && "Not enough space in the char array to write all the data");
//     return ;
//   } else {
//     if(kpm_measRecord->type == MeasRecord_int){
//       int const rc = snprintf(out, max,
//           "INSERT INTO KPM_MeasRecord VALUES("
//           "%u,"// tstamp
//           "%d," //ngran_node  
//           "%d," //mcc
//           "%d," //mnc
//           "%d," //mnc_digit_len   
//           "%d," //nb_id
//           "'%s'," //cu_du_id
//           "%p,"  //kpm_measData->incompleteFlag
//           "%ld"  //kpm_measRecord->int_val
//           ");" 
//           , tstamp
//           , id->type
//           , id->plmn.mcc
//           , id->plmn.mnc
//           , id->plmn.mnc_digit_len
//           , id->nb_id
//           , id->cu_du_id ? c_cu_du_id : c_null
//           , (void *)kpm_measData->incompleteFlag
//           , kpm_measRecord->int_val
//           );
//       assert(rc < (int)max && "Not enough space in the char array to write all the data");
//       return;
//     }else if (kpm_measRecord->type == MeasRecord_real){
//       int const rc = snprintf(out, max,
//           "INSERT INTO KPM_MeasRecord VALUES("
//           "%u,"// tstamp
//           "%d," //ngran_node  
//           "%d," //mcc
//           "%d," //mnc
//           "%d," //mnc_digit_len   
//           "%d," //nb_id 
//           "'%s'," //cu_du_id
//           "%p,"  //kpm_measData->incompleteFlag
//           "%f"  //kpm_measRecord->real_val
//           ");" 
//           , tstamp
//           , id->type
//           , id->plmn.mcc
//           , id->plmn.mnc
//           , id->plmn.mnc_digit_len
//           , id->nb_id
//           , id->cu_du_id ? c_cu_du_id : c_null
//           , (void *)kpm_measData->incompleteFlag
//           , kpm_measRecord->real_val
//           );
//       assert(rc < (int)max && "Not enough space in the char array to write all the data");
//       return;
//     }else if (kpm_measRecord->type == MeasRecord_noval){
//       int const rc = snprintf(out, max,
//           "INSERT INTO KPM_MeasRecord VALUES("
//           "%u,"// tstamp
//           "%d," //ngran_node  
//           "%d," //mcc
//           "%d," //mnc
//           "%d," //mnc_digit_len   
//           "%d," //nb_id 
//           "'%s'," //cu_du_id
//           "%p,"  //kpm_measData->incompleteFlag
//           "-1"  //kpm_measRecord->noVal
//           ");" 
//           , tstamp
//           , id->type
//           , id->plmn.mcc
//           , id->plmn.mnc
//           , id->plmn.mnc_digit_len
//           , id->nb_id
//           , id->cu_du_id ? c_cu_du_id : c_null
//           , (void *)kpm_measData->incompleteFlag
//           );
//       assert(rc < (int)max && "Not enough space in the char array to write all the data");
//       return;
//     }
//   }
//   assert(0!=0 && "Bad input data. Nothing for SQL to be created");
// }

static
void write_mac_stats(sqlite3* db, global_e2_node_id_t const* id, mac_ind_data_t const* ind )
{
  assert(db != NULL);
  assert(ind != NULL);

  mac_ind_msg_t const* ind_msg_mac = &ind->msg; 

  char buffer[2048] = {0};
  int pos = 0;

  for(size_t i = 0; i < ind_msg_mac->len_ue_stats; ++i){
    pos += to_sql_string_mac_ue(id, &ind_msg_mac->ue_stats[i], ind_msg_mac->tstamp, buffer + pos, 2048 - pos);
  }

  insert_db(db, buffer);
}

static
void write_rlc_stats(sqlite3* db, global_e2_node_id_t const* id, rlc_ind_data_t const* ind)
{
  assert(db != NULL);
  assert(ind != NULL);

  rlc_ind_msg_t const* ind_msg_rlc = &ind->msg; 

  char buffer[2048] = {0};
  int pos = 0;

  for(size_t i = 0; i < ind_msg_rlc->len; ++i){
    pos += to_sql_string_rlc_rb(id, &ind_msg_rlc->rb[i], ind_msg_rlc->tstamp, buffer + pos, 2048 - pos);
  }

  insert_db(db, buffer);

}

static
void write_zxc_stats(sqlite3* db, global_e2_node_id_t const* id, zxc_ind_data_t const* ind)
{
  assert(db != NULL);
  assert(ind != NULL);

  zxc_ind_msg_t const* ind_msg_zxc = &ind->msg; 

  char buffer[2048] = {0};
  int pos = 0;

  for(size_t i = 0; i < ind_msg_zxc->len; ++i){
    pos += to_sql_string_zxc_rb(id, &ind_msg_zxc->rb[i], ind_msg_zxc->tstamp, buffer + pos, 2048 - pos);
  }

  insert_db(db, buffer);

}

static
void write_sib1_stats(sqlite3* db, global_e2_node_id_t const* id, sib1_ind_data_t const* ind)
{
  assert(db != NULL);
  assert(ind != NULL);

  sib1_ind_msg_t const* ind_msg_sib1 = &ind->msg; 

  char buffer[2048] = {0};
  int pos = 0;

  for(size_t i = 0; i < ind_msg_sib1->len; ++i){
    pos += to_sql_string_sib1_rb(id, &ind_msg_sib1->rb[i], ind_msg_sib1->tstamp, buffer + pos, 2048 - pos);
  }

  insert_db(db, buffer);

}

static
void write_uetrace_stats(sqlite3* db, global_e2_node_id_t const* id, uetrace_ind_data_t const* ind)
{
  assert(db != NULL);
  assert(ind != NULL);

  uetrace_ind_msg_t const* ind_msg_uetrace = &ind->msg; 

  char buffer[40960] = {0};
  int pos = 0;

  for(size_t i = 0; i < ind_msg_uetrace->len; ++i){
    pos += to_sql_string_uetrace_rb(id, &ind_msg_uetrace->rb[i], ind_msg_uetrace->tstamp, buffer + pos, 40960 - pos);
  }

  insert_db(db, buffer);

}

static
void write_sib2_stats(sqlite3* db, global_e2_node_id_t const* id, sib2_ind_data_t const* ind)
{
  assert(db != NULL);
  assert(ind != NULL);

  sib2_ind_msg_t const* ind_msg_sib2 = &ind->msg; 

  char buffer[2048] = {0};
  int pos = 0;

  for(size_t i = 0; i < ind_msg_sib2->len; ++i){
    pos += to_sql_string_sib2_rb(id, &ind_msg_sib2->rb[i], ind_msg_sib2->tstamp, buffer + pos, 2048 - pos);
  }

  insert_db(db, buffer);

}

static
void write_rr_stats(sqlite3* db, global_e2_node_id_t const* id, rr_ind_data_t const* ind)
{
  assert(db != NULL);
  assert(ind != NULL);

  rr_ind_msg_t const* ind_msg_rr = &ind->msg; 

  char buffer[2048] = {0};
  int pos = 0;

  for(size_t i = 0; i < ind_msg_rr->len; ++i){
    pos += to_sql_string_rr_rb(id, &ind_msg_rr->rb[i], ind_msg_rr->tstamp, buffer + pos, 2048 - pos);
  }

  insert_db(db, buffer);

}

static
void write_enb_conf_stats(sqlite3* db, global_e2_node_id_t const* id, enb_conf_ind_data_t const* ind)
{
  assert(db != NULL);
  assert(ind != NULL);

  enb_conf_ind_msg_t const* ind_msg_enb_conf = &ind->msg; 

  char buffer[2048] = {0};
  int pos = 0;

  for(size_t i = 0; i < ind_msg_enb_conf->len; ++i){
      pos += to_sql_string_enb_conf_rb(id, &ind_msg_enb_conf->rb[i], ind_msg_enb_conf->tstamp, buffer + pos, 2048 - pos);
  }

  insert_db(db, buffer);

}

static
void write_counters_stats(sqlite3* db, global_e2_node_id_t const* id, counters_ind_data_t const* ind)
{
  assert(db != NULL);
  assert(ind != NULL);

  counters_ind_msg_t const* ind_msg_counters = &ind->msg; 

  char buffer[5120] = {0};
  int pos = 0;

  for(size_t i = 0; i < ind_msg_counters->len; ++i){
    if (ind_msg_counters->rb[i].sector_number > 0)
    {
      pos += to_sql_string_counters_rb(id, &ind_msg_counters->rb[i], ind_msg_counters->tstamp, buffer + pos, 5120 - pos);
    }
        
  }

  insert_db(db, buffer);

}

static
void write_pdcp_stats(sqlite3* db, global_e2_node_id_t const* id, pdcp_ind_data_t const* ind)
{
  assert(db != NULL);
  assert(ind != NULL);

  pdcp_ind_msg_t const* ind_msg_pdcp = &ind->msg; 

  char buffer[2048] = {0};
  int pos = 0;

  for(size_t i = 0; i < ind_msg_pdcp->len; ++i){
    pos += to_sql_string_pdcp_rb(id, &ind_msg_pdcp->rb[i], ind_msg_pdcp->tstamp, buffer + pos, 2048 - pos);
  }

  insert_db(db, buffer);
}

static
void write_slice_conf_stats(sqlite3* db, global_e2_node_id_t const* id, int64_t tstamp, slice_conf_t const* slice_conf)
{
  char buffer[4096] = {0};
  int pos = 0;

  ul_dl_slice_conf_t const* dlslices = &slice_conf->dl;
  if (dlslices->len_slices > 0) {
    for(size_t i = 0; i < dlslices->len_slices; ++i) {
      fr_slice_t const* s = &dlslices->slices[i];
      pos += to_sql_string_slice_rb(id, dlslices, s, tstamp, buffer + pos, 4096 - pos);
    }
  } else {
    pos += to_sql_string_slice_rb(id, dlslices, NULL, tstamp, buffer + pos, 4096 - pos);
  }

  // TODO: Process uplink slice stats

  insert_db(db, buffer);
}

static
void write_ue_slice_conf_stats(sqlite3* db, global_e2_node_id_t const* id, int64_t tstamp, ue_slice_conf_t const* ue_slice_conf)
{
  char buffer[4096] = {0};
  int pos = 0;

  if (ue_slice_conf->len_ue_slice > 0) {
    for(uint32_t j = 0; j < ue_slice_conf->len_ue_slice; ++j) {
      ue_slice_assoc_t *u = &ue_slice_conf->ues[j];
      pos += to_sql_string_ue_slice_rb(id, ue_slice_conf, u, tstamp, buffer + pos, 2048 - pos);
    }
  } else {
    pos += to_sql_string_ue_slice_rb(id, ue_slice_conf, NULL, tstamp, buffer + pos, 2048 - pos);
  }

  insert_db(db, buffer);
}

static
void write_slice_stats(sqlite3* db, global_e2_node_id_t const* id, slice_ind_data_t const* ind)
{
  assert(db != NULL);
  assert(ind != NULL);

  slice_ind_msg_t const* ind_msg_slice = &ind->msg;

  write_slice_conf_stats(db, id, ind_msg_slice->tstamp, &ind_msg_slice->slice_conf);
  write_ue_slice_conf_stats(db, id, ind_msg_slice->tstamp, &ind_msg_slice->ue_slice_conf);

}

static
void write_gtp_stats(sqlite3* db, global_e2_node_id_t const* id, gtp_ind_data_t const* ind)
{
  assert(db != NULL);
  assert(ind != NULL);

  gtp_ind_msg_t const* ind_msg_gtp = &ind->msg; 

  char buffer[2048] = {0};
  int pos = 0;
  for(size_t i = 0; i < ind_msg_gtp->len; ++i){
    pos += to_sql_string_gtp_NGUT(id, &ind_msg_gtp->ngut[i], ind_msg_gtp->tstamp, buffer + pos, 2048 - pos);
  }

  insert_db(db, buffer);
}

// void write_kpm_stats(sqlite3* db, global_e2_node_id_t const* id, kpm_ric_indication_t const* ind)
// {
//   // TODO: Add granulPeriod into database
//   // TODO: Add MeasInfo and LabelInfo into database

//   assert(db != NULL);
//   assert(ind != NULL);

//   kpm_ind_msg_t const* ind_msg_kpm = &ind->msg;
//   char buffer[512] = {0};


//   for(size_t i = 0; i < ind_msg_kpm->MeasData_len; i++){
//     MeasDataItem_t* curMeasData = &ind_msg_kpm->MeasData[i];
//     if (curMeasData->measRecord_len > 0){
//       for (size_t j = 0; j < curMeasData->measRecord_len; j++){
//         MeasRecord_t* curMeasRecord = &curMeasData->measRecord[j];
//         memset(buffer, 0, sizeof(buffer));
//         to_sql_string_kpm_measRecord(id, curMeasData, curMeasRecord, ind->hdr.collectStartTime, 
//                                      buffer, 512);
//         insert_db(db, buffer);
//       }
//     } else {
//       memset(buffer, 0, sizeof(buffer));
//       to_sql_string_kpm_measRecord(id, curMeasData, NULL, ind->hdr.collectStartTime, 
//                                    buffer, 512);
//       insert_db(db, buffer);
//     }
//   }
// }

void init_db_sqlite3(sqlite3** db, char const* db_filename)
{
  assert(db != NULL);
  assert(db_filename != NULL);

  int const rc = sqlite3_open(db_filename, db);
  assert(rc != SQLITE_CANTOPEN && "SQLITE3 cannot open the directory. Does it already exist?");
  assert(rc == SQLITE_OK && "Error while creating the DB at /tmp/db_xapp");

  // Optimizations. Write Ahead Logging
  char* err_msg = NULL;
  int const rc_2 = sqlite3_exec(*db, "pragma journal_mode=wal" , 0, 0, &err_msg);
  assert(rc_2 == SQLITE_OK && "Error while setting the wal mode in sqlite3");

  int const rc_3 = sqlite3_exec(*db, "pragma synchronous=normal" , 0, 0, &err_msg);
  assert(rc_3 == SQLITE_OK && "Error while setting the syncronous mode to normal");


  //////
  // MAC
  //////
  create_mac_ue_table(*db);

  //////
  // RLC
  //////
  create_rlc_bearer_table(*db);

    //////
  // zxc
  //////
  create_zxc_bearer_table(*db);

    //////
  // sib1
  //////
  create_sib1_bearer_table(*db);

    //////
  // sib2
  //////
  create_sib2_bearer_table(*db);

    //////
  // rr
  //////
  create_rr_bearer_table(*db);

    //////
  // uetrace
  //////
  create_uetrace_bearer_table(*db);

    //////
  // enb_conf
  //////
  create_enb_conf_table(*db);

  //////
  // counters
  //////
  create_counters_table(*db);

  //////
  // PDCP
  //////
  create_pdcp_bearer_table(*db);

  //////
  // SLICE
  //////
  create_slice_table(*db);
  create_ue_slice_table(*db);

  ////
  // GTP
  ////
  create_gtp_table(*db);
  // KPM
  ////
  create_kpm_table(*db);
}

void close_db_sqlite3(sqlite3* db)
{
  assert(db != NULL);
  int const rc = sqlite3_close(db);
  assert(rc == SQLITE_OK && "Error while closing the DB");
}

static
int kpm_acc = 0; 
static
int rc_acc = 0; 


void write_db_sqlite3(sqlite3* db, global_e2_node_id_t const* id, sm_ag_if_rd_t const* ag_rd)
{
  assert(db != NULL);
  assert(ag_rd != NULL);
  assert(ag_rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);

  sm_ag_if_rd_ind_t const* rd = &ag_rd->ind; 
  assert(rd->type == MAC_STATS_V0   || rd->type == RLC_STATS_V0 
      || rd->type == PDCP_STATS_V0  || rd->type == SLICE_STATS_V0 
      || rd->type == KPM_STATS_V3_0 || rd->type == GTP_STATS_V0
      || rd->type == ZXC_STATS_V0   || rd->type == RAN_CTRL_STATS_V1_03 
      || rd->type == COUNTERS_STATS_V0   || rd->type == ENB_CONF_STATS_V0
      || rd->type == SIB1_STATS_V0  || rd->type == SIB2_STATS_V0
      || rd->type == UETRACE_STATS_V0 || rd->type == RR_STATS_V0);

  if(rd->type == MAC_STATS_V0){
    write_mac_stats(db, id, &rd->mac);
  } else if(rd->type == RLC_STATS_V0 ){
    write_rlc_stats(db, id, &rd->rlc);
  } else if(rd->type == ZXC_STATS_V0){
    write_zxc_stats(db, id, &rd->zxc);
  } else if(rd->type == SIB1_STATS_V0){
    write_sib1_stats(db, id, &rd->sib1);
  } else if(rd->type == SIB2_STATS_V0){
    write_sib2_stats(db, id, &rd->sib2);
  } else if(rd->type == RR_STATS_V0){
    write_rr_stats(db, id, &rd->rr);
  } else if(rd->type == UETRACE_STATS_V0){
    write_uetrace_stats(db, id, &rd->uetrace);
  } else if(rd->type == COUNTERS_STATS_V0){
    write_counters_stats(db, id, &rd->counters);
  } else if(rd->type == ENB_CONF_STATS_V0){
    write_enb_conf_stats(db, id, &rd->enb_conf);
  } else if( rd->type == PDCP_STATS_V0) {
    write_pdcp_stats(db, id, &rd->pdcp);
  } else if (rd->type == SLICE_STATS_V0) {
    write_slice_stats(db, id, &rd->slice);
  } else if (rd->type == GTP_STATS_V0) {
    write_gtp_stats(db, id, &rd->gtp);
  } else if (rd->type == KPM_STATS_V3_0) {
    kpm_acc++;
    if(kpm_acc > 2048){
    printf("KPM sqlite not implemented\n"); 
    kpm_acc = 0;
    }
  } else if(rd->type ==  RAN_CTRL_STATS_V1_03){
    rc_acc++;
    if(rc_acc > 2048){
      printf("RAN Control sqlite not implemented\n"); 
      rc_acc = 0;
    }
  } else {
    assert(0!=0 && "Unknown statistics type received ");
  }
}


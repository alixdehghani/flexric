#include "sm_counters.h"
#include "../src/util/time_now_us.h"

static http_client_t *counters_http_client = NULL;
static uint8_t sector_num = 0;
static char *backend_addr = NULL;

#define COUNTERS_ADDR_SECTOR1 "/sector-1/performance/kpi"
#define COUNTERS_ADDR_SECTOR2 "/sector-2/performance/kpi"
#define COUNTERS_ADDR_SECTOR3 "/sector-3/performance/kpi"

void init_counters_sm(void)
{
}

void set_counters_http_client(http_client_t *client)
{
  counters_http_client = client;
}

void set_counters_num_of_sector(uint8_t num)
{
  sector_num = num;
}

void set_counters_backed_addr(char *addr)
{
  backend_addr = addr;
}

void free_counters_sm(void)
{
  // No allocation needed
}

bool read_counters_sm(void *data)
{
  assert(data != NULL);

  counters_ind_data_t *counters = (counters_ind_data_t *)data;

  assert(counters != NULL);

  srand(time(0));
  counters_ind_msg_t *ind_msg = &counters->msg;

  ind_msg->tstamp = time_now_us();

  ind_msg->len = sector_num;
  if (ind_msg->len > 0)
  {
    ind_msg->rb = calloc(ind_msg->len, sizeof(counters_stats_t));
    assert(ind_msg->rb != NULL);
  }
  for (int i = 0; i < sector_num; i++)
  {
    counters_stats_t *rb = &ind_msg->rb[i];
    char *url;
    if (i == 0)
    {
      asprintf(&url, "%s%s", backend_addr, COUNTERS_ADDR_SECTOR1);
    }

    if (i == 1)
    {
      asprintf(&url, "%s%s", backend_addr, COUNTERS_ADDR_SECTOR2);
    }

    if (i == 2)
    {
      asprintf(&url, "%s%s", backend_addr, COUNTERS_ADDR_SECTOR3);
    }
    http_result_t result_get = http_get_custome(counters_http_client, url);
    if (!result_get.success)
    {
      fprintf(stderr, "Failed to get stats\n");
      // return false;
      continue;
    }

    // printf("url is: %s\n%s\n", url, result_get.data);
    struct json_object *json_counters = json_parse_string(result_get.data);
    

    http_result_free(&result_get);

    rb->sector_number = i + 1;
    rb->time_stamp = time_now_us();

    rb->dl_bitrate = json_get_double(json_counters, "dl_bitrate");
    rb->dl_errors = json_get_double(json_counters, "dl_errors");
    rb->dl_nas_transport = json_get_double(json_counters, "dl_nas_transport");
    rb->dl_tx = json_get_double(json_counters, "dl_tx");
    rb->dl_use_avg = json_get_double(json_counters, "dl_use_avg");
    rb->dl_use_max = json_get_double(json_counters, "dl_use_max");
    rb->dl_use_min = json_get_double(json_counters, "dl_use_min");
    rb->dl_use_online = json_get_double(json_counters, "dl_use_online");
    rb->nof_pdcp_pak = json_get_double(json_counters, "nof_pdcp_pak");
    rb->nof_fail_pdcp_pak = json_get_double(json_counters, "nof_fail_pdcp_pak");
    rb->dl_nof_volte_pak = json_get_double(json_counters, "dl_nof_volte_pak");
    rb->dl_nof_fail_volte_pak = json_get_double(json_counters, "dl_nof_fail_volte_pak");
    rb->dl_trafic_volte = json_get_double(json_counters, "dl_trafic_volte");
    rb->erab_count_avg = json_get_double(json_counters, "erab_count_avg");
    rb->erab_count_max = json_get_double(json_counters, "erab_count_max");
    rb->erab_count_min = json_get_double(json_counters, "erab_count_min");
    rb->erab_modify_request = json_get_double(json_counters, "erab_modify_request");
    rb->erab_modify_response = json_get_double(json_counters, "erab_modify_response");
    rb->erab_release_command = json_get_double(json_counters, "erab_release_command");
    rb->erab_release_response = json_get_double(json_counters, "erab_release_response");
    rb->erab_setup_request = json_get_double(json_counters, "erab_setup_request");
    rb->erab_setup_response = json_get_double(json_counters, "erab_setup_response");
    rb->volte_erab_attempts = json_get_double(json_counters, "volte_erab_attempts");
    rb->number_of_rach = json_get_double(json_counters, "number_of_rach");
    rb->number_of_rar = json_get_double(json_counters, "number_of_rar");
    rb->max_time_adv = json_get_double(json_counters, "max_time_adv");
    rb->call_duration = json_get_double(json_counters, "call_duration");
    rb->rrc_connection_reconfiguration = json_get_double(json_counters, "rrc_connection_reconfiguration");
    rb->rrc_connection_reconfiguration_complete = json_get_double(json_counters, "rrc_connection_reconfiguration_complete");
    rb->rrc_connection_reestablishment = json_get_double(json_counters, "rrc_connection_reestablishment");
    rb->rrc_connection_reestablishment_reject = json_get_double(json_counters, "rrc_connection_reestablishment_reject");
    rb->rrc_connection_reestablishment_request = json_get_double(json_counters, "rrc_connection_reestablishment_request");
    rb->rrc_connection_reconfiguration_modify_bearer = json_get_double(json_counters, "rrc_connection_reconfiguration_modify_bearer");
    rb->rrc_connection_reconfiguration_new_bearer = json_get_double(json_counters, "rrc_connection_reconfiguration_new_bearer");
    rb->rrc_connection_reconfiguration_rem_bearer = json_get_double(json_counters, "rrc_connection_reconfiguration_rem_bearer");
    rb->rrc_connection_reconfiguration_handover = json_get_double(json_counters, "rrc_connection_reconfiguration_handover");
    rb->rrc_connection_reconfiguration_mac_ce = json_get_double(json_counters, "rrc_connection_reconfiguration_mac_ce");
    rb->rrc_connection_reject = json_get_double(json_counters, "rrc_connection_reject");
    rb->rrc_connection_release = json_get_double(json_counters, "rrc_connection_release");
    rb->rrc_connection_request = json_get_double(json_counters, "rrc_connection_request");
    rb->rrc_connection_setup = json_get_double(json_counters, "rrc_connection_setup");
    rb->rrc_connection_setup_complete = json_get_double(json_counters, "rrc_connection_setup_complete");
    rb->rrc_dl_information_transfer = json_get_double(json_counters, "rrc_dl_information_transfer");
    rb->rrc_security_mode_command = json_get_double(json_counters, "rrc_security_mode_command");
    rb->rrc_security_mode_complete = json_get_double(json_counters, "rrc_security_mode_complete");
    rb->rrc_security_mode_failure = json_get_double(json_counters, "rrc_security_mode_failure");
    rb->rrc_ue_capability_enquiry = json_get_double(json_counters, "rrc_ue_capability_enquiry");
    rb->rrc_ue_capability_information = json_get_double(json_counters, "rrc_ue_capability_information");
    rb->rrc_ul_information_transfer = json_get_double(json_counters, "rrc_ul_information_transfer");
    rb->csfb_attempt = json_get_double(json_counters, "csfb_attempt");
    rb->csfb_success = json_get_double(json_counters, "csfb_success");
    rb->srvcc_attempt = json_get_double(json_counters, "srvcc_attempt");
    rb->srvcc_success = json_get_double(json_counters, "srvcc_success");
    rb->volte_qci1_attempts = json_get_double(json_counters, "volte_qci1_attempts");
    rb->success_volte_establishment_qci1 = json_get_double(json_counters, "success_volte_establishment_qci1");
    rb->csfb_geran_attempt = json_get_double(json_counters, "csfb_geran_attempt");
    rb->csfb_umts_attempt = json_get_double(json_counters, "csfb_umts_attempt");
    rb->handover_success_inter_sec = json_get_double(json_counters, "handover_success_inter_sec");
    rb->handover_request_inter_sec = json_get_double(json_counters, "handover_request_inter_sec");
    rb->s1_setup_failure = json_get_double(json_counters, "s1_setup_failure");
    rb->s1_setup_request = json_get_double(json_counters, "s1_setup_request");
    rb->s1_setup_response = json_get_double(json_counters, "s1_setup_response");
    rb->handover_request = json_get_double(json_counters, "handover_request");
    rb->handover_request_acknowledge = json_get_double(json_counters, "handover_request_acknowledge");
    rb->handover_send_notify = json_get_double(json_counters, "handover_send_notify");
    rb->handover_success = json_get_double(json_counters, "handover_success");
    rb->handover_failure = json_get_double(json_counters, "handover_failure");
    rb->ue_context_modify_response = json_get_double(json_counters, "ue_context_modify_response");
    rb->handover_success_volte = json_get_double(json_counters, "handover_success_volte");
    rb->ue_context_modify_failure = json_get_double(json_counters, "ue_context_modify_failure");
    rb->ue_context_modify_request = json_get_double(json_counters, "ue_context_modify_request");
    rb->ue_context_release_command = json_get_double(json_counters, "ue_context_release_command");
    rb->ue_context_release_complete = json_get_double(json_counters, "ue_context_release_complete");
    rb->ue_context_release_request = json_get_double(json_counters, "ue_context_release_request");
    rb->ue_context_setup_complete = json_get_double(json_counters, "ue_context_setup_complete");
    rb->ue_count_avg = json_get_double(json_counters, "ue_count_avg");
    rb->ue_count_max = json_get_double(json_counters, "ue_count_max");
    rb->ue_count_min = json_get_double(json_counters, "ue_count_min");
    rb->ue_count_online = json_get_double(json_counters, "ue_count_online");
    rb->initial_context_setup_request = json_get_double(json_counters, "initial_context_setup_request");
    rb->initial_context_setup_failure = json_get_double(json_counters, "initial_context_setup_failure");
    rb->initial_context_setup_response = json_get_double(json_counters, "initial_context_setup_response");
    rb->initial_ue_message = json_get_double(json_counters, "initial_ue_message");
    rb->mme_status_transfer = json_get_double(json_counters, "mme_status_transfer");
    rb->ul_bitrate = json_get_double(json_counters, "ul_bitrate");
    rb->ul_errors = json_get_double(json_counters, "ul_errors");
    rb->ul_nas_transport = json_get_double(json_counters, "ul_nas_transport");
    rb->ul_tx = json_get_double(json_counters, "ul_tx");
    rb->ul_use_avg = json_get_double(json_counters, "ul_use_avg");
    rb->ul_use_max = json_get_double(json_counters, "ul_use_max");
    rb->ul_use_min = json_get_double(json_counters, "ul_use_min");
    rb->ul_use_online = json_get_double(json_counters, "ul_use_online");
    rb->ul_interference = json_get_double(json_counters, "ul_interference");
    rb->ul_trafic_volte = json_get_double(json_counters, "ul_trafic_volte");

    json_object_put(json_counters);
  }
  return true;
}

void read_counters_setup_sm(void *data)
{
  assert(data != NULL);
  //  assert(data->type == enb_conf_AGENT_IF_E2_SETUP_ANS_V0 );
  assert(0 != 0 && "Not supported");
}

sm_ag_if_ans_t write_ctrl_counters_sm(void const *data)
{

  assert(data != NULL);

  enb_conf_ctrl_req_data_t *ctrl = (enb_conf_ctrl_req_data_t *)data;
  // printf("Action: %d\n", ctrl->msg.action);
  printf("Dummy: %d\n", ctrl->hdr.dummy);

  enb_conf_stats_t *rb = ctrl->msg.enb_rb;
  printf("BBU Addr: %s\n", rb->bbu_addr);
  printf("Cell ID: %s\n", rb->cell_id);
  printf("ENB ID: %s\n", rb->enb_id);
  printf("GERAN CI: %s\n", rb->geran_ci);
  printf("GERAN LAC: %s\n", rb->geran_lac);
  printf("GTP Bind Addr: %s\n", rb->gtp_bind_addr);
  printf("MCC: %s\n", rb->mcc);
  printf("MME Addr: %s\n", rb->mme_addr);
  printf("MNC: %s\n", rb->mnc);
  printf("N PRB: %s\n", rb->n_prb);
  printf("Name: %s\n", rb->name);
  printf("NOF Ports: %s\n", rb->nof_ports);
  printf("P A: %s\n", rb->p_a);
  printf("PHY Cell ID: %s\n", rb->phy_cell_id);
  printf("RRU Addr: %s\n", rb->rru_addr);
  printf("S1C Bind Addr: %s\n", rb->s1c_bind_addr);
  printf("SEC1 PCI: %s\n", rb->sec1_pci);
  printf("SEC1 X2 Bind Addr: %s\n", rb->sec1_x2_bind_addr);
  printf("SEC2 PCI: %s\n", rb->sec2_pci);
  printf("SEC2 X2 Bind Addr: %s\n", rb->sec2_x2_bind_addr);
  printf("SEC3 X2 Bind Addr: %s\n", rb->sec3_x2_bind_addr);
  printf("Sector ID: %s\n", rb->sector_id);
  printf("TAC: %s\n", rb->tac);
  printf("TM: %s\n", rb->tm);
  printf("WS Port: %s\n", rb->ws_port);
  //   assert(ctrl->hdr.dummy == 0);
  //   assert(ctrl->msg.action == 42);

  json_object *root = json_object_new_object();
  if (root == NULL)
  {
    fprintf(stderr, "Error: root JSON object is NULL\n");
    return;
  }

  /* Construction enb  */
  json_object *enb = json_object_new_object();
  json_object *enb_files = json_object_new_object();
  json_object *expert = json_object_new_object();
  json_object *gui = json_object_new_object();
  json_object *log = json_object_new_object();
  json_object *pcap = json_object_new_object();
  json_object *rf = json_object_new_object();
  json_object *scheduler = json_object_new_object();

  // enb
  json_add_object(enb, "cell_barred", json_object_new_string(rb->bbu_addr));
  json_add_object(enb, "cell_id", json_object_new_string(rb->cell_id));
  json_add_object(enb, "enb_id", json_object_new_string(rb->enb_id));
  json_add_object(enb, "geran_ci", json_object_new_string(rb->geran_ci));
  json_add_object(enb, "geran_lac", json_object_new_string(rb->geran_lac));
  json_add_object(enb, "bbu_addr", json_object_new_string(rb->bbu_addr));
  json_add_object(enb, "cell_id", json_object_new_string(rb->cell_id));
  json_add_object(enb, "enb_id", json_object_new_string(rb->enb_id));
  json_add_object(enb, "geran_ci", json_object_new_string(rb->geran_ci));
  json_add_object(enb, "geran_lac", json_object_new_string(rb->geran_lac));
  json_add_object(enb, "gtp_bind_addr", json_object_new_string(rb->gtp_bind_addr));
  json_add_object(enb, "mcc", json_object_new_string(rb->mcc));
  json_add_object(enb, "mme_addr", json_object_new_string(rb->mme_addr));
  json_add_object(enb, "mnc", json_object_new_string(rb->mnc));
  json_add_object(enb, "n_prb", json_object_new_string(rb->n_prb));
  json_add_object(enb, "name", json_object_new_string(rb->name));
  json_add_object(enb, "nof_ports", json_object_new_string(rb->nof_ports));
  json_add_object(enb, "p_a", json_object_new_string(rb->p_a));
  json_add_object(enb, "phy_cell_id", json_object_new_string(rb->phy_cell_id));
  json_add_object(enb, "rru_addr", json_object_new_string(rb->rru_addr));
  json_add_object(enb, "s1c_bind_addr", json_object_new_string(rb->s1c_bind_addr));
  json_add_object(enb, "sec1_pci", json_object_new_string(rb->sec1_pci));
  json_add_object(enb, "sec1_x2_bind_addr", json_object_new_string(rb->sec1_x2_bind_addr));
  json_add_object(enb, "sec2_pci", json_object_new_string(rb->sec2_pci));
  json_add_object(enb, "sec2_x2_bind_addr", json_object_new_string(rb->sec2_x2_bind_addr));
  json_add_object(enb, "sec3_x2_bind_addr", json_object_new_string(rb->sec3_x2_bind_addr));
  json_add_object(enb, "sector_id", json_object_new_string(rb->sector_id));
  json_add_object(enb, "tac", json_object_new_string(rb->tac));
  json_add_object(enb, "tm", json_object_new_string(rb->tm));
  json_add_object(enb, "ws_port", json_object_new_string(rb->ws_port));
  json_add_object(root, "enb", enb);

  // enb_files
  json_add_object(enb_files, "drb_config", json_object_new_string(rb->drb_config));
  json_add_object(enb_files, "mbms_sib_config", json_object_new_string(rb->mbms_sib_config));
  json_add_object(enb_files, "rr_config", json_object_new_string(rb->rr_config));
  json_add_object(enb_files, "sib_config", json_object_new_string(rb->sib_config));
  json_add_object(root, "enb_files", enb_files);

  // expert
  json_add_object(expert, "accept_handover_ratio", json_object_new_string(rb->accept_handover_ratio));
  json_add_object(expert, "agc_energy_b2x0", json_object_new_string(rb->agc_energy_b2x0));
  json_add_object(expert, "alpha", json_object_new_string(rb->alpha));
  json_add_object(expert, "bi", json_object_new_string(rb->bi));
  json_add_object(expert, "bi_flag", json_object_new_string(rb->bi_flag));
  json_add_object(expert, "csfb_geran_list", json_object_new_string(rb->csfb_geran_list));
  json_add_object(expert, "eea_pref_list", json_object_new_string(rb->eea_pref_list));
  json_add_object(expert, "eia_pref_list", json_object_new_string(rb->eia_pref_list));
  json_add_object(expert, "enable_mbsfn", json_object_new_string(rb->enable_mbsfn));
  json_add_object(expert, "geran_csfb_flag", json_object_new_string(rb->geran_csfb_flag));
  json_add_object(expert, "handover_drb_id", json_object_new_string(rb->handover_drb_id));
  json_add_object(expert, "link_failure_nof_err", json_object_new_string(rb->link_failure_nof_err));
  json_add_object(expert, "m1u_if_addr", json_object_new_string(rb->m1u_if_addr));
  json_add_object(expert, "m1u_multiaddr", json_object_new_string(rb->m1u_multiaddr));
  json_add_object(expert, "mbms_file", json_object_new_string(rb->mbms_file));
  json_add_object(expert, "metrics_addr", json_object_new_string(rb->metrics_addr));
  json_add_object(expert, "metrics_period_secs", json_object_new_string(rb->metrics_period_secs));
  json_add_object(expert, "metrics_port", json_object_new_string(rb->metrics_port));
  json_add_object(expert, "nof_phy_threads", json_object_new_string(rb->nof_phy_threads));
  json_add_object(expert, "packet_size", json_object_new_string(rb->packet_size));
  json_add_object(expert, "pusch_max_its", json_object_new_string(rb->pusch_max_its));
  json_add_object(expert, "radio_unit", json_object_new_string(rb->radio_unit));
  json_add_object(expert, "rrc_connected", json_object_new_string(rb->rrc_connected));
  json_add_object(expert, "rrc_inactivity_timer", json_object_new_string(rb->rrc_inactivity_timer));
  json_add_object(expert, "snr_pucch", json_object_new_string(rb->snr_pucch));
  json_add_object(expert, "snr_pusch", json_object_new_string(rb->snr_pusch));
  json_add_object(root, "expert", expert);

  // gui
  json_add_object(gui, "enable", json_object_new_string(rb->enable_gui));
  json_add_object(root, "gui", gui);

  // log
  json_add_object(log, "all_hex_limit", json_object_new_string(rb->all_hex_limit));
  json_add_object(log, "all_level", json_object_new_string(rb->all_level));
  json_add_object(log, "file_max_size", json_object_new_string(rb->file_max_size));
  json_add_object(log, "filename", json_object_new_string(rb->filename_log));
  json_add_object(root, "log", log);

  // pcap
  json_add_object(pcap, "enable", json_object_new_string(rb->enable_pcap));
  json_add_object(pcap, "filename", json_object_new_string(rb->filename_pcap));
  json_add_object(root, "pcap", pcap);

  // rf
  json_add_object(rf, "dl_earfcn", json_object_new_string(rb->dl_earfcn));
  json_add_object(rf, "rx_gain", json_object_new_string(rb->rx_gain));
  json_add_object(rf, "tx_gain", json_object_new_string(rb->tx_gain));
  json_add_object(root, "rf", rf);

  // scheduler
  json_add_object(scheduler, "nof_ctrl_symbols", json_object_new_string(rb->nof_ctrl_symbols));
  json_add_object(scheduler, "pdsch_max_mcs1", json_object_new_string(rb->pdsch_max_mcs1));
  json_add_object(scheduler, "pdsch_max_mcs2", json_object_new_string(rb->pdsch_max_mcs2));
  json_add_object(scheduler, "pusch_max_mcs", json_object_new_string(rb->pusch_max_mcs));
  json_add_object(root, "scheduler", scheduler);

  if (root == NULL)
  {
    fprintf(stderr, "Error: root JSON object is NULL\n");
    return;
  }

  // printf("Generated JSON:\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));

  const char *root_string = json_to_string(root);
  // http_result_t result_post = http_post_custom(client_enb, ENB_ADDR_CONF_SEC_1, root_string, "SNMP");
  //   if (!result_post.success) {
  //     fprintf(stderr, "HTTP POST failed with status code %ld\n", result_post.status_code);
  //     return;
  // }

  // printf("POST successful\n");
  // printf("Response: %s\n", result_post.data);

  switch (ctrl->hdr.dummy)
  {
  case 123:

    break;

  default:
    break;
  }
  sm_ag_if_ans_t ans = {.type = CTRL_OUTCOME_SM_AG_IF_ANS_V0};
  return ans;
}

#include "sm_enb_conf.h"
#include "../src/util/time_now_us.h"

static http_client_t *enb_http_client = NULL;
static uint8_t sector_num = 0;
static char *backend_addr = NULL;

#define ENB_ADDR_CONF_SEC_1 "/sector-1/configuration/enb"
#define ENB_ADDR_CONF_SEC_2 "/sector-2/configuration/enb"
#define ENB_ADDR_CONF_SEC_3 "/sector-3/configuration/enb"

void init_enb_conf_sm(void)
{
}

void free_enb_conf_sm(void)
{
    // No allocation needed
    enb_http_client = NULL;
}

void set_enb_conf_http_client(http_client_t *client)
{
    enb_http_client = client;
}

void set_enb_conf_num_of_sector(uint8_t num)
{
    sector_num = num;
}

void set_enb_conf_backed_addr(char *addr)
{
    backend_addr = addr;
}

bool read_enb_conf_sm(void *data)
{
    assert(data != NULL);

    enb_conf_ind_data_t *enb_conf = (enb_conf_ind_data_t *)data;

    assert(enb_conf != NULL);

    srand(time(0));
    enb_conf_ind_msg_t *ind_msg = &enb_conf->msg;

    ind_msg->tstamp = time_now_us();

    ind_msg->len = sector_num;
    if (ind_msg->len > 0)
    {
        ind_msg->rb = calloc(ind_msg->len, sizeof(enb_conf_stats_t));
        assert(ind_msg->rb != NULL);
    }
    for (int i = 0; i < sector_num; i++)
    {
        enb_conf_stats_t *rb = &ind_msg->rb[i];
        char *url;
        if (i == 0)
        {
            asprintf(&url, "%s%s", backend_addr, ENB_ADDR_CONF_SEC_1);
        }

        if (i == 1)
        {
            asprintf(&url, "%s%s", backend_addr, ENB_ADDR_CONF_SEC_2);
        }

        if (i == 2)
        {
            asprintf(&url, "%s%s", backend_addr, ENB_ADDR_CONF_SEC_3);
        }

        http_result_t result_get = http_get_custome(enb_http_client, url);
        if (!result_get.success)
        {
            fprintf(stderr, "Failed to get stats\n");
            return false;
        }

        struct json_object *parsed_json = json_parse_string(result_get.data);
        struct json_object *json_get = json_get_object(parsed_json, "enb");
        struct json_object *enb_files = json_get_object(parsed_json, "enb_files");
        struct json_object *expert = json_get_object(parsed_json, "expert");
        struct json_object *gui = json_get_object(parsed_json, "gui");
        struct json_object *log = json_get_object(parsed_json, "log");
        struct json_object *pcap = json_get_object(parsed_json, "pcap");
        struct json_object *rf = json_get_object(parsed_json, "rf");
        struct json_object *scheduler = json_get_object(parsed_json, "scheduler");

        http_result_free(&result_get);

        // enb
        snprintf(rb->bbu_addr, sizeof(rb->bbu_addr), json_get_string(json_get, "bbu_addr"));
        snprintf(rb->cell_id, sizeof(rb->cell_id), json_get_string(json_get, "cell_id"));
        snprintf(rb->enb_id, sizeof(rb->enb_id), json_get_string(json_get, "enb_id"));
        snprintf(rb->geran_ci, sizeof(rb->geran_ci), json_get_string(json_get, "geran_ci"));
        snprintf(rb->geran_lac, sizeof(rb->geran_lac), json_get_string(json_get, "geran_lac"));
        snprintf(rb->gtp_bind_addr, sizeof(rb->gtp_bind_addr), json_get_string(json_get, "gtp_bind_addr"));
        snprintf(rb->mcc, sizeof(rb->mcc), json_get_string(json_get, "mcc"));
        snprintf(rb->mme_addr, sizeof(rb->mme_addr), json_get_string(json_get, "mme_addr"));
        snprintf(rb->mnc, sizeof(rb->mnc), json_get_string(json_get, "mnc"));
        snprintf(rb->n_prb, sizeof(rb->n_prb), json_get_string(json_get, "n_prb"));
        snprintf(rb->name, sizeof(rb->name), json_get_string(json_get, "name"));
        snprintf(rb->nof_ports, sizeof(rb->nof_ports), json_get_string(json_get, "nof_ports"));
        snprintf(rb->p_a, sizeof(rb->p_a), json_get_string(json_get, "p_a"));
        snprintf(rb->phy_cell_id, sizeof(rb->phy_cell_id), json_get_string(json_get, "phy_cell_id"));
        snprintf(rb->rru_addr, sizeof(rb->rru_addr), json_get_string(json_get, "rru_addr"));
        snprintf(rb->s1c_bind_addr, sizeof(rb->s1c_bind_addr), json_get_string(json_get, "s1c_bind_addr"));
        snprintf(rb->sec1_pci, sizeof(rb->sec1_pci), json_get_string(json_get, "sec1_pci"));
        snprintf(rb->sec1_x2_bind_addr, sizeof(rb->sec1_x2_bind_addr), json_get_string(json_get, "sec1_x2_bind_addr"));
        snprintf(rb->sec2_pci, sizeof(rb->sec2_pci), json_get_string(json_get, "sec2_pci"));
        snprintf(rb->sec2_x2_bind_addr, sizeof(rb->sec2_x2_bind_addr), json_get_string(json_get, "sec2_x2_bind_addr"));
        snprintf(rb->sec3_x2_bind_addr, sizeof(rb->sec3_x2_bind_addr), json_get_string(json_get, "sec3_x2_bind_addr"));
        snprintf(rb->sector_id, sizeof(rb->sector_id), json_get_string(json_get, "sector_id"));
        snprintf(rb->tac, sizeof(rb->tac), json_get_string(json_get, "tac"));
        snprintf(rb->tm, sizeof(rb->tm), json_get_string(json_get, "tm"));
        snprintf(rb->ws_port, sizeof(rb->ws_port), json_get_string(json_get, "ws_port"));

        // enb_files
        snprintf(rb->drb_config, sizeof(rb->drb_config), json_get_string(enb_files, "drb_config"));
        snprintf(rb->mbms_sib_config, sizeof(rb->mbms_sib_config), json_get_string(enb_files, "mbms_sib_config"));
        snprintf(rb->rr_config, sizeof(rb->rr_config), json_get_string(enb_files, "rr_config"));
        snprintf(rb->sib_config, sizeof(rb->sib_config), json_get_string(enb_files, "sib_config"));

        // expert
        snprintf(rb->accept_handover_ratio, sizeof(rb->accept_handover_ratio), json_get_string(expert, "accept_handover_ratio"));
        snprintf(rb->agc_energy_b2x0, sizeof(rb->agc_energy_b2x0), json_get_string(expert, "agc_energy_b2x0"));
        snprintf(rb->alpha, sizeof(rb->alpha), json_get_string(expert, "alpha"));
        snprintf(rb->bi, sizeof(rb->bi), json_get_string(expert, "bi"));
        snprintf(rb->bi_flag, sizeof(rb->bi_flag), json_get_string(expert, "bi_flag"));
        snprintf(rb->csfb_geran_list, sizeof(rb->csfb_geran_list), json_get_string(expert, "csfb_geran_list"));
        snprintf(rb->eea_pref_list, sizeof(rb->eea_pref_list), json_get_string(expert, "eea_pref_list"));
        snprintf(rb->eia_pref_list, sizeof(rb->eia_pref_list), json_get_string(expert, "eia_pref_list"));
        snprintf(rb->enable_mbsfn, sizeof(rb->enable_mbsfn), json_get_string(expert, "enable_mbsfn"));
        snprintf(rb->geran_csfb_flag, sizeof(rb->geran_csfb_flag), json_get_string(expert, "geran_csfb_flag"));
        snprintf(rb->handover_drb_id, sizeof(rb->handover_drb_id), json_get_string(expert, "handover_drb_id"));
        snprintf(rb->link_failure_nof_err, sizeof(rb->link_failure_nof_err), json_get_string(expert, "link_failure_nof_err"));
        snprintf(rb->m1u_if_addr, sizeof(rb->m1u_if_addr), json_get_string(expert, "m1u_if_addr"));
        snprintf(rb->m1u_multiaddr, sizeof(rb->m1u_multiaddr), json_get_string(expert, "m1u_multiaddr"));
        snprintf(rb->mbms_file, sizeof(rb->mbms_file), json_get_string(expert, "mbms_file"));
        snprintf(rb->metrics_addr, sizeof(rb->metrics_addr), json_get_string(expert, "metrics_addr"));
        snprintf(rb->metrics_period_secs, sizeof(rb->metrics_period_secs), json_get_string(expert, "metrics_period_secs"));
        snprintf(rb->metrics_port, sizeof(rb->metrics_port), json_get_string(expert, "metrics_port"));
        snprintf(rb->nof_phy_threads, sizeof(rb->nof_phy_threads), json_get_string(expert, "nof_phy_threads"));
        snprintf(rb->packet_size, sizeof(rb->packet_size), json_get_string(expert, "packet_size"));
        snprintf(rb->pusch_max_its, sizeof(rb->pusch_max_its), json_get_string(expert, "pusch_max_its"));
        snprintf(rb->radio_unit, sizeof(rb->radio_unit), json_get_string(expert, "radio_unit"));
        snprintf(rb->rrc_connected, sizeof(rb->rrc_connected), json_get_string(expert, "rrc_connected"));
        snprintf(rb->rrc_inactivity_timer, sizeof(rb->rrc_inactivity_timer), json_get_string(expert, "rrc_inactivity_timer"));
        snprintf(rb->snr_pucch, sizeof(rb->snr_pucch), json_get_string(expert, "snr_pucch"));
        snprintf(rb->snr_pusch, sizeof(rb->snr_pusch), json_get_string(expert, "snr_pusch"));

        // gui
        snprintf(rb->enable_gui, sizeof(rb->enable_gui), json_get_string(gui, "enable"));

        // log
        snprintf(rb->all_hex_limit, sizeof(rb->all_hex_limit), json_get_string(log, "all_hex_limit"));
        snprintf(rb->all_level, sizeof(rb->all_level), json_get_string(log, "all_level"));
        snprintf(rb->file_max_size, sizeof(rb->file_max_size), json_get_string(log, "file_max_size"));
        snprintf(rb->filename_log, sizeof(rb->filename_log), json_get_string(log, "filename"));

        // pcap
        snprintf(rb->enable_pcap, sizeof(rb->enable_pcap), json_get_string(pcap, "enable"));
        snprintf(rb->filename_pcap, sizeof(rb->filename_pcap), json_get_string(pcap, "filename"));

        // rf
        snprintf(rb->dl_earfcn, sizeof(rb->dl_earfcn), json_get_string(rf, "dl_earfcn"));
        snprintf(rb->rx_gain, sizeof(rb->rx_gain), json_get_string(rf, "rx_gain"));
        snprintf(rb->tx_gain, sizeof(rb->tx_gain), json_get_string(rf, "tx_gain"));

        // scheduler
        snprintf(rb->nof_ctrl_symbols, sizeof(rb->nof_ctrl_symbols), json_get_string(scheduler, "nof_ctrl_symbols"));
        snprintf(rb->pdsch_max_mcs1, sizeof(rb->pdsch_max_mcs1), json_get_string(scheduler, "pdsch_max_mcs1"));
        snprintf(rb->pdsch_max_mcs2, sizeof(rb->pdsch_max_mcs2), json_get_string(scheduler, "pdsch_max_mcs2"));
        snprintf(rb->pusch_max_mcs, sizeof(rb->pusch_max_mcs), json_get_string(scheduler, "pusch_max_mcs"));
        json_object_put(parsed_json);
    }
    return true;
}

void read_enb_conf_setup_sm(void *data)
{
    assert(data != NULL);
    //  assert(data->type == enb_conf_AGENT_IF_E2_SETUP_ANS_V0 );
    assert(0 != 0 && "Not supported");
}

sm_ag_if_ans_t write_ctrl_enb_conf_sm(void const *data)
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
    http_result_t result_post = http_post_custom(enb_http_client, ENB_ADDR_CONF_SEC_1, root_string, "SNMP");
    if (!result_post.success)
    {
        fprintf(stderr, "HTTP POST failed with status code %ld\n", result_post.status_code);
        return;
    }

    printf("POST successful\n");
    printf("Response: %s\n", result_post.data);

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

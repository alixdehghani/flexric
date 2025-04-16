#include "sm_sib2.h"


static http_client_t *sib2_http_client = NULL;
static uint8_t sector_num = 0;
static char *backend_addr = NULL;

#define SIB2_ADDR_CONF_SEC_1 "/sector-1/configuration/sib"
#define SIB2_ADDR_CONF_SEC_2 "/sector-2/configuration/sib"

void init_sib2_sm(void)
{
  // No allocation needed
}

void free_sib2_sm(void)
{
  // No allocation needed
}

void set_sib2_http_client(http_client_t *client)
{
  sib2_http_client = client;
}

void set_sib2_num_of_sector(uint8_t num)
{
  sector_num = num;
}

void set_sib2_backend_addr(char *addr)
{
  backend_addr = addr;
}





bool read_sib2_sm(void* data)
{
  assert(data != NULL);

    sib2_ind_data_t *sib2 = (sib2_ind_data_t *)data;

    assert(sib2 != NULL);

    srand(time(0));
    sib2_ind_msg_t *ind_msg = &sib2->msg;

    ind_msg->tstamp = time_now_us();
    
    ind_msg->len = sector_num;
    if (ind_msg->len > 0)
    {
        ind_msg->rb = calloc(ind_msg->len, sizeof(sib2_stats_t));
        assert(ind_msg->rb != NULL);
    }
    for (int i = 0; i < sector_num; i++)
    {
    
      sib2_stats_t *rb = &ind_msg->rb[i];
      char *url;
      if (i == 0)
      {
          asprintf(&url, "%s%s", backend_addr, SIB2_ADDR_CONF_SEC_1);
      }

      if (i == 1)
      {
          asprintf(&url, "%s%s", backend_addr, SIB2_ADDR_CONF_SEC_2);
      }

      http_result_t result_get = http_get_custome(sib2_http_client, url);
      if (!result_get.success)
      {
        fprintf(stderr, "Failed to get stats\n");
          return false;
      }

      // Parse the JSON response  
      struct json_object *parsed_json = json_parse_string(result_get.data);
      struct json_object *json_get = json_get_object(parsed_json, "sib2");
      struct json_object *freqInfo = json_get_object(json_get, "freqInfo");


      struct json_object *rr_config_common_sib = json_get_object(json_get, "rr_config_common_sib");
      struct json_object *bcch_cnfg = json_get_object(rr_config_common_sib, "bcch_cnfg");

      struct json_object *pcch_cnfg = json_get_object(rr_config_common_sib, "pcch_cnfg");

      struct json_object *pdsch_cnfg = json_get_object(rr_config_common_sib, "pdsch_cnfg");

      struct json_object *prach_cnfg = json_get_object(rr_config_common_sib, "prach_cnfg");
      struct json_object *prach_cnfg_info = json_get_object(prach_cnfg, "prach_cnfg_info");

      struct json_object *pucch_cnfg = json_get_object(rr_config_common_sib, "pucch_cnfg");

      struct json_object *pusch_cnfg = json_get_object(rr_config_common_sib, "pusch_cnfg");
      struct json_object *ul_rs = json_get_object(pusch_cnfg, "ul_rs");

      struct json_object *rach_cnfg = json_get_object(rr_config_common_sib, "rach_cnfg");
      struct json_object *ul_pwr_ctrl = json_get_object(rr_config_common_sib, "ul_pwr_ctrl");
      struct json_object *delta_flist_pucch = json_get_object(ul_pwr_ctrl, "delta_flist_pucch");

      struct json_object *ue_timers_and_constants = json_get_object(json_get, "ue_timers_and_constants");

      // struct json_object *prach_cnfg_info = json_get_object(prach_cnfg, "prach_cnfg_info");
      // struct json_object *prach_cnfg_info = json_get_object(prach_cnfg, "prach_cnfg_info");


      http_result_free(&result_get);
        
      rb->additional_spectrum_emission = json_get_int(freqInfo, "additional_spectrum_emission");
      rb->ul_bw_present = json_get_bool(freqInfo, "ul_bw_present");
      rb->ul_carrier_freq_present = json_get_bool(freqInfo, "ul_carrier_freq_present");
      rb->modification_period_coeff = json_get_int(bcch_cnfg, "modification_period_coeff");
      rb->default_paging_cycle = json_get_int(pcch_cnfg, "default_paging_cycle");
      snprintf(rb->nB, sizeof(rb->nB), json_get_string(pcch_cnfg, "nB"));
      rb->p_b = json_get_int(pdsch_cnfg, "p_b");
      rb->rs_power  = json_get_int(pdsch_cnfg, "rs_power");
      rb->high_speed_flag = json_get_bool(prach_cnfg_info, "high_speed_flag");
      rb->prach_config_index  = json_get_int(prach_cnfg_info, "prach_config_index");
      rb->prach_freq_offset  = json_get_int(prach_cnfg_info, "prach_freq_offset");
      rb->zero_correlation_zone_config  = json_get_int(prach_cnfg_info, "zero_correlation_zone_config");
      rb->root_sequence_index  = json_get_int(prach_cnfg, "root_sequence_index");

      rb->delta_pucch_shift  = json_get_int(pucch_cnfg, "delta_pucch_shift");
      rb->n1_pucch_an  = json_get_int(pucch_cnfg, "n1_pucch_an");
      rb->n_cs_an  = json_get_int(pucch_cnfg, "n_cs_an");
      rb->n_rb_cqi  = json_get_int(pucch_cnfg, "n_rb_cqi");

      rb->enable_64_qam  = json_get_bool(pusch_cnfg, "enable_64_qam");
      snprintf(rb->hopping_mode, sizeof(rb->hopping_mode), json_get_string(pusch_cnfg, "hopping_mode"));
      rb->n_sb = json_get_int(pusch_cnfg, "n_sb");
      rb->pusch_hopping_offset  = json_get_int(pusch_cnfg, "pusch_hopping_offset");

      rb->cyclic_shift = json_get_int(ul_rs, "cyclic_shift");
      rb->group_assignment_pusch = json_get_int(ul_rs, "group_assignment_pusch");
      rb->group_hopping_enabled = json_get_bool(ul_rs, "group_hopping_enabled");
      rb->sequence_hopping_enabled = json_get_bool(ul_rs, "sequence_hopping_enabled");

      rb->mac_con_res_timer = json_get_int(rach_cnfg, "mac_con_res_timer");
      rb->max_harq_msg3_tx = json_get_int(rach_cnfg, "max_harq_msg3_tx");
      rb->num_ra_preambles = json_get_int(rach_cnfg, "num_ra_preambles");
      rb->preamble_init_rx_target_pwr = json_get_int(rach_cnfg, "preamble_init_rx_target_pwr");
      rb->preamble_trans_max = json_get_int(rach_cnfg, "preamble_trans_max");
      rb->pwr_ramping_step = json_get_int(rach_cnfg, "pwr_ramping_step");
      rb->ra_resp_win_size = json_get_int(rach_cnfg, "ra_resp_win_size");

      snprintf(rb->ul_cp_length, sizeof(rb->ul_cp_length), json_get_string(rr_config_common_sib, "ul_cp_length"));

      rb->alpha = json_get_double(ul_pwr_ctrl, "alpha");

      rb->format_1 = json_get_int(delta_flist_pucch, "format_1");
      rb->format_1b = json_get_int(delta_flist_pucch, "format_1b");
      rb->format_2 = json_get_int(delta_flist_pucch, "format_2");
      rb->format_2a = json_get_int(delta_flist_pucch, "format_2a");
      rb->format_2b = json_get_int(delta_flist_pucch, "format_2b");
      rb->delta_preamble_msg3 = json_get_int(ul_pwr_ctrl, "delta_preamble_msg3");
      rb->p0_nominal_pucch = json_get_int(ul_pwr_ctrl, "p0_nominal_pucch");
      rb->p0_nominal_pusch = json_get_int(ul_pwr_ctrl, "p0_nominal_pusch");

      snprintf(rb->time_alignment_timer, sizeof(rb->time_alignment_timer), json_get_string(json_get, "time_alignment_timer"));
      
      rb->n310 = json_get_int(ue_timers_and_constants, "n310");
      rb->n311 = json_get_int(ue_timers_and_constants, "n311");
      rb->t300 = json_get_int(ue_timers_and_constants, "t300");
      rb->t301 = json_get_int(ue_timers_and_constants, "t301");
      rb->t310 = json_get_int(ue_timers_and_constants, "t310");
      rb->t311 = json_get_int(ue_timers_and_constants, "t311");

    }
    
}

void read_sib2_setup_sm(void* data)
{
  assert(data != NULL);
//  assert(data->type == sib2_AGENT_IF_E2_SETUP_ANS_V0 );
  assert(0 !=0 && "Not supported");
}


sm_ag_if_ans_t write_ctrl_sib2_sm(void const* data)
{
  (void)data;
  assert(0!=0 && "Not supported");
}
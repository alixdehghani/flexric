#include "sm_rr.h"
#include "../src/util/time_now_us.h"


static http_client_t *rr_http_client = NULL;
static uint8_t sector_num = 0;
static char *backend_addr = NULL;

#define RR_ADDR_CONF_SEC_1 "/sector-1/configuration/rr"
#define RR_ADDR_CONF_SEC_2 "/sector-2/configuration/rr"

void init_rr_sm(void)
{
  // No allocation needed
}

void free_rr_sm(void)
{
  // No allocation needed
}

void set_rr_http_client(http_client_t *client)
{
  rr_http_client = client;
}

void set_rr_num_of_sector(uint8_t num)
{
  sector_num = num;
}

void set_rr_backend_addr(char *addr)
{
  backend_addr = addr;
}





bool read_rr_sm(void* data)
{
  assert(data != NULL);

    rr_ind_data_t *rr = (rr_ind_data_t *)data;

    assert(rr != NULL);

    srand(time(0));
    rr_ind_msg_t *ind_msg = &rr->msg;

    ind_msg->tstamp = time_now_us();
    
    ind_msg->len = sector_num;
    if (ind_msg->len > 0)
    {
        ind_msg->rb = calloc(ind_msg->len, sizeof(rr_stats_t));
        assert(ind_msg->rb != NULL);
    }
    for (int i = 0; i < sector_num; i++)
    {
    
      rr_stats_t *rb = &ind_msg->rb[i];
      char *url;
      if (i == 0)
      {
          asprintf(&url, "%s%s", backend_addr, RR_ADDR_CONF_SEC_1);
      }

      if (i == 1)
      {
          asprintf(&url, "%s%s", backend_addr, RR_ADDR_CONF_SEC_2);
      }

      http_result_t result_get = http_get_custome(rr_http_client, url);
      if (!result_get.success)
      {
        fprintf(stderr, "Failed to get stats\n");
          return false;
      }

      // Parse the JSON response  
      struct json_object *parsed_json = json_parse_string(result_get.data);
      struct json_object *mac_cnfg = json_get_object(parsed_json, "mac_cnfg");
      struct json_object *phr_cnfg = json_get_object(mac_cnfg, "phr_cnfg");
      struct json_object *ulsch_cnfg = json_get_object(mac_cnfg, "ulsch_cnfg");

      struct json_object *phy_cnfg = json_get_object(parsed_json, "phy_cnfg");
      struct json_object *cqi_report_cnfg = json_get_object(phy_cnfg, "cqi_report_cnfg");
      struct json_object *phich_cnfg = json_get_object(phy_cnfg, "phich_cnfg");
      struct json_object *pusch_cnfg_ded = json_get_object(phy_cnfg, "pusch_cnfg_ded");
      struct json_object *sched_request_cnfg = json_get_object(phy_cnfg, "sched_request_cnfg");

      http_result_free(&result_get);
        
      // int array_length = json_object_array_length(sched_info);

      snprintf(rb->dl_pathloss_change, sizeof(rb->dl_pathloss_change), json_get_string(phr_cnfg, "dl_pathloss_change"));
      
      rb->periodic_phr_timer = json_get_int(phr_cnfg, "periodic_phr_timer");
      rb->prohibit_phr_timer = json_get_int(phr_cnfg, "prohibit_phr_timer");

      rb->time_alignment_timer = json_get_int(mac_cnfg, "time_alignment_timer");

      rb->max_harq_tx = json_get_int(ulsch_cnfg, "max_harq_tx");
      rb->periodic_bsr_timer = json_get_int(ulsch_cnfg, "periodic_bsr_timer");
      rb->retx_bsr_timer = json_get_int(ulsch_cnfg, "retx_bsr_timer");

      snprintf(rb->mode, sizeof(rb->mode), json_get_string(cqi_report_cnfg, "mode"));
      rb->cqi_report_cnfg_nof_prb = json_get_int(cqi_report_cnfg, "nof_prb");
      rb->cqi_report_cnfg_period = json_get_int(cqi_report_cnfg, "period");
      rb->simultaneousAckCQI = json_get_bool(cqi_report_cnfg, "simultaneousAckCQI");
      rb->retx_bsr_timer = json_get_int(ulsch_cnfg, "retx_bsr_timer");
      json_object* cqi_report_cnfg_subframe = json_get_array(cqi_report_cnfg, "subframe");
      snprintf(rb->cqi_report_cnfg_subframe, sizeof(rb->cqi_report_cnfg_subframe), json_object_to_json_string(cqi_report_cnfg_subframe)); 

      snprintf(rb->duration, sizeof(rb->duration), json_get_string(phich_cnfg, "duration"));
      snprintf(rb->resources, sizeof(rb->resources), json_get_string(phich_cnfg, "resources"));

      rb->beta_offset_ack_idx = json_get_int(pusch_cnfg_ded, "beta_offset_ack_idx");
      rb->beta_offset_cqi_idx = json_get_int(pusch_cnfg_ded, "beta_offset_cqi_idx");
      rb->beta_offset_ri_idx = json_get_int(pusch_cnfg_ded, "beta_offset_ri_idx");  

      rb->dsr_trans_max = json_get_int(sched_request_cnfg, "dsr_trans_max");
      rb->sched_request_cnfg_nof_prb = json_get_int(sched_request_cnfg, "nof_prb");
      rb->sched_request_cnfg_period = json_get_int(sched_request_cnfg, "period");
      json_object* sched_request_cnfg_subframe = json_get_array(sched_request_cnfg, "subframe");
      snprintf(rb->sched_request_cnfg_subframe, sizeof(rb->sched_request_cnfg_subframe), json_object_to_json_string(cqi_report_cnfg_subframe)); 
      
    }
    return true;

}

void read_rr_setup_sm(void* data)
{
  assert(data != NULL);
//  assert(data->type == RR_AGENT_IF_E2_SETUP_ANS_V0 );
  assert(0 !=0 && "Not supported");
}


sm_ag_if_ans_t write_ctrl_rr_sm(void const* data)
{

  assert(data != NULL);
  int size_arr;
  int max_size = 150;
  int array[max_size];

  rr_ctrl_req_data_t *ctrl = (rr_ctrl_req_data_t *)data;
  // printf("Action: %d\n", ctrl->msg.action);
  // printf("Dummy: %d\n", ctrl->hdr.dummy);
  rr_stats_t *rb = ctrl->msg.rr_rb;

  printf("dl_pathloss_change: %s\n", rb->dl_pathloss_change);
  printf("periodic_phr_timer: %d\n", rb->periodic_phr_timer);
  printf("prohibit_phr_timer: %d\n", rb->prohibit_phr_timer);
  printf("time_alignment_timer: %d\n", rb->time_alignment_timer);
  printf("max_harq_tx: %d\n", rb->max_harq_tx);
  printf("periodic_bsr_timer: %d\n", rb->periodic_bsr_timer);
  printf("retx_bsr_timer: %d\n", rb->retx_bsr_timer);
  printf("mode: %s\n", rb->mode);
  printf("cqi_report_cnfg_nof_prb: %d\n", rb->cqi_report_cnfg_nof_prb);
  printf("cqi_report_cnfg_period: %d\n", rb->cqi_report_cnfg_period);
  printf("simultaneousAckCQI: %d\n", rb->simultaneousAckCQI);
  printf("cqi_report_cnfg_subframe: %s\n", rb->cqi_report_cnfg_subframe);
  printf("duration: %s\n", rb->duration);
  printf("resources: %s\n", rb->resources);
  printf("beta_offset_ack_idx: %d\n", rb->beta_offset_ack_idx);
  printf("beta_offset_cqi_idx: %d\n", rb->beta_offset_cqi_idx);
  printf("beta_offset_ri_idx: %d\n", rb->beta_offset_ri_idx);
  printf("dsr_trans_max: %d\n", rb->dsr_trans_max);
  printf("sched_request_cnfg_nof_prb: %d\n", rb->sched_request_cnfg_nof_prb);
  printf("sched_request_cnfg_period: %d\n", rb->sched_request_cnfg_period);
  printf("sched_request_cnfg_subframe: %s\n", rb->sched_request_cnfg_subframe);


  struct json_object *root = json_object_new_object();
  
  struct json_object *mac_cnfg = json_object_new_object();
  struct json_object *phr_cnfg = json_object_new_object();
  struct json_object *ulsch_cnfg = json_object_new_object();

  struct json_object *phy_cnfg = json_object_new_object();
  struct json_object *cqi_report_cnfg = json_object_new_object();
  struct json_object *phich_cnfg = json_object_new_object();
  struct json_object *pusch_cnfg_ded = json_object_new_object();
  struct json_object *sched_request_cnfg = json_object_new_object();
 

  // mac_cnfg

  json_object_object_add(phr_cnfg, "dl_pathloss_change", json_object_new_string(rb->dl_pathloss_change));
  json_object_object_add(phr_cnfg, "periodic_phr_timer", json_object_new_int(rb->periodic_phr_timer));
  json_object_object_add(phr_cnfg, "prohibit_phr_timer", json_object_new_int(rb->prohibit_phr_timer));
  json_object_object_add(ulsch_cnfg, "max_harq_tx", json_object_new_int(rb->max_harq_tx));
  json_object_object_add(ulsch_cnfg, "periodic_bsr_timer", json_object_new_int(rb->periodic_bsr_timer));
  json_object_object_add(ulsch_cnfg, "retx_bsr_timer", json_object_new_int(rb->retx_bsr_timer));
  json_object_object_add(mac_cnfg, "time_alignment_timer", json_object_new_int(rb->time_alignment_timer));
  json_add_object(mac_cnfg, "ulsch_cnfg", ulsch_cnfg);
  json_add_object(mac_cnfg, "phr_cnfg", phr_cnfg);
  json_add_object(root, "mac_cnfg", mac_cnfg);

  // phy_cnfg
  json_object_object_add(cqi_report_cnfg, "mode", json_object_new_string(rb->mode));
  json_object_object_add(cqi_report_cnfg, "nof_prb", json_object_new_int(rb->cqi_report_cnfg_nof_prb));
  json_object_object_add(cqi_report_cnfg, "period", json_object_new_int(rb->cqi_report_cnfg_period));
  json_object_object_add(cqi_report_cnfg, "simultaneousAckCQI", json_object_new_boolean(rb->simultaneousAckCQI));

  struct json_object *cqi_report_cnfg_subframe = json_object_new_array();
  const char* str;

  str = rb->cqi_report_cnfg_subframe;
  parseStringToArray_rr(str, array, max_size, &size_arr);
  for(int i = 0; i < size_arr; i++) {
    json_object_array_add(cqi_report_cnfg_subframe, json_object_new_int(array[i]));  
  }
  json_object_object_add(cqi_report_cnfg, "subframe", cqi_report_cnfg_subframe);

  json_object_object_add(phich_cnfg, "duration", json_object_new_string(rb->duration));
  json_object_object_add(phich_cnfg, "resources", json_object_new_string(rb->resources));

  json_object_object_add(pusch_cnfg_ded, "beta_offset_ack_idx", json_object_new_int(rb->beta_offset_ack_idx));
  json_object_object_add(pusch_cnfg_ded, "beta_offset_cqi_idx", json_object_new_int(rb->beta_offset_cqi_idx));
  json_object_object_add(pusch_cnfg_ded, "beta_offset_ri_idx", json_object_new_int(rb->beta_offset_ri_idx));

  json_object_object_add(sched_request_cnfg, "dsr_trans_max", json_object_new_int(rb->dsr_trans_max));
  json_object_object_add(sched_request_cnfg, "nof_prb", json_object_new_int(rb->sched_request_cnfg_nof_prb));
  json_object_object_add(sched_request_cnfg, "period", json_object_new_int(rb->sched_request_cnfg_period));
  struct json_object *sched_request_cnfg_subframe = json_object_new_array();
  const char* str_1;

  str_1 = rb->sched_request_cnfg_subframe;
  parseStringToArray_rr(str, array, max_size, &size_arr);
  for(int i = 0; i < size_arr; i++) {
    json_object_array_add(sched_request_cnfg_subframe, json_object_new_int(array[i]));  
  }
  json_object_object_add(sched_request_cnfg, "subframe", sched_request_cnfg_subframe);
  
  json_add_object(phy_cnfg, "cqi_report_cnfg", cqi_report_cnfg);
  json_add_object(phy_cnfg, "phich_cnfg", phich_cnfg);
  json_add_object(phy_cnfg, "pusch_cnfg_ded", pusch_cnfg_ded);
  json_add_object(phy_cnfg, "sched_request_cnfg", sched_request_cnfg);
  json_add_object(root, "phy_cnfg", phy_cnfg);

  const char *root_string = json_to_string(root);
  char *addr_url = 0;
  if (asprintf(&addr_url, "%s%s", backend_addr, RR_ADDR_CONF_SEC_1) == -1) {
    perror("asprintf");
  }

  http_result_t result_post = http_post_custom(rr_http_client, addr_url, root_string, "SNMP");
  if (!result_post.success)
  {
      fprintf(stderr, "HTTP POST failed with status code %ld\n", result_post.status_code);
      return;
  }

  printf("POST successful\n");
  printf("Response: %s\n", result_post.data);

    // switch (ctrl->hdr.dummy)
    // {
    // case 123:

    //     break;

    // default:
    //     break;
    // }
    // sm_ag_if_ans_t ans = {.type = CTRL_OUTCOME_SM_AG_IF_ANS_V0};
    // return ans;
}

  
void parseStringToArray_rr(const char* str, int* array, int max_size, int* size) {
    if (str == NULL || array == NULL || max_size <= 0) {
        return;
    }
    *size = 0;
    memset(array, 0, sizeof(int) * max_size);
    int count = 0;
    const char* ptr = str;
    
    while (*ptr && *ptr != '[') ptr++;
    if (*ptr == '[') ptr++;
    
    
    while (*ptr && *ptr != ']' && count < max_size) {
        while (*ptr && (*ptr == ' ' || *ptr == ',')) ptr++;
        
        if (*ptr >= '0' && *ptr <= '9' || *ptr == '-') {
            array[count++] = atoi(ptr);
            (*size)++;

            // Skip the number we just parsed
            if (*ptr == '-') ptr++; // Skip minus sign if present
            while (*ptr && *ptr >= '0' && *ptr <= '9') ptr++;
        } else if (*ptr && *ptr != ']') {
            ptr++; // Skip any other characters
        }
    }
    
    return;
}
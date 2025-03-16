#include "sm_zxc.h"
#include "../src/util/time_now_us.h"

#define ENB_ADDR_CONF "https://192.168.80.222/bk/sector-1/configuration/enb"

void init_zxc_sm(void)
{
    printf("=========================\n\n");
    client = http_client_init();
    if (!client)
    {
        fprintf(stderr, "Failed to initialize HTTP client\n");
        return 1;
    }
    printf("HTTP client initialized successfully\n\n");
}

void free_zxc_sm(void)
{
  // No allocation needed
}


bool read_zxc_sm(void* data)
{
  assert(data != NULL);

  zxc_ind_data_t* zxc = (zxc_ind_data_t*)data;

  assert(zxc != NULL);

  srand(time(0));
  zxc_ind_msg_t* ind_msg = &zxc->msg;

  ind_msg->tstamp = time_now_us();

  ind_msg->len = 1;
  if(ind_msg->len > 0 ){
    ind_msg->rb = calloc(ind_msg->len, sizeof(zxc_radio_bearer_stats_t) );
    assert(ind_msg->rb != NULL);
  }

  http_result_t result = http_get_custome(client, ENB_ADDR_CONF);
  if (!result.success)
  {
      fprintf(stderr, "Failed to get stats\n");
      return false;
  }

  struct json_object* parsed_json = json_parse_string(result.data);
  struct json_object* json_get = json_get_object(parsed_json, "enb");
  
  http_result_free(&result);
  
  // ind_msg->pci = 123;
  // ind_msg->len_str = 12; // Length of "Hello World" + 1 for null terminator
  // ind_msg->str = calloc(ind_msg->len_str, sizeof(char));
  // assert(ind_msg->str != NULL); 
  // snprintf(ind_msg->str, ind_msg->len_str, "Hello World");

  zxc_radio_bearer_stats_t* rb = &ind_msg->rb[0];

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
  snprintf(rb->ws_port , sizeof(rb->ws_port), json_get_string(json_get, "ws_port"));
  
  json_object_put(parsed_json);
  return true;
}

void read_zxc_setup_sm(void* data)
{
  assert(data != NULL);
//  assert(data->type == zxc_AGENT_IF_E2_SETUP_ANS_V0 );
  assert(0 !=0 && "Not supported");
}


sm_ag_if_ans_t write_ctrl_zxc_sm(void const* data)
{

  assert(data != NULL);

  zxc_ctrl_req_data_t* ctrl = (zxc_ctrl_req_data_t*)data; 

//   printf("Action: %d\n", ctrl->msg.action);
//   printf("Action2: %d\n", ctrl->msg.action2);

  printf("Dummy: %d\n", ctrl->hdr.dummy);
  zxc_radio_bearer_stats_t* rb = ctrl->msg.rb;
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
  switch (ctrl->hdr.dummy)
  {
  case 123:
    
    break;
  
  default:
    break;
  }
  sm_ag_if_ans_t ans = {.type = CTRL_OUTCOME_SM_AG_IF_ANS_V0 };
  return ans;
}


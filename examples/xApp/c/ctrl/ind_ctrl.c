#include "../../../../src/xApp/e42_xapp_api.h"
#include "../../../../src/util/alg_ds/alg/defer.h"
#include "../../../../src/util/time_now_us.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

static uint64_t cnt_zxc;
static uint32_t* change_pci;    



static void sm_cb_zxc(sm_ag_if_rd_t const *rd)
{
  change_pci = (uint32_t*)malloc(sizeof(uint32_t));
//   assert(change_pci == NULL);
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);

    
  assert(rd->ind.type == ZXC_STATS_V0);
  if(!rd->ind.mac.msg.len_ue_stats == 0)
  {
    // printf("%d",rd->ind.zxc.msg.rb->zxc_data_t);   //zxc_get_msg
    printf("%s", rd->ind.zxc.msg.str);
  }
  
  printf("\nPCI: %u \n", rd->ind.zxc.msg.pci);
  *change_pci = rd->ind.zxc.msg.pci;

  int64_t now = time_now_us();

  if (cnt_zxc % 1024 == 0)
    printf("ZXC ind_msg latency = %ld μs\n", now - rd->ind.zxc.msg.tstamp);
  cnt_zxc++;
}


void run_xapp_reporting() {

  // Init the xApp
  // init_xapp_api(args);
  // sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });

  assert(nodes.len > 0);

  printf("Connected E2 nodes = %d\n", nodes.len);

  // MAC indication
  const char *i_0 = "0_ms";
  sm_ans_xapp_t *zxc_handle = NULL;
  // RLC indication
  // const char *i_1 = "1_ms";
  // sm_ans_xapp_t *rlc_handle = NULL;
  // // PDCP indication
  // const char *i_2 = "1_ms";
  // sm_ans_xapp_t *pdcp_handle = NULL;
  // // GTP indication
  // const char *i_3 = "1_ms";
  // sm_ans_xapp_t *gtp_handle = NULL;

  // const char *i_4 = "1_ms";
  // sm_ans_xapp_t *zxc_handle = NULL;

  if (nodes.len > 0)
  {
    // mac_handle = calloc(nodes.len, sizeof(sm_ans_xapp_t));
    // assert(mac_handle != NULL);
    // rlc_handle = calloc(nodes.len, sizeof(sm_ans_xapp_t));
    // assert(rlc_handle != NULL);
    // pdcp_handle = calloc(nodes.len, sizeof(sm_ans_xapp_t));
    // assert(pdcp_handle != NULL);
    // gtp_handle = calloc(nodes.len, sizeof(sm_ans_xapp_t));
    // assert(gtp_handle != NULL);
    zxc_handle = calloc(nodes.len, sizeof(sm_ans_xapp_t));
    assert(zxc_handle != NULL);
  }

  for (int i = 0; i < nodes.len; i++)
  {
    e2_node_connected_xapp_t *n = &nodes.n[i];
    for (size_t j = 0; j < n->len_rf; j++)
      printf("Registered node %d ran func id = %d \n ", i, n->rf[j].id);

    if (n->id.type == ngran_gNB || n->id.type == ngran_eNB)
    {
      // MAC Control is not yet implemented in OAI RAN
      // mac_ctrl_req_data_t wr = {.hdr.dummy = 1, .msg.action = 42 };
      // sm_ans_xapp_t const a = control_sm_xapp_api(&nodes.n[i].id, 142, &wr);
      // assert(a.success == true);

      // mac_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 142, (void *)i_0, sm_cb_mac);
      // assert(mac_handle[i].success == true);

      // rlc_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 143, (void *)i_1, sm_cb_rlc);
      // assert(rlc_handle[i].success == true);

      // pdcp_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 144, (void *)i_2, sm_cb_pdcp);
      // assert(pdcp_handle[i].success == true);

      // gtp_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 148, (void *)i_3, sm_cb_gtp);
      // assert(gtp_handle[i].success == true);

      zxc_handle[i] = report_sm_xapp_api(&nodes.n[i].id, 149, (void *)i_0, sm_cb_zxc);
      assert(zxc_handle[i].success == true);
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

  sleep(1);
  
  for (int i = 0; i < nodes.len; ++i)
  {
    // Remove the handle previously returned
    // if (mac_handle[i].u.handle != 0)
    //   rm_report_sm_xapp_api(mac_handle[i].u.handle);
    // if (rlc_handle[i].u.handle != 0)
    //   rm_report_sm_xapp_api(rlc_handle[i].u.handle);
    if (zxc_handle[i].u.handle != 0)
      rm_report_sm_xapp_api(zxc_handle[i].u.handle);
      // if (pdcp_handle[i].u.handle != 0)
    //   rm_report_sm_xapp_api(pdcp_handle[i].u.handle);
    // if (gtp_handle[i].u.handle != 0)
    //   rm_report_sm_xapp_api(gtp_handle[i].u.handle);
  }
  
  if (nodes.len > 0)
  {
    // free(mac_handle);
    // free(rlc_handle);
    free(zxc_handle);
    // free(pdcp_handle);
    // free(gtp_handle);
  }

  // Stop the xApp
//   while (try_stop_xapp_api() == false)
//     usleep(1000);

  printf("Test xApp run SUCCESSFULLY\n");

}

void run_xapp_control() {
    // Init the xApp
    // init_xapp_api(args);
    // sleep(1);

    e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
    defer({ free_e2_node_arr_xapp(&nodes); });
  
    assert(nodes.len > 0);
  
    printf("Connected E2 nodes = %d\n", nodes.len);
  
    for (int i = 0; i < nodes.len; i++) {
      e2_node_connected_xapp_t* n = &nodes.n[i];
  
      for (size_t j = 0; j < n->len_rf; j++)
        printf("Registered node %d ran func id = %d \n ", i, n->rf[j].id);
  
      if(n->id.type == ngran_gNB || n->id.type == ngran_gNB_DU || n->id.type == ngran_eNB){
        zxc_ctrl_req_data_t wr = {.hdr.dummy = 123, .msg.action = 420, .msg.action2 = *change_pci};
        sm_ans_xapp_t const a = control_sm_xapp_api(&nodes.n[i].id, 149, &wr);
        free(change_pci);
        change_pci = NULL;
        assert(a.success == true);
       } else {
         printf("Cannot send MAC ctrl to if the E2 Node is not a GNB or DU\n");
      }
    }
  
//    //Stop the xApp
//     while(try_stop_xapp_api() == false)
//       usleep(1000);
  
    printf("Test xApp run SUCCESSFULLY\n");

}


int main(int argc, char *argv[]) {
    fr_args_t args = init_fr_args(argc, argv);

    init_xapp_api(&args);
    sleep(1);

    // First, run the reporting logic
    
    run_xapp_reporting();
  

    // Then, run the control logic
    run_xapp_control();

    while(try_stop_xapp_api() == false)
    usleep(1000);

    printf("Unified xApp run COMPLETED SUCCESSFULLY\n");
    return 0;
}
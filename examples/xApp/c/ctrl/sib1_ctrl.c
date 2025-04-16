#include "../../../../src/xApp/e42_xapp_api.h"
#include "../../../../src/util/alg_ds/alg/defer.h"
#include "../../../../src/xApp/db/sqlite3/sqlite3.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>


static int callback_sib1(void *data, int argc, char **argv, char **azColName) {
    sib1_stats_t *rb = (sib1_stats_t *)data;
    for (int i = 0; i < argc; i++) {
        if (strcmp(azColName[i], "cell_barred") == 0) strcpy(rb->cell_barred, argv[i]);
        if (strcmp(azColName[i], "intra_freq_reselection") == 0) strcpy(rb->intra_freq_reselection, argv[i]);
        if (strcmp(azColName[i], "p_max") == 0) rb->p_max = atoi(argv[i]);
        if (strcmp(azColName[i], "q_rx_lev_min") == 0) rb->q_rx_lev_min = atoi(argv[i]);
        if (strcmp(azColName[i], "si_window_length") == 0) rb->si_window_length = atoi(argv[i]);
        if (strcmp(azColName[i], "system_info_value_tag") == 0) rb->system_info_value_tag = atoi(argv[i]);
        if (strcmp(azColName[i], "sched_info_si_mapping_info_1") == 0) strcpy(rb->sched_info_si_mapping_info_1, argv[i]);
        if (strcmp(azColName[i], "sched_info_si_periodicity_1") == 0) rb->sched_info_si_periodicity_1 = atoi(argv[i]);
        if (strcmp(azColName[i], "sched_info_si_mapping_info_2") == 0) strcpy(rb->sched_info_si_mapping_info_2, argv[i]);
        if (strcmp(azColName[i], "sched_info_si_periodicity_2") == 0) rb->sched_info_si_periodicity_2 = atoi(argv[i]);
        if (strcmp(azColName[i], "sched_info_si_mapping_info_3") == 0) strcpy(rb->sched_info_si_mapping_info_3, argv[i]);
        if (strcmp(azColName[i], "sched_info_si_periodicity_3") == 0) rb->sched_info_si_periodicity_3 = atoi(argv[i]);
        if (strcmp(azColName[i], "sched_info_si_mapping_info_4") == 0) strcpy(rb->sched_info_si_mapping_info_4, argv[i]);
        if (strcmp(azColName[i], "sched_info_si_periodicity_4") == 0) rb->sched_info_si_periodicity_4 = atoi(argv[i]);
        if (strcmp(azColName[i], "sched_info_si_mapping_info_5") == 0) strcpy(rb->sched_info_si_mapping_info_5, argv[i]);
        if (strcmp(azColName[i], "sched_info_si_periodicity_5") == 0) rb->sched_info_si_periodicity_5 = atoi(argv[i]);
        if (strcmp(azColName[i], "sched_info_si_mapping_info_6") == 0) strcpy(rb->sched_info_si_mapping_info_6, argv[i]);
        if (strcmp(azColName[i], "sched_info_si_periodicity_6") == 0) rb->sched_info_si_periodicity_6 = atoi(argv[i]);
        if (strcmp(azColName[i], "sched_info_si_mapping_info_7") == 0) strcpy(rb->sched_info_si_mapping_info_7, argv[i]);
        if (strcmp(azColName[i], "sched_info_si_periodicity_7") == 0) rb->sched_info_si_periodicity_7 = atoi(argv[i]);
        if (strcmp(azColName[i], "sched_info_si_mapping_info_8") == 0) strcpy(rb->sched_info_si_mapping_info_8, argv[i]);
        if (strcmp(azColName[i], "sched_info_si_periodicity_8") == 0) rb->sched_info_si_periodicity_8 = atoi(argv[i]);
  
    }
    return 0;
  }
  
  void fill_rb_from_db_sib1(sib1_stats_t *rb, const char *addr_db) {
    sqlite3 *db;
    char *err_msg = 0;
    
    // sqlite address should change 
    int rc = sqlite3_open(addr_db, &db);
  
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
  
        sqlite3_close(db);
        return;
    }
  
    const char *sql = "SELECT * FROM SIB1 LIMIT 1;";
  
    rc = sqlite3_exec(db, sql, callback_sib1, rb, &err_msg);
  
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
    printf("\n\n%s\n\n", addr_db);
  
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
          // zxc_radio_bearer_stats_t rb;
          sib1_stats_t sib1_rb;
          // fill_rb_from_db(&rb);
          fill_rb_from_db_sib1(&sib1_rb, &addr_db);
          // zxc_radio_bearer_stats_t rb = {.bbu_addr = "bbu_addr", .cell_id = "cell_id", .enb_id = "enb_id", .geran_ci = "geran_ci", .geran_lac = "geran_lac", .gtp_bind_addr = "gtp_bind_addr", .mcc = "mcc", .mme_addr = "mme_addr", .mnc = "mnc", .n_prb = "n_prb", .name = "name", .nof_ports = "nof_ports", .p_a = "p_a", .phy_cell_id = "phy_cell_id", .rru_addr = "rru_addr", .s1c_bind_addr = "s1c_bind_addr", .sec1_pci = "sec1_pci", .sec1_x2_bind_addr = "sec1_x2_bind_addr", .sec2_pci = "sec2_pci", .sec2_x2_bind_addr = "sec2_x2_bind_addr", .sec3_x2_bind_addr = "sec3_x2_bind_addr", .sector_id = "sector_id", .tac = "tac", .tm = "tm", .ws_port = "ws_port"};
        // zxc_ctrl_req_data_t wr = {.hdr.dummy = 123, .msg.len = 1, .msg.rb = &rb};
        sib1_ctrl_req_data_t wr_sib1 = {.hdr.dummy = 124, .msg.len = 1, .msg.sib1_rb = &sib1_rb};
        
        sm_ans_xapp_t const a = control_sm_xapp_api(&nodes.n[i].id, 153, &wr_sib1);
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
  
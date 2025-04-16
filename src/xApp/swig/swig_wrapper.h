#ifndef SWIG_WRAPPER_H
#define SWIG_WRAPPER_H 

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "../../lib/e2ap/e2ap_global_node_id_wrapper.h"
#include "../../lib/e2ap/e2ap_plmn_wrapper.h"
#include "../../lib/e2ap/e2ap_ran_function_wrapper.h"

#include "../../sm/mac_sm/ie/mac_data_ie.h"
#include "../../sm/rlc_sm/ie/rlc_data_ie.h"
#include "../../sm/zxc_sm/ie/zxc_data_ie.h"
#include "../../sm/sib1_sm/ie/sib1_data_ie.h"
#include "../../sm/sib2_sm/ie/sib2_data_ie.h"
#include "../../sm/rr_sm/ie/rr_data_ie.h"
#include "../../sm/uetrace_sm/ie/uetrace_data_ie.h"
#include "../../sm/counters_sm/ie/counters_data_ie.h"
#include "../../sm/enb_conf_sm/ie/enb_conf_data_ie.h"
#include "../../sm/pdcp_sm/ie/pdcp_data_ie.h"
#include "../../sm/slice_sm/ie/slice_data_ie.h"
#include "../../sm/gtp_sm/ie/gtp_data_ie.h"

//////////////////////////////////////
// General    
/////////////////////////////////////

struct E2Node {
  global_e2_node_id_t id;
  std::vector<ran_function_t> ran_func;
};

void init(void); 

bool try_stop(void);

std::vector<E2Node> conn_e2_nodes(void);

enum class Interval {
  ms_1,
  ms_2,
  ms_5,
  ms_10,
};

//////////////////////////////////////
// MAC SM   
/////////////////////////////////////

struct swig_mac_ind_msg_t{
  std::vector<mac_ue_stats_impl_t> ue_stats;
  int64_t tstamp;
};

struct mac_cb {
    virtual void handle(swig_mac_ind_msg_t* a) = 0;
    virtual ~mac_cb() {}
};

int report_mac_sm(global_e2_node_id_t* id, Interval inter, mac_cb* handler);

void rm_report_mac_sm(int);

//////////////////////////////////////
// RLC SM   
/////////////////////////////////////

struct swig_rlc_ind_msg_t{
  std::vector<rlc_radio_bearer_stats_t> rb_stats; 
  int64_t tstamp;
};

struct rlc_cb {
    virtual void handle(swig_rlc_ind_msg_t* a) = 0;
    virtual ~rlc_cb() {}
};

int report_rlc_sm(global_e2_node_id_t* id, Interval inter, rlc_cb* handler);

void rm_report_rlc_sm(int);

//////////////////////////////////////
// ZXC SM   
/////////////////////////////////////

struct swig_zxc_ind_msg_t{
    std::vector<zxc_radio_bearer_stats_t> rb_stats; 
    int64_t tstamp;
  };
  
  struct zxc_cb {
      virtual void handle(swig_zxc_ind_msg_t* a) = 0;
      virtual ~zxc_cb() {}
  };
  
  int report_zxc_sm(global_e2_node_id_t* id, Interval inter, zxc_cb* handler);
  
  void rm_report_zxc_sm(int);


//////////////////////////////////////
// SIB1 SM   
/////////////////////////////////////

struct swig_sib1_ind_msg_t{
  std::vector<sib1_stats_t> rb_stats; 
  int64_t tstamp;
};

struct sib1_cb {
    virtual void handle(swig_sib1_ind_msg_t* a) = 0;
    virtual ~sib1_cb() {}
};

int report_sib1_sm(global_e2_node_id_t* id, Interval inter, sib1_cb* handler);

void rm_report_sib1_sm(int);


//////////////////////////////////////
// RR SM   
/////////////////////////////////////

struct swig_rr_ind_msg_t{
  std::vector<rr_stats_t> rb_stats; 
  int64_t tstamp;
};

struct rr_cb {
    virtual void handle(swig_rr_ind_msg_t* a) = 0;
    virtual ~rr_cb() {}
};

int report_rr_sm(global_e2_node_id_t* id, Interval inter, rr_cb* handler);

void rm_report_rr_sm(int);

//////////////////////////////////////
// UETRACE SM   
/////////////////////////////////////

struct swig_uetrace_ind_msg_t{
  std::vector<uetrace_stats_t> rb_stats; 
  int64_t tstamp;
};

struct uetrace_cb {
    virtual void handle(swig_uetrace_ind_msg_t* a) = 0;
    virtual ~uetrace_cb() {}
};

int report_uetrace_sm(global_e2_node_id_t* id, Interval inter, uetrace_cb* handler);

void rm_report_uetrace_sm(int);

//////////////////////////////////////
// SIB2 SM   
/////////////////////////////////////

struct swig_sib2_ind_msg_t{
  std::vector<sib2_stats_t> rb_stats; 
  int64_t tstamp;
};

struct sib2_cb {
    virtual void handle(swig_sib2_ind_msg_t* a) = 0;
    virtual ~sib2_cb() {}
};

int report_sib2_sm(global_e2_node_id_t* id, Interval inter, sib2_cb* handler);

void rm_report_sib2_sm(int);


//////////////////////////////////////
// COUNTERS SM   
/////////////////////////////////////

struct swig_counters_ind_msg_t{
  std::vector<counters_stats_t> rb_stats; 
  int64_t tstamp;
};

struct counters_cb {
    virtual void handle(swig_counters_ind_msg_t* a) = 0;
    virtual ~counters_cb() {}
};

int report_counters_sm(global_e2_node_id_t* id, Interval inter, counters_cb* handler);

void rm_report_counters_sm(int);



//////////////////////////////////////
// ENB_CONF SM   
/////////////////////////////////////

struct swig_enb_conf_ind_msg_t{
  std::vector<enb_conf_stats_t> rb_stats; 
  int64_t tstamp;
};

struct enb_conf_cb {
    virtual void handle(swig_enb_conf_ind_msg_t* a) = 0;
    virtual ~enb_conf_cb() {}
};

int report_enb_conf_sm(global_e2_node_id_t* id, Interval inter, enb_conf_cb* handler);

void rm_report_enb_conf_sm(int);

//////////////////////////////////////
// PDCP SM   
/////////////////////////////////////

struct swig_pdcp_ind_msg_t{
  std::vector<pdcp_radio_bearer_stats_t> rb_stats;
  int64_t tstamp;
};

struct pdcp_cb {
    virtual void handle(swig_pdcp_ind_msg_t* a) = 0;
    virtual ~pdcp_cb() {}
};

int report_pdcp_sm(global_e2_node_id_t* id, Interval inter, pdcp_cb* handler);

void rm_report_pdcp_sm(int);

//////////////////////////////////////
// SLICE SM   
/////////////////////////////////////

typedef struct{
    uint32_t id;

    uint32_t len_label;
    std::vector<std::string> label;

    uint32_t len_sched;
    std::vector<std::string> sched;

    slice_params_t params;
} swig_fr_slice_t ;

typedef struct{
    uint32_t len_slices;
    std::vector<swig_fr_slice_t> slices;

    uint32_t len_sched_name;
    std::vector<std::string> sched_name;
} swig_ul_dl_slice_conf_t ;

typedef struct{
    swig_ul_dl_slice_conf_t dl;
    swig_ul_dl_slice_conf_t ul;
} swig_slice_conf_t ;

typedef struct{
    uint32_t len_ue_slice;
    std::vector<ue_slice_assoc_t> ues;
} swig_ue_slice_conf_t;

struct swig_slice_ind_msg_t{
  swig_slice_conf_t slice_stats;
  swig_ue_slice_conf_t ue_slice_stats;
  int64_t tstamp;
};

struct slice_cb {
    virtual void handle(swig_slice_ind_msg_t* a) = 0;
    virtual ~slice_cb() {}
};

int report_slice_sm(global_e2_node_id_t* id, Interval inter, slice_cb* handler);

void rm_report_slice_sm(int);

void control_slice_sm(global_e2_node_id_t* id, slice_ctrl_msg_t* ctrl);

//////////////////////////////////////
// GTP SM   
/////////////////////////////////////

struct swig_gtp_ind_msg_t{
  std::vector<gtp_ngu_t_stats_t> gtp_stats; 
  int64_t tstamp;
};

struct gtp_cb {
    virtual void handle(swig_gtp_ind_msg_t* a) = 0;
    virtual ~gtp_cb() {}
};

int report_gtp_sm(global_e2_node_id_t* id, Interval inter, gtp_cb* handler);

void rm_report_gtp_sm(int);

#endif


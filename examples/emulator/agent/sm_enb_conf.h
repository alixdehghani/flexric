#ifndef SM_ENB_CONF_READ_WRITE_AGENT_H
#define SM_ENB_CONF_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"
#include "../../../src/util/http_json/http_client.h"
#include "../../../src/util/http_json/json_parser.h"

void init_enb_conf_sm(void);

void free_enb_conf_sm(void);

bool read_enb_conf_sm(void*);
bool read_enb_conf_sm(void*);

void read_enb_conf_setup_sm(void* data);
void read_enb_conf_setup_sm(void* data);

sm_ag_if_ans_t write_ctrl_enb_conf_sm(void const* data);
void set_enb_conf_http_client(http_client_t* client);
void set_enb_conf_num_of_sector(uint8_t num);
void set_enb_conf_backed_addr(char* addr);

#endif


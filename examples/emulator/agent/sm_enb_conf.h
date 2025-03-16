#ifndef SM_ENB_CONF_READ_WRITE_AGENT_H
#define SM_ENB_CONF_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"
#include "../../../src/util/http_json/http_client.h"
#include "../../../src/util/http_json/json_parser.h"

static http_client_t *client_enb;
static int sector_num;

void init_enb_conf_sm(void);

void free_enb_conf_sm(void);

bool read_enb_conf_sm(void*);
bool read_enb_conf_sm(void*);

void read_enb_conf_setup_sm(void* data);
void read_enb_conf_setup_sm(void* data);

sm_ag_if_ans_t write_ctrl_enb_conf_sm(void const* data);

#endif


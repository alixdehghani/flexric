#ifndef SM_ZXC_READ_WRITE_AGENT_H
#define SM_ZXC_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"
#include "../../../src/util/http_json/http_client.h"
#include "../../../src/util/http_json/json_parser.h"

static http_client_t *client;

void init_zxc_sm(void);

void free_zxc_sm(void);

bool read_zxc_sm(void*);
bool read_zxc_sm(void*);

void read_zxc_setup_sm(void* data);
void read_zxc_setup_sm(void* data);

sm_ag_if_ans_t write_ctrl_zxc_sm(void const* data);

#endif


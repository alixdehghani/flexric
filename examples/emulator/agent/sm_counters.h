#ifndef SM_COUNTERS_READ_WRITE_AGENT_H
#define SM_COUNTERS_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"
#include "../../../src/util/http_json/http_client.h"
#include "../../../src/util/http_json/json_parser.h"

void init_counters_sm(void);

void free_counters_sm(void);

bool read_counters_sm(void*);
bool read_counters_sm(void*);

void read_counters_setup_sm(void* data);
void read_counters_setup_sm(void* data);

sm_ag_if_ans_t write_ctrl_counters_sm(void const* data);
void set_counters_http_client(http_client_t* client);
void set_counters_num_of_sector(uint8_t num);
void set_counters_backed_addr(char* addr);

#endif


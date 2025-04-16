#ifndef SM_SIB2_READ_WRITE_AGENT_H
#define SM_SIB2_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"
#include "../../../src/util/http_json/http_client.h"
#include "../../../src/util/http_json/json_parser.h"

void init_sib2_sm(void);

void free_sib2_sm(void);

bool read_sib2_sm(void*);
bool read_sib2_sm(void*);

void read_sib2_setup_sm(void* data);
void read_sib2_setup_sm(void* data);

sm_ag_if_ans_t write_ctrl_sib2_sm(void const* data);
void set_sib2_http_client(http_client_t* client);
void set_sib2_num_of_sector(uint8_t num);
void set_sib2_backend_addr(char* addr);

#endif
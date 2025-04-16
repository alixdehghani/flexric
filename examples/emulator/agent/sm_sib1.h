#ifndef SM_SIB1_READ_WRITE_AGENT_H
#define SM_SIB1_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"
#include "../../../src/util/http_json/http_client.h"
#include "../../../src/util/http_json/json_parser.h"

void init_sib1_sm(void);

void free_sib1_sm(void);

bool read_sib1_sm(void*);
bool read_sib1_sm(void*);

void read_sib1_setup_sm(void* data);
void read_sib1_setup_sm(void* data);

sm_ag_if_ans_t write_ctrl_sib1_sm(void const* data);
void set_sib1_http_client(http_client_t* client);
void set_sib1_num_of_sector(uint8_t num);
void set_sib1_backend_addr(char* addr);
void parseStringToArray(const char* str, int* array, int max_size, int* size);

#endif

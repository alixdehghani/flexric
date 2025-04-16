#ifndef SM_RR_READ_WRITE_AGENT_H
#define SM_RR_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"
#include "../../../src/util/http_json/http_client.h"
#include "../../../src/util/http_json/json_parser.h"

void init_rr_sm(void);

void free_rr_sm(void);

bool read_rr_sm(void*);
bool read_rr_sm(void*);

void read_rr_setup_sm(void* data);
void read_rr_setup_sm(void* data);

sm_ag_if_ans_t write_ctrl_rr_sm(void const* data);
void set_rr_http_client(http_client_t* client);
void set_rr_num_of_sector(uint8_t num);
void set_rr_backend_addr(char* addr);
void parseStringToArray_rr(const char* str, int* array, int max_size, int* size);

#endif

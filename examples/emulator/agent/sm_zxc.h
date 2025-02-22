#ifndef SM_ZXC_READ_WRITE_AGENT_H
#define SM_ZXC_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"

void init_zxc_sm(void);

void free_zxc_sm(void);

bool read_zxc_sm(void*);
bool read_zxc_sm(void*);

void read_zxc_setup_sm(void* data);
void read_zxc_setup_sm(void* data);

sm_ag_if_ans_t write_ctrl_zxc_sm(void const* data);

#endif


#include "sm_zxc.h"
#include "../../../test/rnd/fill_rnd_data_zxc.h"

void init_zxc_sm(void)
{
  // No allocation needed
}

void free_zxc_sm(void)
{
  // No allocation needed
}



bool read_zxc_sm(void* data)
{
  assert(data != NULL);
//  assert(data->type ==  zxc_STATS_V0);

  zxc_ind_data_t* zxc = (zxc_ind_data_t*)data;
  fill_zxc_ind_data(zxc);
  return true;
}

void read_zxc_setup_sm(void* data)
{
  assert(data != NULL);
//  assert(data->type == zxc_AGENT_IF_E2_SETUP_ANS_V0 );
  assert(0 !=0 && "Not supported");
}


sm_ag_if_ans_t write_ctrl_zxc_sm(void const* data)
{

  assert(data != NULL);

  zxc_ctrl_req_data_t* ctrl = (zxc_ctrl_req_data_t*)data; 
  printf("Action: %d\n", ctrl->msg.action);
  printf("Action2: %d\n", ctrl->msg.action2);
  printf("Dummy: %d\n", ctrl->hdr.dummy);
//   assert(ctrl->hdr.dummy == 0);
//   assert(ctrl->msg.action == 42);
  switch (ctrl->hdr.dummy)
  {
  case 123:
    
    break;
  
  default:
    break;
  }
  sm_ag_if_ans_t ans = {.type = CTRL_OUTCOME_SM_AG_IF_ANS_V0 };
  return ans;
}


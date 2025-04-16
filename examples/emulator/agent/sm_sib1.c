#include "sm_sib1.h"
#include "../src/util/time_now_us.h"


static http_client_t *sib1_http_client = NULL;
static uint8_t sector_num = 0;
static char *backend_addr = NULL;

#define SIB1_ADDR_CONF_SEC_1 "/sector-1/configuration/sib"
#define SIB1_ADDR_CONF_SEC_2 "/sector-2/configuration/sib"

void init_sib1_sm(void)
{
  // No allocation needed
}

void free_sib1_sm(void)
{
  // No allocation needed
}

void set_sib1_http_client(http_client_t *client)
{
  sib1_http_client = client;
}

void set_sib1_num_of_sector(uint8_t num)
{
  sector_num = num;
}

void set_sib1_backend_addr(char *addr)
{
  backend_addr = addr;
}





bool read_sib1_sm(void* data)
{
  assert(data != NULL);

    sib1_ind_data_t *sib1 = (sib1_ind_data_t *)data;

    assert(sib1 != NULL);

    srand(time(0));
    sib1_ind_msg_t *ind_msg = &sib1->msg;

    ind_msg->tstamp = time_now_us();
    
    ind_msg->len = sector_num;
    if (ind_msg->len > 0)
    {
        ind_msg->rb = calloc(ind_msg->len, sizeof(sib1_stats_t));
        assert(ind_msg->rb != NULL);
    }
    for (int i = 0; i < sector_num; i++)
    {
    
      sib1_stats_t *rb = &ind_msg->rb[i];
      char *url;
      if (i == 0)
      {
          asprintf(&url, "%s%s", backend_addr, SIB1_ADDR_CONF_SEC_1);
      }

      if (i == 1)
      {
          asprintf(&url, "%s%s", backend_addr, SIB1_ADDR_CONF_SEC_2);
      }

      http_result_t result_get = http_get_custome(sib1_http_client, url);
      if (!result_get.success)
      {
        fprintf(stderr, "Failed to get stats\n");
          return false;
      }

      // Parse the JSON response  
      struct json_object *parsed_json = json_parse_string(result_get.data);
      struct json_object *json_get = json_get_object(parsed_json, "sib1");
      struct json_object *sched_info = json_get_array(json_get, "sched_info");

      http_result_free(&result_get);
        
      int array_length = json_object_array_length(sched_info);

      snprintf(rb->cell_barred, sizeof(rb->cell_barred), json_get_string(json_get, "cell_barred"));
      snprintf(rb->intra_freq_reselection, sizeof(rb->intra_freq_reselection), json_get_string(json_get, "intra_freq_reselection"));
      rb->p_max = json_get_int(json_get, "p_max");
      rb->q_rx_lev_min = json_get_int(json_get, "q_rx_lev_min");
      rb->si_window_length = json_get_int(json_get, "si_window_length");
      rb->system_info_value_tag = json_get_int(json_get, "system_info_value_tag");

      for(int j = 0; j < array_length; j++)
      {

        json_object* sched_info_item = json_object_array_get_idx(sched_info, j);
        json_object* si_mapping_info = json_get_array(sched_info_item, "si_mapping_info");
        int si_periodicity = json_get_int(sched_info_item, "si_periodicity");
        if(j == 0)
        {
          rb->sched_info_si_periodicity_1 = si_periodicity;
          snprintf(rb->sched_info_si_mapping_info_1, sizeof(rb->sched_info_si_mapping_info_1), json_object_to_json_string(si_mapping_info)); 
        }
        if(j == 1)
        {
          rb->sched_info_si_periodicity_2 = si_periodicity;
          snprintf(rb->sched_info_si_mapping_info_2, sizeof(rb->sched_info_si_mapping_info_2), json_object_to_json_string(si_mapping_info)); 
        }
        if(j == 2)
        {
          rb->sched_info_si_periodicity_3 = si_periodicity;
          snprintf(rb->sched_info_si_mapping_info_3, sizeof(rb->sched_info_si_mapping_info_3), json_object_to_json_string(si_mapping_info)); 
        }
        if(j == 3)
        {
          rb->sched_info_si_periodicity_4 = si_periodicity;
          snprintf(rb->sched_info_si_mapping_info_4, sizeof(rb->sched_info_si_mapping_info_4), json_object_to_json_string(si_mapping_info)); 
        }
        if(j == 4)
        {
          rb->sched_info_si_periodicity_5 = si_periodicity;
          snprintf(rb->sched_info_si_mapping_info_5, sizeof(rb->sched_info_si_mapping_info_5), json_object_to_json_string(si_mapping_info)); 
        }
        if(j == 5)
        {
          rb->sched_info_si_periodicity_6 = si_periodicity;
          snprintf(rb->sched_info_si_mapping_info_6, sizeof(rb->sched_info_si_mapping_info_6), json_object_to_json_string(si_mapping_info)); 
        }
        if(j == 6)
        {
          rb->sched_info_si_periodicity_7 = si_periodicity;
          snprintf(rb->sched_info_si_mapping_info_7, sizeof(rb->sched_info_si_mapping_info_7), json_object_to_json_string(si_mapping_info)); 
        }
        if(j == 7)
        {
          rb->sched_info_si_periodicity_8 = si_periodicity;
          snprintf(rb->sched_info_si_mapping_info_8, sizeof(rb->sched_info_si_mapping_info_8), json_object_to_json_string(si_mapping_info)); 
        }

      }
    }
    return true;

}

void read_sib1_setup_sm(void* data)
{
  assert(data != NULL);
//  assert(data->type == sib1_AGENT_IF_E2_SETUP_ANS_V0 );
  assert(0 !=0 && "Not supported");
}


sm_ag_if_ans_t write_ctrl_sib1_sm(void const* data)
{

  assert(data != NULL);
  int size_arr;
  int max_size = 20;
  int array[max_size];

  sib1_ctrl_req_data_t *ctrl = (sib1_ctrl_req_data_t *)data;
  // printf("Action: %d\n", ctrl->msg.action);
  // printf("Dummy: %d\n", ctrl->hdr.dummy);
  sib1_stats_t *rb = ctrl->msg.sib1_rb;
  printf("cell barred: %s\n", rb->cell_barred);
  printf("intra_freq_reselection: %s\n", rb->intra_freq_reselection);
  printf("p_max: %d\n", rb->p_max);
  printf("q_rx_lev_min: %d\n", rb->q_rx_lev_min);
  printf("si_window_length: %d\n", rb->si_window_length);
  printf("system_info_value_tag: %d\n", rb->system_info_value_tag);
  printf("sched_info_si_mapping_info_1: %s\n", rb->sched_info_si_mapping_info_1);
  printf("sched_info_si_periodicity_1: %d\n", rb->sched_info_si_periodicity_1);
  printf("sched_info_si_mapping_info_2: %s\n", rb->sched_info_si_mapping_info_2);
  printf("sched_info_si_periodicity_2: %d\n", rb->sched_info_si_periodicity_2);
  printf("sched_info_si_mapping_info_3: %s\n", rb->sched_info_si_mapping_info_3);
  printf("sched_info_si_periodicity_3: %d\n", rb->sched_info_si_periodicity_3);
  printf("sched_info_si_mapping_info_4: %s\n", rb->sched_info_si_mapping_info_4);
  printf("sched_info_si_periodicity_4: %d\n", rb->sched_info_si_periodicity_4);
  printf("sched_info_si_mapping_info_5: %s\n", rb->sched_info_si_mapping_info_5);
  printf("sched_info_si_periodicity_5: %d\n", rb->sched_info_si_periodicity_5);
  printf("sched_info_si_mapping_info_6: %s\n", rb->sched_info_si_mapping_info_6);
  printf("sched_info_si_periodicity_6: %d\n", rb->sched_info_si_periodicity_6);
  printf("sched_info_si_mapping_info_7: %s\n", rb->sched_info_si_mapping_info_7);
  printf("sched_info_si_periodicity_7: %d\n", rb->sched_info_si_periodicity_7);
  printf("sched_info_si_mapping_info_8: %s\n", rb->sched_info_si_mapping_info_8);
  printf("sched_info_si_periodicity_8: %d\n", rb->sched_info_si_periodicity_8);


  struct json_object *root = json_object_new_object();
  struct json_object *sib1 = json_object_new_object();

    // Add simple key-values
  json_object_object_add(sib1, "cell_barred", json_object_new_string(rb->cell_barred));
  json_object_object_add(sib1, "intra_freq_reselection", json_object_new_string(rb->intra_freq_reselection));
  json_object_object_add(sib1, "p_max", json_object_new_int(rb->p_max));
  json_object_object_add(sib1, "q_rx_lev_min", json_object_new_int(rb->q_rx_lev_min));


  struct json_object *sched_info = json_object_new_array();
  struct json_object *sched1 = json_object_new_object();
  

  for (int i = 0; i < 8; i++)
  {
    struct json_object *sched = json_object_new_object();
    struct json_object *si_mapping = json_object_new_array();
    const char* str;

    if (i == 0)
    {
      if (rb->sched_info_si_mapping_info_1[0] == '\0') break;
          

      str = rb->sched_info_si_mapping_info_1;
      parseStringToArray(str, array, max_size, &size_arr);
      for(int i = 0; i < size_arr; i++) {
        json_object_array_add(si_mapping, json_object_new_int(array[i]));  
      }
      json_object_object_add(sched, "si_periodicity", json_object_new_int(rb->sched_info_si_periodicity_1));
      json_object_object_add(sched, "si_mapping_info", si_mapping);
    } 

    if (i == 1)
    {
      if (rb->sched_info_si_mapping_info_2[0] == '\0') break;
        
      str = rb->sched_info_si_mapping_info_2;
      parseStringToArray(str, array, max_size, &size_arr);
      for(int i = 0; i < size_arr; i++) {
        json_object_array_add(si_mapping, json_object_new_int(array[i]));  
      }
      json_object_object_add(sched, "si_periodicity", json_object_new_int(rb->sched_info_si_periodicity_2));
      json_object_object_add(sched, "si_mapping_info", si_mapping);
    }
  
    if (i == 2)
    {
      if (rb->sched_info_si_mapping_info_3[0] == '\0') break;        

      str = rb->sched_info_si_mapping_info_3;
      parseStringToArray(str, array, max_size, &size_arr);
      for(int i = 0; i < size_arr; i++) {
        json_object_array_add(si_mapping, json_object_new_int(array[i]));  
      }
      json_object_object_add(sched, "si_periodicity", json_object_new_int(rb->sched_info_si_periodicity_3));
      json_object_object_add(sched, "si_mapping_info", si_mapping);
    }

    if (i == 3)
    {
      if (rb->sched_info_si_mapping_info_4[0] == '\0') break;
          
      str = rb->sched_info_si_mapping_info_4;
      parseStringToArray(str, array, max_size, &size_arr);
      for(int i = 0; i < size_arr; i++) {
        json_object_array_add(si_mapping, json_object_new_int(array[i]));  
      }
      json_object_object_add(sched, "si_periodicity", json_object_new_int(rb->sched_info_si_periodicity_4));
      json_object_object_add(sched, "si_mapping_info", si_mapping);
    }

    if (i == 4)
    {
      if (rb->sched_info_si_mapping_info_5[0] == '\0') break;
          
      str = rb->sched_info_si_mapping_info_5;
      parseStringToArray(str, array, max_size, &size_arr);
      for(int i = 0; i < size_arr; i++) {
        json_object_array_add(si_mapping, json_object_new_int(array[i]));  
      }
      json_object_object_add(sched, "si_periodicity", json_object_new_int(rb->sched_info_si_periodicity_5));
      json_object_object_add(sched, "si_mapping_info", si_mapping);
    }

    if (i == 5)
    {
      if (rb->sched_info_si_mapping_info_6[0] == '\0') break;
          
      str = rb->sched_info_si_mapping_info_6;
      parseStringToArray(str, array, max_size, &size_arr);
      for(int i = 0; i < size_arr; i++) {
        json_object_array_add(si_mapping, json_object_new_int(array[i]));  
      }
      json_object_object_add(sched, "si_periodicity", json_object_new_int(rb->sched_info_si_periodicity_6));
      json_object_object_add(sched, "si_mapping_info", si_mapping);
    }

    if (i == 6)
    {
      if (rb->sched_info_si_mapping_info_7[0] == '\0') break;
        
      str = rb->sched_info_si_mapping_info_7;
      parseStringToArray(str, array, max_size, &size_arr);
      for(int i = 0; i < size_arr; i++) {
        json_object_array_add(si_mapping, json_object_new_int(array[i]));  
      }
      json_object_object_add(sched, "si_periodicity", json_object_new_int(rb->sched_info_si_periodicity_7));
      json_object_object_add(sched, "si_mapping_info", si_mapping);
    }

    if (i == 7)
    {
      if (rb->sched_info_si_mapping_info_8[0] == '\0') break;
          
      str = rb->sched_info_si_mapping_info_8;
      parseStringToArray(str, array, max_size, &size_arr);
      for(int i = 0; i < size_arr; i++) {
        json_object_array_add(si_mapping, json_object_new_int(array[i]));  
      }
      json_object_object_add(sched, "si_periodicity", json_object_new_int(rb->sched_info_si_periodicity_8));
      json_object_object_add(sched, "si_mapping_info", si_mapping);
    }

    json_object_array_add(sched_info, sched);
  }
  

  // json_object_array_add(sched_info, sched1);
  json_object_object_add(sib1, "si_window_length", json_object_new_int(rb->si_window_length));
  json_object_object_add(sib1, "system_info_value_tag", json_object_new_int(rb->system_info_value_tag));

  json_add_object(sib1, "sched_info", sched_info);
  json_add_object(root, "sib1", sib1);


    // haven't sector for post->->->->->->->->

    const char *root_string = json_to_string(root);
    printf("\n\n %s \n\n", root_string);
    char *addr_url = 0;
    if (asprintf(&addr_url, "%s%s", backend_addr, SIB1_ADDR_CONF_SEC_1) == -1) {
      perror("asprintf");
    }

    // http_result_t result_post = http_post_custom(sib1_http_client, addr_url, root_string, "SNMP");
    // if (!result_post.success)
    // {
    //     fprintf(stderr, "HTTP POST failed with status code %ld\n", result_post.status_code);
    //     return;
    // }

    // printf("POST successful\n");
    // printf("Response: %s\n", result_post.data);

    switch (ctrl->hdr.dummy)
    {
    case 123:

        break;

    default:
        break;
    }
    sm_ag_if_ans_t ans = {.type = CTRL_OUTCOME_SM_AG_IF_ANS_V0};
    return ans;
  }

  
  void parseStringToArray(const char* str, int* array, int max_size, int* size) {
    if (str == NULL || array == NULL || max_size <= 0) {
        return;
    }
    *size = 0;
    int count = 0;
    const char* ptr = str;
    
    while (*ptr && *ptr != '[') ptr++;
    if (*ptr == '[') ptr++;
    
    
    while (*ptr && *ptr != ']' && count < max_size) {
        while (*ptr && (*ptr == ' ' || *ptr == ',')) ptr++;
        
        if (*ptr >= '0' && *ptr <= '9' || *ptr == '-') {
            array[count++] = atoi(ptr);
            (*size)++;

            // Skip the number we just parsed
            if (*ptr == '-') ptr++; // Skip minus sign if present
            while (*ptr && *ptr >= '0' && *ptr <= '9') ptr++;
        } else if (*ptr && *ptr != ']') {
            ptr++; // Skip any other characters
        }
    }
    
    return;
}
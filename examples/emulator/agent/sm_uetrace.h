#ifndef SM_UETRACE_READ_WRITE_AGENT_H
#define SM_UETRACE_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"
#include "../../../src/util/http_json/http_client.h"
#include "../../../src/util/http_json/json_parser.h"
#include "../../../src/util/websocket/websocket_client.h"

void init_uetrace_sm(void);

void free_uetrace_sm(void);

bool read_uetrace_sm(void *);
bool read_uetrace_sm(void *);

void read_uetrace_setup_sm(void *data);
void read_uetrace_setup_sm(void *data);

sm_ag_if_ans_t write_ctrl_uetrace_sm(void const *data);
void set_uetrace_http_client(http_client_t *client);
void set_uetrace_num_of_sector(uint8_t num);
void set_uetrace_backend_host_addr(char *addr);
void set_uetrace_backend_websocket_path(char *addr);

void handle_uetrace_ws_message(websocket_client_t *client, const char *message, size_t len, void *user_data);
void handle_uetrace_ws_connection_change(websocket_client_t *client, websocket_status_t status, void *user_data);
void send_uetrace_subscription_command(websocket_client_t *client);
void send_uetrace_unsubscription_command(websocket_client_t *client);
// void *uetrace_websocket_thread_function(void *arg);
void free_metrics_array();
#endif
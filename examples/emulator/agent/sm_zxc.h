#ifndef SM_ZXC_READ_WRITE_AGENT_H
#define SM_ZXC_READ_WRITE_AGENT_H

#include "../../../src/agent/e2_agent_api.h"
#include "../../../src/util/http_json/http_client.h"
#include "../../../src/util/http_json/json_parser.h"
#include "../../../src/util/websocket/websocket_client.h"

void init_zxc_sm(void);

void free_zxc_sm(void);

bool read_zxc_sm(void*);
bool read_zxc_sm(void*);

void read_zxc_setup_sm(void* data);
void read_zxc_setup_sm(void* data);

sm_ag_if_ans_t write_ctrl_zxc_sm(void const* data);

void handle_zxc_signal(int sig);
void handle_zxc_message(websocket_client_t *client, const char *message, size_t len, void *user_data);
void handle_zxc_connection_change(websocket_client_t *client, websocket_status_t status, void *user_data);
void send_zxc_subscription_command(websocket_client_t *client);
void send_zxc_unsubscription_command(websocket_client_t *client);
void send_zxc_metrics_command(websocket_client_t *client);

#endif


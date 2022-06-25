#ifndef APP_H
#define APP_H

#include "stdint.h"

typedef struct{
	uint8_t head;
	uint8_t protocol_version;
	uint8_t device_type;
	uint8_t device_address[4];
	uint8_t cmd_type;
	uint8_t data;
};

void app_init();
void app_loop();

#endif

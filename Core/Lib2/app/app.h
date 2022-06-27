#ifndef APP_H
#define APP_H

#include "stdint.h"

typedef struct{
	uint8_t head;
	uint8_t protocol_version;
	uint8_t device_type;
	uint8_t device_address[4];
	uint8_t cmd_type;
	uint8_t cmd;
}boot_frame_t;

typedef struct{
	uint8_t address[4];
}boot_config_t;

typedef struct{
	uint16_t index;
	uint8_t data[128];
}boot_cmd_data_t;

typedef struct{
	uint32_t app_len;
}boot_cmd_finish_t;

#define PROTOCOL_HEAD 0xAA
#define PROTOCOL_VERSION 0x00
#define DEVICE_TYPE 0x01

#define FLASH_LEN  (32*1024)

#define APP_ADDRESS (4*1024)
#define CONFIG_ADDRESS (FLASH_LEN - 2*1024)

#define FRAME_DATA_LEN 128

#define APP_BOOT_DELAY 3000

typedef enum{
	BOOT_CMD_DATA,
	BOOT_CMD_FINISH,
}boot_cmd_t;

typedef enum{
	BOOT_STATE_IDLE,
	BOOT_STATE_TO_WRITE,
	BOOT_STATE_WRITING,
}boot_state_t;

typedef struct{
	boot_state_t boot_state;
	uint8_t flash_buf[FRAME_DATA_LEN];
	uint16_t index;
	uint32_t count_1ms;
	uint8_t flag_1s;
	uint8_t is_updating;

	uint8_t uart_buf[256];
	uint16_t uart_len;
	uint8_t uart_flag;
}var_t;

extern var_t var;

void app_init();
void app_loop();
void *memcpy(void* dest,void* source,unsigned int len);

#endif

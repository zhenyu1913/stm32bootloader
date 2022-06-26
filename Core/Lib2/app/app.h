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
	uint8_t app_crc[2];
	uint32_t app_len;
}boot_config_t

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

#define APP_ADDRESS 0x1000
#define CONFIG_ADDRESS 0xC00

#define FRAME_DATA_LEN 128


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
}var_t;

void app_init();
void app_loop();

#endif

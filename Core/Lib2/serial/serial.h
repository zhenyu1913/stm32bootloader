#ifndef FRAME_H
#define FRAME_H

#include "stdint.h"

typedef enum{
	SERIAL_IDLE,
	SERIAL_RECEIVING,
	SERIAL_SENDING,
}serial_state_t;

#define buf_len 256

typedef struct{
	serial_state_t state;
	uint8_t buf[buf_len];
	uint16_t len;
	uint16_t index;
	uint16_t timeout;
	uint16_t timeout_set;
}serial_t;

typedef enum{
	SERIAL_TR_SEND,
	SERIAL_TR_REV
}serial_tr_t;

typedef enum{
	SERIAL_TXE_ENABLE,
	SERIAL_TXE_DISABLE,
}serial_txe_t;

void serial_send_byte(serial_t* serial,uint8_t byte);
void serial_tr_control(serial_t* serial,serial_tr_t tr);
void serial_receive_frame(serial_t* serial,uint8_t* buf,uint16_t len);
void serial_txe_it_controal(serial_t* serial,serial_txe_t txe);

#endif

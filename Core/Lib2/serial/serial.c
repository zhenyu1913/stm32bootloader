#include "../../Lib2/serial/serial.h"

#include "string.h"

void serial_receive_byte(serial_t* serial,uint8_t byte){
	if(serial->state == SERIAL_SENDING){
		return;
	}
	if(serial->state == SERIAL_IDLE){
		serial->index = 0;
		serial->state = SERIAL_RECEIVING;
	}
	serial->buf[serial->index] = byte;
	serial->index++;
	serial->timeout = 0;
}

void serial_1ms_ISR(serial_t* serial){
	if(serial->timeout < serial->timeout_set){
		serial->timeout++;
	}else{
		serial_receive_frame(serial, serial->buf, serial->index);
	}
}

void serial_send_txe_ISR(serial_t* serial){
	if(serial->index < serial->len){
		serial_send_byte(serial,serial->buf[serial->index]);
		serial->index++;
	}else{
		serial->state = SERIAL_IDLE;
		serial_tr_control(serial,SERIAL_TR_REV);
		serial_txe_it_controal(serial,SERIAL_TXE_DISABLE);
	}
}

void serial_send_frame(serial_t* serial,uint8_t* buf,uint16_t len){
	serial->state = SERIAL_SENDING;
	memcpy(serial->buf,buf,len);
	serial->len = len;
	serial->index = 0;
	serial_tr_control(serial,SERIAL_TR_SEND);
	serial_txe_it_controal(serial,SERIAL_TXE_ENABLE);
}


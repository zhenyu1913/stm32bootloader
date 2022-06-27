#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include "serial.h"

extern serial_t* uart;

void serial_1ms_ISR(serial_t* serial);
void serial_send_txe_ISR(serial_t* serial);
void serial_receive_byte(serial_t* serial,uint8_t byte);
void serial_send_frame(serial_t* serial,uint8_t* buf,uint16_t len);

#endif

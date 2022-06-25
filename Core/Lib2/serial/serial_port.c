#include "main.h"

#include "../../Lib2/serial/serial.h"

serial_t uart_instance;
serial_t* uart = &uart_instance;

void serial_send_byte(serial_t* serial,uint8_t byte){
	LL_USART_TransmitData8(USART2, byte);
}

void serial_txe_it_controal(serial_t* serial,serial_txe_t txe){
	if(txe == SERIAL_TXE_ENABLE){
		LL_USART_EnableIT_TXE_TXFNF(USART2);
	}else{
		LL_USART_DisableIT_TXE_TXFNF(USART2);
	}
}

void serial_tr_control(serial_t* serial,serial_tr_t tr){

}

void serial_receive_frame(serial_t* serial,uint8_t* buf,uint16_t len){

}

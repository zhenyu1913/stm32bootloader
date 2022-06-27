#include "app.h"
#include "crc.h"
#include "stm32g0xx_hal_flash.h"
#include "serial_port.h"

var_t var;
boot_config_t boot_config;

typedef void (*fnc_ptr)(void);

uint8_t flash_write(uint16_t index,uint8_t*buf){
	int i;
	HAL_FLASH_Unlock();
	for(i = 0; i < FRAME_DATA_LEN; i += 8){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, APP_ADDRESS+index*FRAME_DATA_LEN+i, *(uint64_t*)((uint8_t*)buf+i));
	}
	HAL_FLASH_Lock();
	return 0;
}

uint8_t flash_earse(){
	FLASH_EraseInitTypeDef pEraseInit;
	uint32_t PageError;
	HAL_FLASH_Unlock();
	pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
	pEraseInit.Page = APP_ADDRESS/FLASH_PAGE_SIZE;
	pEraseInit.NbPages = FLASH_PAGE_NB - 1 - pEraseInit.Page;
	if(HAL_FLASHEx_Erase(&pEraseInit, &PageError) != HAL_OK){
		return 1;
	}
	HAL_FLASH_Lock();
	return 0;
}


void mcu_deInit(){

}

void flash_jump_to_app(void)
{
  /* Function pointer to the address of the user application. */
  fnc_ptr jump_to_app;
  jump_to_app = (fnc_ptr)(*(volatile uint32_t*) (APP_ADDRESS+4u));
  mcu_deInit();
  /* Change the main stack pointer. */
  __set_MSP(*(volatile uint32_t*)APP_ADDRESS);
  jump_to_app();
}

typedef enum{
    CMD_RETURN_OK,
    CMD_RETURN_ERR,
    CMD_RETURN_NO_RETURN,
}cmd_return_t;

int memcmp(void* dest,void* source,unsigned int len){
    uint32_t i;
    for(i = 0; i < len; i++){
        if(((uint8_t*)dest)[i] != ((uint8_t*)source)[i]){
            return 1;
        }
    }
    return 0;
}

void *memcpy(void* dest,void* source,unsigned int len){
    uint32_t i;
    for(i = 0; i < len; i++){
    	((uint8_t*)dest)[i] = ((uint8_t*)source)[i];
    }
    return 0;
}

cmd_return_t receive_deal(uint8_t*buf,uint16_t len){
    boot_frame_t *bf = (boot_frame_t *)buf;
    if(crc16(buf,len) != 0){
        return CMD_RETURN_NO_RETURN;
    }
    if(bf->head != PROTOCOL_HEAD){
        return CMD_RETURN_NO_RETURN;
    }
    if(bf->protocol_version != PROTOCOL_VERSION){
        return CMD_RETURN_NO_RETURN;
    }
    if(bf->device_type != DEVICE_TYPE){
        return CMD_RETURN_NO_RETURN;
    }
    if(memcmp(boot_config.address,bf->device_address,sizeof(boot_config.address)) != 0){
        return CMD_RETURN_NO_RETURN;
    }
    if(bf->cmd_type == BOOT_CMD_DATA){
    	var.is_updating = 1;
        boot_cmd_data_t *cmd = (boot_cmd_data_t *)&bf->cmd;
        if(cmd->index == 0){
            flash_earse();
        }
        var.index = cmd->index;
        flash_write(var.index,cmd->data);
    }
    if(bf->cmd_type == BOOT_CMD_FINISH){
    	var.is_updating = 0;
    	var.count_1ms = APP_BOOT_DELAY - 1000;
        boot_cmd_finish_t *cmd = (boot_cmd_finish_t *)&bf->cmd;
        if(crc16((uint8_t*)APP_ADDRESS,cmd->app_len) == 0){
            return CMD_RETURN_OK;
        }else{
            return CMD_RETURN_ERR;
        }
    }
    return CMD_RETURN_OK;
}

void app_init(){
    memcpy((uint8_t*)&boot_config,(uint8_t*)CONFIG_ADDRESS,sizeof(boot_config));
}

void app_loop(){
    if(var.count_1ms >= APP_BOOT_DELAY && var.is_updating == 0){
    	flash_jump_to_app();
    }
    if(var.uart_flag == 1){
    	var.uart_flag = 0;
    	if(receive_deal(var.uart_buf,var.uart_len) != CMD_RETURN_NO_RETURN){
    		serial_send_frame(uart,var.uart_buf,var.uart_len);
    	}
    }
}

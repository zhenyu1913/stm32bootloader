#include "app.h"
#include "crc.h"

var_t var;
boot_config_t boot_config;

void flash_write(uint32_t flash_address,uint8_t*buf,uint16_t len){
    flash_write(APP_ADDRESS+var.index*FRAME_DATA_LEN,cmd->data,FRAME_DATA_LEN);
}

void flash_earse(){
    
}

typedef enum{
    CMD_RETURN_OK,
    CMD_RETURN_ERR,
    CMD_RETURN_NO_RETURN,
}cmd_return_t;

uint8_t memcmp(uint8_t* dest,uint8_t* source,uint32_t len){
    uint32_t i;
    for(i = 0; i < len; i++){
        if(dest[i] != source[i]){
            return 1;
        }
    }
    return 0;
}

void memcpy(uint8_t* dest,uint8_t* source,uint32_t len){
    uint32_t i;
    for(i = 0; i < len; i++){
        dest[i] = source[i];
    }
}

cmd_return_t receive_deal(uint8_t*buf,uint16_t len){
    boot_frame_t *bf = buf;
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
        boot_cmd_data_t *cmd = &bf->cmd;
        if(cmd->index == 0){
            flash_earse();
        }
        var.index = cmd->index;
        flash_write(var.index,cmd->data);
    }
    if(bf->cmd_type == BOOT_CMD_FINISH){
        boot_cmd_finish_t *cmd = &bf->cmd;
        if(crc16((uint8_t*)APP_ADDRESS,cmd->app_len) == 0){
            return CMD_RETURN_OK;
        }else{
            return CMD_RETURN_ERR;
        }
    }
    return CMD_RETURN_OK;
}

void app_init(){
    memcpy(&boot_config,CONFIG_ADDRESS,sizeof(boot_config));
}

void app_loop(){
    // if(var.boot_state == BOOT_STATE_TO_WRITE){
    //     flash_write(APP_ADDRESS+var.index*FRAME_DATA_LEN,var.flash_buf,FRAME_DATA_LEN);
    //     var.boot_state = BOOT_STATE_IDLE;
    // }
}

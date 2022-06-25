################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LIb/serial/serial.c \
../Core/LIb/serial/serial_port.c 

OBJS += \
./Core/LIb/serial/serial.o \
./Core/LIb/serial/serial_port.o 

C_DEPS += \
./Core/LIb/serial/serial.d \
./Core/LIb/serial/serial_port.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LIb/serial/%.o Core/LIb/serial/%.su: ../Core/LIb/serial/%.c Core/LIb/serial/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32G031xx -DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=0 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"D:/yzy/workspace/bootloader/Core/LIb/serial" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-LIb-2f-serial

clean-Core-2f-LIb-2f-serial:
	-$(RM) ./Core/LIb/serial/serial.d ./Core/LIb/serial/serial.o ./Core/LIb/serial/serial.su ./Core/LIb/serial/serial_port.d ./Core/LIb/serial/serial_port.o ./Core/LIb/serial/serial_port.su

.PHONY: clean-Core-2f-LIb-2f-serial


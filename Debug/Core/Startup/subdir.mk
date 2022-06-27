################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32g031f8px.s 

OBJS += \
./Core/Startup/startup_stm32g031f8px.o 

S_DEPS += \
./Core/Startup/startup_stm32g031f8px.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -I"D:/yzy/workspace/bootloader/Core/Lib2/app" -I"D:/yzy/workspace/bootloader/Core/Lib2/crc" -I"D:/yzy/workspace/bootloader/Core/Lib2/STM32G0xx_HAL_Driver/Inc" -I"D:/yzy/workspace/bootloader/Core/Lib2/serial" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32g031f8px.d ./Core/Startup/startup_stm32g031f8px.o

.PHONY: clean-Core-2f-Startup


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Devices/Menu/Src/menu.c \
../Devices/Menu/Src/menu_config.c 

OBJS += \
./Devices/Menu/Src/menu.o \
./Devices/Menu/Src/menu_config.o 

C_DEPS += \
./Devices/Menu/Src/menu.d \
./Devices/Menu/Src/menu_config.d 


# Each subdirectory must supply rules for building sources it contributes
Devices/Menu/Src/%.o Devices/Menu/Src/%.su: ../Devices/Menu/Src/%.c Devices/Menu/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Devices/LCD_Display/Inc -I../Devices/Menu/Inc -I../Devices/PID_Controller/Inc -I../Devices/BH1750/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Devices-2f-Menu-2f-Src

clean-Devices-2f-Menu-2f-Src:
	-$(RM) ./Devices/Menu/Src/menu.d ./Devices/Menu/Src/menu.o ./Devices/Menu/Src/menu.su ./Devices/Menu/Src/menu_config.d ./Devices/Menu/Src/menu_config.o ./Devices/Menu/Src/menu_config.su

.PHONY: clean-Devices-2f-Menu-2f-Src


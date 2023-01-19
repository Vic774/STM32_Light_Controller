################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Devices/PID_Controller/Src/pid.c 

OBJS += \
./Devices/PID_Controller/Src/pid.o 

C_DEPS += \
./Devices/PID_Controller/Src/pid.d 


# Each subdirectory must supply rules for building sources it contributes
Devices/PID_Controller/Src/%.o Devices/PID_Controller/Src/%.su: ../Devices/PID_Controller/Src/%.c Devices/PID_Controller/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Devices/LCD_Display/Inc -I../Devices/Menu/Inc -I../Devices/PID_Controller/Inc -I../Devices/BH1750/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Devices-2f-PID_Controller-2f-Src

clean-Devices-2f-PID_Controller-2f-Src:
	-$(RM) ./Devices/PID_Controller/Src/pid.d ./Devices/PID_Controller/Src/pid.o ./Devices/PID_Controller/Src/pid.su

.PHONY: clean-Devices-2f-PID_Controller-2f-Src


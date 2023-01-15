################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Devices/LCD_Display/Src/lcd.c \
../Devices/LCD_Display/Src/lcd_config.c 

OBJS += \
./Devices/LCD_Display/Src/lcd.o \
./Devices/LCD_Display/Src/lcd_config.o 

C_DEPS += \
./Devices/LCD_Display/Src/lcd.d \
./Devices/LCD_Display/Src/lcd_config.d 


# Each subdirectory must supply rules for building sources it contributes
Devices/LCD_Display/Src/%.o Devices/LCD_Display/Src/%.su: ../Devices/LCD_Display/Src/%.c Devices/LCD_Display/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Devices/LCD_Display/Inc -I../Devices/PID_Controller/Inc -I../Devices/BH1750/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Devices-2f-LCD_Display-2f-Src

clean-Devices-2f-LCD_Display-2f-Src:
	-$(RM) ./Devices/LCD_Display/Src/lcd.d ./Devices/LCD_Display/Src/lcd.o ./Devices/LCD_Display/Src/lcd.su ./Devices/LCD_Display/Src/lcd_config.d ./Devices/LCD_Display/Src/lcd_config.o ./Devices/LCD_Display/Src/lcd_config.su

.PHONY: clean-Devices-2f-LCD_Display-2f-Src


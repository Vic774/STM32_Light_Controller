################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LCD_display/Src/lcd.c 

OBJS += \
./Drivers/LCD_display/Src/lcd.o 

C_DEPS += \
./Drivers/LCD_display/Src/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LCD_display/Src/%.o Drivers/LCD_display/Src/%.su: ../Drivers/LCD_display/Src/%.c Drivers/LCD_display/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-LCD_display-2f-Src

clean-Drivers-2f-LCD_display-2f-Src:
	-$(RM) ./Drivers/LCD_display/Src/lcd.d ./Drivers/LCD_display/Src/lcd.o ./Drivers/LCD_display/Src/lcd.su

.PHONY: clean-Drivers-2f-LCD_display-2f-Src


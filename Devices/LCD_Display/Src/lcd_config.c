/*
 * lcd_config.c
 *
 *  Created on: 13 sty 2023
 *      Author: Wiktor Piechowiak
 */

/* Includes */
#include "lcd.h"
#include "lcd_config.h"
#include "main.h"
#include "tim.h"

/* Private variables */

Lcd_PortType ports[] = {
		  LCD_D4_GPIO_Port, LCD_D5_GPIO_Port, LCD_D6_GPIO_Port, LCD_D7_GPIO_Port
  };

Lcd_PinType pins[] = {LCD_D4_Pin, LCD_D5_Pin, LCD_D6_Pin, LCD_D7_Pin};

/* Public variables */

Lcd_HandleTypeDef lcd = {
  .mode = LCD_4_BIT_MODE,

  .en_pin = LCD_E_Pin,
  .en_port = LCD_E_GPIO_Port,

  .rs_pin = LCD_RS_Pin,
  .rs_port = LCD_RS_GPIO_Port,

  .data_pin = pins,
  .data_port = ports,

  .timer = &htim14
};

/*
 * menu_config.c
 *
 *  Created on: 18 sty 2023
 *      Author: Wiktor Piechowiak
 */


/* Includes ------------------------------------------------------------------*/
#include "menu.h"
#include <stdio.h>

#include "usart.h"
#include "tim.h"

#include "lcd_config.h"
#include "bh1750_config.h"

/* Private function prototypes -----------------------------------------------*/
void menu_dout_routine(MenuItem_TypeDef* hmenuitem, GPIO_TypeDef* Port, uint16_t Pin, const char* name);
void menu_folder_routine(MenuItem_TypeDef* hmenuitem, const char* name);
//void menu_pwm_routine(MenuItem_TypeDef* hmenuitem, PWM_Handle_TypeDef* hpwm, const char* name);
//void menu_uint_io_routine(MenuItem_TypeDef* hmenuitem, unsigned int value, unsigned int len, const char* name, const char* unit);
void menu_float_io_routine(MenuItem_TypeDef* hmenuitem, float value, unsigned int len, const char* name, const char* unit);
//void menu_dac_routine(MenuItem_TypeDef* hmenuitem, uint32_t channel, const char* name);

/* Public variables ----------------------------------------------------------*/
Menu_TypeDef hmenu = {
  .Display = &lcd, .Timer = &htim6, .SerialPort = &huart3, .Initialized = 0
};

unsigned int ADC1_ConvResults_mV[16];

/* Private variables ---------------------------------------------------------*/
MENU_ITEM_CONTRUCTOR(menu_DO_folder, {menu_folder_routine(hmenuitem, "Dgtl Outputs");} );
MENU_ITEM_CONTRUCTOR(menu_DI_folder, {menu_folder_routine(hmenuitem, "Dgtl Inputs");} );
MENU_ITEM_CONTRUCTOR(menu_AO_folder, {menu_folder_routine(hmenuitem, "Anlg Outputs");} );
MENU_ITEM_CONTRUCTOR(menu_AI_folder, {menu_folder_routine(hmenuitem, "Anlg Inputs");} );

MENU_ITEM_CONTRUCTOR(menu_ld1, {menu_dout_routine(hmenuitem, LD1_GPIO_Port, LD1_Pin, "LD1");} );
MENU_ITEM_CONTRUCTOR(menu_ld2, {menu_dout_routine(hmenuitem, LD2_GPIO_Port, LD2_Pin, "LD2");} );
MENU_ITEM_CONTRUCTOR(menu_ld3, {menu_dout_routine(hmenuitem, LD3_GPIO_Port, LD3_Pin, "LD3");} );

MENU_ITEM_CONTRUCTOR(menu_bh1750, {menu_float_io_routine(hmenuitem, hbh1750_1.Readout, 6, "LIGHT", "lx");} );

#define MENU_FOLDERS_NBR 4
#define MENU_1ST_DO 4
#define MENU_MAIN_LEN (sizeof(MENU_MAIN_ARRAY)/sizeof(MENU_MAIN_ARRAY[0]))
MenuItem_TypeDef* MENU_MAIN_ARRAY[] = { /* Main menu list */
  &menu_DO_folder,	 	/* Digital outputs folder */
  &menu_DI_folder,	 	/* Digital inputs folder */
  &menu_AO_folder,	 	/* Analog outputs folder */
  &menu_AI_folder,	 	/* Analog inputs folder */
  &menu_ld1,     		/* LED Green #1: on-board green LED (LD1) */
  &menu_ld2,     		/* LED Blue #1: on-board blue LED (LD2) */
  &menu_ld3,     		/* LED Red #1: on-board red LED (LD3) */
  &menu_bh1750,   		/* Light sensor: BH1750 */
};

/* Private function ----------------------------------------------------------*/

/**
 * @brief Common digital output menu routine.
 * @param[in/out] hmenuitem : Menu item structure
 * @param[in]     hled      : Digital output handler
 * @param[in]     name      : Output display name
 */
void menu_dout_routine(MenuItem_TypeDef* hmenuitem, GPIO_TypeDef* Port, uint16_t Pin, const char* name)
{
//  if(hmenu.Item == hmenuitem) // If active component
//  {
//    ENC_GetCounter(&henc1);
//    if(henc1.CounterInc)
//    	HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_SET);
//    else if(henc1.CounterDec)
//    	HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_RESET);
//  }

  char temp_str[LCD_LINE_BUF_LEN];
  hmenuitem->DisplayStrLen = snprintf(temp_str, LCD_LINE_LEN, "%s: %s", name, (_Bool)HAL_GPIO_ReadPin(Port, Pin) ? "ON" : "OFF");
  MENU_ITEM_WriteDisplayBuffer(hmenuitem, temp_str); // Set display buffer
  hmenuitem->SerialPortStrLen = 0;
}

/**
 * @brief Common menu folders routine.
 * @param[in/out] hmenuitem : Menu item structure
 * @param[in]     name      : Output display name
 */
void menu_folder_routine(MenuItem_TypeDef* hmenuitem, const char* name)
{
	char temp_str[LCD_LINE_BUF_LEN];
	hmenuitem->DisplayStrLen = snprintf(temp_str, LCD_LINE_LEN, "%s", name);
	MENU_ITEM_WriteDisplayBuffer(hmenuitem, temp_str); // Set display buffer
	hmenuitem->SerialPortStrLen = 0;
}

///**
// * @brief Common PWM menu routine.
// * @param[in/out] hmenuitem : Menu item structure
// * @param[in]     hpwm      : PWM output handler
// * @param[in]     name      : Output display name
// */
//void menu_pwm_routine(MenuItem_TypeDef* hmenuitem, PWM_Handle_TypeDef* hpwm, const char* name)
//{
//  if(hmenu.Item == hmenuitem) // If active component
//  {
//    if(hmenu.ItemChanged) // Reload counter if item changed
//      ENC_SetCounter(&henc1, PWM_ReadDuty(hpwm));
//    PWM_WriteDuty(hpwm, ENC_GetCounter(&henc1));
//  }
//
//  char temp_str[LCD_LINE_BUF_LEN];
//  hmenuitem->DisplayStrLen = snprintf(temp_str, LCD_LINE_LEN, "%s: %3d%%", name, (int)PWM_ReadDuty(hpwm));
//  MENU_ITEM_WriteDisplayBuffer(hmenuitem, temp_str); // Set display buffer
//  hmenuitem->SerialPortStrLen = 0;
//}

//void menu_uint_io_routine(MenuItem_TypeDef* hmenuitem, unsigned int value, unsigned int len, const char* name, const char* unit)
//{
//  char temp_str[LCD_LINE_BUF_LEN];
//  hmenuitem->DisplayStrLen = snprintf(temp_str, LCD_LINE_LEN, "%s: %*d %s", name, len, value, unit);
//  MENU_ITEM_WriteDisplayBuffer(hmenuitem, temp_str); // Set display buffer
//  hmenuitem->SerialPortStrLen = 0;
//}

void menu_float_io_routine(MenuItem_TypeDef* hmenuitem, float value, unsigned int len, const char* name, const char* unit)
{
  char temp_str[LCD_LINE_BUF_LEN];
  hmenuitem->DisplayStrLen = snprintf(temp_str, LCD_LINE_LEN, "%s: %*.2f%s", name, len, value, unit);
  MENU_ITEM_WriteDisplayBuffer(hmenuitem, temp_str); // Set display buffer
  hmenuitem->SerialPortStrLen = 0;
}

//void menu_dac_routine(MenuItem_TypeDef* hmenuitem, uint32_t channel, const char* name)
//{
//  if(hmenu.Item == hmenuitem) // If active component
//  {
//    if(hmenu.ItemChanged) // Reload counter if item changed
//      ENC_SetCounter(&henc1, DAC_REG2PERCENT(HAL_DAC_GetValue(&hdac, channel)));
//    HAL_DAC_SetValue(&hdac, channel, DAC_ALIGN_12B_R, DAC_PERCENT2REG(ENC_GetCounter(&henc1)));
//  }
//  char temp_str[LCD_LINE_BUF_LEN];
//  hmenuitem->DisplayStrLen = snprintf(temp_str, LCD_LINE_LEN, "%s: %4dmV", name, (int)DAC_REG2VOLTAGE(HAL_DAC_GetValue(&hdac, channel)));
//  MENU_ITEM_WriteDisplayBuffer(hmenuitem, temp_str); // Set display buffer
//  hmenuitem->SerialPortStrLen = 0;
//}

/* Public function -----------------------------------------------------------*/
/**
 * @brief Menu initialization. Creates doubly-linked list from elements of MENU_MAIN_ARRAY.
 * @param[in/out] hmenu : Menu structure
 */
void MENU_Init(Menu_TypeDef* hmenu)
{
  /* Active element initialization */
  hmenu->Item = MENU_MAIN_ARRAY[0];

  /* Folders loop*/
  for(uint8_t i = 0; i < (uint8_t)(MENU_FOLDERS_NBR-1); i++) //< Next item
      {
  	  MENU_MAIN_ARRAY[i]->Next = MENU_MAIN_ARRAY[i+1];
      }

  for(uint8_t i = 1; i < (uint8_t)MENU_FOLDERS_NBR; i++)     //< Previous item
      {
  	  MENU_MAIN_ARRAY[i]->Prev = MENU_MAIN_ARRAY[i-1];
      }
  /* Cyclic list */
  MENU_MAIN_ARRAY[MENU_FOLDERS_NBR-1]->Next = MENU_MAIN_ARRAY[0]; //< Next of last is first item
  MENU_MAIN_ARRAY[0]->Prev = MENU_MAIN_ARRAY[MENU_FOLDERS_NBR-1]; //< Previous of first is last item

  MENU_MAIN_ARRAY[0]->Child = MENU_MAIN_ARRAY[MENU_1ST_DO];
//  MENU_MAIN_ARRAY[1]->Child = MENU_MAIN_ARRAY[MENU_1ST_DO];
//  MENU_MAIN_ARRAY[2]->Child = MENU_MAIN_ARRAY[MENU_1ST_DO];
//  MENU_MAIN_ARRAY[3]->Child = MENU_MAIN_ARRAY[MENU_1ST_DO];

  hmenu->Initialized = 1;

  /* LCD set-up */
  Lcd_cursor(hmenu->Display, 0, 0);
  Lcd_string(hmenu->Display, ">");
  Lcd_cursor(hmenu->Display, 1, 0);
  Lcd_string(hmenu->Display, " ");
}

/**
 * @brief Menu routine. Calls active items routines and updates output devices.
 * @param[in/out] hmenu : Menu structure
 */
void MENU_ROUTINE(Menu_TypeDef* hmenu)
{

  if(!hmenu->Initialized)
  {
	  return;
  }

  MENU_CALL_ROUTINE(hmenu->Item);
  MENU_CALL_ROUTINE(hmenu->Item->Next);

  hmenu->ItemChanged = 0;

  // #1 line - active item
  Lcd_cursor(hmenu->Display, 0, 1);
  Lcd_string(hmenu->Display, hmenu->Item->DisplayStr);

  // #1 line - next item
  Lcd_cursor(hmenu->Display, 1, 1);
  Lcd_string(hmenu->Display, hmenu->Item->Next->DisplayStr);


  // Serial port streaming
  HAL_UART_Transmit(hmenu->SerialPort, (uint8_t*)hmenu->Item->SerialPortStr, hmenu->Item->SerialPortStrLen, 10);
}

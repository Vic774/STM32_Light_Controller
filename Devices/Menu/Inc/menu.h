/*
 * menu.h
 *
 *  Created on: 18 sty 2023
 *      Author: Wiktor Piechowiak
 */

#ifndef MENU_MENU_H_
#define MENU_MENU_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
#include "stm32f7xx_hal.h"

/* Define --------------------------------------------------------------------*/
#define SERIAL_PORT_MSG_BUF_LEN 64

/* Typedef -------------------------------------------------------------------*/
typedef struct _MenuItem MenuItem_TypeDef;

struct _MenuItem {
  char DisplayStr[LCD_LINE_BUF_LEN];
  uint16_t DisplayStrLen;
  char SerialPortStr[SERIAL_PORT_MSG_BUF_LEN];
  uint16_t SerialPortStrLen;
  MenuItem_TypeDef* Next;
  MenuItem_TypeDef* Prev;
  MenuItem_TypeDef* Child;
  MenuItem_TypeDef* Parent;
  void (*Routine)(MenuItem_TypeDef* hmenuitem);
};

#define MENU_DisplayType Lcd_HandleTypeDef*
#define MENU_SerialType UART_HandleTypeDef*
#define MENU_TimerType TIM_HandleTypeDef*

typedef struct {
  /* Menu structure */
  MenuItem_TypeDef* Item;
  _Bool ItemChanged;
  /* Output devices */
  MENU_DisplayType Display;
  MENU_TimerType Timer;
  MENU_SerialType SerialPort;
  _Bool Initialized;
} Menu_TypeDef;

/* Macro ---------------------------------------------------------------------*/
#define MENU_ITEM_CONTRUCTOR(__NAME__, __FUNC__)                       \
void __##__NAME__##_routine(MenuItem_TypeDef* hmenuitem) __FUNC__      \
MenuItem_TypeDef __NAME__ = {                                          \
  .Next = &__NAME__, .Prev = &__NAME__, .Child = NULL, .Parent = NULL, \
  .Routine = __##__NAME__##_routine, .DisplayStrLen = LCD_LINE_LEN     \
}

#define MENU_CALL_ROUTINE(__NAME__)  (__NAME__)->Routine((__NAME__))
/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Clear menu item display buffer content (write spaces)
 * @param[out] hmenuitem : Menu item handler
 */
void MENU_ITEM_ClearDisplayBuffer(MenuItem_TypeDef* hmenuitem);

/**
 * @brief Write menu item display buffer content
 * @param[in/out] hmenuitem : Menu item handler
 */
void MENU_ITEM_WriteDisplayBuffer(MenuItem_TypeDef* hmenuitem, const char* str);

#endif /* MENU_MENU_H_ */

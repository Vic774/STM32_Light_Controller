/*
 * menu.c
 *
 *  Created on: 18 sty 2023
 *      Author: Wiktor Piechowiak
 */

/* Includes ------------------------------------------------------------------*/
#include "menu.h"

/* Private variables ---------------------------------------------------------*/
  const char __menu__padding[] = "                    "; // space x20

/* Public function -----------------------------------------------------------*/

/**
 * @brief Clear menu item display buffer content (write spaces)
 * @param[out] hmenuitem : Menu item handler
 */
void MENU_ITEM_ClearDisplayBuffer(MenuItem_TypeDef* hmenuitem)
{
  sprintf(hmenuitem->DisplayStr, "%.*s", LCD_LINE_LEN, __menu__padding);
}

/**
 * @brief Write menu item display buffer content
 * @param[in/out] hmenuitem : Menu item handler
 */
void MENU_ITEM_WriteDisplayBuffer(MenuItem_TypeDef* hmenuitem, const char* str)
{
  int pad_len = LCD_LINE_LEN - hmenuitem->DisplayStrLen;
  sprintf(hmenuitem->DisplayStr, "%s%.*s", str, pad_len, __menu__padding);
}

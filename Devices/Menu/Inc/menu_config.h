/*
 * menu_config.h
 *
 *  Created on: 18 sty 2023
 *      Author: Wiktor Piechowiak
 */

#ifndef MENU_MENU_CONFIG_H_
#define MENU_MENU_CONFIG_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "menu.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern Menu_TypeDef hmenu;

/* Public function prototypes ------------------------------------------------*/

void MENU_Init(Menu_TypeDef* hmenu);

void MENU_ROUTINE(Menu_TypeDef* hmenu);

#endif /* MENU_MENU_CONFIG_H_ */

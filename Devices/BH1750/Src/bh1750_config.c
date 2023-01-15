/*
 * bh1750_config.c
 *
 *  Created on: 13 sty 2023
 *      Author: Wiktor Piechowiak
 */


/* Includes ------------------------------------------------------------------*/

#include "bh1750.h"
#include "bh1750_config.h"
#include "main.h"
#include "i2c.h"

/* Public variables ----------------------------------------------------------*/

BH1750_HandleTypeDef hbh1750_1 = {
  .I2C = &hi2c1, .Address = BH1750_ADDRESS_L, .Timeout = 0xffff
};

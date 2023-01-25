/*
 * pid_config.c
 *
 *  Created on: 25 sty 2023
 *      Author: Wiktor Piechowiak
 */

/* Includes ------------------------------------------------------------------*/

#include "pid.h"
#include "pid_config.h"
#include "main.h"
#include "i2c.h"

/* Public variables ----------------------------------------------------------*/

PID_TypeDef Light_PID = {
		.SampleTime = 20,

		.OutMin = 0,
		.OutMax = 999
};

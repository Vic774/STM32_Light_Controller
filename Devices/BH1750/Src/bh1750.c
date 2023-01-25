/*
 * bh1750.c
 *
 *  Created on: 11 sty 2023
 *      Author: Wiktor Piechowiak
 */


/* Includes */
#include "bh1750.h"
#include "main.h"
#include "i2c.h"


/*
 * @brief BH1750 initialization procedure.
 * @note Sensor is set to continuous high resolution mode (1).
 *       Uses blocking mode I2C transmitting routine.
 * @param[in] hbh1750 BH1750 digital light sensor handler
 * @return None
 */
void BH1750_Init(BH1750_HandleTypeDef* hbh1750)
{
  uint8_t command;
  command = BH1750_POWER_ON;
  HAL_I2C_Master_Transmit(hbh1750->I2C, hbh1750->Address, &command, BH1750_COMMAND_SIZE, hbh1750->Timeout);
  command = BH1750_CONTINOUS_L_RES_MODE;
  HAL_I2C_Master_Transmit(hbh1750->I2C, hbh1750->Address, &command, BH1750_COMMAND_SIZE, hbh1750->Timeout);
}

/*
 * @brief BH1750 measurement read routine.
 * @note Uses blocking mode I2C receiving routine.
 * @param[in] hbh1750 BH1750 digital light sensor handler
 * @return Measurement result in lux [lx]
 */
float BH1750_ReadLux(BH1750_HandleTypeDef* hbh1750)
{
  float measure;
  uint8_t rxarray[BH1750_DATA_SIZE];
  HAL_I2C_Master_Receive(hbh1750->I2C, hbh1750->Address, rxarray, BH1750_DATA_SIZE, hbh1750->Timeout);
  measure = ((rxarray[BH1750_DATA_MSB]<<8) | rxarray[BH1750_DATA_LSB]) / 1.2;
  hbh1750->Readout = measure;
  return  measure;// @see BH1750 technical note p. 10;
}



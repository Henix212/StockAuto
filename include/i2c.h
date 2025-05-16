/**
 *  I2C Library to send 1, 2 or an array of bytes through i2c1 channel. Generated with CubeMX 
 *  and then added 3 functions at the end to simplify the i2c communication.
 * 
 *  @author StockAuto 
 */

/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   This file contains all the function prototypes for
  *          the i2c.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

extern I2C_HandleTypeDef hi2c1;

void MX_I2C1_Init(void);

/* USER CODE BEGIN Prototypes */

void I2C_TransmitDualByte(uint16_t addr, uint8_t* data);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */


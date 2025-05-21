/**
 * OLED Screen Library to easily use I2C for the screen.
 * 
 * @pre I2C Initialised (Probably pins PA15 for SCL and PB7 for SDA)
 * 
 * @author StockAuto
 */

#ifndef __OLED_H__
#define __OLED_H__

#include <string.h>

#include "i2c.h"

#define OLED_ADDR (0x3C << 1)

#define OLED_WIDTH 128 // Pixels
#define OLED_HEIGHT 64 // Pixels

#define OLED_PIXEL_ON 1
#define OLED_PIXEL_OFF 0

void OLED_Init();

void OLED_SendCommand(uint8_t command);

void OLED_SendData(uint8_t* data, uint16_t dataSize);

void OLED_SetCursor(uint8_t x, uint8_t y);

//
// Graphic functions
//  

void OLED_Clear();

void OLED_SetPixel(int x, int y, uint8_t state);

void OLED_PutChar(char c);

void OLED_Print(char* str);

#endif /* __OLED_H__ */
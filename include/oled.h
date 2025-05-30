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

#define ICON_SIZE 8 // CANNOT BE MODIFIED

#define OLED_PIXEL_ON 1
#define OLED_PIXEL_OFF 0

// Structrures

typedef enum {
    OLED_INVERTED,
    OLED_NON_INVERTED
} OLED_InversionMode;

typedef enum {
    OLED_BAR_ON,
    OLED_BAR_OFF
} OLED_BarMode;

typedef enum {
    OLED_FONT_COLOR_BLACK,
    OLED_FONT_COLOR_COLORED
} OLED_FontColor;

typedef struct {
    uint8_t map[ICON_SIZE];
} OLED_Icon;

void OLED_Init();

void OLED_SendCommand(uint8_t command);

void OLED_SendData(uint8_t* data, uint16_t dataSize);

void OLED_SetCursor(uint8_t x, uint8_t y);

void OLED_SetInverted(OLED_InversionMode mode);

void OLED_SetBar(OLED_BarMode mode);

//
// Graphic functions
//  

void OLED_Clear();

void OLED_SetPixel(uint8_t x, uint8_t y, uint8_t state);

void OLED_PutChar(char c, OLED_FontColor color);

void OLED_Print(char* str, OLED_FontColor color);

void OLED_CenterPrint(char* str, uint8_t x, uint8_t y, OLED_FontColor color);

void OLED_PutIcon(OLED_Icon* icon, uint8_t x, uint8_t y);

//
//  Icons
//

extern OLED_Icon OLED_SQUARE;
extern OLED_Icon OLED_EMPTY_SQUARE;
extern OLED_Icon OLED_CROSS;
extern OLED_Icon OLED_EMPTY_CROSS;
extern OLED_Icon OLED_ARROW_UP;
extern OLED_Icon OLED_ARROW_DOWN;
extern OLED_Icon OLED_ARROW_LEFT;
extern OLED_Icon OLED_ARROW_RIGHT;
extern OLED_Icon OLED_EMPTY_ARROW_UP;
extern OLED_Icon OLED_EMPTY_ARROW_DOWN;
extern OLED_Icon OLED_EMPTY_ARROW_LEFT;
extern OLED_Icon OLED_EMPTY_ARROW_RIGHT;
extern OLED_Icon OLED_ROUND;
extern OLED_Icon OLED_CIRCLE;

#endif /* __OLED_H__ */
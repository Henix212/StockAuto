/**
 * A librairy to display special pages on an OLED screen (128x64)
 * 
 * @pre OLED initialized (OLED lib, oled.h)
 * 
 *  @author StockAuto
 */

#include "pages.h"

static OLED_Icon LOCKER_ICON_1;
static OLED_Icon LOCKER_ICON_2;
static OLED_Icon EMPTY_LOCKER_ICON_1;
static OLED_Icon EMPTY_LOCKER_ICON_2;
static OLED_Icon EMPTY_LOCKER_ICON_3;
static OLED_Icon EMPTY_LOCKER_ICON_4;

static void PAGES_PutLocker(uint8_t x, uint8_t y);
static void PAGES_PutEmptyLocker(uint8_t x, uint8_t y);

void PAGE_Start() {
    OLED_SetBar(OLED_BAR_ON);
    OLED_SetInverted(OLED_INVERTED);

    OLED_CenterPrint("StockAuto", 64, 4, OLED_FONT_COLOR_COLORED);
}

void PAGE_Action() {
    OLED_SetBar(OLED_BAR_OFF);
    OLED_SetInverted(OLED_NON_INVERTED);

    // Page start

    OLED_PutIcon(&OLED_ROUND, 4, 1);
    OLED_CenterPrint("Action", 64, 1, OLED_FONT_COLOR_COLORED);
    OLED_PutIcon(&OLED_ROUND, 116, 1);

    OLED_CenterPrint("_____________________", 64, 2, OLED_FONT_COLOR_COLORED);

    OLED_PutIcon(&OLED_ARROW_DOWN, 28, 4);
    OLED_CenterPrint("Prendre", 32, 5, OLED_FONT_COLOR_COLORED);
    OLED_CenterPrint("(1)", 32, 6, OLED_FONT_COLOR_COLORED);

    OLED_PutIcon(&OLED_ARROW_UP, 92, 4);
    OLED_CenterPrint("Deposer", 96, 5, OLED_FONT_COLOR_COLORED);
    OLED_CenterPrint("(2)", 96, 6, OLED_FONT_COLOR_COLORED);
    
    OLED_CenterPrint("_____________________", 64, 7, OLED_FONT_COLOR_COLORED);

    // Page end
}

void PAGE_Lockers(PAGES_LockersStatus status) {
    OLED_SetBar(OLED_BAR_OFF);
    OLED_SetInverted(OLED_NON_INVERTED);

    // Page start

    OLED_PutIcon(&OLED_ROUND, 4, 1);
    OLED_CenterPrint("Casiers", 64, 1, OLED_FONT_COLOR_COLORED);
    OLED_PutIcon(&OLED_ROUND, 116, 1);

    OLED_CenterPrint("_____________________", 64, 2, OLED_FONT_COLOR_COLORED);

    for (uint8_t i = 0; i < PAGES_NB_LOCKERS; i++) {
        if (status.map[i] == LOCKER_EMPTY) {
            PAGES_PutEmptyLocker(8 + 32 * i, 4);
            OLED_CenterPrint((char[]) {'(', (char)(i + 1) + '0', ')'}, 16 + 32 * i, 7, OLED_FONT_COLOR_COLORED);
        } else if (status.map[i] == LOCKER_OCCUPIED) {
            PAGES_PutLocker(8 + 32 * i, 4);
        } else {
            Error_Handler();
        }
    }

    // Page end
}

static void PAGES_PutLocker(uint8_t x, uint8_t y) {
    OLED_PutIcon(&LOCKER_ICON_1, x, y);
    OLED_PutIcon(&LOCKER_ICON_2, x + 8, y);
    OLED_PutIcon(&OLED_SQUARE, x, y + 1);
    OLED_PutIcon(&OLED_SQUARE, x + 8, y + 1);
}

static void PAGES_PutEmptyLocker(uint8_t x, uint8_t y) {
    OLED_PutIcon(&EMPTY_LOCKER_ICON_1, x, y);
    OLED_PutIcon(&EMPTY_LOCKER_ICON_2, x + 8, y);
    OLED_PutIcon(&EMPTY_LOCKER_ICON_3, x, y + 1);
    OLED_PutIcon(&EMPTY_LOCKER_ICON_4, x + 8, y + 1);
}

//
//  Icons for the pages
//
static OLED_Icon LOCKER_ICON_1 = 
{
    {
        0b11111111,
        0b11111111,
        0b00110011,
        0b00110011,
        0b00110011,
        0b00110011,
        0b00110011,
        0b00110011
    }
};
static OLED_Icon LOCKER_ICON_2 = 
{
    {
        0b00110011,
        0b00110011,
        0b00110011,
        0b00110011,
        0b00110011,
        0b00110011,
        0b11111111,
        0b11111111
    }
};
static OLED_Icon EMPTY_LOCKER_ICON_1 = 
{
    {
        0b11111111,
        0b00000001,
        0b00000001,
        0b01001001,
        0b01001001,
        0b01001001,
        0b01001001,
        0b01001001,
    }
};
static OLED_Icon EMPTY_LOCKER_ICON_2 = 
{
    {
        0b01001001,
        0b01001001,
        0b01001001,
        0b01001001,
        0b01001001,
        0b00000001,
        0b00000001,
        0b11111111
    }
};
static OLED_Icon EMPTY_LOCKER_ICON_3 = 
{
    {
        0b11111111,
        0b10000000,
        0b10000000,
        0b10000000,
        0b10000000,
        0b10000000,
        0b10000000,
        0b10000000
    }
};
static OLED_Icon EMPTY_LOCKER_ICON_4 = 
{
    {
        0b10000000,
        0b10000000,
        0b10000000,
        0b10000000,
        0b10000000,
        0b10000000,
        0b10000000,
        0b11111111
    }
};
/**
 * OLED Screen Library to easily use I2C for the screen.
 *
 * @pre I2C Initialised (Probably pins PA15 for SCL and PB7 for SDA)
 *
 * @author StockAuto
 */

#include "oled.h"

/// @brief Initilizes the OLED Screen. It sends the initialisation
/// sequence to turn on the screen properly.
///
/// @pre I2C initialized
///
/// @post OLED Initialised
void OLED_Init()
{
    // Initialisation sequence
    uint8_t init[] = {
        0xA8, 0x3F,
        0xD3, 0x00,
        0x20, 0x00,
        0x40,
        0xA1,
        0xC8,
        0xDA, 0x12,
        0x81, 0x7F,
        0xA4,
        0xA6,
        0xD5, 0x80,
        0x8D, 0x14,
        0xAF};

    // Sends the sequence which is are commands
    for (uint8_t i = 0; i < sizeof(init); i++)
    {
        OLED_SendCommand(init[i]);
    }
}

/// @brief Sends a command to the OLED screen a command is made this way :
///
/// 2 bytes : {0x00 (to tell the screen its a command (0x40 for data instead)), command}
///
/// @param command The command to send to the screen
///
/// @pre I2C Initialized
void OLED_SendCommand(uint8_t command)
{
    uint8_t data[2] = {0x00, command};
    I2C_TransmitDualByte(OLED_ADDR, data);
}

/// @brief Sends data to the screen, basically bytes corresponding
/// to 8 of height columns
///
/// @param data The bytes to sends. Each byte represents a column
/// @param dataSize The number of bytes sent
void OLED_SendData(uint8_t *data, uint16_t dataSize)
{
    uint8_t buffer[dataSize + 1];
    buffer[0] = 0x40;
    memcpy(&buffer[1], data, dataSize);
    I2C_TransmitBytes(OLED_ADDR, buffer, sizeof(buffer));
}

/// @brief Places the cursor at the x, y position (y being the page ...)
/// @param x
/// @param y The page not exactly the y
void OLED_SetCursor(uint8_t x, uint8_t y)
{
    // Checking the values of X and Y
    if (x >= 128 || y >= 64)
    {
        Error_Handler();
    }

    // X
    OLED_SendCommand(0x21);
    OLED_SendCommand(x);
    OLED_SendCommand(OLED_WIDTH - 1);

    // Y
    OLED_SendCommand(0x22);
    OLED_SendCommand(0xA0 | y);
    OLED_SendCommand(0xB0);
}

/**
 * @brief Inverses the color of the background and the one of the text.
 */
void OLED_SetInverted(OLED_InversionMode mode)
{
    if (mode == OLED_INVERTED) {
        OLED_SendCommand(0xA7);
    } else if (mode == OLED_NON_INVERTED) {
        OLED_SendCommand(0xA6);
    } else {
        Error_Handler();
    }
}

/**
 * @brief Toggle ON/OFF the whole status bar
 */
void OLED_SetBar(OLED_BarMode mode)
{
    const uint16_t SIZE = 256;
    uint8_t buffer[SIZE];

    uint8_t byte = 0x01; // If not set then error
    if (mode == OLED_BAR_ON) {
        byte = 0xFF;
    } else if (mode == OLED_BAR_OFF) {
        byte = 0x00;
    } else {
        // ERROR
    }

    memset(buffer, byte, SIZE);

    OLED_SetCursor(0, 0);
    OLED_SendData(buffer, SIZE);
}

//
//  Graphic functions
//

/// @brief Clears the screen filling it with black pixels
void OLED_Clear()
{
    uint16_t size = OLED_WIDTH * OLED_HEIGHT / 8;
    uint8_t buffer[size + 1];
    buffer[0] = 0x40;
    memset(&buffer[1], 0x00, size);
    I2C_TransmitBytes(OLED_ADDR, buffer, size + 1);
}

/// @brief Set the state of the pixel (x, y) to ON / OFF
/// @param x
/// @param y
/// @param state The state of the pixel OLED_PIXEL_ON / OLED_PIXEL_OFF
void OLED_SetPixel(uint8_t x, uint8_t y, uint8_t state)
{
    OLED_SetCursor(x, y);

    uint8_t data = state;
    OLED_SendData(&data, 1);
}

/**
 * @brief Creates a mapping of char to uint8_t[5] which represents
 * the bytes to send to the screen. A byte represenet a column of 8 pixels
 * to light on.
 *
 * @param c The char to get the byte array
 * @return The byte array of the char
 */
static uint8_t *get_font(char c)
{
    static uint8_t font[][5] = {// By ChatGPT
        [' '] = {0x00, 0x00, 0x00, 0x00, 0x00},
        ['!'] = {0x00, 0x00, 0x5F, 0x00, 0x00},
        ['"'] = {0x00, 0x07, 0x00, 0x07, 0x00},
        ['#'] = {0x14, 0x7F, 0x14, 0x7F, 0x14},
        ['$'] = {0x24, 0x2A, 0x7F, 0x2A, 0x12},
        ['%'] = {0x23, 0x13, 0x08, 0x64, 0x62},
        ['&'] = {0x36, 0x49, 0x55, 0x22, 0x50},
        ['\''] = {0x00, 0x05, 0x03, 0x00, 0x00},
        ['('] = {0x00, 0x1C, 0x22, 0x41, 0x00},
        [')'] = {0x00, 0x41, 0x22, 0x1C, 0x00},
        ['*'] = {0x14, 0x08, 0x3E, 0x08, 0x14},
        ['+'] = {0x08, 0x08, 0x3E, 0x08, 0x08},
        [','] = {0x00, 0x50, 0x30, 0x00, 0x00},
        ['-'] = {0x08, 0x08, 0x08, 0x08, 0x08},
        ['.'] = {0x00, 0x60, 0x60, 0x00, 0x00},
        ['/'] = {0x20, 0x10, 0x08, 0x04, 0x02},
        ['0'] = {0x3E, 0x51, 0x49, 0x45, 0x3E},
        ['1'] = {0x00, 0x42, 0x7F, 0x40, 0x00},
        ['2'] = {0x42, 0x61, 0x51, 0x49, 0x46},
        ['3'] = {0x21, 0x41, 0x45, 0x4B, 0x31},
        ['4'] = {0x18, 0x14, 0x12, 0x7F, 0x10},
        ['5'] = {0x27, 0x45, 0x45, 0x45, 0x39},
        ['6'] = {0x3C, 0x4A, 0x49, 0x49, 0x30},
        ['7'] = {0x01, 0x71, 0x09, 0x05, 0x03},
        ['8'] = {0x36, 0x49, 0x49, 0x49, 0x36},
        ['9'] = {0x06, 0x49, 0x49, 0x29, 0x1E},
        [':'] = {0x00, 0x36, 0x36, 0x00, 0x00},
        [';'] = {0x00, 0x56, 0x36, 0x00, 0x00},
        ['<'] = {0x08, 0x14, 0x22, 0x41, 0x00},
        ['='] = {0x14, 0x14, 0x14, 0x14, 0x14},
        ['>'] = {0x00, 0x41, 0x22, 0x14, 0x08},
        ['?'] = {0x02, 0x01, 0x51, 0x09, 0x06},
        ['@'] = {0x32, 0x49, 0x79, 0x41, 0x3E},
        ['A'] = {0x7E, 0x11, 0x11, 0x11, 0x7E},
        ['B'] = {0x7F, 0x49, 0x49, 0x49, 0x36},
        ['C'] = {0x3E, 0x41, 0x41, 0x41, 0x22},
        ['D'] = {0x7F, 0x41, 0x41, 0x22, 0x1C},
        ['E'] = {0x7F, 0x49, 0x49, 0x49, 0x41},
        ['F'] = {0x7F, 0x09, 0x09, 0x09, 0x01},
        ['G'] = {0x3E, 0x41, 0x49, 0x49, 0x7A},
        ['H'] = {0x7F, 0x08, 0x08, 0x08, 0x7F},
        ['I'] = {0x00, 0x41, 0x7F, 0x41, 0x00},
        ['J'] = {0x20, 0x40, 0x41, 0x3F, 0x01},
        ['K'] = {0x7F, 0x08, 0x14, 0x22, 0x41},
        ['L'] = {0x7F, 0x40, 0x40, 0x40, 0x40},
        ['M'] = {0x7F, 0x02, 0x0C, 0x02, 0x7F},
        ['N'] = {0x7F, 0x04, 0x08, 0x10, 0x7F},
        ['O'] = {0x3E, 0x41, 0x41, 0x41, 0x3E},
        ['P'] = {0x7F, 0x09, 0x09, 0x09, 0x06},
        ['Q'] = {0x3E, 0x41, 0x51, 0x21, 0x5E},
        ['R'] = {0x7F, 0x09, 0x19, 0x29, 0x46},
        ['S'] = {0x46, 0x49, 0x49, 0x49, 0x31},
        ['T'] = {0x01, 0x01, 0x7F, 0x01, 0x01},
        ['U'] = {0x3F, 0x40, 0x40, 0x40, 0x3F},
        ['V'] = {0x1F, 0x20, 0x40, 0x20, 0x1F},
        ['W'] = {0x7F, 0x20, 0x18, 0x20, 0x7F},
        ['X'] = {0x63, 0x14, 0x08, 0x14, 0x63},
        ['Y'] = {0x07, 0x08, 0x70, 0x08, 0x07},
        ['Z'] = {0x61, 0x51, 0x49, 0x45, 0x43},
        ['['] = {0x00, 0x7F, 0x41, 0x41, 0x00},
        ['\\'] = {0x02, 0x04, 0x08, 0x10, 0x20},
        [']'] = {0x00, 0x41, 0x41, 0x7F, 0x00},
        ['^'] = {0x04, 0x02, 0x01, 0x02, 0x04},
        ['_'] = {0x40, 0x40, 0x40, 0x40, 0x40},
        ['`'] = {0x00, 0x01, 0x02, 0x04, 0x00},
        ['a'] = {0x20, 0x54, 0x54, 0x54, 0x78},
        ['b'] = {0x7F, 0x48, 0x44, 0x44, 0x38},
        ['c'] = {0x38, 0x44, 0x44, 0x44, 0x20},
        ['d'] = {0x38, 0x44, 0x44, 0x48, 0x7F},
        ['e'] = {0x38, 0x54, 0x54, 0x54, 0x18},
        ['f'] = {0x08, 0x7E, 0x09, 0x01, 0x02},
        ['g'] = {0x08, 0x54, 0x54, 0x54, 0x3C},
        ['h'] = {0x7F, 0x08, 0x04, 0x04, 0x78},
        ['i'] = {0x00, 0x44, 0x7D, 0x40, 0x00},
        ['j'] = {0x20, 0x40, 0x44, 0x3D, 0x00},
        ['k'] = {0x7F, 0x10, 0x28, 0x44, 0x00},
        ['l'] = {0x00, 0x41, 0x7F, 0x40, 0x00},
        ['m'] = {0x7C, 0x04, 0x18, 0x04, 0x78},
        ['n'] = {0x7C, 0x08, 0x04, 0x04, 0x78},
        ['o'] = {0x38, 0x44, 0x44, 0x44, 0x38},
        ['p'] = {0x7C, 0x14, 0x14, 0x14, 0x08},
        ['q'] = {0x08, 0x14, 0x14, 0x18, 0x7C},
        ['r'] = {0x7C, 0x08, 0x04, 0x04, 0x08},
        ['s'] = {0x48, 0x54, 0x54, 0x54, 0x20},
        ['t'] = {0x04, 0x3F, 0x44, 0x40, 0x20},
        ['u'] = {0x3C, 0x40, 0x40, 0x20, 0x7C},
        ['v'] = {0x1C, 0x20, 0x40, 0x20, 0x1C},
        ['w'] = {0x3C, 0x40, 0x30, 0x40, 0x3C},
        ['x'] = {0x44, 0x28, 0x10, 0x28, 0x44},
        ['y'] = {0x0C, 0x50, 0x50, 0x50, 0x3C},
        ['z'] = {0x44, 0x64, 0x54, 0x4C, 0x44},
        ['{'] = {0x00, 0x08, 0x36, 0x41, 0x00},
        ['|'] = {0x00, 0x00, 0x7F, 0x00, 0x00},
        ['}'] = {0x00, 0x41, 0x36, 0x08, 0x00},
        ['~'] = {0x08, 0x08, 0x2A, 0x1C, 0x08}
    };
    return font[(unsigned char)c];
}

/**
 * @brief Displays a char on the screen by sending a byte array (see get_font above)
 * @param c The char ot display
 * @param color The color of the char colored or black
 */
void OLED_PutChar(char c, OLED_FontColor color)
{
    const uint8_t FONT_WIDTH = 5;

    uint8_t* dataSrc = get_font(c);
    uint8_t data[FONT_WIDTH];
    memcpy(data, dataSrc, FONT_WIDTH);
    if (color == OLED_FONT_COLOR_BLACK) {
        for (uint8_t i = 0; i < FONT_WIDTH; i++) {
            data[i]^= 0xFF;
        }
    }

    OLED_SendData(data, FONT_WIDTH);
    uint8_t esp = (color == OLED_FONT_COLOR_BLACK) ? 0xFF : 0x00;
    OLED_SendData(&esp, 1);
}

/**
 * @brief Prints a text to the current cursor position usin OLED_PutChar()
 * @param str The text to print
 * @param color The color of the print colored or black
 */
void OLED_Print(char *str, OLED_FontColor color)
{
    for (int i = 0; i < strlen(str); i++)
    {
        OLED_PutChar(str[i], color);
    }
}

/**
 * @brief Prints a string put the reference point is at the center of the x
 * axis of the string and at the top the y axis
 *
 * @param str The string to print
 * @param x The coordinate x (CENTER of the string)
 * @param y The coordinate y (TOP of the string)
 * @param color The color of the print colored or black
 */
void OLED_CenterPrint(char *str, uint8_t x, uint8_t y, OLED_FontColor color)
{
    uint16_t strLen = strlen(str);

    const uint8_t CHAR_TOTAL_WIDTH = 6;

    uint8_t offsetX = 0;
    if (strLen % 2 == 0)
    {
        offsetX = -CHAR_TOTAL_WIDTH * strLen / 2;
    }
    else
    {
        offsetX = -CHAR_TOTAL_WIDTH * (strLen - 1) / 2 - CHAR_TOTAL_WIDTH / 2;
    }

    OLED_SetCursor(x + offsetX, y);

    OLED_Print(str, color);
}

/**
 * @brief Draws an icon on the screen
 * @param x
 * @param y
 * @param icon The icon to draw (see OLED_Icon to create your own)
 */
void OLED_PutIcon(OLED_Icon* icon, uint8_t x, uint8_t y) {
    uint8_t buffer[ICON_SIZE];
    memcpy(buffer, icon->map, ICON_SIZE);
    OLED_SetCursor(x, y);
    OLED_SendData(buffer, ICON_SIZE);
}

/**
 * Icons (a list of the available ones)
 */

OLED_Icon OLED_SQUARE = 
{
    {
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
    }
};

OLED_Icon OLED_EMPTY_SQUARE = {
    {
        0b11111111,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
        0b11111111,
    }
};

OLED_Icon OLED_CROSS = {
    {
        0b11000011,
        0b11100111,
        0b01111110,
        0b00111100,
        0b00111100,
        0b01111110,
        0b11100111,
        0b11000011,
    }
};

OLED_Icon OLED_EMPTY_CROSS = {
    {
        0b10000001,
        0b01000010,
        0b00100100,
        0b00011000,
        0b00011000,
        0b00100100,
        0b01000010,
        0b10000001,
    }
};

OLED_Icon OLED_ARROW_UP = {
    {
        0b00000000,
        0b00001100,
        0b00001110,
        0b11111111,
        0b11111111,
        0b00001110,
        0b00001100,
        0b00000000,
    }
};

OLED_Icon OLED_ARROW_DOWN = {
    {
        0b00000000,
        0b00110000,
        0b01110000,
        0b11111111,
        0b11111111,
        0b01110000,
        0b00110000,
        0b00000000,
    }
};

OLED_Icon OLED_ARROW_LEFT = {
    {
        0b00011000,
        0b00111100,
        0b01111110,
        0b01111110,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
    }
};

OLED_Icon OLED_ARROW_RIGHT = {
    {
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b01111110,
        0b01111110,
        0b00111100,
        0b00011000,
    }
};

OLED_Icon OLED_EMPTY_ARROW_UP = {
    {
        0b00010000,
        0b00110000,
        0b01011111,
        0b10000001,
        0b10000001,
        0b01011111,
        0b00110000,
        0b00010000,
    }
};

OLED_Icon OLED_EMPTY_ARROW_DOWN = {
    {
        0b00010000,
        0b00011000,
        0b11110100,
        0b10000001,
        0b10000001,
        0b11110100,
        0b00011000,
        0b00010000,
    }
};

OLED_Icon OLED_EMPTY_ARROW_LEFT = {
    {
        0b00011000,
        0b00100100,
        0b01000010,
        0b11100111,
        0b00100100,
        0b00100100,
        0b00100100,
        0b00111100,
    }
};

OLED_Icon OLED_EMPTY_ARROW_RIGHT = {
    {
        0b00111100,
        0b00100100,
        0b00100100,
        0b00100100,
        0b11100111,
        0b01000010,
        0b00100100,
        0b00011000,
    }
};

OLED_Icon OLED_ROUND = {
    {
        0b00111100,
        0b01111110,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b01111110,
        0b00111100,
    }
};

OLED_Icon OLED_CIRCLE = {
    {
        0b00111100,
        0b01000010,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
        0b01000010,
        0b00111100,
    }
};
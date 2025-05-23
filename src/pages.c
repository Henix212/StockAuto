/**
 * A librairy to display special pages on an OLED screen (128x64)
 * 
 * @pre OLED initialized (OLED lib, oled.h)
 * 
 *  @author StockAuto
 */

#include "pages.h"

void PAGE_Start() {
    OLED_SetBar(OLED_BAR_ON);
    OLED_SetInverted(OLED_INVERTED);

    OLED_CenterPrint("StockAuto", 64, 4, OLED_FONT_COLOR_COLORED);
}

void PAGE_Action() {
    OLED_SetBar(OLED_BAR_OFF);
    OLED_SetInverted(OLED_NON_INVERTED);

    OLED_CenterPrint("Action", 64, 1, OLED_FONT_COLOR_COLORED);
}
#ifndef MAIN_H
#define MAIN_H

#include "stm32g4xx_hal.h"

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);
char keypad_getkey(void);

#endif

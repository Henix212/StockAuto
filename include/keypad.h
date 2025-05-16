#ifndef KEYPAD_H
#define KEYPAD_H

volatile char last_key = 0;
int keypad_getkey(void);

#endif

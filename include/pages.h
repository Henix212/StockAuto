/**
 * A librairy to display special pages on an OLED screen (128x64)
 * 
 * @pre OLED initialized (OLED lib, oled.h)
 * 
 *  @author StockAuto
 */

#ifndef __PAGES_H__
#define __PAGES_H__

#include "oled.h"

#define PAGES_NB_LOCKERS 4

// Structures
typedef enum {
    LOCKER_OCCUPIED,
    LOCKER_EMPTY
} PAGES_LockerStatus;
typedef struct {
    PAGES_LockerStatus map[PAGES_NB_LOCKERS];
} PAGES_LockersStatus;

/**
 * PAGES
 */

void PAGE_Start();

void PAGE_Action();

void PAGE_Lockers(PAGES_LockersStatus status);

#endif /* __PAGES_H__ */
/*
 * Screens.h
 *
 *  Created on: 29 Eyl 2021
 *      Author: ebaglama
 */

#ifndef SCREENS_H_
#define SCREENS_H_

#include <stdint.h>


extern void appearedScreenMode(uint8_t);

#define TIME_UPDATE_TIME    5

typedef enum
{
    Screen_Home,          //Default value
    Screen_Set_Temp,
    Screen_Hum,
    Screen_Away,
    Screen_Antifreeze,
    Screen_P1,
    Screen_P2,
}Screens;

Screens screenType;



#endif /* SCREENS_H_ */

/*
 * Screens.c
 *
 *  Created on: 29 Eyl 2021
 *      Author: ebaglama
 */

#include "Screens.h"
#include "LCD_drive.h"
#include "HDC_1080.h"
//#include "Button_Function.h"

//#include <ti/drivers/I2C.h>
//#include "Board.h"
#include <stdint.h>



void appearedScreenMode(uint8_t screenType)
{

    LCD_software_reset();
    LCD_software_reset_release();
    LCD_set_ctrl_registers();

    if(screenType == Screen_Home)
    {
        LCD_print(HDC1080_getTemperature());
        LCD_update_temperature_segment(enabled);
        LCD_update_wireless_segment(disabled);
        LCD_update_battery_segment(disabled);
        LCD_update_humidity_segment(disabled);
        LCD_update_homeAway_segment(disabled);
        LCD_update_antiFreeze_segment(disabled);
        LCD_update_modulation_segment(disabled);
        LCD_update_floatingDot_segment(enabled);
        //celcius segment will be added

    }
    else if(screenType == Screen_Set_Temp)
    {
        LCD_update_temperature_segment(disabled);
        LCD_update_wireless_segment(disabled);
        LCD_update_battery_segment(disabled);
        LCD_update_humidity_segment(enabled);
        LCD_update_homeAway_segment(disabled);
        LCD_update_antiFreeze_segment(disabled);
        LCD_update_modulation_segment(disabled);
        LCD_update_floatingDot_segment(disabled);
    }
    else if(screenType == Screen_Hum)
    {
        LCD_update_temperature_segment(disabled);
        LCD_update_wireless_segment(disabled);
        LCD_update_battery_segment(disabled);
        LCD_update_humidity_segment(disabled);
        LCD_update_homeAway_segment(disabled);
        LCD_update_antiFreeze_segment(enabled);
        LCD_update_modulation_segment(disabled);
        LCD_update_floatingDot_segment(disabled);
    }
    else if(screenType == Screen_Away)
    {
        LCD_update_temperature_segment(disabled);
        LCD_update_wireless_segment(disabled);
        LCD_update_battery_segment(disabled);
        LCD_update_humidity_segment(disabled);
        LCD_update_homeAway_segment(disabled);
        LCD_update_antiFreeze_segment(disabled);
        LCD_update_modulation_segment(3);
        LCD_update_floatingDot_segment(disabled);
    }
    else if(screenType == Screen_Antifreeze)
    {
        LCD_update_temperature_segment(disabled);
        LCD_update_wireless_segment(enabled);
        LCD_update_battery_segment(disabled);
        LCD_update_humidity_segment(disabled);
        LCD_update_homeAway_segment(disabled);
        LCD_update_antiFreeze_segment(disabled);
        LCD_update_modulation_segment(disabled);
        LCD_update_floatingDot_segment(disabled);
    }
    else if(screenType == Screen_P1)
    {
        LCD_update_temperature_segment(disabled);
        LCD_update_wireless_segment(disabled);
        LCD_update_battery_segment(disabled);
        LCD_update_humidity_segment(disabled);
        LCD_update_homeAway_segment(disabled);
        LCD_update_antiFreeze_segment(disabled);
        LCD_update_modulation_segment(disabled);
        LCD_update_floatingDot_segment(disabled);
    }
    else if(screenType == Screen_P2)
    {
        LCD_update_temperature_segment(disabled);
        LCD_update_wireless_segment(disabled);
        LCD_update_battery_segment(disabled);
        LCD_update_humidity_segment(disabled);
        LCD_update_homeAway_segment(disabled);
        LCD_update_antiFreeze_segment(disabled);
        LCD_update_modulation_segment(disabled);
        LCD_update_floatingDot_segment(enabled);

        screenType = Screen_Home;
    }
}


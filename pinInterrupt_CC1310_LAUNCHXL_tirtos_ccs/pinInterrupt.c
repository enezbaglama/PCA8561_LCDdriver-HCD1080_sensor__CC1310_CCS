
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/PIN.h>

/* Example/Board Header files */
#include "Board.h"

/* Pin driver handles */
static PIN_Handle buttonPinHandle;

/* Global memory storage for a PIN_Config table */
static PIN_State buttonPinState;
#include "HDC_1080.h"
#include "LCD_drive.h"
#include "Screens.h"



PIN_Config buttonPinTable[] = {
    Board_PIN_BUTTON0  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    Board_PIN_BUTTON1  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    PIN_TERMINATE
};

/*
 *  ======== buttonCallbackFxn ========
 *
 *
 */
void buttonCallbackFxn(PIN_Handle handle, PIN_Id pinId) {

    /* Debounce logic, only toggle if the button is still pushed (low) */
    CPUdelay(8000*50);
    if (!PIN_getInputValue(pinId)) {
        /* Toggle LED based on the button pressed */
        switch (pinId) {
            case Board_PIN_BUTTON0:
                LCD_update_flame_segment(enabled);

                break;

            case Board_PIN_BUTTON1:
                CPUdelay(8000*50);
                LCD_update_flame_segment(disabled);
                break;

            default:
                /* Do nothing */
                break;
        }

//        appearedScreenMode(screenType);
    }
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{

    buttonPinHandle = PIN_open(&buttonPinState, buttonPinTable);
    if(!buttonPinHandle) {
        /* Error initializing button pins */
        while(1);
    }

    /* Setup callback for button pins */
    if (PIN_registerIntCb(buttonPinHandle, &buttonCallbackFxn) != 0) {
        /* Error registering button callback function */
        while(1);
    }

    LCD_software_reset();
    LCD_software_reset_release();
    LCD_set_ctrl_registers();

    /* Loop forever */
    while(1) {
        LCD_print(HDC1080_getTemperature());
        sleep(5);

    }
}

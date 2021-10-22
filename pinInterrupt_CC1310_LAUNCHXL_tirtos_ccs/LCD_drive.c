#include <LCD_drive.h>
#include <ti/drivers/I2C.h>
#include "Board.h"
#include <stdint.h>
#include <ti/drivers/GPIO.h>


#include <stddef.h>
#include <unistd.h>

#include <ti/display/Display.h>
#include <ti/drivers/PIN.h>

#include "HDC_1080.h"

//#include "Button_Function.h"
//#include "Screens.h"



I2C_Handle      i2cHandle;
I2C_Params      i2cParams;
I2C_Transaction i2cTransaction = {0};

void LCD_print(double printingValue)
{
    printingValue = printingValue * 10;

    LCD_update_Digit_3((unsigned int)printingValue % 10);
    printingValue = printingValue / 10;
    LCD_update_Digit_2((unsigned int)printingValue % 10);
    printingValue = printingValue / 10;
    LCD_update_Digit_1((unsigned int)printingValue % 10);
}


/*
 *************************************************************************
 *                      I2C_ready2operation
 *************************************************************************
 */
void I2C_ready2operation(void)
{
    I2C_init();
    /* Create I2C for usage */
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2cHandle = I2C_open(Board_I2C0, &i2cParams);
    if (i2cHandle == NULL)
    {
        //Error Initializing I2C
        while (1);
    }
}





/*
 *************************************************************************
 *                      software_reset
 *************************************************************************
 */
void LCD_software_reset(void)
{
    I2C_ready2operation();

    uint8_t swRESET_buffer[2];

    swRESET_buffer[0] = SW_RESET_REG_ADDR;
    swRESET_buffer[1] = SW_RESET;


    i2cTransaction.slaveAddress = LCD_ADDR;
    i2cTransaction.writeBuf = swRESET_buffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    if (!I2C_transfer(i2cHandle, &i2cTransaction))
    {
        // Error. No i2c device found!
        while(1);
    }

    I2C_close(i2cHandle);
}







/*
 *************************************************************************
 *                      software_reset_release
 *************************************************************************
 */
void LCD_software_reset_release(void)
{
    I2C_ready2operation();

    uint8_t swRESET_buffer[2];

    swRESET_buffer[0] = SW_RESET_REG_ADDR;
    swRESET_buffer[1] = NO_RESET;


    i2cTransaction.slaveAddress = LCD_ADDR;
    i2cTransaction.writeBuf = swRESET_buffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    if (!I2C_transfer(i2cHandle, &i2cTransaction))
    {
        // Error. No i2c device found!
        while(1);
    }
    I2C_close(i2cHandle);
}







/*
 *************************************************************************
 *                      set_ctrl_registers
 *************************************************************************
 */
void LCD_set_ctrl_registers(void)
{
    I2C_ready2operation();

    CTRL.FrameFreq = _32Hz;
    CTRL.OSC = 0 ;
    CTRL.COE = 0;

    CTRL_1.Display_enable = enabled;
    CTRL_1.Bias = _1_3bias;
    CTRL_1.MUX = _1_4mux;
    CTRL_1.Boost = disabled;

    CTRL_2.INV = lineInversion;
    CTRL_2.BlinkControl = blinkOFF;


    uint8_t CTRL_buffer[4];

    CTRL_buffer[0] = DEVICE_CTRL_REG_ADDR;
    CTRL_buffer[1] = CTRL.CTRL_value;
    CTRL_buffer[2] = CTRL_1.CTRL1_value;
    CTRL_buffer[3] = CTRL_2.CTRL2_value;

    i2cTransaction.slaveAddress = LCD_ADDR;
    i2cTransaction.writeBuf = CTRL_buffer;
    i2cTransaction.writeCount = 4;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    if (!I2C_transfer(i2cHandle, &i2cTransaction))
    {
        // Error. No i2c device found!
        while(1);
    }

    I2C_close(i2cHandle);

}








/*
 *************************************************************************
 *                      update_Digit_1
 *************************************************************************
 */
void LCD_update_Digit_1(uint8_t digit1_value)
{
    I2C_ready2operation();
    uint8_t COM0_SEG8_15_buffer[2];
    uint8_t COM1_SEG8_15_buffer[2];
    uint8_t COM2_SEG8_15_buffer[2];
    uint8_t COM3_SEG8_15_buffer[2];


    switch (digit1_value)
    {
    case 0:
        COM3_SEG8_15.SEG8_1A = enabled;
        COM2_SEG8_15.SEG12_1B = enabled;
        COM1_SEG8_15.SEG9_1C = enabled;
        COM0_SEG8_15.SEG12_1D = enabled;
        COM1_SEG8_15.SEG13_1E = enabled;
        COM3_SEG8_15.SEG13_1F = enabled;
        COM1_SEG8_15.SEG12_1G = disabled;
        COM3_SEG8_15.SEG12_1H = enabled;
        COM3_SEG8_15.SEG9_1I = enabled;
        COM2_SEG8_15.SEG9_1J = enabled;
        COM0_SEG8_15.SEG9_1K = enabled;
        COM0_SEG8_15.SEG13_1L = enabled;
        COM2_SEG8_15.SEG13_1M = enabled;

        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM3_SEG8_15_buffer[0] = COM3_SEG8_15_REG_ADDR;
        COM3_SEG8_15_buffer[1] = COM3_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 1:
        COM3_SEG8_15.SEG8_1A = disabled;
        COM2_SEG8_15.SEG12_1B = enabled;
        COM1_SEG8_15.SEG9_1C = enabled;
        COM0_SEG8_15.SEG12_1D = disabled;
        COM1_SEG8_15.SEG13_1E = disabled;
        COM3_SEG8_15.SEG13_1F = disabled;
        COM1_SEG8_15.SEG12_1G = disabled;
        COM3_SEG8_15.SEG12_1H = disabled;
        COM3_SEG8_15.SEG9_1I = enabled;
        COM2_SEG8_15.SEG9_1J = enabled;
        COM0_SEG8_15.SEG9_1K = enabled;
        COM0_SEG8_15.SEG13_1L = disabled;
        COM2_SEG8_15.SEG13_1M = disabled;

        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM3_SEG8_15_buffer[0] = COM3_SEG8_15_REG_ADDR;
        COM3_SEG8_15_buffer[1] = COM3_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 2:
        COM3_SEG8_15.SEG8_1A = enabled;
        COM2_SEG8_15.SEG12_1B = enabled;
        COM1_SEG8_15.SEG9_1C = disabled;
        COM0_SEG8_15.SEG12_1D = enabled;
        COM1_SEG8_15.SEG13_1E = enabled;
        COM3_SEG8_15.SEG13_1F = disabled;
        COM1_SEG8_15.SEG12_1G = enabled;
        COM3_SEG8_15.SEG12_1H = enabled;
        COM3_SEG8_15.SEG9_1I = enabled;
        COM2_SEG8_15.SEG9_1J = enabled;
        COM0_SEG8_15.SEG9_1K = enabled;
        COM0_SEG8_15.SEG13_1L = enabled;
        COM2_SEG8_15.SEG13_1M = enabled;

        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM3_SEG8_15_buffer[0] = COM3_SEG8_15_REG_ADDR;
        COM3_SEG8_15_buffer[1] = COM3_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        break;
    case 3:
        COM3_SEG8_15.SEG8_1A = enabled;
        COM2_SEG8_15.SEG12_1B = enabled;
        COM1_SEG8_15.SEG9_1C = enabled;
        COM0_SEG8_15.SEG12_1D = enabled;
        COM1_SEG8_15.SEG13_1E = disabled;
        COM3_SEG8_15.SEG13_1F = disabled;
        COM1_SEG8_15.SEG12_1G = enabled;
        COM3_SEG8_15.SEG12_1H = enabled;
        COM3_SEG8_15.SEG9_1I = enabled;
        COM2_SEG8_15.SEG9_1J = enabled;
        COM0_SEG8_15.SEG9_1K = enabled;
        COM0_SEG8_15.SEG13_1L = enabled;
        COM2_SEG8_15.SEG13_1M = enabled;

        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM3_SEG8_15_buffer[0] = COM3_SEG8_15_REG_ADDR;
        COM3_SEG8_15_buffer[1] = COM3_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        break;
    case 4:
        COM3_SEG8_15.SEG8_1A = disabled;
        COM2_SEG8_15.SEG12_1B = enabled;
        COM1_SEG8_15.SEG9_1C = enabled;
        COM0_SEG8_15.SEG12_1D = disabled;
        COM1_SEG8_15.SEG13_1E = disabled;
        COM3_SEG8_15.SEG13_1F = enabled;
        COM1_SEG8_15.SEG12_1G = enabled;
        COM3_SEG8_15.SEG12_1H = enabled;
        COM3_SEG8_15.SEG9_1I = enabled;
        COM2_SEG8_15.SEG9_1J = enabled;
        COM0_SEG8_15.SEG9_1K = enabled;
        COM0_SEG8_15.SEG13_1L = disabled;
        COM2_SEG8_15.SEG13_1M = enabled;

        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM3_SEG8_15_buffer[0] = COM3_SEG8_15_REG_ADDR;
        COM3_SEG8_15_buffer[1] = COM3_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        break;
    case 5:
        COM3_SEG8_15.SEG8_1A = enabled;
        COM2_SEG8_15.SEG12_1B = disabled;
        COM1_SEG8_15.SEG9_1C = enabled;
        COM0_SEG8_15.SEG12_1D = enabled;
        COM1_SEG8_15.SEG13_1E = disabled;
        COM3_SEG8_15.SEG13_1F = enabled;
        COM1_SEG8_15.SEG12_1G = enabled;
        COM3_SEG8_15.SEG12_1H = enabled;
        COM3_SEG8_15.SEG9_1I = enabled;
        COM2_SEG8_15.SEG9_1J = enabled;
        COM0_SEG8_15.SEG9_1K = enabled;
        COM0_SEG8_15.SEG13_1L = enabled;
        COM2_SEG8_15.SEG13_1M = enabled;

        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM3_SEG8_15_buffer[0] = COM3_SEG8_15_REG_ADDR;
        COM3_SEG8_15_buffer[1] = COM3_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 6:
        COM3_SEG8_15.SEG8_1A = enabled;
        COM2_SEG8_15.SEG12_1B = disabled;
        COM1_SEG8_15.SEG9_1C = enabled;
        COM0_SEG8_15.SEG12_1D = enabled;
        COM1_SEG8_15.SEG13_1E = enabled;
        COM3_SEG8_15.SEG13_1F = enabled;
        COM1_SEG8_15.SEG12_1G = enabled;
        COM3_SEG8_15.SEG12_1H = enabled;
        COM3_SEG8_15.SEG9_1I = enabled;
        COM2_SEG8_15.SEG9_1J = enabled;
        COM0_SEG8_15.SEG9_1K = enabled;
        COM0_SEG8_15.SEG13_1L = enabled;
        COM2_SEG8_15.SEG13_1M = enabled;

        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM3_SEG8_15_buffer[0] = COM3_SEG8_15_REG_ADDR;
        COM3_SEG8_15_buffer[1] = COM3_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        break;
    case 7:
        COM3_SEG8_15.SEG8_1A = enabled;
        COM2_SEG8_15.SEG12_1B = enabled;
        COM1_SEG8_15.SEG9_1C = enabled;
        COM0_SEG8_15.SEG12_1D = disabled;
        COM1_SEG8_15.SEG13_1E = disabled;
        COM3_SEG8_15.SEG13_1F = disabled;
        COM1_SEG8_15.SEG12_1G = disabled;
        COM3_SEG8_15.SEG12_1H = enabled;
        COM3_SEG8_15.SEG9_1I = enabled;
        COM2_SEG8_15.SEG9_1J = enabled;
        COM0_SEG8_15.SEG9_1K = enabled;
        COM0_SEG8_15.SEG13_1L = disabled;
        COM2_SEG8_15.SEG13_1M = disabled;

        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM3_SEG8_15_buffer[0] = COM3_SEG8_15_REG_ADDR;
        COM3_SEG8_15_buffer[1] = COM3_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        break;
    case 8:
        COM3_SEG8_15.SEG8_1A = enabled;
        COM2_SEG8_15.SEG12_1B = enabled;
        COM1_SEG8_15.SEG9_1C = enabled;
        COM0_SEG8_15.SEG12_1D = enabled;
        COM1_SEG8_15.SEG13_1E = enabled;
        COM3_SEG8_15.SEG13_1F = enabled;
        COM1_SEG8_15.SEG12_1G = enabled;
        COM3_SEG8_15.SEG12_1H = enabled;
        COM3_SEG8_15.SEG9_1I = enabled;
        COM2_SEG8_15.SEG9_1J = enabled;
        COM0_SEG8_15.SEG9_1K = enabled;
        COM0_SEG8_15.SEG13_1L = enabled;
        COM2_SEG8_15.SEG13_1M = enabled;

        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM3_SEG8_15_buffer[0] = COM3_SEG8_15_REG_ADDR;
        COM3_SEG8_15_buffer[1] = COM3_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 9:
        COM3_SEG8_15.SEG8_1A = enabled;
        COM2_SEG8_15.SEG12_1B = enabled;
        COM1_SEG8_15.SEG9_1C = enabled;
        COM0_SEG8_15.SEG12_1D = enabled;
        COM1_SEG8_15.SEG13_1E = disabled;
        COM3_SEG8_15.SEG13_1F = enabled;
        COM1_SEG8_15.SEG12_1G = enabled;
        COM3_SEG8_15.SEG12_1H = enabled;
        COM3_SEG8_15.SEG9_1I = enabled;
        COM2_SEG8_15.SEG9_1J = enabled;
        COM0_SEG8_15.SEG9_1K = enabled;
        COM0_SEG8_15.SEG13_1L = enabled;
        COM2_SEG8_15.SEG13_1M = enabled;

        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM3_SEG8_15_buffer[0] = COM3_SEG8_15_REG_ADDR;
        COM3_SEG8_15_buffer[1] = COM3_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        break;

    default:
        COM3_SEG8_15.SEG8_1A = disabled;
        COM2_SEG8_15.SEG12_1B = disabled;
        COM1_SEG8_15.SEG9_1C = disabled;
        COM0_SEG8_15.SEG12_1D = disabled;
        COM1_SEG8_15.SEG13_1E = disabled;
        COM3_SEG8_15.SEG13_1F = disabled;
        COM1_SEG8_15.SEG12_1G = disabled;
        COM3_SEG8_15.SEG12_1H = disabled;
        COM3_SEG8_15.SEG9_1I = disabled;
        COM2_SEG8_15.SEG9_1J = disabled;
        COM0_SEG8_15.SEG9_1K = disabled;
        COM0_SEG8_15.SEG13_1L = disabled;
        COM2_SEG8_15.SEG13_1M = disabled;

        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();

        COM3_SEG8_15_buffer[0] = COM3_SEG8_15_REG_ADDR;
        COM3_SEG8_15_buffer[1] = COM3_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
    }
}












/*
 *********************************************************************************************************************************************
 *                      update_Digit_2
 *********************************************************************************************************************************************
 */
void LCD_update_Digit_2(uint8_t digit2_value)
{

    I2C_ready2operation();
    uint8_t COM0_SEG0_7_buffer[2];
    uint8_t COM0_SEG8_15_buffer[2];
    uint8_t COM1_SEG0_7_buffer[2];
    uint8_t COM1_SEG8_15_buffer[2];
    uint8_t COM2_SEG0_7_buffer[2];
    uint8_t COM2_SEG8_15_buffer[2];
    uint8_t COM3_SEG0_7_buffer[2];



    switch (digit2_value)
    {
    case 0:
        COM3_SEG0_7.SEG5_2A = enabled;
        COM2_SEG0_7.SEG7_2B = enabled;
        COM1_SEG0_7.SEG6_2C = enabled;
        COM0_SEG0_7.SEG7_2D = enabled;
        COM1_SEG8_15.SEG8_2E = enabled;
        COM3_SEG0_7.SEG7_2F = enabled;
        COM1_SEG0_7.SEG7_2G = disabled;
        COM3_SEG0_7.SEG4_2H = enabled;
        COM3_SEG0_7.SEG6_2I = enabled;
        COM2_SEG0_7.SEG6_2J = enabled;
        COM0_SEG0_7.SEG6_2K = enabled;
        COM0_SEG8_15.SEG8_2L = enabled;
        COM2_SEG8_15.SEG8_2M = enabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 1:
        COM3_SEG0_7.SEG5_2A = disabled;
        COM2_SEG0_7.SEG7_2B = enabled;
        COM1_SEG0_7.SEG6_2C = enabled;
        COM0_SEG0_7.SEG7_2D = disabled;
        COM1_SEG8_15.SEG8_2E = disabled;
        COM3_SEG0_7.SEG7_2F = disabled;
        COM1_SEG0_7.SEG7_2G = disabled;
        COM3_SEG0_7.SEG4_2H = disabled;
        COM3_SEG0_7.SEG6_2I = enabled;
        COM2_SEG0_7.SEG6_2J = enabled;
        COM0_SEG0_7.SEG6_2K = enabled;
        COM0_SEG8_15.SEG8_2L = disabled;
        COM2_SEG8_15.SEG8_2M = disabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 2:
        COM3_SEG0_7.SEG5_2A = enabled;
        COM2_SEG0_7.SEG7_2B = enabled;
        COM1_SEG0_7.SEG6_2C = disabled;
        COM0_SEG0_7.SEG7_2D = enabled;
        COM1_SEG8_15.SEG8_2E = enabled;
        COM3_SEG0_7.SEG7_2F = disabled;
        COM1_SEG0_7.SEG7_2G = enabled;
        COM3_SEG0_7.SEG4_2H = enabled;
        COM3_SEG0_7.SEG6_2I = enabled;
        COM2_SEG0_7.SEG6_2J = enabled;
        COM0_SEG0_7.SEG6_2K = enabled;
        COM0_SEG8_15.SEG8_2L = enabled;
        COM2_SEG8_15.SEG8_2M = enabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 3:
        COM3_SEG0_7.SEG5_2A = enabled;
        COM2_SEG0_7.SEG7_2B = enabled;
        COM1_SEG0_7.SEG6_2C = enabled;
        COM0_SEG0_7.SEG7_2D = enabled;
        COM1_SEG8_15.SEG8_2E = disabled;
        COM3_SEG0_7.SEG7_2F = disabled;
        COM1_SEG0_7.SEG7_2G = enabled;
        COM3_SEG0_7.SEG4_2H = enabled;
        COM3_SEG0_7.SEG6_2I = enabled;
        COM2_SEG0_7.SEG6_2J = enabled;
        COM0_SEG0_7.SEG6_2K = enabled;
        COM0_SEG8_15.SEG8_2L = enabled;
        COM2_SEG8_15.SEG8_2M = enabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 4:
        COM3_SEG0_7.SEG5_2A = disabled;
        COM2_SEG0_7.SEG7_2B = enabled;
        COM1_SEG0_7.SEG6_2C = enabled;
        COM0_SEG0_7.SEG7_2D = disabled;
        COM1_SEG8_15.SEG8_2E = disabled;
        COM3_SEG0_7.SEG7_2F = enabled;
        COM1_SEG0_7.SEG7_2G = enabled;
        COM3_SEG0_7.SEG4_2H = enabled;
        COM3_SEG0_7.SEG6_2I = enabled;
        COM2_SEG0_7.SEG6_2J = enabled;
        COM0_SEG0_7.SEG6_2K = enabled;
        COM0_SEG8_15.SEG8_2L = disabled;
        COM2_SEG8_15.SEG8_2M = enabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 5:
        COM3_SEG0_7.SEG5_2A = enabled;
        COM2_SEG0_7.SEG7_2B = disabled;
        COM1_SEG0_7.SEG6_2C = enabled;
        COM0_SEG0_7.SEG7_2D = enabled;
        COM1_SEG8_15.SEG8_2E = disabled;
        COM3_SEG0_7.SEG7_2F = enabled;
        COM1_SEG0_7.SEG7_2G = enabled;
        COM3_SEG0_7.SEG4_2H = enabled;
        COM3_SEG0_7.SEG6_2I = enabled;
        COM2_SEG0_7.SEG6_2J = enabled;
        COM0_SEG0_7.SEG6_2K = enabled;
        COM0_SEG8_15.SEG8_2L = enabled;
        COM2_SEG8_15.SEG8_2M = enabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 6:
        COM3_SEG0_7.SEG5_2A = enabled;
        COM2_SEG0_7.SEG7_2B = disabled;
        COM1_SEG0_7.SEG6_2C = enabled;
        COM0_SEG0_7.SEG7_2D = enabled;
        COM1_SEG8_15.SEG8_2E = enabled;
        COM3_SEG0_7.SEG7_2F = enabled;
        COM1_SEG0_7.SEG7_2G = enabled;
        COM3_SEG0_7.SEG4_2H = enabled;
        COM3_SEG0_7.SEG6_2I = enabled;
        COM2_SEG0_7.SEG6_2J = enabled;
        COM0_SEG0_7.SEG6_2K = enabled;
        COM0_SEG8_15.SEG8_2L = enabled;
        COM2_SEG8_15.SEG8_2M = enabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 7:
        COM3_SEG0_7.SEG5_2A = enabled;
        COM2_SEG0_7.SEG7_2B = enabled;
        COM1_SEG0_7.SEG6_2C = enabled;
        COM0_SEG0_7.SEG7_2D = disabled;
        COM1_SEG8_15.SEG8_2E = disabled;
        COM3_SEG0_7.SEG7_2F = disabled;
        COM1_SEG0_7.SEG7_2G = disabled;
        COM3_SEG0_7.SEG4_2H = enabled;
        COM3_SEG0_7.SEG6_2I = enabled;
        COM2_SEG0_7.SEG6_2J = enabled;
        COM0_SEG0_7.SEG6_2K = enabled;
        COM0_SEG8_15.SEG8_2L = disabled;
        COM2_SEG8_15.SEG8_2M = disabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 8:
        COM3_SEG0_7.SEG5_2A = enabled;
        COM2_SEG0_7.SEG7_2B = enabled;
        COM1_SEG0_7.SEG6_2C = enabled;
        COM0_SEG0_7.SEG7_2D = enabled;
        COM1_SEG8_15.SEG8_2E = enabled;
        COM3_SEG0_7.SEG7_2F = enabled;
        COM1_SEG0_7.SEG7_2G = enabled;
        COM3_SEG0_7.SEG4_2H = enabled;
        COM3_SEG0_7.SEG6_2I = enabled;
        COM2_SEG0_7.SEG6_2J = enabled;
        COM0_SEG0_7.SEG6_2K = enabled;
        COM0_SEG8_15.SEG8_2L = enabled;
        COM2_SEG8_15.SEG8_2M = enabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 9:
        COM3_SEG0_7.SEG5_2A = enabled;
        COM2_SEG0_7.SEG7_2B = enabled;
        COM1_SEG0_7.SEG6_2C = enabled;
        COM0_SEG0_7.SEG7_2D = enabled;
        COM1_SEG8_15.SEG8_2E = disabled;
        COM3_SEG0_7.SEG7_2F = enabled;
        COM1_SEG0_7.SEG7_2G = enabled;
        COM3_SEG0_7.SEG4_2H = enabled;
        COM3_SEG0_7.SEG6_2I = enabled;
        COM2_SEG0_7.SEG6_2J = enabled;
        COM0_SEG0_7.SEG6_2K = enabled;
        COM0_SEG8_15.SEG8_2L = enabled;
        COM2_SEG8_15.SEG8_2M = enabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;


    default:
        COM3_SEG0_7.SEG5_2A = disabled;
        COM2_SEG0_7.SEG7_2B = disabled;
        COM1_SEG0_7.SEG6_2C = disabled;
        COM0_SEG0_7.SEG7_2D = disabled;
        COM1_SEG8_15.SEG8_2E = disabled;
        COM3_SEG0_7.SEG7_2F = disabled;
        COM1_SEG0_7.SEG7_2G = disabled;
        COM3_SEG0_7.SEG4_2H = disabled;
        COM3_SEG0_7.SEG6_2I = disabled;
        COM2_SEG0_7.SEG6_2J = disabled;
        COM0_SEG0_7.SEG6_2K = disabled;
        COM0_SEG8_15.SEG8_2L = disabled;
        COM2_SEG8_15.SEG8_2M = disabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM0_SEG8_15_buffer[0] = COM0_SEG8_15_REG_ADDR;
        COM0_SEG8_15_buffer[1] = COM0_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG8_15_buffer[0] = COM1_SEG8_15_REG_ADDR;
        COM1_SEG8_15_buffer[1] = COM1_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG8_15_buffer[0] = COM2_SEG8_15_REG_ADDR;
        COM2_SEG8_15_buffer[1] = COM2_SEG8_15.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG8_15_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
    }
}
















/*
 *********************************************************************************************************************************************
 *                      update_Digit_3
 *********************************************************************************************************************************************
 */
void LCD_update_Digit_3(uint8_t digit3_value)
{

    I2C_ready2operation();
    uint8_t COM0_SEG0_7_buffer[2];
    uint8_t COM1_SEG0_7_buffer[2];
    uint8_t COM2_SEG0_7_buffer[2];
    uint8_t COM3_SEG0_7_buffer[2];


    switch (digit3_value)
    {
    case 0:
        COM3_SEG0_7.SEG2_3A = enabled;
        COM2_SEG0_7.SEG3_3B = enabled;
        COM1_SEG0_7.SEG2_3C = enabled;
        COM0_SEG0_7.SEG3_3D = enabled;
        COM1_SEG0_7.SEG5_3E = enabled;
        COM2_SEG0_7.SEG4_3F = enabled;
        COM1_SEG0_7.SEG4_3G = disabled;
        COM3_SEG0_7.SEG3_3H = enabled;
        COM2_SEG0_7.SEG2_3I = enabled;
        COM1_SEG0_7.SEG3_3J = enabled;
        COM0_SEG0_7.SEG2_3K = enabled;
        COM0_SEG0_7.SEG4_3L = enabled;
        COM2_SEG0_7.SEG5_3M = enabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 1:
        COM3_SEG0_7.SEG2_3A = disabled;
        COM2_SEG0_7.SEG3_3B = enabled;
        COM1_SEG0_7.SEG2_3C = enabled;
        COM0_SEG0_7.SEG3_3D = disabled;
        COM1_SEG0_7.SEG5_3E = disabled;
        COM2_SEG0_7.SEG4_3F = disabled;
        COM1_SEG0_7.SEG4_3G = disabled;
        COM3_SEG0_7.SEG3_3H = disabled;
        COM2_SEG0_7.SEG2_3I = enabled;
        COM1_SEG0_7.SEG3_3J = enabled;
        COM0_SEG0_7.SEG2_3K = enabled;
        COM0_SEG0_7.SEG4_3L = disabled;
        COM2_SEG0_7.SEG5_3M = disabled;
        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 2:
        COM3_SEG0_7.SEG2_3A = enabled;
        COM2_SEG0_7.SEG3_3B = enabled;
        COM1_SEG0_7.SEG2_3C = disabled;
        COM0_SEG0_7.SEG3_3D = enabled;
        COM1_SEG0_7.SEG5_3E = enabled;
        COM2_SEG0_7.SEG4_3F = disabled;
        COM1_SEG0_7.SEG4_3G = enabled;
        COM3_SEG0_7.SEG3_3H = enabled;
        COM2_SEG0_7.SEG2_3I = enabled;
        COM1_SEG0_7.SEG3_3J = enabled;
        COM0_SEG0_7.SEG2_3K = enabled;
        COM0_SEG0_7.SEG4_3L = enabled;
        COM2_SEG0_7.SEG5_3M = enabled;
        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 3:
        COM3_SEG0_7.SEG2_3A = enabled;
        COM2_SEG0_7.SEG3_3B = enabled;
        COM1_SEG0_7.SEG2_3C = enabled;
        COM0_SEG0_7.SEG3_3D = enabled;
        COM1_SEG0_7.SEG5_3E = disabled;
        COM2_SEG0_7.SEG4_3F = disabled;
        COM1_SEG0_7.SEG4_3G = enabled;
        COM3_SEG0_7.SEG3_3H = enabled;
        COM2_SEG0_7.SEG2_3I = enabled;
        COM1_SEG0_7.SEG3_3J = enabled;
        COM0_SEG0_7.SEG2_3K = enabled;
        COM0_SEG0_7.SEG4_3L = enabled;
        COM2_SEG0_7.SEG5_3M = enabled;
        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 4:
        COM3_SEG0_7.SEG2_3A = disabled;
        COM2_SEG0_7.SEG3_3B = enabled;
        COM1_SEG0_7.SEG2_3C = enabled;
        COM0_SEG0_7.SEG3_3D = disabled;
        COM1_SEG0_7.SEG5_3E = disabled;
        COM2_SEG0_7.SEG4_3F = enabled;
        COM1_SEG0_7.SEG4_3G = enabled;
        COM3_SEG0_7.SEG3_3H = enabled;
        COM2_SEG0_7.SEG2_3I = enabled;
        COM1_SEG0_7.SEG3_3J = enabled;
        COM0_SEG0_7.SEG2_3K = enabled;
        COM0_SEG0_7.SEG4_3L = disabled;
        COM2_SEG0_7.SEG5_3M = enabled;
        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 5:
        COM3_SEG0_7.SEG2_3A = enabled;
        COM2_SEG0_7.SEG3_3B = disabled;
        COM1_SEG0_7.SEG2_3C = enabled;
        COM0_SEG0_7.SEG3_3D = enabled;
        COM1_SEG0_7.SEG5_3E = disabled;
        COM2_SEG0_7.SEG4_3F = enabled;
        COM1_SEG0_7.SEG4_3G = enabled;
        COM3_SEG0_7.SEG3_3H = enabled;
        COM2_SEG0_7.SEG2_3I = enabled;
        COM1_SEG0_7.SEG3_3J = enabled;
        COM0_SEG0_7.SEG2_3K = enabled;
        COM0_SEG0_7.SEG4_3L = enabled;
        COM2_SEG0_7.SEG5_3M = enabled;
        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 6:
        COM3_SEG0_7.SEG2_3A = enabled;
        COM2_SEG0_7.SEG3_3B = disabled;
        COM1_SEG0_7.SEG2_3C = enabled;
        COM0_SEG0_7.SEG3_3D = enabled;
        COM1_SEG0_7.SEG5_3E = enabled;
        COM2_SEG0_7.SEG4_3F = enabled;
        COM1_SEG0_7.SEG4_3G = enabled;
        COM3_SEG0_7.SEG3_3H = enabled;
        COM2_SEG0_7.SEG2_3I = enabled;
        COM1_SEG0_7.SEG3_3J = enabled;
        COM0_SEG0_7.SEG2_3K = enabled;
        COM0_SEG0_7.SEG4_3L = enabled;
        COM2_SEG0_7.SEG5_3M = enabled;
        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 7:
        COM3_SEG0_7.SEG2_3A = enabled;
        COM2_SEG0_7.SEG3_3B = enabled;
        COM1_SEG0_7.SEG2_3C = enabled;
        COM0_SEG0_7.SEG3_3D = disabled;
        COM1_SEG0_7.SEG5_3E = disabled;
        COM2_SEG0_7.SEG4_3F = disabled;
        COM1_SEG0_7.SEG4_3G = disabled;
        COM3_SEG0_7.SEG3_3H = enabled;
        COM2_SEG0_7.SEG2_3I = enabled;
        COM1_SEG0_7.SEG3_3J = enabled;
        COM0_SEG0_7.SEG2_3K = enabled;
        COM0_SEG0_7.SEG4_3L = disabled;
        COM2_SEG0_7.SEG5_3M = disabled;
        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 8:
        COM3_SEG0_7.SEG2_3A = enabled;
        COM2_SEG0_7.SEG3_3B = enabled;
        COM1_SEG0_7.SEG2_3C = enabled;
        COM0_SEG0_7.SEG3_3D = enabled;
        COM1_SEG0_7.SEG5_3E = enabled;
        COM2_SEG0_7.SEG4_3F = enabled;
        COM1_SEG0_7.SEG4_3G = enabled;
        COM3_SEG0_7.SEG3_3H = enabled;
        COM2_SEG0_7.SEG2_3I = enabled;
        COM1_SEG0_7.SEG3_3J = enabled;
        COM0_SEG0_7.SEG2_3K = enabled;
        COM0_SEG0_7.SEG4_3L = enabled;
        COM2_SEG0_7.SEG5_3M = enabled;
        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 9:
        COM3_SEG0_7.SEG2_3A = enabled;
        COM2_SEG0_7.SEG3_3B = enabled;
        COM1_SEG0_7.SEG2_3C = enabled;
        COM0_SEG0_7.SEG3_3D = enabled;
        COM1_SEG0_7.SEG5_3E = disabled;
        COM2_SEG0_7.SEG4_3F = enabled;
        COM1_SEG0_7.SEG4_3G = enabled;
        COM3_SEG0_7.SEG3_3H = enabled;
        COM2_SEG0_7.SEG2_3I = enabled;
        COM1_SEG0_7.SEG3_3J = enabled;
        COM0_SEG0_7.SEG2_3K = enabled;
        COM0_SEG0_7.SEG4_3L = enabled;
        COM2_SEG0_7.SEG5_3M = enabled;
        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;

    default:
        COM3_SEG0_7.SEG2_3A = disabled;
        COM2_SEG0_7.SEG3_3B = disabled;
        COM1_SEG0_7.SEG2_3C = disabled;
        COM0_SEG0_7.SEG3_3D = disabled;
        COM1_SEG0_7.SEG5_3E = disabled;
        COM2_SEG0_7.SEG4_3F = disabled;
        COM1_SEG0_7.SEG4_3G = disabled;
        COM3_SEG0_7.SEG3_3H = disabled;
        COM2_SEG0_7.SEG2_3I = disabled;
        COM1_SEG0_7.SEG3_3J = disabled;
        COM0_SEG0_7.SEG2_3K = disabled;
        COM0_SEG0_7.SEG4_3L = disabled;
        COM2_SEG0_7.SEG5_3M = disabled;
        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
    }
}











/*
 *********************************************************************************************************************************************
 *                      update_temperature_segment
 *********************************************************************************************************************************************
 */
void LCD_update_temperature_segment(uint8_t temperature_segment_value)
{
    I2C_ready2operation();

    uint8_t temperature_segment_buffer[2];

    i2cTransaction.slaveAddress = LCD_ADDR;
    i2cTransaction.writeBuf = temperature_segment_buffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    switch (temperature_segment_value)
    {
    case 0:
        COM0_SEG8_15.SEG14_temperature = disabled;
        temperature_segment_buffer[0] = COM0_SEG8_15_REG_ADDR;
        temperature_segment_buffer[1] = COM0_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    case 1:
        COM0_SEG8_15.SEG14_temperature = enabled;
        temperature_segment_buffer[0] = COM0_SEG8_15_REG_ADDR;
        temperature_segment_buffer[1] = COM0_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    }

    I2C_close(i2cHandle);
}




/*
 *********************************************************************************************************************************************
 *                      update_flame_segment
 *********************************************************************************************************************************************
 */
void LCD_update_flame_segment(uint8_t flame_segment_value)
{
    I2C_ready2operation();

    uint8_t flame_segment_buffer[2];

    i2cTransaction.slaveAddress = LCD_ADDR;
    i2cTransaction.writeBuf = flame_segment_buffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    switch (flame_segment_value)
    {
    case 0:
        COM0_SEG8_15.SEG15_flame = disabled;
        flame_segment_buffer[0] = COM0_SEG8_15_REG_ADDR;
        flame_segment_buffer[1] = COM0_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    case 1:
        COM0_SEG8_15.SEG15_flame = enabled;
        flame_segment_buffer[0] = COM0_SEG8_15_REG_ADDR;
        flame_segment_buffer[1] = COM0_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);

        }
        break;
    }
    I2C_close(i2cHandle);
}






/*
 *********************************************************************************************************************************************
 *                      update_wireless_segment
 *********************************************************************************************************************************************
 */
void LCD_update_wireless_segment(uint8_t wireless_segment_value)
{
    I2C_ready2operation();

    uint8_t wireless_segment_buffer[2];

    i2cTransaction.slaveAddress = LCD_ADDR;
    i2cTransaction.writeBuf = wireless_segment_buffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;
    switch (wireless_segment_value)
    {
    case 0:
        COM1_SEG8_15.SEG15_wireless = disabled;
        wireless_segment_buffer[0] = COM1_SEG8_15_REG_ADDR;
        wireless_segment_buffer[1] = COM1_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    case 1:
        COM1_SEG8_15.SEG15_wireless = enabled;
        wireless_segment_buffer[0] = COM1_SEG8_15_REG_ADDR;
        wireless_segment_buffer[1] = COM1_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    }
    I2C_close(i2cHandle);
}







/*
 *********************************************************************************************************************************************
 *                      update_battery_segment
 *********************************************************************************************************************************************
 */
void LCD_update_battery_segment(uint8_t battery_segment_value)
{
    I2C_ready2operation();

    uint8_t battery_segment_buffer[2];

    i2cTransaction.slaveAddress = LCD_ADDR;
    i2cTransaction.writeBuf = battery_segment_buffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;
    switch (battery_segment_value)
    {
    case 0:
        COM2_SEG8_15.SEG15_battery = disabled;
        battery_segment_buffer[0] = COM2_SEG8_15_REG_ADDR;
        battery_segment_buffer[1] = COM2_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    case 1:
        COM2_SEG8_15.SEG15_battery = enabled;
        battery_segment_buffer[0] = COM2_SEG8_15_REG_ADDR;
        battery_segment_buffer[1] = COM2_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    }
    I2C_close(i2cHandle);
}




/*
 *********************************************************************************************************************************************
 *                      update_humidity_segment
 *********************************************************************************************************************************************
 */
void LCD_update_humidity_segment(uint8_t humidity_segment_value)
{
    I2C_ready2operation();

    uint8_t humidity_segment_buffer[2];

    i2cTransaction.slaveAddress = LCD_ADDR;
    i2cTransaction.writeBuf = humidity_segment_buffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;
    switch (humidity_segment_value)
    {
    case 0:
        COM1_SEG8_15.SEG14_humidity = disabled;
        humidity_segment_buffer[0] = COM1_SEG8_15_REG_ADDR;
        humidity_segment_buffer[1] = COM1_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    case 1:
        COM1_SEG8_15.SEG14_humidity = enabled;
        humidity_segment_buffer[0] = COM1_SEG8_15_REG_ADDR;
        humidity_segment_buffer[1] = COM1_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    }
    I2C_close(i2cHandle);
}



/*
 *********************************************************************************************************************************************
 *                      update_homeAway_segment
 *********************************************************************************************************************************************
 */
void LCD_update_homeAway_segment(uint8_t homeAway_segment_value)
{
    I2C_ready2operation();

    uint8_t homeAway_segment_buffer[2];

    i2cTransaction.slaveAddress = LCD_ADDR;
    i2cTransaction.writeBuf = homeAway_segment_buffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;
    switch (homeAway_segment_value)
    {
    case 0:
        COM2_SEG8_15.SEG14_homeAway = disabled;
        homeAway_segment_buffer[0] = COM2_SEG8_15_REG_ADDR;
        homeAway_segment_buffer[1] = COM2_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    case 1:
        COM2_SEG8_15.SEG14_homeAway = enabled;
        homeAway_segment_buffer[0] = COM2_SEG8_15_REG_ADDR;
        homeAway_segment_buffer[1] = COM2_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    }
    I2C_close(i2cHandle);
}




/*
 *********************************************************************************************************************************************
 *                      update_antiFreeze_segment
 *********************************************************************************************************************************************
 */
void LCD_update_antiFreeze_segment(uint8_t antiFreeze_segment_value)
{
    I2C_ready2operation();

    uint8_t antiFreeze_segment_buffer[2];

    i2cTransaction.slaveAddress = LCD_ADDR;
    i2cTransaction.writeBuf = antiFreeze_segment_buffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;
    switch (antiFreeze_segment_value)
    {
    case 0:
        COM3_SEG8_15.SEG14_antiFreeze = disabled;
        antiFreeze_segment_buffer[0] = COM3_SEG8_15_REG_ADDR;
        antiFreeze_segment_buffer[1] = COM3_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    case 1:
        COM3_SEG8_15.SEG14_antiFreeze = enabled;
        antiFreeze_segment_buffer[0] = COM3_SEG8_15_REG_ADDR;
        antiFreeze_segment_buffer[1] = COM3_SEG8_15.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    }
    I2C_close(i2cHandle);
}











/*
 *********************************************************************************************************************************************
 *                      update_modulation_segment
 *********************************************************************************************************************************************
 */
void LCD_update_modulation_segment(uint8_t modulation_segment_value)
{
    I2C_ready2operation();
    uint8_t COM0_SEG0_7_buffer[2];
    uint8_t COM1_SEG0_7_buffer[2];
    uint8_t COM2_SEG0_7_buffer[2];
    uint8_t COM3_SEG0_7_buffer[2];


    switch (modulation_segment_value)
    {
    case 0:
        COM3_SEG0_7.SEG1_S8 = disabled;
        COM2_SEG0_7.SEG1_S9 = disabled;
        COM1_SEG0_7.SEG1_S10 = disabled;
        COM0_SEG0_7.SEG1_S11 = disabled;
        COM0_SEG0_7.SEG0_S12 = disabled;
        COM1_SEG0_7.SEG0_S13 = disabled;
        COM2_SEG0_7.SEG0_S14 = disabled;
        COM3_SEG0_7.SEG0_S15 = disabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 1:
        COM3_SEG0_7.SEG1_S8 = disabled;
        COM2_SEG0_7.SEG1_S9 = disabled;
        COM1_SEG0_7.SEG1_S10 = disabled;
        COM0_SEG0_7.SEG1_S11 = enabled;
        COM0_SEG0_7.SEG0_S12 = enabled;
        COM1_SEG0_7.SEG0_S13 = disabled;
        COM2_SEG0_7.SEG0_S14 = disabled;
        COM3_SEG0_7.SEG0_S15 = disabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 2:
        COM3_SEG0_7.SEG1_S8 = disabled;
        COM2_SEG0_7.SEG1_S9 = disabled;
        COM1_SEG0_7.SEG1_S10 = enabled;
        COM0_SEG0_7.SEG1_S11 = enabled;
        COM0_SEG0_7.SEG0_S12 = enabled;
        COM1_SEG0_7.SEG0_S13 = enabled;
        COM2_SEG0_7.SEG0_S14 = disabled;
        COM3_SEG0_7.SEG0_S15 = disabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 3:
        COM3_SEG0_7.SEG1_S8 = disabled;
        COM2_SEG0_7.SEG1_S9 = enabled;
        COM1_SEG0_7.SEG1_S10 = enabled;
        COM0_SEG0_7.SEG1_S11 = enabled;
        COM0_SEG0_7.SEG0_S12 = enabled;
        COM1_SEG0_7.SEG0_S13 = enabled;
        COM2_SEG0_7.SEG0_S14 = enabled;
        COM3_SEG0_7.SEG0_S15 = disabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;
    case 4:
        COM3_SEG0_7.SEG1_S8 = enabled;
        COM2_SEG0_7.SEG1_S9 = enabled;
        COM1_SEG0_7.SEG1_S10 = enabled;
        COM0_SEG0_7.SEG1_S11 = enabled;
        COM0_SEG0_7.SEG0_S12 = enabled;
        COM1_SEG0_7.SEG0_S13 = enabled;
        COM2_SEG0_7.SEG0_S14 = enabled;
        COM3_SEG0_7.SEG0_S15 = enabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);
        break;

    default:
        COM3_SEG0_7.SEG1_S8 = disabled;
        COM2_SEG0_7.SEG1_S9 = disabled;
        COM1_SEG0_7.SEG1_S10 = disabled;
        COM0_SEG0_7.SEG1_S11 = disabled;
        COM0_SEG0_7.SEG0_S12 = disabled;
        COM1_SEG0_7.SEG0_S13 = disabled;
        COM2_SEG0_7.SEG0_S14 = disabled;
        COM3_SEG0_7.SEG0_S15 = disabled;

        COM0_SEG0_7_buffer[0] = COM0_SEG0_7_REG_ADDR;
        COM0_SEG0_7_buffer[1] = COM0_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM0_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM1_SEG0_7_buffer[0] = COM1_SEG0_7_REG_ADDR;
        COM1_SEG0_7_buffer[1] = COM1_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM1_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM2_SEG0_7_buffer[0] = COM2_SEG0_7_REG_ADDR;
        COM2_SEG0_7_buffer[1] = COM2_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM2_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);

        I2C_ready2operation();
        COM3_SEG0_7_buffer[0] = COM3_SEG0_7_REG_ADDR;
        COM3_SEG0_7_buffer[1] = COM3_SEG0_7.value;

        i2cTransaction.slaveAddress = LCD_ADDR;
        i2cTransaction.writeBuf = COM3_SEG0_7_buffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        I2C_close(i2cHandle);


    }
}






/*
 *********************************************************************************************************************************************
 *                      update_floatingDot_segment
 *********************************************************************************************************************************************
 */
void LCD_update_floatingDot_segment(uint8_t floatingDot_segment_value)
{

    I2C_ready2operation();

    uint8_t floatingDot_segment_buffer[2];

    i2cTransaction.slaveAddress = LCD_ADDR;
    i2cTransaction.writeBuf = floatingDot_segment_buffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;
    switch (floatingDot_segment_value)
    {
    case 0:
        COM0_SEG0_7.SEG5_floatingDot = disabled;
        floatingDot_segment_buffer[0] = COM0_SEG0_7_REG_ADDR;
        floatingDot_segment_buffer[1] = COM0_SEG0_7.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    case 1:
        COM0_SEG0_7.SEG5_floatingDot = enabled;
        floatingDot_segment_buffer[0] = COM0_SEG0_7_REG_ADDR;
        floatingDot_segment_buffer[1] = COM0_SEG0_7.value;
        if (!I2C_transfer(i2cHandle, &i2cTransaction))
        {
            // Error. No i2c device found!
            while(1);
        }
        break;
    }
    I2C_close(i2cHandle);
}



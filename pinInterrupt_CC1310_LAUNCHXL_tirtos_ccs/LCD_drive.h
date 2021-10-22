/*
 * LCD_drive.h
 *
 *  Created on: 15 Eyl 2021
 *      Author: ebaglama
 */

#ifndef LCD_DRIVE_H_
#define LCD_DRIVE_H_

#include <stdint.h>
#include <ti/drivers/I2C.h>


/*
 *************************************************************************
 *                      PCA8561 Register Addresses
 *************************************************************************
 */
#define LCD_ADDR                       0x38
#define SW_RESET_REG_ADDR              0x00
#define DEVICE_CTRL_REG_ADDR           0x01
#define DEVICE_CTRL1_REG_ADDR          0x02
#define DEVICE_CTRL2_REG_ADDR          0x03
#define COM0_SEG0_7_REG_ADDR           0x04
#define COM0_SEG8_15_REG_ADDR          0x05
#define COM0_SEG16_17_REG_ADDR         0x06
#define COM1_SEG0_7_REG_ADDR           0x07
#define COM1_SEG8_15_REG_ADDR          0x08
#define COM1_SEG16_17_REG_ADDR         0x09
#define COM2_SEG0_7_REG_ADDR           0x0A
#define COM2_SEG8_15_REG_ADDR          0x0B
#define COM2_SEG16_17_REG_ADDR         0x0C
#define COM3_SEG0_7_REG_ADDR           0x0D
#define COM3_SEG8_15_REG_ADDR          0x0E
#define COM3_SEG16_17_REG_ADDR         0x0F

/*
 *************************************************************************
 *                      PCA8561 Register Static Values
 *************************************************************************
 */
#define SW_RESET                       0x2C
#define NO_RESET                       0x00


/*
 *************************************************************************
 *                      LCD_drive.c Functions
 *************************************************************************
 */

/*!
 *  @brief  SW Reset before every energy-up.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @swRESET_buffer[0] is address of PCA8561 IC's Software_reset register.
 *
 *  @swRESET_buffer[1] is value of PCA8561 IC's Software_reset register.
 *                        0x2C: sw Reset, 0x00: No Reset
 *
 */
extern void LCD_software_reset(void);

/*!
 *  @brief  SW Reset release for after every SW Reset.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @swRESET_buffer[0] is address of PCA8561 IC's Software_reset register.
 *
 *  @swRESET_buffer[1] is value of PCA8561 IC's Software_reset register.
 *                        0x2C: SW Reset, 0x00: No Reset
 *
 */
extern void LCD_software_reset_release(void);

/*!
 *  @brief  Set Device_ctrl, Display_ctrl_1, Display_ctrl_2 registers of PCA8561's.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @CTRL_buffer[0] is address of PCA8561 IC's Device_ctrl register.
 *
 *  @CTRL_buffer[1] is value of PCA8561 IC's Device_ctrl register.
 *
 *  @CTRL_buffer[2] is value of PCA8561 IC's Device_ctrl_1 register.*
 *
 *  @CTRL_buffer[3] is value of PCA8561 IC's Device_ctrl_2 register.
 *
 */
extern void LCD_set_ctrl_registers(void);

/*!
 *  @brief  Control temperature segment on LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 */
extern void LCD_update_temperature_segment(uint8_t);

/*!
 *  @brief  Control flame segment on LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @input enabled(ON) to disabled(OFF)
 *
 */
extern void LCD_update_flame_segment(uint8_t);

/*!
 *  @brief  Control wireless segment on LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @input enabled(ON) to disabled(OFF)
 *
 */
extern void LCD_update_wireless_segment(uint8_t);

/*!
 *  @brief  Control battery segment on LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @input enabled(ON) to disabled(OFF)
 *
 */
extern void LCD_update_battery_segment(uint8_t);

/*!
 *  @brief  Control humidity segment on LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @input enabled(ON) to disabled(OFF)
 *
 */
extern void LCD_update_humidity_segment(uint8_t);

/*!
 *  @brief  Control home away segment on LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @input enabled(ON) to disabled(OFF)
 *
 */
extern void LCD_update_homeAway_segment(uint8_t);

/*!
 *  @brief  Control anti freeze segment on LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @input enabled(ON) to disabled(OFF)
 *
 */
extern void LCD_update_antiFreeze_segment(uint8_t);

/*!
 *  @brief  Control modulation segments on LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @input 0(min) to 4(max)
 *
 */
extern void LCD_update_modulation_segment(uint8_t);

/*!
 *  @brief  Control floating dot segments on LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @input enabled(ON) to disabled(OFF)
 *
 */
extern void LCD_update_floatingDot_segment(uint8_t);

/*!
 *  @brief  Control first digit segments on LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @input Numbers: 0 - 9
 *         Letters: 'a' - 'z'
 *
 */
extern void LCD_update_Digit_1(uint8_t);

/*!
 *  @brief  Control second digit segments on LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @input Numbers: 0 - 9
 *         Letters: 'a' - 'z'
 *
 */
extern void LCD_update_Digit_2(uint8_t);

/*!
 *  @brief  Control third(floating) digit segments on LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 *  @input Numbers: 0 - 9
 *         Letters: 'a' - 'z'
 *
 */
extern void LCD_update_Digit_3(uint8_t);

/*!
 *  @brief  Init and set I2C settings used for decrease total lines in LCD_drive.c.
 *
 *  @pre    I2C_init() has been called.
 *
 *
 */
extern void LCD_I2C_ready2send(uint8_t);

/*!
 *  @brief  print 3 digit and floating point on the LCD.
 *
 *  @pre    I2C_init() has been called.
 *
 *
 */
extern void LCD_print(double);



/*
 *************************************************************************
 *                      Bit Fields of PCA8561 Registers
 *************************************************************************
 */

/*!
 *  @brief  bit fields of device_ctrl register of PCA8561's.
 *
 *  @struct variables are used for setting up the register value.
 *
 *  @CTRL_value is used to assign 1 byte data in CTRL_buffer[1].
 */
union
{
    struct
    {
        volatile uint8_t  COE:1;
        volatile uint8_t  OSC:1;
        volatile uint8_t  FrameFreq:3;
        volatile uint8_t  :3;
    };
    uint8_t CTRL_value;
}CTRL;


/*!
 *  @brief  bit fields of device_ctrl_1 register of PCA8561's.
 *
 *  @struct variables are used for setting up the register value.
 *
 *  @CTRL1_value is used to assign 1 byte data in CTRL_buffer[2].
 */
union
{
    struct
    {
        volatile uint8_t  Display_enable:1;
        volatile uint8_t  Bias:1;
        volatile uint8_t  MUX:2;
        volatile uint8_t  Boost:1;
        volatile uint8_t  RESERVED:3;
    };
    uint8_t CTRL1_value;
}CTRL_1;


/*!
 *  @brief  bit fields of device_ctrl_2 register of PCA8561's.
 *
 *  @struct variables are used for setting up the register value.
 *
 *  @CTRL2_value is used to assign 1 byte data in CTRL_buffer[2].
 */
union
{
    struct
    {
        volatile uint8_t  INV:1;
        volatile uint8_t  BlinkControl:2;
        volatile uint8_t  RESERVED:5;
    };
    uint8_t CTRL2_value;
}CTRL_2;

/*!
 *  @brief  bit fields of COM0 SEG0-7 register of PCA8561's.
 *
 *  @struct variables are used for setting up the register value.
 *
 *  @value is used to assign 1 byte data in i2c send buffer.
 */
union
{
    struct
    {
        uint8_t SEG0_S12:1;
        uint8_t SEG1_S11:1;
        uint8_t SEG2_3K:1;
        uint8_t SEG3_3D:1;
        uint8_t SEG4_3L:1;
        uint8_t SEG5_floatingDot:1;
        uint8_t SEG6_2K:1;
        uint8_t SEG7_2D:1;
    };
    uint8_t value;
}COM0_SEG0_7;

/*!
 *  @brief  bit fields of COM0 SEG8-15 register of PCA8561's.
 *
 *  @struct variables are used for setting up the register value.
 *
 *  @value is used to assign 1 byte data in i2c send buffer.
 */
union
{
    struct
    {
        uint8_t SEG8_2L:1;
        uint8_t SEG9_1K:1;
        uint8_t SEG10_empty:1;
        uint8_t SEG11_empty:1;
        uint8_t SEG12_1D:1;
        uint8_t SEG13_1L:1;
        uint8_t SEG14_temperature:1;
        uint8_t SEG15_flame:1;
    };
    uint8_t value;
}COM0_SEG8_15;

/*!
 *  @brief  bit fields of COM1 SEG0-7 register of PCA8561's.
 *
 *  @struct variables are used for setting up the register value.
 *
 *  @value is used to assign 1 byte data in i2c send buffer.
 */
union
{
    struct
    {
        uint8_t SEG0_S13:1;
        uint8_t SEG1_S10:1;
        uint8_t SEG2_3C:1;
        uint8_t SEG3_3J:1;
        uint8_t SEG4_3G:1;
        uint8_t SEG5_3E:1;
        uint8_t SEG6_2C:1;
        uint8_t SEG7_2G:1;
    };
    uint8_t value;
}COM1_SEG0_7;

/*!
 *  @brief  bit fields of COM1 SEG8-15 register of PCA8561's.
 *
 *  @struct variables are used for setting up the register value.
 *
 *  @value is used to assign 1 byte data in i2c send buffer.
 */
union
{
    struct
    {
        uint8_t SEG8_2E:1;
        uint8_t SEG9_1C:1;
        uint8_t SEG10_empty:1;
        uint8_t SEG11_empty:1;
        uint8_t SEG12_1G:1;
        uint8_t SEG13_1E:1;
        uint8_t SEG14_humidity:1;
        uint8_t SEG15_wireless:1;
    };
    uint8_t value;
}COM1_SEG8_15;

/*!
 *  @brief  bit fields of COM2 SEG0-7 register of PCA8561's.
 *
 *  @struct variables are used for setting up the register value.
 *
 *  @value is used to assign 1 byte data in i2c send buffer.
 */
union
{
    struct
    {
        uint8_t SEG0_S14:1;
        uint8_t SEG1_S9:1;
        uint8_t SEG2_3I:1;
        uint8_t SEG3_3B:1;
        uint8_t SEG4_3F:1;
        uint8_t SEG5_3M:1;
        uint8_t SEG6_2J:1;
        uint8_t SEG7_2B:1;
    };
    uint8_t value;
}COM2_SEG0_7;

/*!
 *  @brief  bit fields of COM2 SEG8-15 register of PCA8561's.
 *
 *  @struct variables are used for setting up the register value.
 *
 *  @value is used to assign 1 byte data in i2c send buffer.
 */
union
{
    struct
    {
        uint8_t SEG8_2M:1;
        uint8_t SEG9_1J:1;
        uint8_t SEG10_empty:1;
        uint8_t SEG11_empty:1;
        uint8_t SEG12_1B:1;
        uint8_t SEG13_1M:1;
        uint8_t SEG14_homeAway:1;
        uint8_t SEG15_battery:1;
    };
    uint8_t value;
}COM2_SEG8_15;

/*!
 *  @brief  bit fields of COM3 SEG0-7 register of PCA8561's.
 *
 *  @struct variables are used for setting up the register value.
 *
 *  @value is used to assign 1 byte data in i2c send buffer.
 */
union
{
    struct
    {
        uint8_t SEG0_S15:1;
        uint8_t SEG1_S8:1;
        uint8_t SEG2_3A:1;
        uint8_t SEG3_3H:1;
        uint8_t SEG4_2H:1;
        uint8_t SEG5_2A:1;
        uint8_t SEG6_2I:1;
        uint8_t SEG7_2F:1;
    };
    uint8_t value;
}COM3_SEG0_7;

/*!
 *  @brief  bit fields of COM3 SEG8-15 register of PCA8561's.
 *
 *  @struct variables are used for setting up the register value.
 *
 *  @value is used to assign 1 byte data in i2c send buffer.
 */
union
{
    struct
    {
        uint8_t SEG8_1A:1;
        uint8_t SEG9_1I:1;
        uint8_t SEG10_empty:1;
        uint8_t SEG11_empty:1;
        uint8_t SEG12_1H:1;
        uint8_t SEG13_1F:1;
        uint8_t SEG14_antiFreeze:1;
        uint8_t SEG15_celcius:1;
    };
    uint8_t value;
}COM3_SEG8_15;


/*!
 *  @brief:  values for setting LCD frame frequency.
 *                  sets bits 4 to 2 of device_ctrl register
 */
typedef enum
{
    _32Hz,          //Default value
    _64Hz,
    _96Hz,
    _128Hz,
    _160Hz,
    _192Hz,
    _224Hz,
    _256Hz
}frameFreq;


/*!
 *  @brief:  values for setting LCD blinking control.
 *                  sets bits 2 to 1 of device_ctrl_2 register
 */
typedef enum
{
    blinkOFF,       //Default value
    blink0_5Hz,
    blink1Hz,
    blink2Hz
}blinkControl;


/*!
 *  @brief:  values for setting inversion mode selection.
 *                  sets bits 2 to 1 of device_ctrl_2 register
 */
typedef enum
{
    lineInversion,  //Default value
    frameInversion
}inversionMode;



typedef enum
{
    disabled,  //Default value
    enabled
}runMode;

/*!
 *  @brief:  values for setting bias mode selection.
 *                  sets bit 1 of device_ctrl_1 register
 */
typedef enum
{
    _1_3bias,  //Default value
    _1_2bias
}biasMode;

/*!
 *  @brief:  values for setting multiplex drive mode selection.
 *                  sets bits 3 to 2 of device_ctrl_1 register
 */
typedef enum
{
    _1_4mux,  //Default value
    _1_3mux,
    _1_2mux,
    static_drive_mode
}muxDriveMode;



#endif /* LCD_DRIVE_H_ */

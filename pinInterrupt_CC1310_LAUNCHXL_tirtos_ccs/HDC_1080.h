/*
 * HDC_1080.h
 *
 *  Created on: 13 Eyl 2021
 *      Author: ebaglama
 */

#ifndef HDC_1080_H_
#define HDC_1080_H_


#include <stdint.h>

#define HDC_I2C_ADDRESS                0x40;
#define HDC_TEMP_REG_ADDRESS           0x00;
#define HDC_HUMID_REG_ADDRESS          0x01;
#define HDC_CONFIG_REG_ADDRESS         0x02;
#define HDC_TEMP_MEASUREMENT_TRIGGER   0x00;
#define HDC_HUMID_MEASUREMENT_TRIGGER  0x01;


extern double HDC1080_getTemperature(void);
extern double HDC1080_getHumidity(void);


double HDC1080_rawData;
double temperatureVal;
double humidityVal;




union
{
    struct
    {
        uint16_t reserved:2;        //always 0  (read only)
        uint16_t temperature:14;    //temperature measurement (read only)
    };
    uint16_t value;
}temperature_reg;


union
{
    struct
    {
        uint16_t reserved:2;        //always 0  (read only)
        uint16_t humidity:14;       //Relative Humidity measurement (read only)
    };
    uint16_t value;
}humidity_reg;





union
{
    struct
    {
        uint16_t reserved:8;                                // must be 0
        uint16_t humidity_measurement_resolution:2;         // 00:14 bit, 01:11 bit, 10: 8 bit
        uint16_t temperature_measurement_resolution:1;      // 0:14 bit, 1:11 bit
        uint16_t battery_status:1;                          // 0:battery voltage>2.8V, 1:battery voltage<2.8V   (read only)
        uint16_t acquisition_mode:1;                        // 0:Temperature or Humidity is acquired. 1:Temperature and Humidity are acquired in sequence, Temperature first.
        uint16_t heater:1;                                  // 0: disabled, 1: enabled
        uint16_t reserved2:1;                                // must be 0
        uint16_t SW_reset:1;                                // 0:Normal Operation, this bit self clears. 1:Software reset
    };
    uint16_t value;
}HDC1080_config_reg;





typedef enum
{
    normal_operation,
    SW_reset
}HDC1080_SW_reset;




typedef enum
{
    temperatureORhumidity,          //Default value
    temperatureANDhumidity
}acquisition_mode;


typedef enum
{
    higher2_8V,          //Default value
    lower2_8V
}battery_status;


typedef enum
{
    _14bit,          //Default value
    _11bit,
    _8bit
}resolution;



#endif /* HDC_1080_H_ */

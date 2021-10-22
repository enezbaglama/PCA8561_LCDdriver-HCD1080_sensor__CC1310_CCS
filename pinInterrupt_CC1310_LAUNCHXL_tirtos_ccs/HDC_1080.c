/*
 * HDC_1080.c
 *
 *  Created on: 15 Eyl 2021
 *      Author: ebaglama
 */


#include<HDC_1080.h>
#include <ti/drivers/I2C.h>
#include "Board.h"
#include <unistd.h>



I2C_Handle      hdc1080_i2cHandle;
I2C_Params      hdc1080_i2cParams;
I2C_Transaction hdc1080_i2cTransaction;

uint8_t TMP_transmition_buffer[3];
uint8_t TMP_receiving_buffer[2];



double HDC1080_getTemperature(void)
{
    I2C_init();

    I2C_Params_init(&hdc1080_i2cParams);
    hdc1080_i2cParams.bitRate = I2C_400kHz;
    hdc1080_i2cHandle = I2C_open(Board_I2C0, &hdc1080_i2cParams);
    if (hdc1080_i2cHandle == NULL)
    {
        //Error Initializing I2C
        while (1);
    }

    HDC1080_config_reg.acquisition_mode = temperatureORhumidity;
    HDC1080_config_reg.temperature_measurement_resolution = _14bit;
    HDC1080_config_reg.humidity_measurement_resolution = _14bit;

    TMP_transmition_buffer[0] = HDC_CONFIG_REG_ADDRESS;
    TMP_transmition_buffer[1] = HDC1080_config_reg.value >> 8; // first 8bit of Configuration Register
    TMP_transmition_buffer[2] = (HDC1080_config_reg.value & 0x00FF); // last 8bit of Configuration Register

    hdc1080_i2cTransaction.slaveAddress = HDC_I2C_ADDRESS;
    hdc1080_i2cTransaction.writeBuf = TMP_transmition_buffer;
    hdc1080_i2cTransaction.writeCount = 3;
    hdc1080_i2cTransaction.readBuf = NULL;
    hdc1080_i2cTransaction.readCount = 0;

    if (!I2C_transfer(hdc1080_i2cHandle, &hdc1080_i2cTransaction))
    {
        // Error. No i2c device found!
        while(1);
    }

    TMP_transmition_buffer[0] = HDC_TEMP_MEASUREMENT_TRIGGER;
    hdc1080_i2cTransaction.slaveAddress = HDC_I2C_ADDRESS;
    hdc1080_i2cTransaction.writeBuf = TMP_transmition_buffer;
    hdc1080_i2cTransaction.writeCount = 1;
    hdc1080_i2cTransaction.readBuf = NULL;
    hdc1080_i2cTransaction.readCount = 0;
    if (!I2C_transfer(hdc1080_i2cHandle, &hdc1080_i2cTransaction))
    {
        // Error. No i2c device found!
        while(1);
    }
    usleep(150000);
    hdc1080_i2cTransaction.slaveAddress = HDC_I2C_ADDRESS;
    hdc1080_i2cTransaction.writeBuf = NULL;
    hdc1080_i2cTransaction.writeCount = 0;
    hdc1080_i2cTransaction.readBuf = TMP_receiving_buffer;
    hdc1080_i2cTransaction.readCount = 2;
    if (!I2C_transfer(hdc1080_i2cHandle, &hdc1080_i2cTransaction))
    {
        // Error. No i2c device found!
        while(1);
    }
    I2C_close(hdc1080_i2cHandle);

    HDC1080_rawData = (TMP_receiving_buffer[0] << 8) | (TMP_receiving_buffer[1]);
    temperatureVal = (((HDC1080_rawData / 0x10000) * 165)) - 40;

    return temperatureVal;
}



double HDC1080_getHumidity(void)
{
    I2C_init();

    I2C_Params_init(&hdc1080_i2cParams);
    hdc1080_i2cParams.bitRate = I2C_400kHz;
    hdc1080_i2cHandle = I2C_open(Board_I2C0, &hdc1080_i2cParams);
    if (hdc1080_i2cHandle == NULL)
    {
        //Error Initializing I2C
        while (1);
    }

    HDC1080_config_reg.acquisition_mode = temperatureORhumidity;
    HDC1080_config_reg.temperature_measurement_resolution = _14bit;
    HDC1080_config_reg.humidity_measurement_resolution = _14bit;

    TMP_transmition_buffer[0] = HDC_CONFIG_REG_ADDRESS;
    TMP_transmition_buffer[1] = HDC1080_config_reg.value >> 8; // first 8bit of Configuration Register
    TMP_transmition_buffer[2] = (HDC1080_config_reg.value & 0x00FF); // last 8bit of Configuration Register

    hdc1080_i2cTransaction.slaveAddress = HDC_I2C_ADDRESS;
    hdc1080_i2cTransaction.writeBuf = TMP_transmition_buffer;
    hdc1080_i2cTransaction.writeCount = 3;
    hdc1080_i2cTransaction.readBuf = NULL;
    hdc1080_i2cTransaction.readCount = 0;

    if (!I2C_transfer(hdc1080_i2cHandle, &hdc1080_i2cTransaction))
    {
        // Error. No i2c device found!
        while(1);
    }

    TMP_transmition_buffer[0] = HDC_HUMID_MEASUREMENT_TRIGGER;
    hdc1080_i2cTransaction.slaveAddress = HDC_I2C_ADDRESS;
    hdc1080_i2cTransaction.writeBuf = TMP_transmition_buffer;
    hdc1080_i2cTransaction.writeCount = 1;
    hdc1080_i2cTransaction.readBuf = NULL;
    hdc1080_i2cTransaction.readCount = 0;
    if (!I2C_transfer(hdc1080_i2cHandle, &hdc1080_i2cTransaction))
    {
        // Error. No i2c device found!
        while(1);
    }
    usleep(150000);
    hdc1080_i2cTransaction.slaveAddress = HDC_I2C_ADDRESS;
    hdc1080_i2cTransaction.writeBuf = NULL;
    hdc1080_i2cTransaction.writeCount = 0;
    hdc1080_i2cTransaction.readBuf = TMP_receiving_buffer;
    hdc1080_i2cTransaction.readCount = 2;
    if (!I2C_transfer(hdc1080_i2cHandle, &hdc1080_i2cTransaction))
    {
        // Error. No i2c device found!
        while(1);
    }
    I2C_close(hdc1080_i2cHandle);

    HDC1080_rawData = (TMP_receiving_buffer[0] << 8) | (TMP_receiving_buffer[1]);
    humidityVal = ((HDC1080_rawData / 0x10000) * 100);

    return humidityVal;
}






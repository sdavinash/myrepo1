/*
 * accelerometer.c
 *
 *  Created on: 07-Dec-2016
 *      Author: AVINASH
 */


#include "main.h"


/* INITIALIZING I2C FOR ACCELEROMETER */
void Init_I2C_Accel(void)
{
	I2C_Init_Accel(I2C0_B); /*INITIALIZE PORT_E I2C*/

}

/* READING CONTENT FROM ACCELEROMETER REGISTERS*/
uint8_t Accel_Read_Reg(uint8_t addr)
{
    uint8_t result;

    I2C_Start(I2C0_B);
    I2C_Write_Byte(I2C0_B, ACCEL_DEVICE_I2C_ADDRESS|I2C_WRITE);

    I2C_Wait(I2C0_B);
    I2C_Get_ACK(I2C0_B);

    I2C_Write_Byte(I2C0_B, addr);
    I2C_Wait(I2C0_B);
    I2C_Get_ACK(I2C0_B);

    I2C_Repeated_Start(I2C0_B);
    I2C_Write_Byte(I2C0_B, ACCEL_DEVICE_I2C_ADDRESS|I2C_READ);
    I2C_Wait(I2C0_B);
    I2C_Get_ACK(I2C0_B);

    I2C_Set_Rx_Mode(I2C0_B);

    I2C_Give_NACK(I2C0_B);
    result = I2C_Read_Byte(I2C0_B);
    I2C_Wait(I2C0_B);

    I2C_Stop(I2C0_B);
    //result = I2C_Read_Byte(I2C0_B);
    pause();
    return result;
}


/* WRITING CONTENT TO ACCELEROMETER REGISTERS*/
void Accel_Write_Reg(uint8_t addr, uint8_t data)
{
	I2C_Start(I2C0_B);

	I2C_Write_Byte(I2C0_B, ACCEL_DEVICE_I2C_ADDRESS|I2C_WRITE);
	I2C_Wait(I2C0_B);
	I2C_Get_ACK(I2C0_B);

	I2C_Write_Byte(I2C0_B, addr);
	I2C_Wait(I2C0_B);
	I2C_Get_ACK(I2C0_B);

	I2C_Write_Byte(I2C0_B, data);
	I2C_Wait(I2C0_B);
	I2C_Get_ACK(I2C0_B);

	I2C_Stop(I2C0_B);
    pause();
}

/* this delay is very important, it may cause w-r operation failure.*/
static void pause(void)
{
    int n;
    for(n=0; n<40; n++){}
       // asm("nop");
}

/*
 * fall_calculation.c
 *
 *  Created on: 07-Dec-2016
 *      Author: AVINASH
 */

#include "main.h"

/*Accelerometer initialization*/
void Accel_init(void){

/*Configure MMA8451 sensor*/
	Init_I2C_Accel();      //Initialize I2C modules
	Accel_Write_Reg(ACCEL_CRTL_REG_1,ACCEL_CRTL_REG_VALUE); 	// Activate the Accelerometer: with LNOISE (4g mode) and ODR = 100 Hz
	Accel_Write_Reg(ACCEL_XYZ_DATA_CFG_REG,ACCEL_XYZ_DATA_CFG);	//Set accelerator to '4 g' mode
	Accel_Write_Reg(ACCEL_CTRL_REG_4,ACCEL_INTR_ENABLE);		//Enable Freefall detection interrupt
	Accel_Write_Reg(ACCEL_CTRL_REG_5,ACCEL_INTR_CONFIG);		//Configure Freefall detection and data-ready interrupts
	Accel_Write_Reg(ACCEL_FF_MT_CFG_REG,ACCEL_FF_MT_CFG);		//Configure Accelerator to detect freefall with latch enable
	Accel_Write_Reg(ACCEL_FF_MT_THS_REG,ACCEL_FF_MT_THS);		//Threshold set to 1g with DBCNTM = 0
	Accel_Write_Reg(ACCEL_FF_MT_CNT_REG,ACCEL_FF_MT_CNT);		//debounce counter set to 0.5 seconds


}



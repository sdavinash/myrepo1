/*
 * fall_calculation.h
 *
 *  Created on: 07-Dec-2016
 *      Author: AVINASH
 */

#include "main.h"

#ifndef INCLUDES_FALL_CALCULATION_H_
#define INCLUDES_FALL_CALCULATION_H_

void Accel_init(void);			/*Accelerometer initialization*/
uint8_t Accel_Data_Read(void);

extern int16_t resultx, resulty, resultz;



#endif /* INCLUDES_FALL_CALCULATION_H_ */

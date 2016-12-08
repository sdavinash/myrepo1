/*
 * I2C.h
 *
 *  Created on: 07-Dec-2016
 *      Author: AVINASH
 */

#ifndef INCLUDES_I2C_H_
#define INCLUDES_I2C_H_

/********************************************************************************
 // INITIALIZE TWO I2C MODULES AT PORT_E FOR TEMPERATURE IC AND ACELEROMETER IC
 ********************************************************************************/
void I2C_Init_Temp(I2C_MemMapPtr p);
void I2C_Init_Accel(I2C_MemMapPtr p);

/***************************************
 	 	SET I2C MODES
 ***************************************/
void I2C_Set_Tx_Mode(I2C_MemMapPtr p);
void I2C_Set_Rx_Mode(I2C_MemMapPtr p);
void I2C_Set_Slave_Mode(I2C_MemMapPtr p);
void I2C_Set_Master_Mode(I2C_MemMapPtr p);

/***************************************
 	 I2C OPERATION FUNCTIONS
 ***************************************/
void I2C_Give_NACK(I2C_MemMapPtr p);
void I2C_Give_ACK(I2C_MemMapPtr p);
void I2C_Repeated_Start(I2C_MemMapPtr p);
void I2C_Write_Byte(I2C_MemMapPtr p, uint8_t data);
uint8_t I2C_Read_Byte(I2C_MemMapPtr p);
void I2C_Start(I2C_MemMapPtr p);
void I2C_Stop(I2C_MemMapPtr p);
void I2C_Wait(I2C_MemMapPtr p);
uint16_t I2C_Get_ACK(I2C_MemMapPtr p);

/**********************************************************************************
 	 DEINITIALIZE BOTH I2C MODULES FOR SENSOR COMMUNICATION WITH MCU
 **********************************************************************************/
void I2C_Deinit_Accel(I2C_MemMapPtr p);
void I2C_Deinit_Temp(I2C_MemMapPtr p);

#define I2C_READ  		1
#define I2C_WRITE 		0

#endif /* INCLUDES_I2C_H_ */

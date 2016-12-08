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
void I2C_Init_Temp(void);
uint8_t I2C_Init_Accel(I2C_MemMapPtr p);
//uint8_t I2C_Init_Accel();

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
#define TRUE 			1
#define FALSE			0

/*******************************************************************************************************************/
/* set the R/W bit for read operation */
#define I2C_READ_ADDRESS(slaveAddress) 		((uint8_t)((slaveAddress << 1) | 1))

/* reset the R/W bit for write operation*/
#define I2C_WRITE_ADDRESS(slaveAddress) 	((uint8_t)((slaveAddress << 1) | 0))


static void I2C_ReadMultipleRegisters(register uint8_t slaveId, register uint8_t startRegisterAddress, register uint8_t registerCount, uint8_t *const buffer);
void I2C_WriteCommand(register uint8_t slaveId, register uint8_t value);
uint8_t I2C_ReadRegister(register uint8_t slaveId, register uint8_t registerAddress);
void I2C_ReadRegisters(register uint8_t slaveId, register uint8_t startRegisterAddress, register uint8_t registerCount, uint8_t *buffer);

/**
 *  Waits for an I2C bus operation to complete
 */
static inline void I2C_Wait_Temp()
{
	while((I2C1->S & I2C_S_IICIF_MASK)==0) {}	/* loop until interrupt is detected */
	I2C1->S |= I2C_S_IICIF_MASK; /* clear interrupt flag */

}

/**
 *  Waits for an I2C bus operation to complete
 */
static inline void I2C_WaitWhileBusy()
{
	while((I2C1->S & I2C_S_BUSY_MASK)!=0) {}
}


/**
 *  Sends a start condition and enters TX mode -> makes the I2C as master transmit mode.
 */
static inline void I2C_SendStart()
{
	I2C1->C1 |= ((1 << I2C_C1_MST_SHIFT) & I2C_C1_MST_MASK);
	I2C1->C1 |= ((1 << I2C_C1_TX_SHIFT) & I2C_C1_TX_MASK);
}

/**
 *  Enters transmit mode -> set as transmit mode.
 */
static inline void I2C_EnterTransmitMode()
{
	I2C1->C1 |= ((1 << I2C_C1_TX_SHIFT) & I2C_C1_TX_MASK);
}

/**
 *  Enters receive mode -> set as receive mode.
 */
static inline void I2C_EnterReceiveMode()
{
	I2C1->C1 &= ~((1 << I2C_C1_TX_SHIFT) & I2C_C1_TX_MASK);
}

/**
 *  Enters receive mode and enables ACK.
 *
 * Enabling ACK may be required when more than one data byte will be read.
 */
static inline void I2C_EnterReceiveModeWithAck()
{
	I2C1->C1 &= ~((1 << I2C_C1_TX_SHIFT) & I2C_C1_TX_MASK)
			& ~((1 << I2C_C1_TXAK_SHIFT) & I2C_C1_TXAK_MASK);
}

/**
 *  Enters receive mode and disables ACK.
 *
 * Disabling ACK may be required when only one data byte will be read.
 */
static inline void I2C_EnterReceiveModeWithoutAck()
{
	/* Straightforward method of clearing TX mode and
	 * setting NACK bit sending.
	 */
	register uint8_t reg = I2C1->C1;
	reg &= ~((1 << I2C_C1_TX_SHIFT) & I2C_C1_TX_MASK);
	reg |=  ((1 << I2C_C1_TXAK_SHIFT) & I2C_C1_TXAK_MASK);
	I2C1->C1 = reg;
}

/**
 *  Sends a repeated start condition and enters TX mode.
 */
static inline void I2C_SendRepeatedStart()
{

	I2C1->C1 |= ((1 << I2C_C1_RSTA_SHIFT) & I2C_C1_RSTA_MASK)
			  | ((1 << I2C_C1_TX_SHIFT) & I2C_C1_TX_MASK);
}

/**
 *  Sends a stop condition (also leaves TX mode)
 */
static inline void I2C_SendStop()
{
	I2C1->C1 &= ~((1 << I2C_C1_MST_SHIFT) & I2C_C1_MST_MASK)
			& ~((1 << I2C_C1_TX_SHIFT) & I2C_C1_TX_MASK);

}

/**
 *  Enables sending of ACK
 *
 * Enabling ACK may be required when more than one data byte will be read.
 */
static inline void I2C_EnableAck()
{
	I2C1->C1 &= ~((1 << I2C_C1_TXAK_SHIFT) & I2C_C1_TXAK_MASK);
}

/**
 *  Enables sending of NACK (disabling ACK)
 *
 * Enabling NACK may be required when no more data byte will be read.
 */
static inline void I2C_DisableAck()
{
	I2C1->C1 |= ((1 << I2C_C1_TXAK_SHIFT) & I2C_C1_TXAK_MASK);
}

/**
 *  Sends a byte over the I2C bus and waits for the operation to complete
 * @param[in] value The byte to send
 */
static inline void I2C_SendBlocking(const uint8_t value)
{
	I2C1->D = value;
	I2C_Wait_Temp();
}


/**
 *  Drives the clock in receiver mode in order to receive the first byte.
 */
static inline uint8_t I2C_ReceiverModeDriveClock()
{
	uint8_t dummy;
	dummy = I2C1->D;
	I2C_Wait_Temp();
	return (dummy);
}


#endif /* INCLUDES_I2C_H_ */

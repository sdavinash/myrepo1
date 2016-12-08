/*
 * I2C.c
 *
 *  Created on: Nov 21, 2016
 *      Author: Avinash
 */
#include "main.h"


/**********************************************************************************
 	 INITIALIZE I2C1 MODULE FOR TEMPERATURE SENSOR COMMUNICATION WITH MCU
 **********************************************************************************/
void I2C_Init_Temp(void)
{
	/* enable clock of I2C1 */
		SIM->SCGC4 |= (1 << SIM_SCGC4_I2C1_SHIFT) & SIM_SCGC4_I2C1_MASK;
		SIM->SCGC5 |= (1 << SIM_SCGC5_PORTE_SHIFT) & SIM_SCGC5_PORTE_MASK;

		/* configure port E pins to I2C operation */
		PORTE->PCR[1] = PORT_PCR_MUX(6); /* SCL */
		PORTE->PCR[0] = PORT_PCR_MUX(6); /* SDA */

		/* Baud rate = busspeed / (mult * SCL divider), ICR = 0x12 -> SCL divider = 64, MUL=0x00 -> mul =1*/
		I2C1->F = I2C_F_MULT(0x00) | I2C_F_ICR(0x12); /* divide by 64 instead, so 375 kHz */


		/* enable the I2C1 module */
		I2C1->C1 = (1 << I2C_C1_IICEN_SHIFT) & I2C_C1_IICEN_MASK;
}
/*********************************************************************
 	 	 	 	 END OF INITIALIZATION OF I2C1 MODULE
 *********************************************************************/


/**********************************************************************************
 	 INITIALIZE I2C0 MODULE FOR ACCELEROMETER SENSOR COMMUNICATION WITH MCU
 **********************************************************************************/

uint8_t I2C_Init_Accel(I2C_MemMapPtr p)
{
		SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;
	    SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	      // configure GPIO for I2C function
	    PORTE_PCR24 = PORT_PCR_MUX(5);
	    PORTE_PCR25 = PORT_PCR_MUX(5);

	    p->F  = 0x14; // baudrate = 300 kHz
	    p->C1 = 0x80; // enable IIC
}
/*********************************************************************
 	 	 	 	 END OF INITIALIZATION OF I2C1 MODULE
 *********************************************************************/




/***************************************
 	 	SET I2C MODES
 ***************************************/
void I2C_Set_Tx_Mode(I2C_MemMapPtr p)
{
    p->C1 |= I2C_C1_TX_MASK;

}
void I2C_Set_Rx_Mode(I2C_MemMapPtr p)
{
    p->C1 &= ~I2C_C1_TX_MASK;
}

void I2C_Set_Slave_Mode(I2C_MemMapPtr p)
{
    p->C1  &= ~I2C_C1_MST_MASK;
}
void I2C_Set_Master_Mode(I2C_MemMapPtr p)
{
    p->C1  |=  I2C_C1_MST_MASK;
}


/***************************************
 	 I2C OPERATION FUNCTIONS
 ***************************************/
void I2C_Give_NACK(I2C_MemMapPtr p)
{
    p->C1 |= I2C_C1_TXAK_MASK;
}
void I2C_Give_ACK(I2C_MemMapPtr p)
{
    p->C1 &= ~I2C_C1_TXAK_MASK;
}
void I2C_Repeated_Start(I2C_MemMapPtr p)
{
    p->C1 |= I2C_C1_RSTA_MASK;
}
void I2C_Write_Byte(I2C_MemMapPtr p, uint8_t data)
{
    p->D = data;
}
uint8_t I2C_Read_Byte(I2C_MemMapPtr p)
{
    return p->D;
}
void I2C_Start(I2C_MemMapPtr p)
{
	I2C_Set_Master_Mode(p);
	I2C_Set_Tx_Mode(p);
}
void I2C_Stop(I2C_MemMapPtr p)
{
	I2C_Set_Slave_Mode(p);
	I2C_Set_Rx_Mode(p);
}
void I2C_Wait(I2C_MemMapPtr p)
{
    // wait flag
    while((p->S & I2C_S_IICIF_MASK)==0)
        ;
    // clear flag
    p->S |= I2C_S_IICIF_MASK;
}
uint16_t I2C_Get_ACK(I2C_MemMapPtr p)
{
    if((p->S & I2C_S_RXAK_MASK) == 0)
        return TRUE;
    else
        return FALSE;
}



/**********************************************************************************
 	 DEINITIALIZE I2C0 MODULE FOR ACCELEROMETER SENSOR COMMUNICATION WITH MCU
**********************************************************************************/
void I2C_Deinit_Accel(I2C_MemMapPtr p)
{
    p->C1 = 0x00;

    SIM_SCGC4 &= ~SIM_SCGC4_I2C0_MASK;
}

/**********************************************************************************
 	 DEINITIALIZE I2C1 MODULE FOR TEMPERATURE SENSOR COMMUNICATION WITH MCU
 **********************************************************************************/
void I2C_Deinit_Temp(I2C_MemMapPtr p)
{
    p->C1 = 0x00;

    SIM_SCGC4 &= ~SIM_SCGC4_I2C1_MASK;
}


/**********************************************************************************************************************/
uint8_t I2C_ReadRegister(register uint8_t slaveId, register uint8_t registerAddress)
{
	/* loop while the bus is still busy */
	I2C_WaitWhileBusy();

	/* send I2C start signal and set write direction, also enables ACK */
	I2C_SendStart();

	/* send the slave address and wait for the I2C bus operation to complete */
	I2C_SendBlocking(I2C_WRITE_ADDRESS(slaveId));

	/* send the register address */
	I2C_SendBlocking(registerAddress);

	/* signal a repeated start condition */
	I2C_SendRepeatedStart();

	/* send the read address */
	I2C_SendBlocking(I2C_READ_ADDRESS(slaveId));

	/* switch to receive mode but disable ACK because only one data byte will be read */
	I2C_EnterReceiveModeWithoutAck();

	/* read a dummy byte to drive the clock */
	I2C_ReceiverModeDriveClock();

	/* stop signal */
	I2C_SendStop();

	/* fetch the last received byte */
	register uint8_t result = I2C1->D;
	return result;
}

/**
 * Reads an 8-bit register from an I2C slave
 */
void I2C_WriteCommand(register uint8_t slaveId, register uint8_t value)
{
	/* loop while the bus is still busy */
	I2C_WaitWhileBusy();

	/* send I2C start signal and set write direction*/
	I2C_SendStart();

	/* send the slave address and wait for the I2C bus operation to complete */
	I2C_SendBlocking(I2C_WRITE_ADDRESS(slaveId));

	/* send the command value */
	I2C_SendBlocking(value);

	/* issue stop signal by clearing master mode. */
	I2C_SendStop();
}



void I2C_ReadRegisters(register uint8_t slaveId, register uint8_t command, register uint8_t registerCount, register uint8_t *buffer)
{
	if (registerCount > 1)
	{
		I2C_ReadMultipleRegisters(slaveId, command, registerCount, buffer);
	}
	else
	{
		register uint8_t result = I2C_ReadRegister(slaveId, command);
		buffer[0] = result;
	}
}


static void I2C_ReadMultipleRegisters(register uint8_t slaveId, register uint8_t startRegisterAddress, register uint8_t registerCount, uint8_t *const buffer)
{

	uint8_t TEM;

	/* loop while the bus is still busy */
	I2C_WaitWhileBusy();

	/* send I2C start signal and set write direction, also enables ACK */
	I2C_SendStart();

	/* send the slave address and wait for the I2C bus operation to complete */
	I2C_SendBlocking(I2C_WRITE_ADDRESS(slaveId));

	/* send the register address */
	I2C_SendBlocking(startRegisterAddress);

	/* signal a repeated start condition */
	I2C_SendRepeatedStart();

	/* send the read address */
	I2C_SendBlocking(I2C_READ_ADDRESS(slaveId));

	/* switch to receive mode and assume more than one register */
	I2C_EnterReceiveModeWithAck();

	/* for all remaining bytes, read */
	uint8_t index = 0;
	while (registerCount-- > 0)
	{
		/* fetch and store value */
		register uint8_t value = I2C1->D;
		buffer[index++] = value;

		/* wait for completion */
		I2C_Wait_Temp();
	}

	/* disable ACK and read second-to-last byte */
	I2C_DisableAck();

	/* fetch and store value */
	buffer[index++] = I2C1->D;

	/* wait for completion */
	I2C_Wait_Temp();

	/* stop signal */
	I2C_SendStop();

	/* fetch the last received byte */
	buffer[index++] = I2C1->D;
}

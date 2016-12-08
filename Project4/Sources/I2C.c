/*
 * I2C.c
 *
 *  Created on: Nov 21, 2016
 *      Author: Avinash
 */
#include "I2C.h"


/**********************************************************************************
 	 INITIALIZE I2C1 MODULE FOR TEMPERATURE SENSOR COMMUNICATION WITH MCU
 **********************************************************************************/
void I2C_Init_Temp(I2C_MemMapPtr p)
{
	/* enable clock of I2C1 */
   SIM_SCGC4 |= (1 << SIM_SCGC4_I2C1_SHIFT) & SIM_SCGC4_I2C1_MASK;
   SIM_SCGC5 |= (1 << SIM_SCGC5_PORTE_SHIFT) & SIM_SCGC5_PORTE_MASK;

   /* configure port E pins to I2C1 operation */
   PORTE_PCR1 = PORT_PCR_MUX(6);	/* SCL */
   PORTE_PCR0 = PORT_PCR_MUX(6);	/* SDA */

    /* Baud rate = busspeed / (mult * SCL divider), ICR = 0x12 -> SCL divider = 64, MUL=0x00 -> mul =1*/
    p->F  = I2C_F_MULT(0x00) | I2C_F_ICR(0x12); // /* divide by 64 instead, so 375 kHz */

    /* enable I2C1*/
    p->C1 = (1 << I2C_C1_IICEN_SHIFT) & I2C_C1_IICEN_MASK;
}
/*********************************************************************
 	 	 	 	 END OF INITIALIZATION OF I2C1 MODULE
 *********************************************************************/


/**********************************************************************************
 	 INITIALIZE I2C0 MODULE FOR ACCELEROMETER SENSOR COMMUNICATION WITH MCU
 **********************************************************************************/
void I2C_Init_Accel(I2C_MemMapPtr p)
{
	/* enable clock of I2C0 */
   SIM_SCGC4 |= (1 << SIM_SCGC4_I2C0_SHIFT) & SIM_SCGC4_I2C0_MASK;;
   SIM_SCGC5 |= (1 << SIM_SCGC5_PORTE_SHIFT) & SIM_SCGC5_PORTE_MASK;

   /* configure port E pins to I2C0 operation */
   PORTE_PCR24 = PORT_PCR_MUX(5);	/* SCL */
   PORTE_PCR25 = PORT_PCR_MUX(5);	/* SDA */

   /* Baud rate = busspeed / (mult * SCL divider), ICR = 0x12 -> SCL divider = 64, MUL=0x00 -> mul =1*/
    p->F  = I2C_F_MULT(0x00) | I2C_F_ICR(0x12);	/* divide by 64 instead, so 375 kHz */

    /* enable I2C1*/
    p->C1 = (1 << I2C_C0_IICEN_SHIFT) & I2C_C0_IICEN_MASK;
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

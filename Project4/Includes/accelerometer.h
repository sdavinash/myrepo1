#ifndef _ACCELEROMETER_H
#define _ACCELEROMETER_H

#include "main.h"


#define ACCEL_DEVICE_I2C_ADDRESS		0x1D			/*ACCELEROMETER DEVICE ADDRESS*/
#define I2C0_B  						I2C0_BASE_PTR



/***********************************************
 * ACCELEROMETER REGISTERS
 **********************************************/
#define ACCEL_STATUS_REG			0x00
#define ACCEL_OUT_X_MSB_REG			0x01
#define ACCEL_OUT_X_LSB_REG			0x02
#define ACCEL_OUT_Y_MSB_REG			0x03
#define ACCEL_OUT_Y_LSB_REG			0x04
#define ACCEL_OUT_Z_MSB_REG			0x05
#define ACCEL_OUT_Z_LSB_REG			0x06
#define ACCEL_F_SETUP_REG			0x09
#define ACCEL_INT_SOURCE REG		0x0C
#define ACCEL_WHO_AM_I_REG			0x0D
#define ACCEL_XYZ_DATA_CFG_REG		0x0E
#define ACCEL_FF_MT_CFG_REG			0x15
#define ACCEL_FF_MT_SRC_REG			0x16
#define ACCEL_FF_MT_THS_REG			0x17
#define ACCEL_FF_MT_CNT_REG			0x18
#define ACCEL_CRTL_REG_1			0X2A
#define ACCEL_CTRL_REG_4			0X2D
#define ACCEL_CTRL_REG_5			0X2E

/**********************************************/

#define ACCEL_CRTL_REG_VALUE		0x1D
#define ACCEL_XYZ_DATA_CFG			0x01
#define ACCEL_INTR_ENABLE			0x04
#define ACCEL_INTR_CONFIG			0x04
#define ACCEL_FF_MT_CFG				0xA0
#define ACCEL_FF_MT_THS				0x10
#define ACCEL_FF_MT_CNT				0x32


void Init_I2C_Accel(void); 							//Prepare I2C0 at PORT_E
uint8_t Accel_Read_Reg(uint8_t addr);				//Read from accelerometer registers
void Accel_Write_Reg(uint8_t addr, uint8_t data);	//Write to accelerometer registers
static void pause(void);							//delay between read and write operations from/to accelerometer registers

//uint16_t hal_dev_mma8451_test_reg_rw(void);
//void hal_dev_mma8451_test_function(void);


#endif /* _ACCELEROMETER_H */

/*
 * i2c_lib.c
 *
 * Created: 11/14/2016 3:43:26 PM
 *  Author: Admin
 */ 

#include <avr/io.h>
#include "i2c_lib.h"
/************************************************************************/
/*     i2c_Init Initialize the I2C                                                                 */
/************************************************************************/
void i2c_Init(void)
{
	SDA=SCL=1;  //setting the input pins of clock and data
	
	//I2C_CR=0x08; //I2C enabled and start condition is given
	
	I2C_ST=0x00; //status register is initiated as 0

	//I2C_ADD=0x10; // Address of the master is given
}

/************************************************************************/
/*       i2c_Wait - wait for I2C transfer to finish                                                               */
/************************************************************************/
void i2c_Wait(void);
{
	while ((I2C_CR & 0x81) || (I2C_ST & )); //Transmit is in progress
}

/************************************************************************/
/*       i2c_Start - Start I2C communication                                                             */
/************************************************************************/
void i2c_Start(void)
{
	i2c_Wait();
	I2C_CR=0x20;  //It will start the i2c
}

/************************************************************************/
/*     i2c_Restart - Re-Start I2C communication                                                                 */
/************************************************************************/
void i2c_Restart(void)
{
	i2c_Wait();
	I2C_CR=0x20; //Repeated start
}

/************************************************************************/
/*     i2c_Stop - Stop I2C communication                                                                 */
/************************************************************************/
void i2c_Stop(void)
{
	i2c_Wait();
	I2C_CR=0x10; //it will stop 
}

/************************************************************************/
/*      i2c_Write - Sends one byte of data                                                                */
/************************************************************************/
void i2c_Write(unsigned char data)
{
	i2c_Wait();
}

/************************************************************************/
/*  i2c_Address - Sends Slave Address and Read/Write mode 
	mode is either I2C_WRITE or I2C_READ                                                                 */
/************************************************************************/
void i2c_Address(unsigned char address, unsigned char mode)
{
	
}

/************************************************************************/
/*    i2c_Read - Reads a byte from Slave device                                                                  */
/************************************************************************/
unsigned char i2c_Read(unsigned char ack)
{
	
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int function(void)
{
    //TODO:: Please write your application code

    return 0;
}
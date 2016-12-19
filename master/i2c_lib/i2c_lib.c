/*
 * i2c_lib.c
 *
 * Created: 11/14/2016 3:43:26 PM
 *  Author: Admin
 */ 

#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include "i2c_lib.h"

/************************************************************************/
/*     i2c_Start Start the I2C                                                                 */
/************************************************************************/
void i2c_Start(void)
{
	SDA = 0;			//make sda line to low
	PORTD = SDA;		// send logic to port
	_delay_ms(1000);		//provide delay	
	I2C_CR = 0b00000001;  //It will start the i2c
	I2C_ST = 0b00000010;	// set status register for start condition
}

/************************************************************************/
/*     i2c_add Send the address to the I2C                                                                 */
/************************************************************************/

void i2c_add()
{
	if ((I2C_ST & 0x02) && (I2C_CR & 0x01) && (SDA == 0))		// START CONDITION FOR I2C
	{
		
		for (unsigned char c=1; c<=8; c++)
		{
			clock(0);							// change state of clock to low
			PORTD=(I2C_ADR >> 7);				//sending 1 bit of data 
			I2C_ADR = I2C_ADR << 1;				//shifting the address register
			_delay_ms(200);						// provide delay
			clock(1);							// change state of clock to high
		}
		i2c_read_ack();
		if (ackn == 1)
		{
			I2C_CR = 0b00001100;
			I2C_ST = 0b00000011;
		}
		
				
	}
}

/************************************************************************/
/*     i2c_ADR Send the adress to the I2C                                                                 */
/************************************************************************/

void i2c_ADR(unsigned char add , unsigned char mode)
{
	I2C_ADR = add;
	I2C_ADR = (I2C_ADR << 1 ) + mode;
	
}
void i2c_read_ack()
{
	_delay_ms(100);
	ackn = 1;
		
}

/************************************************************************/
/*     clock toggling the clock                                                                */
/************************************************************************/

void clock (int x)
{
	SCL = x;
	PORTC = SCL;
	_delay_ms(200);
}

void i2c_Write(unsigned char data)
{
	if ((I2C_ST & 0x0c) && (I2C_CR & 0x03))
	{
		I2C_DR = data;
		for (unsigned char c=1; c<=8; c++)
		{
			clock(0);							// change state of clock to low
			PORTD=(I2C_DR >> 7);		//sending 1 bit of data
			I2C_DR = I2C_DR << 1;				//shifting the address register
			_delay_ms(200);						// provide delay
			clock(1);							// change state of clock to high
		}
	}
	
	i2c_read_ack();
}

/************************************************************************/
/*     i2c_init Initialize the I2C                                                                 */
/************************************************************************/

void i2c_init()
{
	PORTD = SDA;
	PORTC = SCL;
	_delay_ms(2000);
}

/************************************************************************/
/*     i2c_Sop Stop the I2C                                                                 */
/************************************************************************/
void stop()
{
	if (SCL == 0)
	{
		clock(1);
		PORTD = 0x01;
		_delay_ms(100);
	}
	else
	{
		PORTD = 0x01;
		_delay_ms(100);
		
	}
}


void address(unsigned int add)		//address function definition
{
	if(I2CADD==add){				//comparison of address
		flag=1;						//set flag
	}
	if(flag==1){					//checking flag to generate ack
		I2C_SLAVE_write_ack(flag);
	}
	
}
void I2C_SLAVE_read()
{
	uint8_t temp;   //assigning initial value to address
	int c;
	if(flag==0){
		for(uint8_t i=128;i>=1;i=i/2)
		{
			if((PINB & 0x01)==1)
			{
				temp=i;
				
			}
			else
			{
				temp=0;
			}
			if(i==1)
			{
				c=(PINB & 0x01);
				if(c==1){
					I2C_CR = 0x0c;
					I2C_ST = 0x03;
				}
				
				else{
					I2C_CR = 0x28;
					I2C_ST = 0x44;
				}
			}
			else
			{				//calculation of address
				I2C_DR = I2C_DR + temp;	//rest of bits are assumed as address bits
			}
		}
		int sda_p = temp;
		if(I2CADD == I2C_DR){				//comparison of address
			flag=1;						//set flag
		}
	}
	else{									// data reading
		for(int i=128;i>=1;i=i/2)
		{
			if((PINB & 0x01)==1)
			{
				temp=i;
				
			}
			else
			{
				temp=0;
			}
			if(i==1)
			{
				c=(PINB & 0x01);
				if(c==1){
					I2C_CR =	0x0c;
					I2C_ST = 0x03;
				}
				
				else{
					I2C_CR = 0x28;
					I2C_ST = 0x44;
				}
			}
			else
			{				//calculation of address
				I2C_DR = I2C_DR + temp;	//rest of bits are assumed as address bits
			}
		}
		if(I2C_DR == 75){
			PORTD = 0xff;
			_delay_ms(1000);
			I2C_DR = 0x00;
		}
	}
	
}

void I2C_SLAVE_write()
{
	uint8_t my;
	PORTB=0x00;
	my=I2C_DR;
	PORTB=(my<<1&0x03);
	my=my>>1;
}
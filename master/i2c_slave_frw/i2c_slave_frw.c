/*
 * i2c_slave.c
 *
 * Created: 16-Dec-16 12:40:00 PM
 *  Author: Lenovo
 */ 


/*
 * i2c_slave_frw.c
 *
 * Created: 11/14/2016 3:42:44 PM
 *  Author: Admin
 */ 

//#define  F_CPU 8000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
//#include "lib.h"	

uint8_t I2C_CR;
uint8_t I2C_ST;

int main(void)
{	
	DDRB = 0x00;
	DDRD = 0xff;
	int i=0;
	while(1)
	{  
		//_delay_ms(1000);
		if(PINB == 0b00000010)
		{		//condition check I2c start or not
			PORTD=0xff;
			i++;
			//_delay_ms(1000);
			I2C_CR = 0x01;
			I2C_ST = 0x02;
			PORTD=0x00;
			if(i==1){
				break;
			} 			
		}
	else if((I2C_CR == 0x01) && (I2C_ST == 0x02))
	{
		I2C_CR = 0x0c;
		I2C_ST = 0x44;
	}
	else if((I2C_CR == 0x28) && (I2C_ST == 0x44) )
	{
		I2C_SLAVE_read();
	}
	else if((I2C_CR == 0x0c) && (I2C_ST == 0x03))
	{
		I2C_SLAVE_write();
		}	
	}
	return 0;
	  
}

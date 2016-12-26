#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include "i2c_lib.h"


/************************************************************************/
/*     i2c_Start Start the I2C                                                                 */
/************************************************************************/
void i2c_Start(void)
{
	SDA = 0;				//make sda line to low
	PORTC = SDA<<0 | SCL<<1;	// send logic to port
	PORTB = 0x03;
	_delay_ms(2000);		//provide delay
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
			SDA = (I2C_ADR >> 7);
			PORTC= SDA<<0| SCL<<1;				//sending 1 bit of data
			I2C_ADR = I2C_ADR << 1;				//shifting the address register
			_delay_ms(1000);						// provide delay
			clock(1);							// change state of clock to high
		}
		_delay_ms(100);
		PORTC = 0<<0 | 0<<1;
		i2c_read_ack();
		clock(1);
		
		if (ackn == 1)
		{
			PORTB = 0xFF;
			_delay_ms(1000);
			I2C_CR = 0b00001100;
			I2C_ST = 0b00000011;
		}
		else
		{
			I2C_CR =0;
			I2C_ST =0;
			
		}
	}
}

/************************************************************************/
/*     i2c_ADR Send the adress to the I2C                                                                 */
/************************************************************************/

void i2c_ADR(unsigned char add , unsigned char mode)
{
	I2C_ADR = add + mode;
	PORTB = 0x02;
	_delay_ms(100);
}
int i2c_read_ack()
{
	DDRC = 0x00;
	for (int s=20;s>=0;s--)
	{
		if ((PINC & 0x01) == 0)
		{
			ackn = 1;
			DDRC = 0x03;
			return 0;
		}
		_delay_ms(100);
		
	}
	DDRC = 0x03;
	
}

/************************************************************************/
/*     clock toggling the clock                                                                */
/************************************************************************/

void clock (int x)
{
	SCL = x;
	PORTC = SCL<<1 | SDA<<0;
	_delay_ms(2000);
}

void i2c_Write(unsigned char data)
{
	
	if ((I2C_ST & 0x0c) && (I2C_CR & 0x03))
	{
		I2C_DR = data;
		for (unsigned char c=1; c<=8; c++)
		{
			clock(0);							// change state of clock to low
			PORTC=(I2C_DR >> 7) | SCL<<1;		//sending 1 bit of data
			I2C_DR = I2C_DR << 1;				//shifting the address register
			_delay_ms(1000);						// provide delay
			clock(1);							// change state of clock to high
		}
		i2c_read_ack();
		if (ackn == 1)
		{
			PORTB = 0xff;
			_delay_ms(1000);
			PORTB = 0x00;
			_delay_ms(1000);
		}
	}
}

/************************************************************************/
/*     i2c_init Initialize the I2C                                                                 */
/************************************************************************/

void i2c_init()
{
	PORTC = SDA<<0 | SCL<<1;
	PORTB = 0x01;
	_delay_ms(3000);
}

/************************************************************************/
/*     i2c_Sop Stop the I2C                                                                 */
/************************************************************************/
void stop()
{
	if (SCL == 0)
	{
		clock(1);
		PORTC = 1<<0 | SCL<<1;
		_delay_ms(1000);
	}
	else
	{
		PORTC = 1<<0 | SCL<<1;
		_delay_ms(1000);
		
	}
}


void slave_init()
{
	if ((PINC & 0x03) == 0x03)
	{
		start = 1;
		PORTB = 0x01;
		_delay_ms(100);
	}
}

void slave_start()
{
	if ((start == 1) && ((PINC & 0x03) == 0x02))
	{
		read = 1;
		ready = 1;
		PORTB = 0x02;
		_delay_ms(100);
	}
}
void send_ack()
{
	DDRC = 0x02;
	PORTC = 0x01;
	_delay_ms(1500);
	DDRC = 0x00;
	PORTC = 0;
}

void read_add_slave()
{
	int x = 1, check = 0;;
	if (read == 1)
	{
		PORTB = 0x03;
		_delay_ms(100);
		while (x<=8)
		{
			if(((PINC & 0x02) == 0x02) && (ready == 0))
			{
				PORTB = 0x04;
				ready = 1;
				_delay_ms(100);
			}
			if(((PINC & 0x02)==0) && (ready == 1))
			{
				check = 1;
				PORTB = 0x06;
				ready = 0;
				_delay_ms(100);
			}
			
			if (check == 1)
			{
				I2C_DR += (PINC & 0x01);
				I2C_DR = I2C_DR <<1;
				PORTD = (PINC & 0x01);
				check = 0;
				x++;
				
			}
			
		}
		PORTD = I2C_DR;
		send_ack();
		if (I2C_ADR == I2C_DR)
		{
			PORTB = 0x01;
			_delay_ms(100);
		}
		mode_slave = (I2C_DR & 0x01);
		if (mode_slave == 0)
		{
			read_slave = 1;
		}
		else
		{
			write_slave = 1;
			read = 0;
		}
		
		
	}
}
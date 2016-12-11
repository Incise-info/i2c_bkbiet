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
	while ((I2C_CR & 0x81) || (I2C_ST & 0x04)); //Transmit is in progress
}

/************************************************************************/
/*       i2c_Start - Start I2C communication                                                             */
/************************************************************************/
void i2c_Start(void)
{
	i2c_Wait();
	DDRB=0x03;
	if (tm=1)
	{
		PORTB=0x02;
	}
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
	DDRB=0x00;
	for (unsigned char c=0;c<8;c++)
	{
		data =I2C_DR;
		PORTB=(data<<1)&(0x03);
		data=data>>1;
	}
	read_ack();
	I2C_ST=0x09;
}

/************************************************************************/
/*  i2c_Address - Sends Slave Address and Read/Write mode 
	mode is either I2C_WRITE or I2C_READ                                                                 */
/************************************************************************/
void i2c_Address(unsigned char address, unsigned char mode)
{
	i2c_Start();
	add=(add<<1)+mode;
	DDRB=0x00;
	for (unsigned char c=0;c<8;c++)
	{
		PORTB=(add<<1)&(0x03);
		add=add>>1;
	}
	read_ack();
	I2C_ST=0x10;
}

/************************************************************************/
/*    i2c_Read - Slave is reading the address                                                                  */
/************************************************************************/
void I2C_SLAVE_read_add(unsigned int PINB){
	add=0;   //assigning initial value to address
	for(int i=128;i>=1;i=i/2){
		PINB=PINB*i;		//decimal value of bit
		if(i==1){			//store 8th bit for read or write operation
			c=PINB;		//assign value to c
		}
		else{				//calculation of address
			add=add+PINB;	//rest of bits are assumed as address bits
		}
	}
	address(add);					//calling of address function
}
/************************************************************************/
/*    i2c_Read - Slave is reading the address                                                                  */
/************************************************************************/
void I2C_SLAVE_read_data(unsigned int PINB){		//slave_read_data function definition
	for(int i=128;i>=1;i=i/2){
		PINB=PINB*i;					//value of PINB signal
		temp=temp+PINB;					//storing of calculated data in temp
	}
	LCD_Display(temp);					//display data at LCD
	temp=0x00;							//reset the temp
}

/************************************************************************/
/*    i2c_ack - Sends a acknowledgment whenever data is received                                                                  */
/************************************************************************/
void i2c_read_ack()
{
	
	DDRB=0x01;
	if (PINB&0x01)
	{
		I2C_ST=0x08;
	}
}
void I2C_write_ack(){		//function definition
	PORTB=0x00;							//initialize port B
	_delay_ms(10);						//delay for 10ms
	PORTB=0x02;
	I2C_ST=0x10;						//second pin of portB is high
}
/************************************************************************/
/*    i2c_timer - timer or the i2c                                                                  */
/************************************************************************/
ISR(TIMER0_COMPA_vect)
{
	tm=~tm;
}

void timer_init()
{
	TCCR0A=0xc3;
	TCCR0B=0x01;
	TIMSK0=0x02;
	TCNT0=0xff;
}
int timer(void)
{
	sei();
	DDRB=tm;
	timer_init();
	OCR0A=1;
	_delay_ms(5);
}	
/************************************************************************/
/*                                                                      */
/************************************************************************/
int function(void)
{
    //TODO:: Please write your application code

    return 0;
}
//#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
//#include "lib.h"

int main(void)
{
	DDRB = 0xff;
	DDRD = 0xff;
	DDRC = 0x00;
	PORTB = 0x04;
	_delay_ms(1);
	slave_init();
	while(1)
	{
		slave_start();
		read_add_slave();
		slave_i2c_Read();
	}
	return 0;
}

#define F_CPU 16000000UL
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
	_delay_ms(100);
	while(1)
	{
		slave_init();
		slave_start();
		read_add_slave();
	}
	return 0;
	
}
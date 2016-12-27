
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
	while(1)
	{
		slave_init();
		slave_start();
		read_add_slave();
	}
	return 0;
	
}
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
//#include "i2c_lib.h"

int main(void)
{
	DDRC = 0xff;
	DDRD = 0xff;
	DDRB = 0xff;
	i2c_init();
	_delay_ms(500);
	i2c_ADR(0x55, 0);
	_delay_ms(500);
	i2c_Start();
	_delay_ms(500);
	while(1)
	{
		i2c_add();
		//i2c_Write('a');
	}
}
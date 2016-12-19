
#include <avr/io.h>
#include <util/delay.h>
//#include "i2c_lib.h"

int main(void)
{
	DDRC = 0x01;
	DDRD = 0x01;
	DDRB = 0xff;
	i2c_init();
	i2c_Start();
	i2c_ADR(0xaa , 0);
	while(1)
	{
		i2c_add();
		if(ackn == 1)
		{
			PORTB = 0xff;
			_delay_ms(1000);
			PORTB = 0;
			_delay_ms(1000);
			exit(1);
		}
		_delay_ms(1000);
		
	}
}
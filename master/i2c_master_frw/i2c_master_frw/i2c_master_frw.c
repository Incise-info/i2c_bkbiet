
#include <avr/io.h>0
#include <util/delay.h>
//#include "i2c_lib.h"

int main(void)
{
	DDRC = 0xff;
	DDRD = 0xff;
	DDRB = 0xff;
	i2c_init();
	i2c_ADR(0b01100110, 0);
	i2c_Start();
	while(1)
	{
		i2c_add();
		//i2c_Write('a');
	}
}
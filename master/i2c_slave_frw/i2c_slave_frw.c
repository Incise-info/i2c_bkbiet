/*
 * i2c_slave_frw.c
 *
 * Created: 11/14/2016 3:42:44 PM
 *  Author: Admin
 */ 


# include <avr/io.h>
# include "i2c_lib.h"
# define int flag;						//declaration of integer type flag variable
# define int c=0;						//initialize a integer type c variable
# define int b;							//declaration integer type b variable			
# define int a;							//declaration of integer type a variable
# define int *x;						//declaration integer type pointer x variable
# define int temp;						//initialize integer type temp variable	
# define int my;						//initialize integer type temp variable
x=&flag;								//give address to a pointer 
DDRB=0xff;								//to enable a port
int main(void)
{
	  if(SCL=1 && PINB=0){				//condition check I2c start or not
		  a=0;							//assigning value to a for starting of I2c
		  b=1;
	  }
	  else{
		  a=1;
		  exit;							//to stop I2c
	  }
	  while(a!=1){						//check start condition
		  if(b==1){
			  I2C_SLAVE_read_add(PINB);	//first byte of information is address
			  b=0;						//set b for next byte is data
	      }
		  else{
			  if(*x==0){				//weather read or write operation
				  I2C_SLAVE_read_data(PINB);
			  }
			 else{
				  I2C_SLAVE_write_data(PINB);
			  }
	      }
	  }
}
void I2C_SLAVE_read_add(unsigned int SDA){
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
void address(unsigned int add){		//address function definition
	if(I2CADD==add){				//comparison of address
		flag=1;						//set flag
	}
	if(flag==1){					//checking flag to generate ack
		I2C_SLAVE_write_ack(flag);
	}
	
}
void I2C_SLAVE_read_data(unsigned int){		//slave_read_data function definition 
	    for(int i=128;i>=1;i=i/2){
		    PINB=PINB*i;					//value of PINB signal
		    temp=temp+PINB;					//storing of calculated data in temp
		}
		LCD_Display(temp);					//display data at LCD
		temp=0x00;							//reset the temp
}
void I2C_SLAVE_write_ack(unsigned int){		//function definition
		PORTB=0x00;							//initialize port B
		_delay_ms(10);						//delay for 10ms
		PORTB=0x02;							//second pin of portB is high
}
void I2C_SLAVE_write_data(){				//function definition
	PORTB=0x00;								//initialize PORTB
	my=I2CDR;								//save data of data register in my 
	PORTB=(my<<1&0x03);						//masking and shifting to take serial input at pin of PORTB
	my=my>>1;								//one bit shifting of data
}
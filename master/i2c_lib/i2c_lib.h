/*
 * i2c_lib.h
 *
 * Created: 11/14/2016 3:51:05 PM
 *  Author: Admin
 */ 


#ifndef I2C_LIB_H_
#define I2C_LIB_H_

#define I2C_WRITE 0 
#define I2C_READ 1

uint8_t ready = 0;
uint8_t read = 0;
uint8_t start = 0;
uint8_t write_slave;
uint8_t read_slave;
uint8_t mode_slave;
int SCL = 0x01;
int SDA = 0x01;
uint8_t I2C_CR =0;
uint8_t I2C_ST =0;
uint8_t I2C_ADR =0;
uint8_t I2C_DR =0;
uint8_t ackn = 0;
int mode = 0;
int count = 0;
uint8_t flag=0;
uint8_t I2CADD;

void read_add_slave();
void send_ack();
void slave_init();
void slave_start();
void i2c_Start(void);
void i2c_add();
void i2c_ADR(unsigned char add , unsigned char mode);
int i2c_read_ack();
void clock (int x);
void i2c_init();
void i2c_Write(unsigned char data);
void I2C_SLAVE_read();
void I2C_SLAVE_write();

#endif /* I2C_LIB_H_ */
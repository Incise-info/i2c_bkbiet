/*
 * i2c_lib.h
 *
 * Created: 11/14/2016 3:51:05 PM
 *  Author: Admin
 */ 

#ifndef I2C_LIB_H_
#define I2C_LIB_H_

#define SDA
#define SCL
#define I2C_CR uint8_t
#define I2C_ST uint8_t
#define I2C_ADD uint8_t
#define I2C_DR uint8_t
#define tm uint8_t

#define I2C_WRITE 0
#define I2C_READ 1

void i2c_Init(void);
void i2c_read_ack(void);
void I2C_write_ack(void);
void i2c_Wait(void);
void i2c_Start(void);
void i2c_Restart(void);
void i2c_Stop(void);
void i2c_Write(unsigned char data);
void i2c_Address(unsigned char address, unsigned char mode);
void I2C_SLAVE_read_add(unsigned int SDA);
void I2C_SLAVE_read_data(unsigned int SDA);

#endif /* I2C_LIB_H_ */
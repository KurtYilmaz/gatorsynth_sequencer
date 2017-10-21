#ifndef I2C_H_
#define I2C_H_

 // R/!W
 #define read 1
 #define write 0

 // IO Expander Register Addresses
 #define MAX7314_configRegister 0x0F
 #define MAX7314_portConfigRegisterLow 0x06
 #define MAX7314_portConfigRegisterHigh 0x07
 #define MAX7314_inputPortLow 0x00
 #define MAX7314_inputPortHigh 0x01

 #define MAX7314_slaveAddress 0b010000 //7bit address when AD0 = GND

 void init_IO_int();
 void i2c_init();
 void i2c_stop();
 void i2c_start(uint8_t slave_addr, uint8_t mread);
 uint8_t i2c_readNACK();
 uint8_t i2c_readACK();
 void i2c_write(uint8_t data);
 void i2c_writeStop(uint8_t data);

#endif /* I2C_H_ */
 #include <asf.h>
 #include <stdbool.h>
 #include <stdlib.h>

 // R/!W
 #define read 1
 #define write 0

 // IO Expander Register Addresses
 #define MAX7314_configRegister 0x0F
 #define MAX7314_portConfigRegisterLow 0x06
 #define MAX7314_portConfigRegisterHigh 0x07
 #define MAX7314_inputPortLow 0x00
 #define MAX7314_inputPortHigh 0x01

 #define MAX7314_slaveAddress (uint8_t) 0b0100000 //7bit address when AD0 = GND

 void init_IO_int(){

	//enable clock for PIOB
	REG_PMC_PCER0 |= PMC_PCER0_PID12;

	//Set up PB10 as Button IO Expander Input
	REG_PIOB_PER |= PIO_PER_P10; //enable PIO controller
	REG_PIOB_ODR |= PIO_ODR_P10; //disable output
	REG_PIOB_PPDDR |= PIO_PPDDR_P10; //disable pull-down resistor
	REG_PIOB_PUER |= PIO_PUER_P10;	//enable pull-up resistor
	REG_PIOB_IFSCER |= PIO_IFSCER_P10; //turn on slow clock debounce
	REG_PIOB_IFER |= PIO_IFER_P10;	//start debounce filter

	uint32_t flag_clear = REG_PIOB_ISR;	//clear left over interrupt flags

	//Enable interrupts for PB10
	REG_PIOB_IER |= PIO_IER_P10;			//enable falling edge change interrupt
	REG_PIOB_FELLSR |= PIO_FELLSR_P10;

	NVIC_EnableIRQ(PIOB_IRQn);

 }

 void i2c_init(){

	REG_TWI0_CR = TWI_CR_SWRST;

	//enable peripheral clock for i2c using TWI0
	REG_PMC_PCER0 |= PMC_PCER0_PID19;

	//disable GPIO control of i2c pins
	REG_PIOA_PDR |= PIO_PDR_P3;
	REG_PIOA_PDR |= PIO_PDR_P4;

	//REG_TWI0_MMR &= ~TWI_MMR_MREAD;

	//store slave address
	//REG_TWI0_MMR |= TWI_MMR_DADR(MAX7314_slaveAddress);

	// tlow = ((CLDIV * 2^CKDIV) + 4) * Tper
	// thigh = ((CHDIV * 2^CKDIV) + 4) * Tper
	// thigh = tlow => 400kHz (supposedly...)
	//set TWI0 clock to 400kHz (supported by IO expander)
	REG_TWI0_CWGR |= TWI_CWGR_CLDIV(121);
	REG_TWI0_CWGR |= TWI_CWGR_CHDIV(121);

	//disable slave mode & enable master mode
	REG_TWI0_CR |= TWI_CR_SVDIS;
	REG_TWI0_CR |= TWI_CR_MSEN;
 }

 void i2c_stop(){
	REG_TWI0_CR |= TWI_CR_STOP;
 }

 void i2c_start(uint8_t slave_addr, uint8_t mread){
	//set slave address
	REG_TWI0_MMR |= TWI_MMR_DADR(slave_addr);

	//set read/write
	if (mread == write){
		REG_TWI0_MMR &= ~TWI_MMR_MREAD;
	}
	else if (mread == read){
		REG_TWI0_MMR |= TWI_MMR_MREAD;
		REG_TWI0_CR |= TWI_CR_START;
	}



 }

 uint8_t i2c_readNACK(){

	uint8_t readData;

	//SAM4 series requires the stop bit to be sent before data is set
	i2c_stop();

	//wait until data arrives
	while(!(REG_TWI0_SR & TWI_SR_RXRDY));

	//read the received data and store it
	readData = REG_TWI0_RHR;

	while (!(REG_TWI0_SR & TWI_SR_TXCOMP));
	return readData;
 }

 uint8_t i2c_readACK(){

	uint8_t readData;

	//wait until data arrives
	while(!(REG_TWI0_SR & TWI_SR_RXRDY));

	//read the received data and store it
	readData = REG_TWI0_RHR;

	return readData;
 }

 void i2c_write(uint8_t data){

	//send data or register address
	REG_TWI0_THR |= data;

	//wait fro acknowledge
	while(!(REG_TWI0_SR & TWI_SR_TXRDY));
 }

 void i2c_writeStop(uint8_t data){

	//send data or register address
	REG_TWI0_THR |= data;

	//wait for acknowledge
	while(!(REG_TWI0_SR & TWI_SR_TXRDY));

	//send stop bit before data is written
	i2c_stop();

	while(!(REG_TWI0_SR & TWI_SR_TXCOMP));
 }


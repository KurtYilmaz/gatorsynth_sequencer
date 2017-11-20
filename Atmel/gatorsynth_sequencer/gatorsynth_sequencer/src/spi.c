/*
 * spi.c
 *
 * Created: 10/1/2017 12:16:35 AM
 *  Author: Kyle
 */ 

  #include <asf.h>
  #include <stdbool.h>

 void SPI_modeSelect(uint8_t mode){	
    /*
    Mode		CPOL	NCPHA
    Mode0		0		1
    Mode1		0		0
    Mode2		1		1
    Mode3		1		0
    */
    if (mode == 0){
        REG_SPI_CSR &= ~SPI_CSR_CPOL;
        REG_SPI_CSR |= SPI_CSR_NCPHA;
    }
    else if (mode == 1){
        REG_SPI_CSR &= ~SPI_CSR_CPOL;
        REG_SPI_CSR &= ~SPI_CSR_NCPHA;
    }
    else if (mode == 2){
        REG_SPI_CSR |= SPI_CSR_CPOL;
        REG_SPI_CSR |= SPI_CSR_NCPHA;
    }
    else if (mode == 3){
        REG_SPI_CSR |= SPI_CSR_CPOL;
        REG_SPI_CSR &= ~SPI_CSR_NCPHA;
    }
}

void SPI_led_init(){

	//enable peripheral clock
	REG_PMC_PCER0 |= PMC_PCER0_PID21;

	//set spi master mode
	REG_SPI_MR |= SPI_MR_MSTR;

	//set fixed peripheral select(peripheral chosen in SP_MR.PCS instead of SPI_THR.PCS)
	REG_SPI_MR &= ~SPI_MR_PS;
	//REG_SPI_MR |= SPI_MR_PCS(0b1110);

	//set polarity and clock phase to rising edge sample, falling edge shift
	SPI_modeSelect(0);

	//set clock generator (1 = peripheral clock rate), otherwise a divisor
	//SCBR = fperipheral clock / SPCK Bit Rate
	REG_SPI_CSR |= SPI_CSR_SCBR(5);

	//chip select remains low after transfer
	//REG_SPI_CSR |= SPI_CSR_CSNAAT;

	//give peripheral control of pins 
	REG_PIOA_PDR |= PIO_PDR_P11; //NPCS0
	REG_PIOA_PDR |= PIO_PDR_P13; //MOSI
	REG_PIOA_PDR |= PIO_PDR_P14; //SSCK

	//enable SPI
	REG_SPI_CR |= SPI_CR_SPIEN;


}

void SPI_dac_init(){

	//Chip Selects for the DACs / CVs
	REG_PIOB_PER |= PIO_PER_P13; //enable PIO controller on PB13
	REG_PIOB_OER |= PIO_PER_P13; //enable output on pin PB13
	REG_PIOB_SODR |=  PIO_PER_P13;

	REG_PIOB_PER |= PIO_PER_P14; //enable PIO controller on PB14
	REG_PIOB_OER |= PIO_PER_P14; //enable output on pin PB14
	REG_PIOB_SODR |=  PIO_PER_P14;

	//Outputs for the Gates
	REG_PIOB_PER |= PIO_PER_P0; //enable PIO controller on PB13
	REG_PIOB_OER |= PIO_PER_P0; //enable output on pin PB13
	REG_PIOB_SODR |=  PIO_PER_P0;

	REG_PIOB_PER |= PIO_PER_P1; //enable PIO controller on PB13
	REG_PIOB_OER |= PIO_PER_P1; //enable output on pin PB13
	REG_PIOB_SODR |=  PIO_PER_P1;

	REG_PIOB_PER |= PIO_PER_P2; //enable PIO controller on PB13
	REG_PIOB_OER |= PIO_PER_P2; //enable output on pin PB13
	REG_PIOB_SODR |=  PIO_PER_P2;

	REG_PIOB_PER |= PIO_PER_P3; //enable PIO controller on PB13
	REG_PIOB_OER |= PIO_PER_P3; //enable output on pin PB13
	REG_PIOB_SODR |=  PIO_PER_P3;

	//enable peripheral clock
	REG_PMC_PCER0 |= PMC_PCER0_PID21;

	//set spi master mode
	REG_SPI_MR |= SPI_MR_MSTR;

	//set fixed peripheral select(peripheral chosen in SP_MR.PCS instead of SPI_THR.PCS)
	REG_SPI_MR &= ~SPI_MR_PS;
	//REG_SPI_MR |= SPI_MR_PCS(0b1101);

	//set polarity and clock phase to rising edge sample, falling edge shift
	SPI_modeSelect(0);

	//set clock generator (1 = peripheral clock rate), otherwise a divisor
	//SCBR = fperipheral clock / SPCK Bit Rate
	REG_SPI_CSR |= SPI_CSR_SCBR(20);

	//chip select remains low after transfer
	//REG_SPI_CSR |= SPI_CSR_CSNAAT;

	//give peripheral control of pins
	REG_PIOA_PDR |= PIO_PDR_P11; //NPCS1
	REG_PIOA_PDR |= PIO_PDR_P13; //MOSI
	REG_PIOA_PDR |= PIO_PDR_P14; //SSCK

	//enable SPI
	REG_SPI_CR |= SPI_CR_SPIEN;


}

void SPI_byteSend(uint8_t data){
	//wait for transmit register to be empty
	while (!(REG_SPI_SR & SPI_SR_TDRE));
	//send data to transmit register
	REG_SPI_TDR |= (data);
}

// void SPI_dac_load(){
// 
// 	//wait for transmit register to be empty
// 	while (!(REG_SPI_SR & SPI_SR_TDRE));
// 
// 	//Pulse LOAD
// 	REG_PIOB_CODR |= PIO_PER_P13; //set output low on PB14
// 	delay_us(1);
// 	REG_PIOB_SODR |= PIO_PER_P13; //set output high on PB14
// 
// 	//Pulse LDAC
// 	REG_PIOB_CODR |= PIO_PER_P14; //set output low on PB14
// 	delay_us(1);
// 	REG_PIOB_SODR |= PIO_PER_P14; //set output high on PB14
// 
// }	
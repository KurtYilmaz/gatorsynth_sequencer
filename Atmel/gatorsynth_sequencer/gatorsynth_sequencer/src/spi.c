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

void SPI_init(){


	//enable peripheral clock
	REG_PMC_PCER0 |= PMC_PCER0_PID21;
	//set spi master mode
	REG_SPI_MR |= SPI_MR_MSTR;
	//set fixed peripheral select(peripheral chosen in SP_MR.PCS instead of SPI_THR.PCS)
	REG_SPI_MR &= ~SPI_MR_PS;
	//set polarity and clock phase to rising edge sample, falling edge shift
	SPI_modeSelect(0);
	//set clock generator (1 = peripheral clock rate), otherwise a divisor
	//SCBR = fperipheral clock / SPCK Bit Rate
	REG_SPI_CSR |= SPI_CSR_SCBR(5);
	//chip select remains low after transfer
	REG_SPI_CSR |= SPI_CSR_CSNAAT;
	//give peripheral control of pins (Chip select pins are optional)
	REG_PIOA_PDR |= PIO_PDR_P11; //NPCS0
	//REG_PIOA_PDR |= PIO_PDR_P31; //NPCS1
	//REG_PIOA_PDR |= PIO_PDR_P12; //MISO
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
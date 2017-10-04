#include "sam.h"

void SPI_modeSelect(uint8_t mode){

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
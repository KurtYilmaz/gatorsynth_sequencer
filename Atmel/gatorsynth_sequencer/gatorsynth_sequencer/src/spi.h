 #include <asf.h>
 #include <stdbool.h>

#ifndef SPI_H_
#define SPI_H_

void SPI_modeSelect(uint8_t mode);

void SPI_init(void);

void SPI_byteSend(uint8_t data);


#endif /* SPI_H_ */
/*
 * flash_mem.h
 *
 * Created: 11/27/2017 4:23:04 PM
 *  Author: Kyle
 */ 


#ifndef FLASH_MEM_H_
#define FLASH_MEM_H_

void flash_write_mem(uint32_t TEST_PAGE_ADDRESS);
void pattern_mem_read(uint32_t TEST_PAGE_ADDRESS);

#endif /* FLASH_MEM_H_ */
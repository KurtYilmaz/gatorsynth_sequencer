/*
 * flash_mem.c
 *
 * Created: 11/27/2017 4:16:43 PM
 *  Author: Kyle
 */ 
 /**
 * \file
 *
 * \brief Flash program example for SAM.
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

/**
 * \mainpage Flash Program Example
 *
 * \section Purpose
 *
 * This basic example shows how to use the Flash service available on the Atmel
 * SAM microcontrollers. It details steps required to program the internal
 * flash, and manage secure and lock bits.
 *
 * \section Requirements
 *
 * This package can be used with SAM evaluation kits.
 *
 * \section Description
 *
 * The program performs the following set of commands:
 * - Unlock the test page.
 * - Program the test page of the embedded flash with walking bit pattern (0x1,
 * 0x2, 0x4, ...).
 * - Check if the flash is correctly programmed by reading all the values
 * programmed.
 * - Lock the test page and check if it has been locked correctly.
 * - Set the security bit.
 *
 * The SAM MCU features a security bit, based on a specific General Purpose
 * NVM bit 0. When the security bit is enabled, any access to the Flash, SRAM,
 * Core Registers and Internal Peripherals through the ICE interface is
 * forbidden.
 * This example will reproduce this scene.
 *
 * The SAM MCU ROM code embeds small In-Application Programming (IAP) Procedure.
 * Since this function is executed from ROM, this allows Flash programming
 * (such as sector write) to be done when code is running out of Flash.
 * We will use IAP function by default in flash driver.
 *
 * Using Atmel Studio or Segger to debug, to be able to correctly watch the changes 
 * in the flash through the Memory view or through Segger J-Mem, caching needs to 
 * be disabled. This can be done in the Tool tab in the Project Properties 
 * in Atmel Studio. We also need to place a breakpoint in the flash_write function 
 * then do a Step Out to see the changes, otherwise stopping the program execution 
 * anywhere just shows 0xFFs instead of the walking pattern. 
 * \section Usage
 *
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
	-- Flash Program Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	-I- Unlocking test page
	-I- Writing test page with walking bit pattern
	-I- Checking page contents  ......................................... ok
	-I- Locking test page
	-I- Try to program the locked page...
	-I- Please open Segger's JMem program
	-I- Read memory at address 0xxxxxxxxx to check contents
	-I- Press any key to continue...
	-I- Good job!
	-I- Now set the security bit
	-I- Press any key to continue to see what happened...
	-I- Setting security bit
	-I- All tests done
\endcode
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include "asf.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "notes.h"
#include "flash_mem.h"


uint32_t ul_rc;
uint32_t ul_idx;
uint8_t uc_key;
uint32_t ul_page_buffer[64*IFLASH_PAGE_SIZE / sizeof(uint32_t)];

typedef unsigned long UL;

/*#define TEST_PAGE_ADDRESS 0x004FF800;*/

/**
 * Perform initialization and tests on flash.
 */
void flash_write_mem(uint32_t TEST_PAGE_ADDRESS){
	
	uint32_t ul_test_page_addr = TEST_PAGE_ADDRESS;
	uint32_t *pul_test_page = (uint32_t *) ul_test_page_addr;

	/* Initialize flash: 6 wait states for flash writing. */
	ul_rc = flash_init(FLASH_ACCESS_MODE_128, 6);
	if (ul_rc != FLASH_RC_OK) {
		//printf("-F- Initialization error %lu\n\r", (UL)ul_rc);
		//return 0;
	}

	/* Unlock page */
	//printf("-I- Unlocking test page: 0x%08x\r\n", ul_test_page_addr);
	ul_rc = flash_unlock(ul_test_page_addr,
			ul_test_page_addr +64*IFLASH_PAGE_SIZE - 1, 0, 0);
	if (ul_rc != FLASH_RC_OK) {
		//printf("-F- Unlock error %lu\n\r", (UL)ul_rc);
		//return 0;
	}

	uint32_t test = 0;
	/* Write page */
	//printf("-I- Writing test page with walking bit pattern\n\r");
// 	for (ul_idx = 0; ul_idx < (64*IFLASH_PAGE_SIZE / 4); ul_idx++) {
// 		ul_page_buffer[ul_idx] = test++;
// 	}

	ul_idx = 0;
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 16; j++){
			for (int k = 0; k < 16; k++){
				for (int m = 0; m < 2; m++){
					ul_page_buffer[ul_idx] = patterns[i][j][k][m];
					ul_idx++;
				}
			}
		}
	}

#if (SAM4S || SAM4E || SAM4N || SAM4C || SAM4CP || SAMG || SAM4CM || \
	 SAMV71 || SAMV70 || SAMS70 || SAME70)
	/* The EWP command is not supported for non-8KByte sectors in all devices
	 *  SAM4 series, so an erase command is requried before the write operation.
	 */
	
	ul_rc = flash_erase_sector(ul_test_page_addr);

	if (ul_rc != FLASH_RC_OK) {
		//printf("-F- Flash programming error %lu\n\r", (UL)ul_rc);
		//return 0;
	}


	ul_rc = flash_write(ul_test_page_addr, ul_page_buffer,
			64*IFLASH_PAGE_SIZE, 0);

#else
	
#endif
	if (ul_rc != FLASH_RC_OK) {
		//printf("-F- Flash programming error %lu\n\r", (UL)ul_rc);
		//return 0;
	}

	/* Validate page */
	for (ul_idx = 0; ul_idx < (64*IFLASH_PAGE_SIZE / 4); ul_idx++) {
		//printf(".");
		if (pul_test_page[ul_idx] != ul_page_buffer[ul_idx]) {
			//printf("\n\r-F- data error\n\r");
			//return 0;
		}
	}
// 	
// *pul_test_page = (uint32_t *) ul_test_page_addr;
// for (int i = 0; i < 16; i++){
// 				test_array[i][0] = *(pul_test_page);
// 				pul_test_page++;
// 				test_array[i][1] = *(pul_test_page);
// 				pul_test_page++;
// 	}
	/* Lock page */
	//printf("-I- Locking test page\n\r");
	ul_rc = flash_lock(ul_test_page_addr,
			ul_test_page_addr + 64*IFLASH_PAGE_SIZE - 1, 0, 0);
	if (ul_rc != FLASH_RC_OK) {
		//printf("-F- Flash locking error %lu\n\r", (UL)ul_rc);
		//return 0;
	}

	

	/* Check if the associated region is locked. */
	//printf("-I- Try to program the locked page ...\n\r");
// 	ul_rc = flash_write(ul_test_page_addr, ul_page_buffer,
// 			IFLASH_PAGE_SIZE,
// #if (SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP || SAM4CM || \
// 	 SAMV71 || SAMV70 || SAMS70 || SAME70)
// 			0);
// #else
// 			1);
// #endif
// 	if (ul_rc != FLASH_RC_OK) {
// 		//printf("-I- The page to be programmed belongs to locked region. Error %lu\n\r",
// 				//(UL)ul_rc);
// 	}

	//return 1;

}

void pattern_mem_read(uint32_t TEST_PAGE_ADDRESS){

	uint32_t ul_test_page_addr = TEST_PAGE_ADDRESS;
	uint32_t *pul_test_page = (uint32_t *) ul_test_page_addr;
	uint32_t ul_idx;

	
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 16; j++){
			for (int k = 0; k < 16; k++){
				for (int m = 0; m < 2; m++){
					patterns[i][j][k][m] = *pul_test_page;
					pul_test_page++;
				}
			}
		}
	}


}	

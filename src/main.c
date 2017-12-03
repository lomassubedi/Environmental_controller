#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stm32f0xx.h"
#include "stm32f0xx_it.h"

#include "stm32f0xx_tim.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"
//#include "stm32f0xx_rtc.h"
//#include "stm32f0xx_pwr.h"
#include "stm32f0xx_spi.h"

#include "flags_timers.h"
#include "reg_list.h"
#include "stm32f0_discovery.h"

#include "modbus_slave.h"
#include "RTC_STM.h"
#include "eeprom_data.h"
#include "util_usart.h"
#include "iso_i2c_ee.h"

#include "ff.h"

FATFS FatFs;
FIL logfile;

GPIO_InitTypeDef GPIO_InitStructure;

static __IO uint32_t TimingDelay;

struct __FILE {
    int dummy;
};

FILE __stdout;

extern void Delay(__IO uint32_t nTime) {
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

extern void TimingDelay_Decrement(void) {
  if (TimingDelay != 0x00) {
    TimingDelay--;
  }
}

int main(void) {
	
	uint8_t buffer[] = "Hello There SD card !!\r\n";
  uint32_t drive_size;
	
//	uint8_t flag_EEPROM_status;
	
	FRESULT rc;
	
	SysTick_Config(SystemCoreClock / 1000);
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	
	init_usart2();
	init_modbus();
	RTC_Config_LSI();
	I2C_EEPROM_24C0x_Init();
	
	printf("STM32F051 SD CARD TEST !!! \r\n");
	
	
	/*
	sEE_ReadBuffer(&flag_EEPROM_status, ADDRESS_EPRM_STATUS_FLAG, BYTES_EEPRM_STATUS_FLAG);
//	flag_EEPROM_status = 0;
	if(flag_EEPROM_status != 1) { // Data not written
		// Write Tools Default value
		I2C_EEPROM_24C0x_WriteStructTools(tools, EEPROM_ADDRESS_TOOLS, TOOLS_SIZE);
		
		// Write profile 1 default data
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_1, PROFILE_SIZE);
		
		// Write profile 2 default data
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_2, PROFILE_SIZE);
		
		// Write profile 3 default data 
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_3, PROFILE_SIZE);
		
		// Write the flag status so as to indicate that default data has been already written to EEPROM
		flag_EEPROM_status = 1;
		sEE_WriteBuffer(&flag_EEPROM_status, ADDRESS_EPRM_STATUS_FLAG, BYTES_EEPRM_STATUS_FLAG);
		
		printf("Written default tools and profile values to EEPROM.\r\n");
	} else {
		printf("Default data already available at EEPROM.\r\n");
	}	
	
	spi2_send(buffrSPI, sizeof(buffrSPI));
	*/
    rc = f_mount(&FatFs, "", 1);
    if(rc == FR_OK) {
        rc = f_open(&logfile, "log2.txt", FA_WRITE | FA_CREATE_ALWAYS);
        if(rc == FR_OK){
            f_printf(&logfile, "Hello there STM what you doing. I am keil??!!\r\n");
            f_close(&logfile);
        }
    }
		
  while (1) {
//		modbus_update();
	}	
}

#include <stdint.h>
#include <stdio.h>
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"

#include "stm32f0xx_tim.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"
//#include "stm32f0xx_rtc.h"
//#include "stm32f0xx_pwr.h"

#include "flags_timers.h"
#include "reg_list.h"
#include "stm32f0_discovery.h"

#include "modbus_slave.h"
#include "RTC_STM.h"
#include "eeprom_data.h"
#include "util_usart.h"
#include "iso_i2c_ee.h"

#define 		TMP_BUFFER_SIZE			200
uint8_t buffr[TMP_BUFFER_SIZE];

GPIO_InitTypeDef GPIO_InitStructure;

static __IO uint32_t TimingDelay;

//#define LEDToggleValue ((uint16_t) 3000)

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

//uint8_t write_buffr_eprm[] = "Hi lomas this is the data to write into an EEPROM !\r\n";
uint8_t read_buffr_eprm[100];

//uint16_t size_profile = 100;
//const uint8_t* ptrProfile = ((const uint8_t*)(const void*)&profile2);

//uint8_t* ptrProfileRx = (uint8_t*)(void * )&profile1;

int main(void) {
//	int ctr = 0;
//	RTC_TimeTypeDef myRTCTime;
//	RTC_DateTypeDef myRTCDate;
	
	SysTick_Config(SystemCoreClock / 1000);
	
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	
	init_usart2();
	
	init_modbus();
	
	RTC_Config_LSI();
	
	tmrHdVLCSrtDly.HH = 7;
	tmrHdVLCSrtDly.MM = 52;
	tmrHdVLCSrtDly.SS = 0;

	I2C_EEPROM_24C0x_Init();
	
	// Test -- Copy Profile 2 data to profile 1 ----
	I2C_EEPROM_24C0x_WriteStructProfile(profile, 0x00, 10);
	I2C_EEPROM_24C0x_ReadStructProfile(profile, 0x00, 10);
	

	printf("Read Profile values : %d\t%d\t%d\t%d\t%d\t%d\t%d\r\n", \
					
					profile->Ad1_Light_Operation_Mode,
					
					profile->Ad1_Light_OnTime.HH,
					profile->Ad1_Light_OnTime.MM,
					profile->Ad1_Light_OnTime.SS,
					
					profile->Ad1_Light_OffTime.HH,
					profile->Ad1_Light_OffTime.MM,
					profile->Ad1_Light_OffTime.SS
					
					);

  while (1) {
		
		if(flagLEDIndi) {
			flagLEDIndi = 0;
			STM_EVAL_LEDToggle(LED3);
		}
	}
}

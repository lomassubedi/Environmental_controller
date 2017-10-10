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


int main(void) {
	
	RTC_TimeTypeDef myRTCTime;
	RTC_DateTypeDef myRTCDate;
	
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
  I2C_EEPROM_24C0x_WriteAndRead();
	
  while (1) {
		
		if(flagLEDIndi) {
			flagLEDIndi = 0;
			STM_EVAL_LEDToggle(LED3);
		}
	}
}

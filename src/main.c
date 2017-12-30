#include "config.h"
#include "flags_timers.h"
#include "modbus_slave.h"
#include "RTC_STM.h"
#include "eeprom_data.h"
#include "util_usart.h"
#include "iso_i2c_ee.h"
#include "sdlog.h"
#include "diskio.h"

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
		
	SysTick_Config(SystemCoreClock / 1000);	
	
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);	
	
	init_pushbtn();
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
	
	ADC_Config();
	
	init_usart2();
	init_modbus();	
	
	RTC_Config_LSI();		
	
	init_sd();
//	read_file();
//	init_spi();
//	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
//	GPIOA->PUPDR |= (1 << (1 << 12));
  while (1) {
				
//		modbus_update();		
//			if((GPIOA->IDR & (1 << 12))) {
//				STM_EVAL_LEDOn(LED3);
//			} else {
//				STM_EVAL_LEDOff(LED3);
//			}		
	
	}	
}

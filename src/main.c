#include "config.h"
#include "flags_timers.h"
#include "modbus_slave.h"
#include "RTC_STM.h"
#include "eeprom_data.h"
#include "util_usart.h"
#include "iso_i2c_ee.h"
#include "sdlog.h"
#include "diskio.h"

struct __FILE {
    int dummy;
};

FILE __stdout;

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
		
  while (1) {
				
		modbus_update();	
	
	}	
}

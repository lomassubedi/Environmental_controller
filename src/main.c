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
	RTC_TimeTypeDef myRTCTime;
	RTC_DateTypeDef myRTCDate;
		
	SysTick_Config(SystemCoreClock / 1000);	
	
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);	
	
	init_pushbtn();
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
	
	ADC_Config();
	
	init_usart2();
	init_modbus();	
	
	RTC_Config_LSE();
	
	init_sd();
		
  while (1) {
				
		modbus_update();	
		
		if(flagLEDIndi) {
			
			flagLEDIndi = 0;
			STM_EVAL_LEDToggle(LED3);
			RTC_GetTime(RTC_Format_BIN, &myRTCTime);
			RTC_GetDate(RTC_Format_BIN, &myRTCDate);
			#if 1
				printf("Year: %d, \tMonth: %d, \tDay: %d, \t", (myRTCDate.RTC_Year + 2000), myRTCDate.RTC_Month, myRTCDate.RTC_Date);
				printf("Hour: %d, \tMinute: %d, \tSec: %d\r\n", myRTCTime.RTC_Hours, myRTCTime.RTC_Minutes, myRTCTime.RTC_Seconds);							
			#endif
		}					
	}	
}

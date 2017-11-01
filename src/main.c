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

// Currently EEPROM data is 496 Bytes
#define 		SIZE_EEPROM_DATA		1024
uint8_t tmeEEPBuffr[SIZE_EEPROM_DATA];

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
	int ctr = 0;
	uint8_t flag_EEPROM_status;
	
	extern PROFILE dummyInitProfile;
	extern TOOLS dummyInitTools;
	
//	uint8_t readBuffr[PROFILE_SIZE];
	
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
	
	sEE_ReadBuffer(&flag_EEPROM_status, ADDRESS_EPRM_STATUS_FLAG, BYTES_EEPRM_STATUS_FLAG);
//	flag_EEPROM_status = 0;
	if(flag_EEPROM_status != 1) { // Data not written
//			profile = &dummyInitProfile;
//			tools = &dummyInitTools;
		// Write Tools Default value
		I2C_EEPROM_24C0x_WriteStructTools(tools, EEPROM_ADDRESS_TOOLS, TOOLS_SIZE);
		
		// Write profile 1 default data
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_1, PROFILE_SIZE);
		
		
		// Write profile 2 default data
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_2, PROFILE_SIZE);
		
		
		// Write profile 3 default data 
		profile->Ad1_HdV_DeH_DC_OffHum = 70.3458;
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_3, PROFILE_SIZE);
		
		/*
		// Write profile 4 default data
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_4, PROFILE_SIZE);
		
		// Write profile 5 default data
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_5, PROFILE_SIZE);
		
		// Write profile 6 default data 
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_6, PROFILE_SIZE);
		
		// Write profile 7 default data
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_7, PROFILE_SIZE);
		
		// Write profile 8 default data
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_8, PROFILE_SIZE);
		
		// Write profile 9 default data 
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_9, PROFILE_SIZE);
		
		// Write profile 10 default data 
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_10, PROFILE_SIZE);
		*/
		// Write the flag status so as to indicate that default data has been already written to EEPROM
		flag_EEPROM_status = 1;
		sEE_WriteBuffer(&flag_EEPROM_status, ADDRESS_EPRM_STATUS_FLAG, BYTES_EEPRM_STATUS_FLAG);
		
		printf("Written default tools and profile values to EEPROM.\r\n");
	} else {
		printf("Default data already available at EEPROM.\r\n");
	}
	
	I2C_EEPROM_24C0x_ReadStructTools(tools, EEPROM_ADDRESS_TOOLS, TOOLS_SIZE);
	I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_2, PROFILE_SIZE);
	

	printf("Read Profile values : %d\t %d:%d:%d \t%d:%d:%d\t %d:%d:%d\t %f\t %f\t%d\r\n", \
					
					profile->Ad1_Light_Operation_Mode,
					
					profile->Ad1_Light_OnTime.HH,
					profile->Ad1_Light_OnTime.MM,
					profile->Ad1_Light_OnTime.SS,
					
					profile->Ad1_Light_OffTime.HH,
					profile->Ad1_Light_OffTime.MM,
					profile->Ad1_Light_OffTime.SS,
					
					profile->Ad1_Light_LC_Duration.HH,
					profile->Ad1_Light_LC_Duration.MM,
					profile->Ad1_Light_LC_Duration.SS,
					
					profile->Ad1_HdV_DeH_DC_OffHum,
					
					profile->Ad1_HdV_DeH_DC_OnHum,
					
					profile->Ad1_FXP2_Tmr_LC_RptAftr.MM
					);
					
		printf("Tools values : %f\r\n", tools->Ad1_Tools_HiTemp_Warning_StPt);
		
		profile->Ad1_HdV_DeH_DC_OffHum = 20.3458;
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_2, PROFILE_SIZE);
		

  while (1) {
		modbus_update();
//		printf("Hello World !!\r\n");
//		printf("var_code_Ad1_Tools_HiHum_Warning_StPt number = %d\r\n", var_code_Ad1_Tools_HiHum_Warning_StPt);
//		Delay(1000);
//		if(flagLEDIndi) {
//			flagLEDIndi = 0;
//			STM_EVAL_LEDToggle(LED3);
//		}
	}
}

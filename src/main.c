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
	
	if(flag_EEPROM_status != 1) { // Data not written
		
		// Write Tools Default value
		I2C_EEPROM_24C0x_WriteStructTools(tools, EEPROM_ADDRESS_TOOLS, TOOLS_SIZE);
		
		// Write profile 1 default data
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_1, PROFILE_SIZE);
		
		// Write profile 2 default data
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_2, PROFILE_SIZE);
		
		// Write profile 3 default data 
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_3, PROFILE_SIZE);
		
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
		
		flag_EEPROM_status = 1;
		sEE_WriteBuffer(&flag_EEPROM_status, ADDRESS_EPRM_STATUS_FLAG, BYTES_EEPRM_STATUS_FLAG);
		
		printf("Written default tools and profile value to EEPROM.\r\n");
	} else {
		printf("Default data already available at EEPROM.\r\n");
	}
	
	
	/* If no data is written to EEPROM, write default data */
	

//	I2C_EEPROM_24C0x_WriteStructTools(tools, EEPROM_ADDRESS_TOOLS, TOOLS_SIZE);
	
//	profile->Ad1_FXP2_Co2_Gen_OffPPM = 5000;
//	
//	I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_1, PROFILE_SIZE);
//	
//	profile->Ad1_FXP2_Co2_Gen_OffPPM = 1200;
//	I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_2, PROFILE_SIZE);
//	
//	I2C_EEPROM_24C0x_ReadStructTools(tools, EEPROM_ADDRESS_TOOLS, TOOLS_SIZE);
//	printf("This is a tools data i.e. Ad1_Tools_Critical_OverTemp_StPt = %f\r\n", tools->Ad1_Tools_Critical_OverTemp_StPt);
//	
//	I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_1, PROFILE_SIZE);
//	printf("This is a profile data i.e. Ad1_FXP2_Co2_Gen_OffPPM = %d\r\n", profile->Ad1_FXP2_Co2_Gen_OffPPM);

//		printf("Profile 1 address : %d\r\n", EEPROM_ADDRESS_PROFILE_1);
//		printf("Profile 2 address : %d\r\n", EEPROM_ADDRESS_PROFILE_2);
//		printf("Profile 3 address : %d\r\n", EEPROM_ADDRESS_PROFILE_3);
//		printf("Profile 4 address : %d\r\n", EEPROM_ADDRESS_PROFILE_4);
//		printf("Profile 5 address : %d\r\n", EEPROM_ADDRESS_PROFILE_5);
//		printf("Profile 6 address : %d\r\n", EEPROM_ADDRESS_PROFILE_6);
//		printf("Profile 7 address : %d\r\n", EEPROM_ADDRESS_PROFILE_7);
//		printf("Profile 8 address : %d\r\n", EEPROM_ADDRESS_PROFILE_8);
//		printf("Profile 9 address : %d\r\n", EEPROM_ADDRESS_PROFILE_9);
//		printf("Profile 10 address : %d\r\n", EEPROM_ADDRESS_PROFILE_10);
//		printf("Profile 11 address : %d\r\n", EEPROM_ADDRESS_PROFILE_11);
//		printf("Profile 12 address : %d\r\n", EEPROM_ADDRESS_PROFILE_12);
//		printf("Profile 13 address : %d\r\n", EEPROM_ADDRESS_PROFILE_13);
//		printf("Profile 14 address : %d\r\n", EEPROM_ADDRESS_PROFILE_14);
//		printf("Profile 15 address : %d\r\n", EEPROM_ADDRESS_PROFILE_15);
//		printf("Profile 16 address : %d\r\n", EEPROM_ADDRESS_PROFILE_16);
//		printf("Profile 17 address : %d\r\n", EEPROM_ADDRESS_PROFILE_17);
//		printf("Profile 18 address : %d\r\n", EEPROM_ADDRESS_PROFILE_18);
//		printf("Profile 19 address : %d\r\n", EEPROM_ADDRESS_PROFILE_19);
//		printf("Profile 20 address : %d\r\n", EEPROM_ADDRESS_PROFILE_20);

//	sEE_ReadBuffer(tmeEEPBuffr, 0x00, SIZE_EEPROM_DATA);
	
	
//	I2C_EEPROM_24C0x_ReadStructProfile(testProfile, 0x00, 700);

/*
for(ctr = 0; ctr < SIZE_EEPROM_DATA; ctr++) {
	usart2_putchar(tmeEEPBuffr[ctr]);
	}
*/
		
//		sEE_ReadBuffer(tmeEEPBuffr, SIZE_EEPROM_DATA+1, SIZE_EEPROM_DATA);
//		printf("\r\n\r\n");
//	
//	for(ctr = 0; ctr < (SIZE_EEPROM_DATA); ctr++) {
//		usart2_putchar(tmeEEPBuffr[ctr]);
//	}

/*
printf("\r\n");
	

printf("Read Profile values : %d\t %d:%d:%d \t%d:%d:%d\t %d:%d:%d\t %f\t %f\t%d\r\n", \
					
					testProfile->Ad1_Light_Operation_Mode,
					
					testProfile->Ad1_Light_OnTime.HH,
					testProfile->Ad1_Light_OnTime.MM,
					testProfile->Ad1_Light_OnTime.SS,
					
					testProfile->Ad1_Light_OffTime.HH,
					testProfile->Ad1_Light_OffTime.MM,
					testProfile->Ad1_Light_OffTime.SS,
					
					testProfile->Ad1_Light_LC_Duration.HH,
					testProfile->Ad1_Light_LC_Duration.MM,
					testProfile->Ad1_Light_LC_Duration.SS,
					
					testProfile->Ad1_HdV_DeH_DC_OffHum,
					
					testProfile->Ad1_HdV_DeH_DC_OnHum,
					
					testProfile->Ad1_FXP2_Tmr_LC_RptAftr.MM

					);
*/
  while (1) {
		
		if(flagLEDIndi) {
			flagLEDIndi = 0;
			STM_EVAL_LEDToggle(LED3);
		}
	}
}

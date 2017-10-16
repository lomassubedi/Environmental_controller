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
#define 		SIZE_EEPROM_DATA		500
uint8_t tmeEEPBuffr[1000];

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
	PROFILE *testProfile;
	int ctr = 0;
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
	
	// Test -- Write a profile ----
	I2C_EEPROM_24C0x_WriteStructProfile(profile, 0x00, SIZE_EEPROM_DATA);
	
	// Write another profile again
	I2C_EEPROM_24C0x_WriteStructProfile(profile, SIZE_EEPROM_DATA+1, SIZE_EEPROM_DATA);
	
	sEE_ReadBuffer(tmeEEPBuffr, 0x00, SIZE_EEPROM_DATA);
//	printf("This is the size of a Profile %d\r\n", sizeof(PROFILE));
//	I2C_EEPROM_24C0x_ReadStructProfile(testProfile, 0x00, 700);

/*
for(ctr = 0; ctr < SIZE_EEPROM_DATA; ctr++) {
	usart2_putchar(tmeEEPBuffr[ctr]);
	}
*/
		
		sEE_ReadBuffer(tmeEEPBuffr, SIZE_EEPROM_DATA+1, SIZE_EEPROM_DATA);
		printf("\r\n\r\n");
	
	for(ctr = 0; ctr < (SIZE_EEPROM_DATA); ctr++) {
		usart2_putchar(tmeEEPBuffr[ctr]);
	}

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

#include "config.h"
#include "flags_timers.h"
#include "modbus_slave.h"
#include "RTC_STM.h"
#include "eeprom_data.h"
#include "util_usart.h"
#include "iso_i2c_ee.h"
#include "sdlog.h"
#include "diskio.h"

#include "setup.h"

struct __FILE {
    int dummy;
};

FILE __stdout;

void get_profile(uint8_t prof_num) {

	/* read the respective profile */
	switch(prof_num) {
		
		case PROFILE_NUMBER_1:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_1, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_2:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_2, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_3:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_3, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_4:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_4, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_5:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_5, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_6:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_6, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_7:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_7, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_8:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_8, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_9:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_9, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_10:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_10, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_11:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_11, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_12:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_12, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_13:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_13, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_14:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_14, PROFILE_SIZE);
			break;
		
		case PROFILE_NUMBER_15:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_15, PROFILE_SIZE);
			break;

		case PROFILE_NUMBER_16:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_16, PROFILE_SIZE);
			break;		
	
		case PROFILE_NUMBER_17:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_17, PROFILE_SIZE);
			break;
		
		case PROFILE_NUMBER_18:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_18, PROFILE_SIZE);
			break;
		
		case PROFILE_NUMBER_19:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_19, PROFILE_SIZE);
			break;
		
		case PROFILE_NUMBER_20:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_20, PROFILE_SIZE);
			break;		
	}	
}

int main(void) {
	RTC_TimeTypeDef myRTCTime;
	RTC_DateTypeDef myRTCDate;	
	
	/*--------------------------------------
	 * MCU POWER ON, INITIALIZE MCU,
	 * DECLARE VARIABLES, ETC. 
	 * ------------------------------------- */
	SysTick_Config(SystemCoreClock / 1000);	
	
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);	
	
	init_pushbtn();
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
	
	ADC_Config();
	
	init_usart2();
	
	init_modbus();	
	
	I2C_EEPROM_24C0x_Init();
	
	RTC_Config_LSE();
	
	init_sd();
	
	/* ----------------------------------------------- */
	if(!flagPowerUp) {				// Raise Power ON Flag
		flagPowerUp = YES;
	}
	
	// Get the Device turn ON Time and Date
	RTC_GetTime(RTC_Format_BIN, &myRTCTime);
	RTC_GetDate(RTC_Format_BIN, &myRTCDate);
	
	sEE_ReadBuffer(&active_profile, ADDRESS_EEPRM_CURRENT_PRF, sizeof(active_profile));
	
	// Only if the profile is valid !!
	if((active_profile > TOOLS_NUMBER) && (active_profile <= PROFILE_NUMBER_20)) {
		printf("Active profile: %d\r\n", active_profile);
	} else {
		printf("No active profile found set and the new active profile is 1.\r\n");
		active_profile = 1;	// Set active profile 
		sEE_WriteBuffer(&active_profile, ADDRESS_EEPRM_CURRENT_PRF, sizeof(active_profile));
	}	
	// Read the active profile data from an EEPROM
	get_profile(active_profile);
	
	initial_setup();
	
//	switch(profile->Ad1_Light_Operation_Mode) {
//		case ALWAYS_ON:
//			// Set "Current Cycle flag"
//			flagCurrentCycle = LIGHT;
//			flagAd1PreviousCycle = LIGHT;
//			flagCycleFlipToLightCycle = YES;			
//			break;
//		
//		case ALWAYS_OFF:
//			break;
//		
//	}
	
	
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

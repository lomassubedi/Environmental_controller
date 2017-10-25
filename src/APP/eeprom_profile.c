// File Name: eeprom_profile.c
// Author: Lomas
// Date 24 Oct 2017

#include "eeprom_profile.h"
#include <string.h>
#include <stddef.h>

// --------- Function defination for manipulation of EEPROM var
void eeprom_get_var(uint8_t profNum, uint8_t varCode, uint8_t * bytesCount, uint8_t * bytesArry) {
	volatile union {
    float floatVar;
    uint8_t floatArry[sizeof(float)];
  } floatVal;
	
//	uint8_t * base;
//	uint16_t offset = 0;
//	uint8_t * memAddr;
	
	switch(profNum) {
		
		// Read Tools value
		case TOOLS_NUMBER:
			
			I2C_EEPROM_24C0x_ReadStructTools(tools, EEPROM_ADDRESS_TOOLS, TOOLS_SIZE);
//			base = (uint8_t *)tools;
			switch(varCode) {
				
				case var_code_Ad1_DeviceType :
					bytesArry[0] = tools->Ad1_DeviceType;
					*bytesCount = 1;
					return;
					break;
				
				case var_code_Ad1_Tools_LoHum_Warning_StPt :
					
//					offset = offsetof(TOOLS, Ad1_Tools_LoHum_Warning_StPt);
//					memAddr = (uint8_t *)(base + offset);
				floatVal.floatVar = tools->Ad1_Tools_LoHum_Warning_StPt;
				
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
				
					return;
					break;
			}
//			printf("I am here !!\r\n");
			break;
		
		// Read profile 1 data
		case PROFILE_NUMBER_1:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_1, PROFILE_SIZE);
			
			switch(varCode) {
				case var_code_Ad1_Light_OnTime:
					bytesArry[0] = profile->Ad1_Light_OnTime.HH;
					bytesArry[1] = profile->Ad1_Light_OnTime.MM;
					bytesArry[2] = profile->Ad1_Light_OnTime.SS;
					*bytesCount = 3;
					return;
					break;
			}
			break;
		
		// Read profile 2 data
		case PROFILE_NUMBER_2:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_2, PROFILE_SIZE);
			break;
		
		// Read profile 3 data 
		case PROFILE_NUMBER_3:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_3, PROFILE_SIZE);
			break;
		
		// Read profile 4 data
		case PROFILE_NUMBER_4:
				I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_4, PROFILE_SIZE);
			break;
		
		// Read profile 5 data
		case PROFILE_NUMBER_5:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_5, PROFILE_SIZE);
			break;
		
		// Read profile 6 data
		case PROFILE_NUMBER_6:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_6, PROFILE_SIZE);
			break;
		
		// Read profile 7 data
		case PROFILE_NUMBER_7:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_7, PROFILE_SIZE);
			break;
		
		// Read profile 8 data
		case PROFILE_NUMBER_8:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_8, PROFILE_SIZE);
			break;
		
		// Read profile 9 data
		case PROFILE_NUMBER_9:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_9, PROFILE_SIZE);
			break;
		
		// Read profile 10 data
		case PROFILE_NUMBER_10:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_10, PROFILE_SIZE);
			break;		
		
		// Read profile 11 data
		case PROFILE_NUMBER_11:
			break;
		
		// Read profile 12 data
		case PROFILE_NUMBER_12:
			break;
		
		// Read profile 13 data
		case PROFILE_NUMBER_13:
			break;
		
		// Read profile 14 data
		case PROFILE_NUMBER_14:
			break;
		
		// Read profile 15 data
		case PROFILE_NUMBER_15:
			break;
		
		// Read profile 16 data
		case PROFILE_NUMBER_16:
			break;
		
		// Read profile 17 data
		case PROFILE_NUMBER_17:
			break;
		
		// Read profile 18 data
		case PROFILE_NUMBER_18:
			break;		
		
		// Read profile 19 data
		case PROFILE_NUMBER_19:
			break;
		
		// Read profile 20 data
		case PROFILE_NUMBER_20:
			break;
		
		default:
			break;
		
	}
}
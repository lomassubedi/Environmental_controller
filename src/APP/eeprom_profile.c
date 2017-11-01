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
	
	volatile union {
		uint16_t intVar;
		uint8_t intArry[sizeof(uint16_t)];
	} intVal;
	
	switch(profNum) {
		
		// Read Tools value
		case TOOLS_NUMBER:
			
			I2C_EEPROM_24C0x_ReadStructTools(tools, EEPROM_ADDRESS_TOOLS, TOOLS_SIZE);
		
			switch(varCode) {
				
				// Read var_code_Ad1_DeviceType
				case var_code_Ad1_DeviceType :
					bytesArry[0] = tools->Ad1_DeviceType;
					*bytesCount = 1;
					break;
				
				// Read Ad1_Tools_Units_EnglishMetric 
				case var_code_Ad1_Tools_Units_EnglishMetric :
					bytesArry[0] = tools->Ad1_Tools_Units_EnglishMetric;
					*bytesCount = sizeof(UNIT_S);
					break;
				
				case var_code_Ad1_Tools_Sensor_Fault :
					bytesArry[0] = tools->Ad1_Tools_Sensor_Fault;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Tools_ACFault_Message_YesNo :
					bytesArry[0] = tools->Ad1_Tools_ACFault_Message_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Tools_LoTemp_Warning_YesNo :
					bytesArry[0] = tools->Ad1_Tools_LoTemp_Warning_YesNo;
					*bytesCount = sizeof(BOOL);
					break;

				case var_code_Ad1_Tools_LoTemp_Warning_StPt :
					floatVal.floatVar = tools->Ad1_Tools_LoTemp_Warning_StPt;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Tools_HiTemp_Warning_YesNo : 
					bytesArry[0] = tools->Ad1_Tools_HiTemp_Warning_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				// Read Ad1_Tools_HiTemp_Warning_StPt
				case var_code_Ad1_Tools_HiTemp_Warning_StPt :
					floatVal.floatVar = tools->Ad1_Tools_HiTemp_Warning_StPt;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Tools_LoHum_Warning_YesNo :
					bytesArry[0] = tools->Ad1_Tools_LoHum_Warning_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				// Read Ad1_Tools_LoHum_Warning_StPt
				case var_code_Ad1_Tools_LoHum_Warning_StPt :
					floatVal.floatVar = tools->Ad1_Tools_LoHum_Warning_StPt;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Tools_HiHum_Warning_YesNo :
					bytesArry[0] = tools->Ad1_Tools_HiHum_Warning_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Tools_HiHum_Warning_StPt :
					floatVal.floatVar = tools->Ad1_Tools_HiHum_Warning_StPt;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Tools_Critical_OverTemp_Fault_YesNo :
					bytesArry[0] = tools->Ad1_Tools_Critical_OverTemp_Fault_YesNo;
					*bytesCount = sizeof(BOOL);
					break;

				case var_code_Ad1_Tools_Critical_OverTemp_Fault_Flag :
					bytesArry[0] = tools->Ad1_Tools_Critical_OverTemp_Fault_Flag;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Tools_Critical_OverTemp_StPt :
					floatVal.floatVar = tools->Ad1_Tools_Critical_OverTemp_StPt;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Tools_Critical_OverTemp_Response :
					bytesArry[0] = tools->Ad1_Tools_Critical_OverTemp_Response;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Tools_Critical_OverTemp_Message_YesNo :
					bytesArry[0] = tools->Ad1_Tools_Critical_OverTemp_Message_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Tools_ReStrike_Fault_YesNo :
					bytesArry[0] = tools->Ad1_Tools_ReStrike_Fault_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_Co2_CylGen :
					bytesArry[0] = tools->Ad1_Tools_ReStrike_Delay_Time.HH;
					bytesArry[1] = tools->Ad1_Tools_ReStrike_Delay_Time.MM;
					bytesArry[2] = tools->Ad1_Tools_ReStrike_Delay_Time.SS;
				 *bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Tools_ReStrike_Message_YesNo :
					bytesArry[0] = tools->Ad1_Tools_ReStrike_Message_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Tools_LoBat_Fault_Message_YesNo :
					bytesArry[0] = tools->Ad1_Tools_LoBat_Fault_Message_YesNo;
					*bytesCount = sizeof(BOOL);
					break;

				case var_code_Ad1_Tools_Batt_Current_Volt :
					floatVal.floatVar = tools->Ad1_Tools_Batt_Current_Volt;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;	
				
				case var_code_Ad1_Tools_Light_Relay_Cycle_Counter :
					intVal.intVar = tools->Ad1_Tools_Light_Relay_Cycle_Counter;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;	
				
				case var_code_Ad1_Tools_HdVent_Relay_Cycle_Counter :
					intVal.intVar = tools->Ad1_Tools_HdVent_Relay_Cycle_Counter;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;	
								
				case var_code_Ad1_Tools_Circ_Relay_Cycle_Counter :
					intVal.intVar = tools->Ad1_Tools_Circ_Relay_Cycle_Counter;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;	

				case var_code_Ad1_Tools_Vent_Relay_Cycle_Counter :
					intVal.intVar = tools->Ad1_Tools_Vent_Relay_Cycle_Counter;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;	

				case var_code_Ad1_Tools_FXP1_Relay_Cycle_Counter :
					intVal.intVar = tools->Ad1_Tools_FXP1_Relay_Cycle_Counter;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;	

				case var_code_Ad1_Tools_FXP2_Relay_Cycle_Counter :
					intVal.intVar = tools->Ad1_Tools_FXP2_Relay_Cycle_Counter;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;			
				
				case var_code_Ad1_Tools_Switch_YesNo : 
					bytesArry[0] = tools->Ad1_Tools_Switch_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Tools_HdVent_DC_DeAct_FactSet_Delay :
					bytesArry[0] = tools->Ad1_Tools_HdVent_DC_DeAct_FactSet_Delay.HH;
					bytesArry[1] = tools->Ad1_Tools_HdVent_DC_DeAct_FactSet_Delay.MM;
					bytesArry[2] = tools->Ad1_Tools_HdVent_DC_DeAct_FactSet_Delay.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Tools_CO2_PVA_PostVent_FactSet_Delay :
					bytesArry[0] = tools->Ad1_Tools_CO2_PVA_PostVent_FactSet_Delay.HH;
					bytesArry[1] = tools->Ad1_Tools_CO2_PVA_PostVent_FactSet_Delay.MM;
					bytesArry[2] = tools->Ad1_Tools_CO2_PVA_PostVent_FactSet_Delay.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Tools_LED_OnOff : 
					bytesArry[0] = tools->Ad1_Tools_LED_OnOff;
					*bytesCount = sizeof(BOOL);
					break;				
			}
			break;
		
		// Read profile 1 data
		case PROFILE_NUMBER_1:
			I2C_EEPROM_24C0x_ReadStructProfile(profile, EEPROM_ADDRESS_PROFILE_1, PROFILE_SIZE);
			
			switch(varCode) {

				case var_code_Ad1_Light_Operation_Mode :
					bytesArry[0] = profile->Ad1_Light_Operation_Mode;
					*bytesCount = sizeof(TRISTATE_OPERATION_MODE);
					break;
	
				case var_code_Ad1_Light_OnTime:
					bytesArry[0] = profile->Ad1_Light_OnTime.HH;
					bytesArry[1] = profile->Ad1_Light_OnTime.MM;
					bytesArry[2] = profile->Ad1_Light_OnTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
									
				case var_code_Ad1_Light_OffTime : 
					bytesArry[0] = profile->Ad1_Light_OffTime.HH;
					bytesArry[1] = profile->Ad1_Light_OffTime.MM;
					bytesArry[2] = profile->Ad1_Light_OffTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;

				case var_code_Ad1_Light_LC_Duration : 
					bytesArry[0] = profile->Ad1_Light_LC_Duration.HH;
					bytesArry[1] = profile->Ad1_Light_LC_Duration.MM;
					bytesArry[2] = profile->Ad1_Light_LC_Duration.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Light_DC_Duration :
					bytesArry[0] = profile->Ad1_Light_DC_Duration.HH;
					bytesArry[1] = profile->Ad1_Light_DC_Duration.MM;
					bytesArry[2] = profile->Ad1_Light_DC_Duration.SS;
					*bytesCount = sizeof(TIME_M);						
					break;
				
				case var_code_Ad1_Light_LC_TimeRemain : 
					bytesArry[0] = profile->Ad1_Light_LC_TimeRemain.HH;
					bytesArry[1] = profile->Ad1_Light_LC_TimeRemain.MM;
					bytesArry[2] = profile->Ad1_Light_LC_TimeRemain.SS;
					*bytesCount = sizeof(TIME_M);							
					break;
				
				case var_code_Ad1_Light_DC_TimeRemain : 
					bytesArry[0] = profile->Ad1_Light_DC_TimeRemain.HH;
					bytesArry[1] = profile->Ad1_Light_DC_TimeRemain.MM;
					bytesArry[2] = profile->Ad1_Light_DC_TimeRemain.SS;
					*bytesCount = sizeof(TIME_M);	
					break;
				
				case var_code_Ad1_HdV_OnOff : 
					bytesArry[0] = profile->Ad1_HdV_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_HdV_LC_OnOff : 
					bytesArry[0] = profile->Ad1_HdV_LC_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_HdV_LC_SrtDly : 
					bytesArry[0] = profile->Ad1_HdV_LC_SrtDly.HH;
					bytesArry[1] = profile->Ad1_HdV_LC_SrtDly.MM;
					bytesArry[2] = profile->Ad1_HdV_LC_SrtDly.SS;
					*bytesCount = sizeof(TIME_M);	
					break;
				
				case var_code_Ad1_HdV_DC_OnOff : 
					bytesArry[0] = profile->Ad1_HdV_DC_OnOff;
					*bytesCount = sizeof(BOOL);
					break; 
				
				case var_code_Ad1_HdV_DC_SrtDly : 
					bytesArry[0] = profile->Ad1_HdV_DC_SrtDly.HH;
					bytesArry[1] = profile->Ad1_HdV_DC_SrtDly.MM;
					bytesArry[2] = profile->Ad1_HdV_DC_SrtDly.SS;
					*bytesCount = sizeof(TIME_M);
					break;   
				
				case var_code_Ad1_HdV_FlexFunc_YesNo : 
					bytesArry[0] = profile->Ad1_HdV_FlexFunc_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_HdV_FlexFunc_RptTmr : 
					bytesArry[0] = profile->Ad1_HdV_FlexFunc_RptTmr;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_HdV_FlexFunc_Heat : 
					bytesArry[0] = profile->Ad1_HdV_FlexFunc_Heat;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_HdV_FlexFunc_Cool : 
					bytesArry[0] = profile->Ad1_HdV_FlexFunc_Cool;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_HdV_FlexFunc_Hum : 
					bytesArry[0] = profile->Ad1_HdV_FlexFunc_Hum;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_HdV_FlexFunc_DeHum : 
					bytesArry[0] = profile->Ad1_HdV_FlexFunc_DeHum;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_HdV_FlexFunc_CO2 : 
					bytesArry[0] = profile->Ad1_HdV_FlexFunc_CO2;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_HdV_FlexFunc_Follow :
					bytesArry[0] = profile->Ad1_HdV_FlexFunc_Follow;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_HdV_FlexFunc_Flip :
					bytesArry[0] = profile->Ad1_HdV_FlexFunc_Flip;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_HdV_VentLoc_YesNo : 
					bytesArry[0] = profile->Ad1_HdV_VentLoc_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
					
				case var_code_Ad1_HdV_Tmr_LC_CclTime:
					bytesArry[0] = profile->Ad1_HdV_Tmr_LC_CclTime.HH;
					bytesArry[1] = profile->Ad1_HdV_Tmr_LC_CclTime.MM;
					bytesArry[2] = profile->Ad1_HdV_Tmr_LC_CclTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
									
				case var_code_Ad1_HdV_Tmr_LC_RptAftr : 
					bytesArry[0] = profile->Ad1_HdV_Tmr_LC_RptAftr.HH;
					bytesArry[1] = profile->Ad1_HdV_Tmr_LC_RptAftr.MM;
					bytesArry[2] = profile->Ad1_HdV_Tmr_LC_RptAftr.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_HdV_Tmr_DC_CclTime : 
					bytesArry[0] = profile->Ad1_HdV_Tmr_DC_CclTime.HH;
					bytesArry[1] = profile->Ad1_HdV_Tmr_DC_CclTime.MM;
					bytesArry[2] = profile->Ad1_HdV_Tmr_DC_CclTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_HdV_Tmr_DC_RptAftr : 
					bytesArry[0] = profile->Ad1_HdV_Tmr_DC_RptAftr.HH;
					bytesArry[1] = profile->Ad1_HdV_Tmr_DC_RptAftr.MM;
					bytesArry[2] = profile->Ad1_HdV_Tmr_DC_RptAftr.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_HdV_Htr_LC_OnTemp :
					floatVal.floatVar = profile->Ad1_HdV_Htr_LC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_Htr_LC_OffTemp : 
					floatVal.floatVar = profile->Ad1_HdV_Htr_LC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_Htr_DC_OnTemp : 
					floatVal.floatVar = profile->Ad1_HdV_Htr_DC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_Htr_DC_OffTemp : 
					floatVal.floatVar = profile->Ad1_HdV_Htr_DC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_Cool_LC_OnTemp :
					floatVal.floatVar = profile->Ad1_HdV_Cool_LC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);					
					break;
				
				case var_code_Ad1_HdV_Cool_LC_OffTemp : 
					floatVal.floatVar = profile->Ad1_HdV_Cool_LC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_Cool_DC_OnTemp : 
					floatVal.floatVar = profile->Ad1_HdV_Cool_DC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_Cool_DC_OffTemp : 
					floatVal.floatVar = profile->Ad1_HdV_Cool_DC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_Hum_LC_OnHum : 
					floatVal.floatVar = profile->Ad1_HdV_Hum_LC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_Hum_LC_OffHum : 
					floatVal.floatVar = profile->Ad1_HdV_Hum_LC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_Hum_DC_OnHum : 
					floatVal.floatVar = profile->Ad1_HdV_Hum_DC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_Hum_DC_OffHum : 
					floatVal.floatVar = profile->Ad1_HdV_Hum_DC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_DeH_LC_OnHum : 
					floatVal.floatVar = profile->Ad1_HdV_DeH_LC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_DeH_LC_OffHum : 
					floatVal.floatVar = profile->Ad1_HdV_DeH_LC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_DeH_DC_OnHum : 
					floatVal.floatVar = profile->Ad1_HdV_DeH_DC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_DeH_DC_OffHum : 
					floatVal.floatVar = profile->Ad1_HdV_DeH_DC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_HdV_Co2_Opnlp_InjTime : 
					bytesArry[0] = profile->Ad1_HdV_Co2_Opnlp_InjTime.HH;
					bytesArry[1] = profile->Ad1_HdV_Co2_Opnlp_InjTime.MM;
					bytesArry[2] = profile->Ad1_HdV_Co2_Opnlp_InjTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_HdV_Co2_CylGen : 
					bytesArry[0] = profile->Ad1_HdV_Co2_CylGen;
					*bytesCount = sizeof(CYL_GEN);
					break;
				
				case var_code_Ad1_HdV_Co2_Cyl_StPtPPM : 
					intVal.intVar = profile->Ad1_HdV_Co2_Cyl_StPtPPM;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;
				
				case var_code_Ad1_HdV_Co2_Gen_OnPPM : 
					intVal.intVar = profile->Ad1_HdV_Co2_Gen_OnPPM;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;
				
				case var_code_Ad1_HdV_Co2_Gen_OffPPM : 
					intVal.intVar = profile->Ad1_HdV_Co2_Gen_OffPPM;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;
				
				case var_code_Ad1_Cir_OnOff :
					bytesArry[0] = profile->Ad1_Cir_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_LC_OnOff : 
					bytesArry[0] = profile->Ad1_Cir_LC_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_LC_SrtDly :
					bytesArry[0] = profile->Ad1_Cir_LC_SrtDly.HH;
					bytesArry[1] = profile->Ad1_Cir_LC_SrtDly.MM;
					bytesArry[2] = profile->Ad1_Cir_LC_SrtDly.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Cir_DC_OnOff :
					bytesArry[0] = profile->Ad1_Cir_DC_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_DC_SrtDly : 
					bytesArry[0] = profile->Ad1_Cir_DC_SrtDly.HH;
					bytesArry[1] = profile->Ad1_Cir_DC_SrtDly.MM;
					bytesArry[2] = profile->Ad1_Cir_DC_SrtDly.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Cir_FlexFunc_YesNo :
					bytesArry[0] = profile->Ad1_Cir_FlexFunc_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_FlexFunc_RptTmr : 
					bytesArry[0] = profile->Ad1_Cir_FlexFunc_RptTmr;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_FlexFunc_Heat : 
					bytesArry[0] = profile->Ad1_Cir_FlexFunc_Heat;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_FlexFunc_Cool : 
					bytesArry[0] = profile->Ad1_Cir_FlexFunc_Cool;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_FlexFunc_Hum : 
					bytesArry[0] = profile->Ad1_Cir_FlexFunc_Hum;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_FlexFunc_DeHum : 
					bytesArry[0] = profile->Ad1_Cir_FlexFunc_DeHum;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_FlexFunc_CO2 : 
					bytesArry[0] = profile->Ad1_Cir_FlexFunc_CO2;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_FlexFunc_Follow : 
					bytesArry[0] = profile->Ad1_Cir_FlexFunc_Follow;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_FlexFunc_Flip : 
					bytesArry[0] = profile->Ad1_Cir_FlexFunc_Flip;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_VentLoc_YesNo : 
					bytesArry[0] = profile->Ad1_Cir_VentLoc_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Cir_Tmr_LC_CclTime : 
					bytesArry[0] = profile->Ad1_Cir_Tmr_LC_CclTime.HH;
					bytesArry[1] = profile->Ad1_Cir_Tmr_LC_CclTime.MM;
					bytesArry[2] = profile->Ad1_Cir_Tmr_LC_CclTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Cir_Tmr_LC_RptAftr : 
					bytesArry[0] = profile->Ad1_Cir_Tmr_LC_RptAftr.HH;
					bytesArry[1] = profile->Ad1_Cir_Tmr_LC_RptAftr.MM;
					bytesArry[2] = profile->Ad1_Cir_Tmr_LC_RptAftr.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Cir_Tmr_DC_CclTime : 
					bytesArry[0] = profile->Ad1_Cir_Tmr_DC_CclTime.HH;
					bytesArry[1] = profile->Ad1_Cir_Tmr_DC_CclTime.MM;
					bytesArry[2] = profile->Ad1_Cir_Tmr_DC_CclTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Cir_Tmr_DC_RptAftr : 
					bytesArry[0] = profile->Ad1_Cir_Tmr_DC_RptAftr.HH;
					bytesArry[1] = profile->Ad1_Cir_Tmr_DC_RptAftr.MM;
					bytesArry[2] = profile->Ad1_Cir_Tmr_DC_RptAftr.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Cir_Htr_LC_OnTemp : 
					floatVal.floatVar = profile->Ad1_Cir_Htr_LC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_Htr_LC_OffTemp : 
					floatVal.floatVar = profile->Ad1_Cir_Htr_LC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_Htr_DC_OnTemp : 
					floatVal.floatVar = profile->Ad1_Cir_Htr_DC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_Htr_DC_OffTemp : 
					floatVal.floatVar = profile->Ad1_Cir_Htr_DC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_Cool_LC_OnTemp : 
					floatVal.floatVar = profile->Ad1_Cir_Cool_LC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_Cool_LC_OffTemp : 
					floatVal.floatVar = profile->Ad1_Cir_Cool_LC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_Cool_DC_OnTemp : 
					floatVal.floatVar = profile->Ad1_Cir_Cool_DC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_Cool_DC_OffTemp : 
					floatVal.floatVar = profile->Ad1_Cir_Cool_DC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_Hum_LC_OnHum : 
					floatVal.floatVar = profile->Ad1_Cir_Hum_LC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_Hum_LC_OffHum : 
					floatVal.floatVar = profile->Ad1_Cir_Hum_LC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_Hum_DC_OnHum : 
					floatVal.floatVar = profile->Ad1_Cir_Hum_DC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_Hum_DC_OffHum : 
					floatVal.floatVar = profile->Ad1_Cir_Hum_DC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_DeH_LC_OnHum : 
					floatVal.floatVar = profile->Ad1_Cir_DeH_LC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_DeH_LC_OffHum : 
					floatVal.floatVar = profile->Ad1_Cir_DeH_LC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_DeH_DC_OnHum : 
					floatVal.floatVar = profile->Ad1_Cir_DeH_DC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_DeH_DC_OffHum : 
					floatVal.floatVar = profile->Ad1_Cir_DeH_DC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Cir_Co2_Opnlp_InjTime : 
					bytesArry[0] = profile->Ad1_Cir_Co2_Opnlp_InjTime.HH;
					bytesArry[1] = profile->Ad1_Cir_Co2_Opnlp_InjTime.MM;
					bytesArry[2] = profile->Ad1_Cir_Co2_Opnlp_InjTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Cir_Co2_CylGen : 
					bytesArry[0] = profile->Ad1_Cir_Co2_CylGen;
					*bytesCount = sizeof(CYL_GEN);
					break;
				
				case var_code_Ad1_Cir_Co2_Cyl_StPtPPM : 
					intVal.intVar = profile->Ad1_Cir_Co2_Cyl_StPtPPM;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;
				
				case var_code_Ad1_Cir_Co2_Gen_OnPPM : 
					intVal.intVar = profile->Ad1_Cir_Co2_Gen_OnPPM;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;
				
				case var_code_Ad1_Cir_Co2_Gen_OffPPM : 
					intVal.intVar = profile->Ad1_Cir_Co2_Gen_OffPPM;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;
				
				case var_code_Ad1_Ven_OnOff : 
					bytesArry[0] = profile->Ad1_Ven_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Ven_LC_OnOff : 
					bytesArry[0] = profile->Ad1_Ven_LC_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Ven_LC_SrtDly : 
					bytesArry[0] = profile->Ad1_Ven_LC_SrtDly.HH;
					bytesArry[1] = profile->Ad1_Ven_LC_SrtDly.MM;
					bytesArry[2] = profile->Ad1_Ven_LC_SrtDly.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Ven_RptVnt_LC_OnOff : 
					bytesArry[0] = profile->Ad1_Ven_RptVnt_LC_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Ven_RptVnt_LC_CclTime : 
					bytesArry[0] = profile->Ad1_Ven_RptVnt_LC_CclTime.HH;
					bytesArry[1] = profile->Ad1_Ven_RptVnt_LC_CclTime.MM;
					bytesArry[2] = profile->Ad1_Ven_RptVnt_LC_CclTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Ven_RptVnt_LC_RptAftr : 
					bytesArry[0] = profile->Ad1_Ven_RptVnt_LC_RptAftr.HH;
					bytesArry[1] = profile->Ad1_Ven_RptVnt_LC_RptAftr.MM;
					bytesArry[2] = profile->Ad1_Ven_RptVnt_LC_RptAftr.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Ven_TempVnt_OnOff : 
					bytesArry[0] = profile->Ad1_Ven_TempVnt_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Ven_TempVnt_LC_OnTemp : 
					floatVal.floatVar = profile->Ad1_Ven_TempVnt_LC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Ven_TempVnt_LC_OffTemp : 
					floatVal.floatVar = profile->Ad1_Ven_TempVnt_LC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Ven_HumVnt_OnOff : 
					bytesArry[0] = profile->Ad1_Ven_HumVnt_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Ven_LC_HumVnt_OnHum : 
					floatVal.floatVar = profile->Ad1_Ven_LC_HumVnt_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Ven_LC_HumVnt_OffHum : 
					floatVal.floatVar = profile->Ad1_Ven_LC_HumVnt_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Ven_DC_OnOff : 
					bytesArry[0] = profile->Ad1_Ven_DC_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Ven_DC_SrtDly : 
					bytesArry[0] = profile->Ad1_Ven_DC_SrtDly.HH;
					bytesArry[1] = profile->Ad1_Ven_DC_SrtDly.MM;
					bytesArry[2] = profile->Ad1_Ven_DC_SrtDly.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Ven_RptVnt_DC_OnOff : 
					bytesArry[0] = profile->Ad1_Ven_RptVnt_DC_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_Ven_RptVnt_DC_CclTime : 
					bytesArry[0] = profile->Ad1_Ven_RptVnt_DC_CclTime.HH;
					bytesArry[1] = profile->Ad1_Ven_RptVnt_DC_CclTime.MM;
					bytesArry[2] = profile->Ad1_Ven_RptVnt_DC_CclTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_Ven_RptVnt_DC_RptAftr : 
					bytesArry[0] = profile->Ad1_Ven_RptVnt_DC_RptAftr.HH;
					bytesArry[1] = profile->Ad1_Ven_RptVnt_DC_RptAftr.MM;
					bytesArry[2] = profile->Ad1_Ven_RptVnt_DC_RptAftr.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
			//	var_code_Ad1_Ven_TempVnt_OnOff,
				
				case var_code_Ad1_Ven_TempVnt_DC_OnTemp : 
					floatVal.floatVar = profile->Ad1_Ven_TempVnt_DC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Ven_TempVnt_DC_OffTemp : 
					floatVal.floatVar = profile->Ad1_Ven_TempVnt_DC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
			//	var_code_Ad1_Ven_HumVnt_OnOff,
				
				case var_code_Ad1_Ven_HumVnt_DC_OnHum : 
					floatVal.floatVar = profile->Ad1_Ven_HumVnt_DC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_Ven_HumVnt_DC_OffHum : 
					floatVal.floatVar = profile->Ad1_Ven_HumVnt_DC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_OnOff : 
					bytesArry[0] = profile->Ad1_FXP1_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_LC_OnOff : 
					bytesArry[0] = profile->Ad1_FXP1_LC_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_LC_SrtDly : 
					bytesArry[0] = profile->Ad1_FXP1_LC_SrtDly.HH;
					bytesArry[1] = profile->Ad1_FXP1_LC_SrtDly.MM;
					bytesArry[2] = profile->Ad1_FXP1_LC_SrtDly.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_FXP1_DC_OnOff : 
					bytesArry[0] = profile->Ad1_FXP1_DC_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_DC_SrtDly : 
					bytesArry[0] = profile->Ad1_FXP1_DC_SrtDly.HH;
					bytesArry[1] = profile->Ad1_FXP1_DC_SrtDly.MM;
					bytesArry[2] = profile->Ad1_FXP1_DC_SrtDly.SS;
					*bytesCount = sizeof(TIME_M);
					break;     
				
				case var_code_Ad1_FXP1_FlexFunc_YesNo : 
					bytesArry[0] = profile->Ad1_FXP1_FlexFunc_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_FlexFunc_RptTmr : 
					bytesArry[0] = profile->Ad1_FXP1_FlexFunc_RptTmr;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_FlexFunc_Heat : 
					bytesArry[0] = profile->Ad1_FXP1_FlexFunc_Heat;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_FlexFunc_Cool : 
					bytesArry[0] = profile->Ad1_FXP1_FlexFunc_Cool;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_FlexFunc_Hum : 
					bytesArry[0] = profile->Ad1_FXP1_FlexFunc_Hum;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_FlexFunc_DeHum : 
					bytesArry[0] = profile->Ad1_FXP1_FlexFunc_DeHum;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_FlexFunc_CO2 : 
					bytesArry[0] = profile->Ad1_FXP1_FlexFunc_CO2;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_FlexFunc_Follow : 
					bytesArry[0] = profile->Ad1_FXP1_FlexFunc_Follow;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_FlexFunc_Flip : 
					bytesArry[0] = profile->Ad1_FXP1_FlexFunc_Flip;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_VentLoc_YesNo : 
					bytesArry[0] = profile->Ad1_FXP1_VentLoc_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP1_Tmr_LC_CclTime : 
					bytesArry[0] = profile->Ad1_FXP1_Tmr_LC_CclTime.HH;
					bytesArry[1] = profile->Ad1_FXP1_Tmr_LC_CclTime.MM;
					bytesArry[2] = profile->Ad1_FXP1_Tmr_LC_CclTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_FXP1_Tmr_LC_RptAftr : 
					bytesArry[0] = profile->Ad1_FXP1_Tmr_LC_RptAftr.HH;
					bytesArry[1] = profile->Ad1_FXP1_Tmr_LC_RptAftr.MM;
					bytesArry[2] = profile->Ad1_FXP1_Tmr_LC_RptAftr.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_FXP1_Tmr_DC_CclTime : 
					bytesArry[0] = profile->Ad1_FXP1_Tmr_DC_CclTime.HH;
					bytesArry[1] = profile->Ad1_FXP1_Tmr_DC_CclTime.MM;
					bytesArry[2] = profile->Ad1_FXP1_Tmr_DC_CclTime.SS;
					*bytesCount = sizeof(TIME_M);

					break;
				
				case var_code_Ad1_FXP1_Tmr_DC_RptAftr : 
					bytesArry[0] = profile->Ad1_FXP1_Tmr_DC_RptAftr.HH;
					bytesArry[1] = profile->Ad1_FXP1_Tmr_DC_RptAftr.MM;
					bytesArry[2] = profile->Ad1_FXP1_Tmr_DC_RptAftr.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_FXP1_Htr_LC_OnTemp : 
					floatVal.floatVar = profile->Ad1_FXP1_Htr_LC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_Htr_LC_OffTemp : 
					floatVal.floatVar = profile->Ad1_FXP1_Htr_LC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_Htr_DC_OnTemp : 
					floatVal.floatVar = profile->Ad1_FXP1_Htr_DC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_Htr_DC_OffTemp : 
					floatVal.floatVar = profile->Ad1_FXP1_Htr_DC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_Cool_LC_OnTemp : 
					floatVal.floatVar = profile->Ad1_FXP1_Cool_LC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_Cool_LC_OffTemp : 
					floatVal.floatVar = profile->Ad1_FXP1_Cool_LC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_Cool_DC_OnTemp : 
					floatVal.floatVar = profile->Ad1_FXP1_Cool_DC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_Cool_DC_OffTemp : 
					floatVal.floatVar = profile->Ad1_FXP1_Cool_DC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_Hum_LC_OnHum : 
					floatVal.floatVar = profile->Ad1_FXP1_Hum_LC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_Hum_LC_OffHum : 
					floatVal.floatVar = profile->Ad1_FXP1_Hum_LC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_Hum_DC_OnHum : 
					floatVal.floatVar = profile->Ad1_FXP1_Hum_DC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_Hum_DC_OffHum : 
					floatVal.floatVar = profile->Ad1_FXP1_Hum_DC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_DeH_LC_OnHum : 
					floatVal.floatVar = profile->Ad1_FXP1_DeH_LC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_DeH_LC_OffHum : 
					floatVal.floatVar = profile->Ad1_FXP1_DeH_LC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_DeH_DC_OnHum : 
					floatVal.floatVar = profile->Ad1_FXP1_DeH_DC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_DeH_DC_OffHum : 
					floatVal.floatVar = profile->Ad1_FXP1_DeH_DC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP1_Co2_Opnlp_InjTime : 
					bytesArry[0] = profile->Ad1_FXP1_Co2_Opnlp_InjTime.HH;
					bytesArry[1] = profile->Ad1_FXP1_Co2_Opnlp_InjTime.MM;
					bytesArry[2] = profile->Ad1_FXP1_Co2_Opnlp_InjTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_FXP1_Co2_CylGen : 
					bytesArry[0] = profile->Ad1_FXP1_Co2_CylGen;
					*bytesCount = sizeof(CYL_GEN);
					break;
				
				case var_code_Ad1_FXP1_Co2_Cyl_StPtPPM : 
					intVal.intVar = profile->Ad1_FXP1_Co2_Cyl_StPtPPM;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;
				
				case var_code_Ad1_FXP1_Co2_Gen_OnPPM : 
					intVal.intVar = profile->Ad1_FXP1_Co2_Gen_OnPPM;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;
				
				case var_code_Ad1_FXP1_Co2_Gen_OffPPM : 
					intVal.intVar = profile->Ad1_FXP1_Co2_Gen_OffPPM;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;
				
				case var_code_Ad1_FXP2_OnOff : 
					bytesArry[0] = profile->Ad1_FXP2_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_LC_OnOff : 
					bytesArry[0] = profile->Ad1_FXP2_LC_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_LC_SrtDly : 
					bytesArry[0] = profile->Ad1_FXP2_LC_SrtDly.HH;
					bytesArry[1] = profile->Ad1_FXP2_LC_SrtDly.MM;
					bytesArry[2] = profile->Ad1_FXP2_LC_SrtDly.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_FXP2_DC_OnOff : 
					bytesArry[0] = profile->Ad1_FXP2_DC_OnOff;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_DC_SrtDly : 
					bytesArry[0] = profile->Ad1_FXP2_DC_SrtDly.HH;
					bytesArry[1] = profile->Ad1_FXP2_DC_SrtDly.MM;
					bytesArry[2] = profile->Ad1_FXP2_DC_SrtDly.SS;
					*bytesCount = sizeof(TIME_M);
					break;      
				
				case var_code_Ad1_FXP2_FlexFunc_YesNo : 
					bytesArry[0] = profile->Ad1_FXP2_FlexFunc_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_FlexFunc_RptTmr : 
					bytesArry[0] = profile->Ad1_FXP2_FlexFunc_RptTmr;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_FlexFunc_Heat : 
					bytesArry[0] = profile->Ad1_FXP2_FlexFunc_Heat;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_FlexFunc_Cool : 
					bytesArry[0] = profile->Ad1_FXP2_FlexFunc_Cool;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_FlexFunc_Hum : 
					bytesArry[0] = profile->Ad1_FXP2_FlexFunc_Hum;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_FlexFunc_DeHum : 
					bytesArry[0] = profile->Ad1_FXP2_FlexFunc_DeHum;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_FlexFunc_CO2 : 
					bytesArry[0] = profile->Ad1_FXP2_FlexFunc_CO2;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_FlexFunc_Follow : 
					bytesArry[0] = profile->Ad1_FXP2_FlexFunc_Follow;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_FlexFunc_Flip : 
					bytesArry[0] = profile->Ad1_FXP2_FlexFunc_Flip;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_VentLoc_YesNo : 
					bytesArry[0] = profile->Ad1_FXP2_VentLoc_YesNo;
					*bytesCount = sizeof(BOOL);
					break;
				
				case var_code_Ad1_FXP2_Tmr_LC_CclTime : 
					bytesArry[0] = profile->Ad1_FXP2_Tmr_LC_CclTime.HH;
					bytesArry[1] = profile->Ad1_FXP2_Tmr_LC_CclTime.MM;
					bytesArry[2] = profile->Ad1_FXP2_Tmr_LC_CclTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_FXP2_Tmr_LC_RptAftr : 
					bytesArry[0] = profile->Ad1_FXP2_Tmr_LC_RptAftr.HH;
					bytesArry[1] = profile->Ad1_FXP2_Tmr_LC_RptAftr.MM;
					bytesArry[2] = profile->Ad1_FXP2_Tmr_LC_RptAftr.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_FXP2_Tmr_DC_CclTime : 
					bytesArry[0] = profile->Ad1_FXP2_Tmr_DC_CclTime.HH;
					bytesArry[1] = profile->Ad1_FXP2_Tmr_DC_CclTime.MM;
					bytesArry[2] = profile->Ad1_FXP2_Tmr_DC_CclTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_FXP2_Tmr_DC_RptAftr : 
					bytesArry[0] = profile->Ad1_FXP2_Tmr_DC_RptAftr.HH;
					bytesArry[1] = profile->Ad1_FXP2_Tmr_DC_RptAftr.MM;
					bytesArry[2] = profile->Ad1_FXP2_Tmr_DC_RptAftr.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_FXP2_Htr_LC_OnTemp : 
					floatVal.floatVar = profile->Ad1_FXP2_Htr_LC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_Htr_LC_OffTemp : 
					floatVal.floatVar = profile->Ad1_FXP2_Htr_LC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_Htr_DC_OnTemp : 
					floatVal.floatVar = profile->Ad1_FXP2_Htr_DC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_Htr_DC_OffTemp : 
					floatVal.floatVar = profile->Ad1_FXP2_Htr_DC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_Cool_LC_OnTemp : 
					floatVal.floatVar = profile->Ad1_FXP2_Cool_LC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_Cool_LC_OffTemp : 
					floatVal.floatVar = profile->Ad1_FXP2_Cool_LC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_Cool_DC_OnTemp : 
					floatVal.floatVar = profile->Ad1_FXP2_Cool_DC_OnTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_Cool_DC_OffTemp : 
					floatVal.floatVar = profile->Ad1_FXP2_Cool_DC_OffTemp;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_Hum_LC_OnHum : 
					floatVal.floatVar = profile->Ad1_FXP2_Hum_LC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_Hum_LC_OffHum : 
					floatVal.floatVar = profile->Ad1_FXP2_Hum_LC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_Hum_DC_OnHum : 
					floatVal.floatVar = profile->Ad1_FXP2_Hum_DC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_Hum_DC_OffHum : 
					floatVal.floatVar = profile->Ad1_FXP2_Hum_DC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_DeH_LC_OnHum : 
					floatVal.floatVar = profile->Ad1_FXP2_DeH_LC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_DeH_LC_OffHum : 
					floatVal.floatVar = profile->Ad1_FXP2_DeH_LC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_DeH_DC_OnHum : 
					floatVal.floatVar = profile->Ad1_FXP2_DeH_DC_OnHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_DeH_DC_OffHum : 
					floatVal.floatVar = profile->Ad1_FXP2_DeH_DC_OffHum;
					memcpy(bytesArry, (void *)floatVal.floatArry, sizeof(float));
					*bytesCount = sizeof(float);
					break;
				
				case var_code_Ad1_FXP2_Co2_Opnlp_InjTime : 
					bytesArry[0] = profile->Ad1_FXP2_Co2_Opnlp_InjTime.HH;
					bytesArry[1] = profile->Ad1_FXP2_Co2_Opnlp_InjTime.MM;
					bytesArry[2] = profile->Ad1_FXP2_Co2_Opnlp_InjTime.SS;
					*bytesCount = sizeof(TIME_M);
					break;
				
				case var_code_Ad1_FXP2_Co2_CylGen : 
					bytesArry[0] = profile->Ad1_FXP2_Co2_CylGen;
					*bytesCount = sizeof(CYL_GEN);
					break;
				
				case var_code_Ad1_FXP2_Co2_Cyl_StPtPPM : 
					intVal.intVar = profile->Ad1_FXP2_Co2_Cyl_StPtPPM;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;
				
				case var_code_Ad1_FXP2_Co2_Gen_OnPPM : 
					intVal.intVar = profile->Ad1_FXP2_Co2_Gen_OnPPM;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
					break;
					
				case var_code_Ad1_FXP2_Co2_Gen_OffPPM : 
					intVal.intVar = profile->Ad1_FXP2_Co2_Gen_OffPPM;
					memcpy(bytesArry, (void *)intVal.intArry, sizeof(uint16_t));
					*bytesCount = sizeof(uint16_t);
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
	return;
}

void eeprom_set_var(uint8_t profNum, uint8_t varCode, uint8_t bytesCount, uint8_t * bytesArry) {
	
	volatile union {
    float floatVar;
    uint8_t floatArry[sizeof(float)];
  } floatVal;
	
	switch(profNum) {
		
		// Write Tools value
		case TOOLS_NUMBER:
			
			switch(varCode) {
				
				case var_code_Ad1_DeviceType :
					
					tools->Ad1_DeviceType = bytesArry[0];
				
					I2C_EEPROM_24C0x_WriteStructTools(tools, EEPROM_ADDRESS_TOOLS, TOOLS_SIZE);
					break;
				
				case var_code_Ad1_Tools_HiTemp_Warning_StPt:
					
					memcpy((void *)floatVal.floatArry, bytesArry, sizeof(float));
				
					tools->Ad1_Tools_HiTemp_Warning_StPt = 	floatVal.floatVar;
				
					I2C_EEPROM_24C0x_WriteStructTools(tools, EEPROM_ADDRESS_TOOLS, TOOLS_SIZE);

					break;
								
				
				case var_code_Ad1_Tools_LoHum_Warning_StPt :
					
					memcpy((void *)floatVal.floatArry, bytesArry, sizeof(float));
				
					tools->Ad1_Tools_LoHum_Warning_StPt = floatVal.floatVar;
				
					I2C_EEPROM_24C0x_WriteStructTools(tools, EEPROM_ADDRESS_TOOLS, TOOLS_SIZE);
				
					break;
			}
			break;
		
		// Write profile 1 data
		case PROFILE_NUMBER_1:
			
			switch(varCode) {
				
				case var_code_Ad1_Light_OnTime:
					
					profile->Ad1_Light_OnTime.HH = bytesArry[0];
					profile->Ad1_Light_OnTime.MM = bytesArry[1];
					profile->Ad1_Light_OnTime.SS = bytesArry[2];
				
					I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_1, PROFILE_SIZE);
					
					break;
				
				case var_code_Ad1_HdV_Tmr_LC_CclTime:
					
					profile->Ad1_HdV_Tmr_LC_CclTime.HH = bytesArry[0];
					profile->Ad1_HdV_Tmr_LC_CclTime.MM = bytesArry[1];
					profile->Ad1_HdV_Tmr_LC_CclTime.SS = bytesArry[2];
					I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_1, PROFILE_SIZE);
				
					break;
			}
			break;
		
		// Write profile 2 data
		case PROFILE_NUMBER_2:
			I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_2, PROFILE_SIZE);
			break;
		
		// Write profile 3 data 
		case PROFILE_NUMBER_3:
			I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_3, PROFILE_SIZE);
			break;
		
		// Write profile 4 data
		case PROFILE_NUMBER_4:
				I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_4, PROFILE_SIZE);
			break;
		
		// Write profile 5 data
		case PROFILE_NUMBER_5:
			I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_5, PROFILE_SIZE);
			break;
		
		// Write profile 6 data
		case PROFILE_NUMBER_6:
			I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_6, PROFILE_SIZE);
			break;
		
		// Write profile 7 data
		case PROFILE_NUMBER_7:
			I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_7, PROFILE_SIZE);
			break;
		
		// Write profile 8 data
		case PROFILE_NUMBER_8:
			I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_8, PROFILE_SIZE);
			break;
		
		// Write profile 9 data
		case PROFILE_NUMBER_9:
			I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_9, PROFILE_SIZE);
			break;
		
		// Write profile 10 data
		case PROFILE_NUMBER_10:
			I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_10, PROFILE_SIZE);
			break;		
		
		// Write profile 11 data
		case PROFILE_NUMBER_11:
			break;
		
		// Write profile 12 data
		case PROFILE_NUMBER_12:
			break;
		
		// Write profile 13 data
		case PROFILE_NUMBER_13:
			break;
		
		// Write profile 14 data
		case PROFILE_NUMBER_14:
			break;
		
		// Write profile 15 data
		case PROFILE_NUMBER_15:
			break;
		
		// Write profile 16 data
		case PROFILE_NUMBER_16:
			break;
		
		// Write profile 17 data
		case PROFILE_NUMBER_17:
			break;
		
		// Write profile 18 data
		case PROFILE_NUMBER_18:
			break;		
		
		// Write profile 19 data
		case PROFILE_NUMBER_19:
			break;
		
		// Write profile 20 data
		case PROFILE_NUMBER_20:
			break;
		
		default:
			break;
	}
	return;
}

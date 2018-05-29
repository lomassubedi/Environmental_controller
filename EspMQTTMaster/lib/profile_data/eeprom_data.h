// File Name: eeprom_data.h
// Author: Lomas
// Date: 07-10-2017

#ifndef EEPROM_DATA_H_
#define EEPROM_DATA_H_

#include "data_types.h"

 /* -----------------------------------------
  * Data Types used in a profile and their count
  * TIME_M -> 41 (41x3)
  * float  -> 72
  * uint16_t -> 12
  * BOOL -> 72
  * CYL_GEN -> 4
  * TRISTATE_OPERATION_MODE -> 1
  */
// ----- Defines -----------
#define 		ADDRESS_EPRM_STATUS_FLAG		0
#define			VALUE_EEPRM_WRITE_DONE			1
#define			BYTES_EEPRM_STATUS_FLAG			1

#define 		ADDRESS_EEPRM_CURRENT_PRF		1

#define 		ADDRESS_EEPRM_DAY_COUNT			2


#define 		TOOLS_SIZE			100		// TOOLS size (60 Bytes in actual)
#define			PROFILE_SIZE		600		// Profile size 600 Bytes (In actual its 496 Bytes)

// Variable to point current/active profile
extern uint8_t active_profile;

// Variable for storing day count value 
extern uint8_t day_count;

enum EEPROM_ADDRESS {
	// Address 0-99 is reserved for now !!
	EEPROM_ADDRESS_TOOLS = 100,
	EEPROM_ADDRESS_PROFILE_1 = EEPROM_ADDRESS_TOOLS + TOOLS_SIZE,				// Profile1 address starts from 200 - 799
	EEPROM_ADDRESS_PROFILE_2 = EEPROM_ADDRESS_PROFILE_1 + PROFILE_SIZE,	// Profile2 address starts from 800 - 1399
	EEPROM_ADDRESS_PROFILE_3 = EEPROM_ADDRESS_PROFILE_2 + PROFILE_SIZE,	// 1400
	EEPROM_ADDRESS_PROFILE_4 = EEPROM_ADDRESS_PROFILE_3 + PROFILE_SIZE, // 2000
	EEPROM_ADDRESS_PROFILE_5 = EEPROM_ADDRESS_PROFILE_4 + PROFILE_SIZE, // 2600
	EEPROM_ADDRESS_PROFILE_6 = EEPROM_ADDRESS_PROFILE_5 + PROFILE_SIZE, // 3200
	EEPROM_ADDRESS_PROFILE_7 = EEPROM_ADDRESS_PROFILE_6 + PROFILE_SIZE, // 3800
	EEPROM_ADDRESS_PROFILE_8 = EEPROM_ADDRESS_PROFILE_7 + PROFILE_SIZE, // 4400
	EEPROM_ADDRESS_PROFILE_9 = EEPROM_ADDRESS_PROFILE_8 + PROFILE_SIZE, // 5000
	EEPROM_ADDRESS_PROFILE_10 = EEPROM_ADDRESS_PROFILE_9 + PROFILE_SIZE, // 5600
	EEPROM_ADDRESS_PROFILE_11 = EEPROM_ADDRESS_PROFILE_10 + PROFILE_SIZE, // 6200
	EEPROM_ADDRESS_PROFILE_12 = EEPROM_ADDRESS_PROFILE_11 + PROFILE_SIZE, // 6800
	EEPROM_ADDRESS_PROFILE_13 = EEPROM_ADDRESS_PROFILE_12 + PROFILE_SIZE, // 7400
	EEPROM_ADDRESS_PROFILE_14 = EEPROM_ADDRESS_PROFILE_13 + PROFILE_SIZE, // 8000
	EEPROM_ADDRESS_PROFILE_15 = EEPROM_ADDRESS_PROFILE_14 + PROFILE_SIZE, // 8600
	EEPROM_ADDRESS_PROFILE_16 = EEPROM_ADDRESS_PROFILE_15 + PROFILE_SIZE, // 9200
	EEPROM_ADDRESS_PROFILE_17 = EEPROM_ADDRESS_PROFILE_16 + PROFILE_SIZE, // 9800
	EEPROM_ADDRESS_PROFILE_18 = EEPROM_ADDRESS_PROFILE_17 + PROFILE_SIZE, // 10400
	EEPROM_ADDRESS_PROFILE_19 = EEPROM_ADDRESS_PROFILE_18 + PROFILE_SIZE, // 11000
	EEPROM_ADDRESS_PROFILE_20 = EEPROM_ADDRESS_PROFILE_19 + PROFILE_SIZE  // 11600
};

enum profileNo {
	TOOLS_NUMBER = 0,
	PROFILE_NUMBER_1,
	PROFILE_NUMBER_2,
	PROFILE_NUMBER_3,
	PROFILE_NUMBER_4,
	PROFILE_NUMBER_5,
	PROFILE_NUMBER_6,
	PROFILE_NUMBER_7,
	PROFILE_NUMBER_8,
	PROFILE_NUMBER_9,
	PROFILE_NUMBER_10,
	PROFILE_NUMBER_11,
	PROFILE_NUMBER_12,
	PROFILE_NUMBER_13,
	PROFILE_NUMBER_14,
	PROFILE_NUMBER_15,
	PROFILE_NUMBER_16,
	PROFILE_NUMBER_17,
	PROFILE_NUMBER_18,
	PROFILE_NUMBER_19,
	PROFILE_NUMBER_20
};

typedef struct tools {
	
	uint8_t Ad1_DeviceType;
	
	UNIT_S Ad1_Tools_Units_EnglishMetric;
	
	BOOL Ad1_Tools_Sensor_Fault;
	BOOL Ad1_Tools_ACFault_Message_YesNo;
	BOOL Ad1_Tools_LoTemp_Warning_YesNo;
	
	float Ad1_Tools_LoTemp_Warning_StPt;
	
	BOOL Ad1_Tools_HiTemp_Warning_YesNo;
	
	float Ad1_Tools_HiTemp_Warning_StPt;
	
	BOOL Ad1_Tools_LoHum_Warning_YesNo;
	
	float Ad1_Tools_LoHum_Warning_StPt;
	
	BOOL Ad1_Tools_HiHum_Warning_YesNo;
	
	float Ad1_Tools_HiHum_Warning_StPt;
	
	BOOL Ad1_Tools_Critical_OverTemp_Fault_YesNo;
	BOOL Ad1_Tools_Critical_OverTemp_Fault_Flag;
	
	float Ad1_Tools_Critical_OverTemp_StPt;
	
	BOOL Ad1_Tools_Critical_OverTemp_Response;
	BOOL Ad1_Tools_Critical_OverTemp_Message_YesNo;
	BOOL Ad1_Tools_ReStrike_Fault_YesNo;
	
	// Moved to tmp flags 
//	BOOL Ad1_Tools_ReStrike_Fault_Flag; 
	
	TIME_M Ad1_Tools_ReStrike_Delay_Time;
	
	BOOL Ad1_Tools_ReStrike_Message_YesNo;
	BOOL Ad1_Tools_LoBat_Fault_Message_YesNo;
	
	float Ad1_Tools_Batt_Current_Volt;
	
	uint16_t Ad1_Tools_Light_Relay_Cycle_Counter;
	uint16_t Ad1_Tools_HdVent_Relay_Cycle_Counter;
	uint16_t Ad1_Tools_Circ_Relay_Cycle_Counter;
	uint16_t Ad1_Tools_Vent_Relay_Cycle_Counter;
	uint16_t Ad1_Tools_FXP1_Relay_Cycle_Counter;
	uint16_t Ad1_Tools_FXP2_Relay_Cycle_Counter;
	
	BOOL Ad1_Tools_Switch_YesNo;
	TIME_M Ad1_Tools_HdVent_DC_DeAct_FactSet_Delay;
	TIME_M Ad1_Tools_CO2_PVA_PostVent_FactSet_Delay;
	BOOL Ad1_Tools_LED_OnOff;	
} TOOLS;

// --- tools instantiation ---
extern TOOLS *tools;

typedef struct profile {
	
	TRISTATE_OPERATION_MODE Ad1_Light_Operation_Mode;
	
	TIME_M Ad1_Light_OnTime;
	TIME_M Ad1_Light_OffTime;

	TIME_M Ad1_Light_LC_Duration;
	TIME_M Ad1_Light_DC_Duration;
	
	TIME_M Ad1_Light_LC_TimeElapsed;
	TIME_M Ad1_Light_DC_TimeElapsed;
	
	TIME_M Ad1_Light_LC_TimeRemain;
	TIME_M Ad1_Light_DC_TimeRemain;
	
	BOOL Ad1_HdV_OnOff;
	BOOL Ad1_HdV_LC_OnOff;
	
	TIME_M Ad1_HdV_LC_SrtDly;
	
	BOOL Ad1_HdV_DC_OnOff; 
	
	TIME_M Ad1_HdV_DC_SrtDly;   
	
	BOOL Ad1_HdV_FlexFunc_YesNo;
	BOOL Ad1_HdV_FlexFunc_RptTmr;
	BOOL Ad1_HdV_FlexFunc_Heat;
	BOOL Ad1_HdV_FlexFunc_Cool;
	BOOL Ad1_HdV_FlexFunc_Hum;
	BOOL Ad1_HdV_FlexFunc_DeHum;
	BOOL Ad1_HdV_FlexFunc_CO2;
	BOOL Ad1_HdV_FlexFunc_Follow;
	BOOL Ad1_HdV_FlexFunc_Flip;
	BOOL Ad1_HdV_VentLoc_YesNo;
	
	TIME_M Ad1_HdV_Tmr_LC_CclTime;
	TIME_M Ad1_HdV_Tmr_LC_RptAftr;
	TIME_M Ad1_HdV_Tmr_DC_CclTime;
	TIME_M Ad1_HdV_Tmr_DC_RptAftr;
	
	float Ad1_HdV_Htr_LC_OnTemp;
	float Ad1_HdV_Htr_LC_OffTemp;
	float Ad1_HdV_Htr_DC_OnTemp;
	float Ad1_HdV_Htr_DC_OffTemp;
	float Ad1_HdV_Cool_LC_OnTemp;
	float Ad1_HdV_Cool_LC_OffTemp;
	float Ad1_HdV_Cool_DC_OnTemp;
	float Ad1_HdV_Cool_DC_OffTemp;
	float Ad1_HdV_Hum_LC_OnHum;
	float Ad1_HdV_Hum_LC_OffHum;
	float Ad1_HdV_Hum_DC_OnHum;
	float Ad1_HdV_Hum_DC_OffHum;
	float Ad1_HdV_DeH_LC_OnHum;
	float Ad1_HdV_DeH_LC_OffHum;
	float Ad1_HdV_DeH_DC_OnHum;
	float Ad1_HdV_DeH_DC_OffHum;
	
	TIME_M Ad1_HdV_Co2_Opnlp_InjTime;
	
	CYL_GEN Ad1_HdV_Co2_CylGen;
	
	uint16_t Ad1_HdV_Co2_Cyl_StPtPPM;
	uint16_t Ad1_HdV_Co2_Gen_OnPPM;
	uint16_t Ad1_HdV_Co2_Gen_OffPPM;
	
	BOOL Ad1_Cir_OnOff;
	BOOL Ad1_Cir_LC_OnOff;
	
	TIME_M Ad1_Cir_LC_SrtDly;
	
	BOOL Ad1_Cir_DC_OnOff;
	
	TIME_M Ad1_Cir_DC_SrtDly;
	
	BOOL Ad1_Cir_FlexFunc_YesNo;
	BOOL Ad1_Cir_FlexFunc_RptTmr;
	BOOL Ad1_Cir_FlexFunc_Heat;
	BOOL Ad1_Cir_FlexFunc_Cool;
	BOOL Ad1_Cir_FlexFunc_Hum;
	BOOL Ad1_Cir_FlexFunc_DeHum;
	BOOL Ad1_Cir_FlexFunc_CO2;
	BOOL Ad1_Cir_FlexFunc_Follow;
	
	BOOL Ad1_Cir_FlexFunc_Flip;
	BOOL Ad1_Cir_VentLoc_YesNo;
	
	TIME_M Ad1_Cir_Tmr_LC_CclTime;
	TIME_M Ad1_Cir_Tmr_LC_RptAftr;
	TIME_M Ad1_Cir_Tmr_DC_CclTime;
	TIME_M Ad1_Cir_Tmr_DC_RptAftr;
	
	float Ad1_Cir_Htr_LC_OnTemp;
	float Ad1_Cir_Htr_LC_OffTemp;
	float Ad1_Cir_Htr_DC_OnTemp;
	float Ad1_Cir_Htr_DC_OffTemp;
	float Ad1_Cir_Cool_LC_OnTemp;
	float Ad1_Cir_Cool_LC_OffTemp;
	float Ad1_Cir_Cool_DC_OnTemp;
	float Ad1_Cir_Cool_DC_OffTemp;
	float Ad1_Cir_Hum_LC_OnHum;
	float Ad1_Cir_Hum_LC_OffHum;
	float Ad1_Cir_Hum_DC_OnHum;
	float Ad1_Cir_Hum_DC_OffHum;
	float Ad1_Cir_DeH_LC_OnHum;
	float Ad1_Cir_DeH_LC_OffHum;
	float Ad1_Cir_DeH_DC_OnHum;
	float Ad1_Cir_DeH_DC_OffHum;
	
	TIME_M Ad1_Cir_Co2_Opnlp_InjTime;
	CYL_GEN Ad1_Cir_Co2_CylGen;
	
	uint16_t Ad1_Cir_Co2_Cyl_StPtPPM;
	uint16_t Ad1_Cir_Co2_Gen_OnPPM;
	uint16_t Ad1_Cir_Co2_Gen_OffPPM;
	
	BOOL Ad1_Ven_OnOff;
	BOOL Ad1_Ven_LC_OnOff;
	
	TIME_M Ad1_Ven_LC_SrtDly;
	
	BOOL Ad1_Ven_RptVnt_LC_OnOff;
	
	TIME_M Ad1_Ven_RptVnt_LC_CclTime;
	TIME_M Ad1_Ven_RptVnt_LC_RptAftr;
	
	BOOL Ad1_Ven_TempVnt_OnOff;
	float Ad1_Ven_TempVnt_LC_OnTemp;
	float Ad1_Ven_TempVnt_LC_OffTemp;
	
	BOOL Ad1_Ven_HumVnt_OnOff;
	
	float Ad1_Ven_LC_HumVnt_OnHum;
	float Ad1_Ven_LC_HumVnt_OffHum;
	
	BOOL Ad1_Ven_DC_OnOff;
	
	TIME_M Ad1_Ven_DC_SrtDly;
	
	BOOL Ad1_Ven_RptVnt_DC_OnOff;
	
	TIME_M Ad1_Ven_RptVnt_DC_CclTime;
	
	TIME_M Ad1_Ven_RptVnt_DC_RptAftr;
	
//	BOOL Ad1_Ven_TempVnt_OnOff;
	
	float Ad1_Ven_TempVnt_DC_OnTemp;
	float Ad1_Ven_TempVnt_DC_OffTemp;
	
//	BOOL Ad1_Ven_HumVnt_OnOff;
	
	float Ad1_Ven_HumVnt_DC_OnHum;
	float Ad1_Ven_HumVnt_DC_OffHum;
	
	BOOL Ad1_FXP1_OnOff;
	BOOL Ad1_FXP1_LC_OnOff;
	
	TIME_M Ad1_FXP1_LC_SrtDly;
	BOOL Ad1_FXP1_DC_OnOff;
	
	TIME_M Ad1_FXP1_DC_SrtDly;     
	
	BOOL Ad1_FXP1_FlexFunc_YesNo;
	BOOL Ad1_FXP1_FlexFunc_RptTmr;
	BOOL Ad1_FXP1_FlexFunc_Heat;
	BOOL Ad1_FXP1_FlexFunc_Cool;
	BOOL Ad1_FXP1_FlexFunc_Hum;
	BOOL Ad1_FXP1_FlexFunc_DeHum;
	BOOL Ad1_FXP1_FlexFunc_CO2;
	BOOL Ad1_FXP1_FlexFunc_Follow;
	BOOL Ad1_FXP1_FlexFunc_Flip;
	BOOL Ad1_FXP1_VentLoc_YesNo;
	
	TIME_M Ad1_FXP1_Tmr_LC_CclTime;
	TIME_M Ad1_FXP1_Tmr_LC_RptAftr;
	TIME_M Ad1_FXP1_Tmr_DC_CclTime;
	TIME_M Ad1_FXP1_Tmr_DC_RptAftr;
	
	float Ad1_FXP1_Htr_LC_OnTemp;
	float Ad1_FXP1_Htr_LC_OffTemp;
	float Ad1_FXP1_Htr_DC_OnTemp;
	float Ad1_FXP1_Htr_DC_OffTemp;
	float Ad1_FXP1_Cool_LC_OnTemp;
	float Ad1_FXP1_Cool_LC_OffTemp;
	float Ad1_FXP1_Cool_DC_OnTemp;
	float Ad1_FXP1_Cool_DC_OffTemp;
	float Ad1_FXP1_Hum_LC_OnHum;
	float Ad1_FXP1_Hum_LC_OffHum;
	float Ad1_FXP1_Hum_DC_OnHum;
	float Ad1_FXP1_Hum_DC_OffHum;
	float Ad1_FXP1_DeH_LC_OnHum;
	float Ad1_FXP1_DeH_LC_OffHum;
	float Ad1_FXP1_DeH_DC_OnHum;
	float Ad1_FXP1_DeH_DC_OffHum;
	
	TIME_M Ad1_FXP1_Co2_Opnlp_InjTime;
	
	CYL_GEN Ad1_FXP1_Co2_CylGen;
	
	uint16_t Ad1_FXP1_Co2_Cyl_StPtPPM;
	uint16_t Ad1_FXP1_Co2_Gen_OnPPM;
	uint16_t Ad1_FXP1_Co2_Gen_OffPPM;
	
	BOOL Ad1_FXP2_OnOff;
	BOOL Ad1_FXP2_LC_OnOff;
	
	TIME_M Ad1_FXP2_LC_SrtDly;
	
	BOOL Ad1_FXP2_DC_OnOff;
	
	TIME_M Ad1_FXP2_DC_SrtDly;      
	
	BOOL Ad1_FXP2_FlexFunc_YesNo;
	BOOL Ad1_FXP2_FlexFunc_RptTmr;
	BOOL Ad1_FXP2_FlexFunc_Heat;
	BOOL Ad1_FXP2_FlexFunc_Cool;
	BOOL Ad1_FXP2_FlexFunc_Hum;
	BOOL Ad1_FXP2_FlexFunc_DeHum;
	BOOL Ad1_FXP2_FlexFunc_CO2;
	BOOL Ad1_FXP2_FlexFunc_Follow;
	BOOL Ad1_FXP2_FlexFunc_Flip;
	BOOL Ad1_FXP2_VentLoc_YesNo;
	
	TIME_M Ad1_FXP2_Tmr_LC_CclTime;
	TIME_M Ad1_FXP2_Tmr_LC_RptAftr;
	TIME_M Ad1_FXP2_Tmr_DC_CclTime;
	TIME_M Ad1_FXP2_Tmr_DC_RptAftr;
	
	float Ad1_FXP2_Htr_LC_OnTemp;
	float Ad1_FXP2_Htr_LC_OffTemp;
	float Ad1_FXP2_Htr_DC_OnTemp;
	float Ad1_FXP2_Htr_DC_OffTemp;
	float Ad1_FXP2_Cool_LC_OnTemp;
	float Ad1_FXP2_Cool_LC_OffTemp;
	float Ad1_FXP2_Cool_DC_OnTemp;
	float Ad1_FXP2_Cool_DC_OffTemp;
	float Ad1_FXP2_Hum_LC_OnHum;
	float Ad1_FXP2_Hum_LC_OffHum;
	float Ad1_FXP2_Hum_DC_OnHum;
	float Ad1_FXP2_Hum_DC_OffHum;
	float Ad1_FXP2_DeH_LC_OnHum;
	float Ad1_FXP2_DeH_LC_OffHum;
	float Ad1_FXP2_DeH_DC_OnHum;
	float Ad1_FXP2_DeH_DC_OffHum;
	
	TIME_M Ad1_FXP2_Co2_Opnlp_InjTime;
	CYL_GEN Ad1_FXP2_Co2_CylGen;
	
	uint16_t Ad1_FXP2_Co2_Cyl_StPtPPM;
	uint16_t Ad1_FXP2_Co2_Gen_OnPPM;
	uint16_t Ad1_FXP2_Co2_Gen_OffPPM;

} PROFILE;
// --- profile instantiation ---
extern PROFILE *profile;

// ---------- Var Code Tools Enum -------
enum varCodeTools {
	
	var_code_Ad1_DeviceType = 1,
	
	var_code_Ad1_Tools_Units_EnglishMetric,
	
	var_code_Ad1_Tools_Sensor_Fault,
	var_code_Ad1_Tools_ACFault_Message_YesNo,
	var_code_Ad1_Tools_LoTemp_Warning_YesNo,
	
	var_code_Ad1_Tools_LoTemp_Warning_StPt,
	
	var_code_Ad1_Tools_HiTemp_Warning_YesNo,
	
	var_code_Ad1_Tools_HiTemp_Warning_StPt,
	
	var_code_Ad1_Tools_LoHum_Warning_YesNo,
	
	var_code_Ad1_Tools_LoHum_Warning_StPt,
	
	var_code_Ad1_Tools_HiHum_Warning_YesNo,
	
	var_code_Ad1_Tools_HiHum_Warning_StPt,
	
	var_code_Ad1_Tools_Critical_OverTemp_Fault_YesNo,
	var_code_Ad1_Tools_Critical_OverTemp_Fault_Flag,
	
	var_code_Ad1_Tools_Critical_OverTemp_StPt,
	
	var_code_Ad1_Tools_Critical_OverTemp_Response,
	var_code_Ad1_Tools_Critical_OverTemp_Message_YesNo,
	var_code_Ad1_Tools_ReStrike_Fault_YesNo,
	
	// Moved to tmp flags 
//	var_code_Ad1_Tools_ReStrike_Fault_Flag, 
	
	var_code_Ad1_Tools_ReStrike_Delay_Time,
	
	var_code_Ad1_Tools_ReStrike_Message_YesNo,
	var_code_Ad1_Tools_LoBat_Fault_Message_YesNo,
	
	var_code_Ad1_Tools_Batt_Current_Volt,
	
	var_code_Ad1_Tools_Light_Relay_Cycle_Counter,
	var_code_Ad1_Tools_HdVent_Relay_Cycle_Counter,
	var_code_Ad1_Tools_Circ_Relay_Cycle_Counter,
	var_code_Ad1_Tools_Vent_Relay_Cycle_Counter,
	var_code_Ad1_Tools_FXP1_Relay_Cycle_Counter,
	var_code_Ad1_Tools_FXP2_Relay_Cycle_Counter,
	
	var_code_Ad1_Tools_Switch_YesNo,
	var_code_Ad1_Tools_HdVent_DC_DeAct_FactSet_Delay,
	var_code_Ad1_Tools_CO2_PVA_PostVent_FactSet_Delay,
	var_code_Ad1_Tools_LED_OnOff
};

// Var Code Profile enum
enum varCodeProfile {
	var_code_Ad1_Light_Operation_Mode = 1,
	
	var_code_Ad1_Light_OnTime,
	var_code_Ad1_Light_OffTime,

	var_code_Ad1_Light_LC_Duration,
	var_code_Ad1_Light_DC_Duration,
	var_code_Ad1_Light_LC_TimeRemain,
	var_code_Ad1_Light_DC_TimeRemain,
	
	var_code_Ad1_HdV_OnOff,
	var_code_Ad1_HdV_LC_OnOff,
	
	var_code_Ad1_HdV_LC_SrtDly,
	
	var_code_Ad1_HdV_DC_OnOff, 
	
	var_code_Ad1_HdV_DC_SrtDly,   
	
	var_code_Ad1_HdV_FlexFunc_YesNo,
	var_code_Ad1_HdV_FlexFunc_RptTmr,
	var_code_Ad1_HdV_FlexFunc_Heat,
	var_code_Ad1_HdV_FlexFunc_Cool,
	var_code_Ad1_HdV_FlexFunc_Hum,
	var_code_Ad1_HdV_FlexFunc_DeHum,
	var_code_Ad1_HdV_FlexFunc_CO2,
	var_code_Ad1_HdV_FlexFunc_Follow,
	var_code_Ad1_HdV_FlexFunc_Flip,
	var_code_Ad1_HdV_VentLoc_YesNo,
	
	var_code_Ad1_HdV_Tmr_LC_CclTime,
	var_code_Ad1_HdV_Tmr_LC_RptAftr,
	var_code_Ad1_HdV_Tmr_DC_CclTime,
	var_code_Ad1_HdV_Tmr_DC_RptAftr,
	
	var_code_Ad1_HdV_Htr_LC_OnTemp,
	var_code_Ad1_HdV_Htr_LC_OffTemp,
	var_code_Ad1_HdV_Htr_DC_OnTemp,
	var_code_Ad1_HdV_Htr_DC_OffTemp,
	var_code_Ad1_HdV_Cool_LC_OnTemp,
	var_code_Ad1_HdV_Cool_LC_OffTemp,
	var_code_Ad1_HdV_Cool_DC_OnTemp,
	var_code_Ad1_HdV_Cool_DC_OffTemp,
	var_code_Ad1_HdV_Hum_LC_OnHum,
	var_code_Ad1_HdV_Hum_LC_OffHum,
	var_code_Ad1_HdV_Hum_DC_OnHum,
	var_code_Ad1_HdV_Hum_DC_OffHum,
	var_code_Ad1_HdV_DeH_LC_OnHum,
	var_code_Ad1_HdV_DeH_LC_OffHum,
	var_code_Ad1_HdV_DeH_DC_OnHum,
	var_code_Ad1_HdV_DeH_DC_OffHum,
	
	var_code_Ad1_HdV_Co2_Opnlp_InjTime,
	
	var_code_Ad1_HdV_Co2_CylGen,
	
	var_code_Ad1_HdV_Co2_Cyl_StPtPPM,
	var_code_Ad1_HdV_Co2_Gen_OnPPM,
	var_code_Ad1_HdV_Co2_Gen_OffPPM,
	
	var_code_Ad1_Cir_OnOff,
	var_code_Ad1_Cir_LC_OnOff,
	
	var_code_Ad1_Cir_LC_SrtDly,
	
	var_code_Ad1_Cir_DC_OnOff,
	
	var_code_Ad1_Cir_DC_SrtDly,
	
	var_code_Ad1_Cir_FlexFunc_YesNo,
	var_code_Ad1_Cir_FlexFunc_RptTmr,
	var_code_Ad1_Cir_FlexFunc_Heat,
	var_code_Ad1_Cir_FlexFunc_Cool,
	var_code_Ad1_Cir_FlexFunc_Hum,
	var_code_Ad1_Cir_FlexFunc_DeHum,
	var_code_Ad1_Cir_FlexFunc_CO2,
	var_code_Ad1_Cir_FlexFunc_Follow,
	
	var_code_Ad1_Cir_FlexFunc_Flip,
	var_code_Ad1_Cir_VentLoc_YesNo,
	
	var_code_Ad1_Cir_Tmr_LC_CclTime,
	var_code_Ad1_Cir_Tmr_LC_RptAftr,
	var_code_Ad1_Cir_Tmr_DC_CclTime,
	var_code_Ad1_Cir_Tmr_DC_RptAftr,
	
	var_code_Ad1_Cir_Htr_LC_OnTemp,
	var_code_Ad1_Cir_Htr_LC_OffTemp,
	var_code_Ad1_Cir_Htr_DC_OnTemp,
	var_code_Ad1_Cir_Htr_DC_OffTemp,
	var_code_Ad1_Cir_Cool_LC_OnTemp,
	var_code_Ad1_Cir_Cool_LC_OffTemp,
	var_code_Ad1_Cir_Cool_DC_OnTemp,
	var_code_Ad1_Cir_Cool_DC_OffTemp,
	var_code_Ad1_Cir_Hum_LC_OnHum,
	var_code_Ad1_Cir_Hum_LC_OffHum,
	var_code_Ad1_Cir_Hum_DC_OnHum,
	var_code_Ad1_Cir_Hum_DC_OffHum,
	var_code_Ad1_Cir_DeH_LC_OnHum,
	var_code_Ad1_Cir_DeH_LC_OffHum,
	var_code_Ad1_Cir_DeH_DC_OnHum,
	var_code_Ad1_Cir_DeH_DC_OffHum,
	
	var_code_Ad1_Cir_Co2_Opnlp_InjTime,
	var_code_Ad1_Cir_Co2_CylGen,
	
	var_code_Ad1_Cir_Co2_Cyl_StPtPPM,
	var_code_Ad1_Cir_Co2_Gen_OnPPM,
	var_code_Ad1_Cir_Co2_Gen_OffPPM,
	
	var_code_Ad1_Ven_OnOff,
	var_code_Ad1_Ven_LC_OnOff,
	
	var_code_Ad1_Ven_LC_SrtDly,
	
	var_code_Ad1_Ven_RptVnt_LC_OnOff,
	
	var_code_Ad1_Ven_RptVnt_LC_CclTime,
	var_code_Ad1_Ven_RptVnt_LC_RptAftr,
	
	var_code_Ad1_Ven_TempVnt_OnOff,
	var_code_Ad1_Ven_TempVnt_LC_OnTemp,
	var_code_Ad1_Ven_TempVnt_LC_OffTemp,
	
	var_code_Ad1_Ven_HumVnt_OnOff,
	
	var_code_Ad1_Ven_LC_HumVnt_OnHum,
	var_code_Ad1_Ven_LC_HumVnt_OffHum,
	
	var_code_Ad1_Ven_DC_OnOff,
	
	var_code_Ad1_Ven_DC_SrtDly,
	
	var_code_Ad1_Ven_RptVnt_DC_OnOff,
	
	var_code_Ad1_Ven_RptVnt_DC_CclTime,
	
	var_code_Ad1_Ven_RptVnt_DC_RptAftr,
	
//	var_code_Ad1_Ven_TempVnt_OnOff,
	
	var_code_Ad1_Ven_TempVnt_DC_OnTemp,
	var_code_Ad1_Ven_TempVnt_DC_OffTemp,
	
//	var_code_Ad1_Ven_HumVnt_OnOff,
	
	var_code_Ad1_Ven_HumVnt_DC_OnHum,
	var_code_Ad1_Ven_HumVnt_DC_OffHum,
	
	var_code_Ad1_FXP1_OnOff,
	var_code_Ad1_FXP1_LC_OnOff,
	
	var_code_Ad1_FXP1_LC_SrtDly,
	var_code_Ad1_FXP1_DC_OnOff,
	
	var_code_Ad1_FXP1_DC_SrtDly,     
	
	var_code_Ad1_FXP1_FlexFunc_YesNo,
	var_code_Ad1_FXP1_FlexFunc_RptTmr,
	var_code_Ad1_FXP1_FlexFunc_Heat,
	var_code_Ad1_FXP1_FlexFunc_Cool,
	var_code_Ad1_FXP1_FlexFunc_Hum,
	var_code_Ad1_FXP1_FlexFunc_DeHum,
	var_code_Ad1_FXP1_FlexFunc_CO2,
	var_code_Ad1_FXP1_FlexFunc_Follow,
	var_code_Ad1_FXP1_FlexFunc_Flip,
	var_code_Ad1_FXP1_VentLoc_YesNo,
	
	var_code_Ad1_FXP1_Tmr_LC_CclTime,
	var_code_Ad1_FXP1_Tmr_LC_RptAftr,
	var_code_Ad1_FXP1_Tmr_DC_CclTime,
	var_code_Ad1_FXP1_Tmr_DC_RptAftr,
	
	var_code_Ad1_FXP1_Htr_LC_OnTemp,
	var_code_Ad1_FXP1_Htr_LC_OffTemp,
	var_code_Ad1_FXP1_Htr_DC_OnTemp,
	var_code_Ad1_FXP1_Htr_DC_OffTemp,
	var_code_Ad1_FXP1_Cool_LC_OnTemp,
	var_code_Ad1_FXP1_Cool_LC_OffTemp,
	var_code_Ad1_FXP1_Cool_DC_OnTemp,
	var_code_Ad1_FXP1_Cool_DC_OffTemp,
	var_code_Ad1_FXP1_Hum_LC_OnHum,
	var_code_Ad1_FXP1_Hum_LC_OffHum,
	var_code_Ad1_FXP1_Hum_DC_OnHum,
	var_code_Ad1_FXP1_Hum_DC_OffHum,
	var_code_Ad1_FXP1_DeH_LC_OnHum,
	var_code_Ad1_FXP1_DeH_LC_OffHum,
	var_code_Ad1_FXP1_DeH_DC_OnHum,
	var_code_Ad1_FXP1_DeH_DC_OffHum,
	
	var_code_Ad1_FXP1_Co2_Opnlp_InjTime,
	
	var_code_Ad1_FXP1_Co2_CylGen,
	
	var_code_Ad1_FXP1_Co2_Cyl_StPtPPM,
	var_code_Ad1_FXP1_Co2_Gen_OnPPM,
	var_code_Ad1_FXP1_Co2_Gen_OffPPM,
	
	var_code_Ad1_FXP2_OnOff,
	var_code_Ad1_FXP2_LC_OnOff,
	
	var_code_Ad1_FXP2_LC_SrtDly,
	
	var_code_Ad1_FXP2_DC_OnOff,
	
	var_code_Ad1_FXP2_DC_SrtDly,      
	
	var_code_Ad1_FXP2_FlexFunc_YesNo,
	var_code_Ad1_FXP2_FlexFunc_RptTmr,
	var_code_Ad1_FXP2_FlexFunc_Heat,
	var_code_Ad1_FXP2_FlexFunc_Cool,
	var_code_Ad1_FXP2_FlexFunc_Hum,
	var_code_Ad1_FXP2_FlexFunc_DeHum,
	var_code_Ad1_FXP2_FlexFunc_CO2,
	var_code_Ad1_FXP2_FlexFunc_Follow,
	var_code_Ad1_FXP2_FlexFunc_Flip,
	var_code_Ad1_FXP2_VentLoc_YesNo,
	
	var_code_Ad1_FXP2_Tmr_LC_CclTime,
	var_code_Ad1_FXP2_Tmr_LC_RptAftr,
	var_code_Ad1_FXP2_Tmr_DC_CclTime,
	var_code_Ad1_FXP2_Tmr_DC_RptAftr,
	
	var_code_Ad1_FXP2_Htr_LC_OnTemp,
	var_code_Ad1_FXP2_Htr_LC_OffTemp,
	var_code_Ad1_FXP2_Htr_DC_OnTemp,
	var_code_Ad1_FXP2_Htr_DC_OffTemp,
	var_code_Ad1_FXP2_Cool_LC_OnTemp,
	var_code_Ad1_FXP2_Cool_LC_OffTemp,
	var_code_Ad1_FXP2_Cool_DC_OnTemp,
	var_code_Ad1_FXP2_Cool_DC_OffTemp,
	var_code_Ad1_FXP2_Hum_LC_OnHum,
	var_code_Ad1_FXP2_Hum_LC_OffHum,
	var_code_Ad1_FXP2_Hum_DC_OnHum,
	var_code_Ad1_FXP2_Hum_DC_OffHum,
	var_code_Ad1_FXP2_DeH_LC_OnHum,
	var_code_Ad1_FXP2_DeH_LC_OffHum,
	var_code_Ad1_FXP2_DeH_DC_OnHum,
	var_code_Ad1_FXP2_DeH_DC_OffHum,
	
	var_code_Ad1_FXP2_Co2_Opnlp_InjTime,
	var_code_Ad1_FXP2_Co2_CylGen,
	
	var_code_Ad1_FXP2_Co2_Cyl_StPtPPM,
	var_code_Ad1_FXP2_Co2_Gen_OnPPM,
	var_code_Ad1_FXP2_Co2_Gen_OffPPM
};

#endif // EEPROM_DATA_H_

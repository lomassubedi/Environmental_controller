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
// Profile size 522 Bytes 
//#define			PROFILE_SIZE		522

//uint8_t read_buffr_EEPROM[PROFILE_SIZE];

typedef __packed struct profile {
	
	TRISTATE_OPERATION_MODE Ad1_Light_Operation_Mode;
	
	TIME_M Ad1_Light_OnTime;
	TIME_M Ad1_Light_OffTime;

	TIME_M Ad1_Light_LC_Duration;
	TIME_M Ad1_Light_DC_Duration;
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
	
	TIME_M Ad1_Cir_FlexFunc_RptTmr;
	
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

} PROFILE ;
// --- 20 profile decleration ---
extern PROFILE *profile1;
extern PROFILE *profile2;

/*
extern PROFILE profile2;
extern PROFILE profile3;
extern PROFILE profile4;
extern PROFILE profile5;
extern PROFILE profile6;
extern PROFILE profile7;
extern PROFILE profile8;
extern PROFILE profile9;
extern PROFILE profile10;
extern PROFILE profile11;
extern PROFILE profile12;
extern PROFILE profile13;
extern PROFILE profile14;
extern PROFILE profile15;
extern PROFILE profile16;
extern PROFILE profile17;
extern PROFILE profile18;
extern PROFILE profile19;
extern PROFILE profile20;
*/

//extern void init_profile1(void);

//extern void init_profile2(void);

#endif // EEPROM_DATA_H_

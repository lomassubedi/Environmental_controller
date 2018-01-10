// File Name: eeprom_data.c
// Author: Lomas
// Date: 07-10-2017

#include "eeprom_data.h"

uint8_t active_profile;

TOOLS dummyInitTools = {
	1,						// Ad1_DeviceType
	
	METRIC,				// Ad1_Tools_Units_EnglishMetric
	
	YES,					// Ad1_Tools_Sensor_Fault
	YES,					// Ad1_Tools_ACFault_Message_YesNo
	YES,					// Ad1_Tools_LoTemp_Warning_YesNo
	YES,					// Ad1_Tools_LoTemp_Warning_StPt
	YES,					// Ad1_Tools_HiTemp_Warning_YesNo
	
	38.0,					// Ad1_Tools_HiTemp_Warning_StPt
	
	YES,					// Ad1_Tools_LoHum_Warning_YesNo
	
	30.0,					// Ad1_Tools_LoHum_Warning_StPt
	
	YES,					// Ad1_Tools_HiHum_Warning_YesNo
	
	70.0,					// Ad1_Tools_HiHum_Warning_StPt
	
	YES,					// Ad1_Tools_Critical_OverTemp_Fault_YesNo
	YES,					// Ad1_Tools_Critical_OverTemp_Fault_Flag
	
	38.0,					// Ad1_Tools_Critical_OverTemp_StPt
	
	// TODO Need to see this variable type again 
	YES,					// Ad1_Tools_Critical_OverTemp_Response
	YES,					// Ad1_Tools_Critical_OverTemp_Message_YesNo
	
	YES,					// Ad1_Tools_ReStrike_Fault_YesNo  
	
	/* --- This variable has been moved to TEMP FLAGS ----
	YES,					// Ad1_Tools_ReStrike_Fault_Flag
	 ---------------------------------------------------- */
	{0, 0, 0},		// Ad1_Tools_ReStrike_Delay_Time
	
	YES,					// Ad1_Tools_ReStrike_Message_YesNo
	YES,					// Ad1_Tools_LoBat_Fault_Message_YesNo
	0.0,					// Ad1_Tools_Batt_Current_Volt
	1400,						// Ad1_Tools_Light_Relay_Cycle_Counter
	0,						// Ad1_Tools_HdVent_Relay_Cycle_Counter
	0,						// Ad1_Tools_Circ_Relay_Cycle_Counter
	0,						// Ad1_Tools_Vent_Relay_Cycle_Counter
	0,						// Ad1_Tools_FXP1_Relay_Cycle_Counter
	0,						// Ad1_Tools_FXP2_Relay_Cycle_Counter
	
	OPEN,					// Ad1_Tools_Switch_YesNo
	
	{0, 5, 0},		// Ad1_Tools_HdVent_DC_DeAct_FactSet_Delay
	{0, 5, 0},		// Ad1_Tools_CO2_PVA_PostVent_FactSet_Delay
	ON,						// Ad1_Tools_LED_OnOff	
};

TOOLS *tools = &dummyInitTools;

PROFILE dummyInitProfile = {
	NORMAL,					// Ad1_Light_Operation_Mode
	{0, 0, 0},			// Ad1_Light_OnTime
	{1, 0, 0},			// Ad1_Light_OffTime
	{0, 0, 0},			// Ad1_Light_LC_Duration
	{0, 0, 0},			// Ad1_Light_DC_Duration
	{0, 0, 0},			// Ad1_Light_LC_TimeRemain
	{0, 0, 0},			// Ad1_Light_DC_TimeRemain
	
	ON,							// Ad1_HdV_OnOff
	ON,							// Ad1_HdV_LC_OnOff
	
	{0, 0, 0},			// Ad1_HdV_LC_SrtDly
	
	ON,							// Ad1_HdV_DC_OnOff
	
	{0, 0, 0},    	// Ad1_HdV_DC_SrtDly
	
	NO,							// Ad1_HdV_FlexFunc_YesNo
	YES,						// Ad1_HdV_FlexFunc_RptTmr
	NO,							// Ad1_HdV_FlexFunc_Heat
	NO,							// Ad1_HdV_FlexFunc_Cool
	NO,							// Ad1_HdV_FlexFunc_Hum
	NO,							// Ad1_HdV_FlexFunc_DeHum
	NO,							// Ad1_HdV_FlexFunc_CO2
	NO,							// Ad1_HdV_FlexFunc_Follow
	
	NO,							// Ad1_HdV_FlexFunc_Flip
	
	NO,							// Ad1_HdV_VentLoc_YesNo
	
	{0, 5, 0},			// Ad1_HdV_Tmr_LC_CclTime
	{1, 30, 0},			// Ad1_HdV_Tmr_LC_RptAftr
	{0, 5, 0},			// Ad1_HdV_Tmr_DC_CclTime
	{1, 30, 0},			// Ad1_HdV_Tmr_DC_RptAftr

	18.0,  					// Ad1_HdV_Htr_LC_OnTemp
	21.0,						// Ad1_HdV_Htr_LC_OffTemp
	18.0,						// Ad1_HdV_Htr_DC_OnTemp
	21.0,						// Ad1_HdV_Htr_DC_OffTemp
	21.0,						// Ad1_HdV_Cool_LC_OnTemp
	18.0,						// Ad1_HdV_Cool_LC_OffTemp
	21.0,						// Ad1_HdV_Cool_DC_OnTemp
	18.0,						// Ad1_HdV_Cool_DC_OffTemp
	
	50.0,						// Ad1_HdV_Hum_LC_OnHum
	60.0,						// Ad1_HdV_Hum_LC_OffHum
	50.0,						// Ad1_HdV_Hum_DC_OnHum
	60.0,						// Ad1_HdV_Hum_DC_OffHum
	60.0,						// Ad1_HdV_DeH_LC_OnHum
	50.0,						// Ad1_HdV_DeH_LC_OffHum
	60.0,						// Ad1_HdV_DeH_DC_OnHum
	50.0,						// Ad1_HdV_DeH_DC_OffHum
	
	{0, 3, 0},			// Ad1_HdV_Co2_Opnlp_InjTime
	
	YES,						// Ad1_HdV_Co2_CylGen;
	
	1500,						// Ad1_HdV_Co2_Cyl_StPtPPM;
	1500, 					// Ad1_HdV_Co2_Gen_OnPPM;
	100,						// Ad1_HdV_Co2_Gen_OffPPM;
	
	ON,							// Ad1_Cir_OnOff;
	OFF,						// Ad1_Cir_LC_OnOff;
	
	{0,0,0},				// Ad1_Cir_LC_SrtDly;
	
	ON,							// Ad1_Cir_DC_OnOff;
	
	{0,0,0},				// Ad1_Cir_DC_SrtDly;
	
	NO, 						// Ad1_Cir_FlexFunc_YesNo;
	
	YES,						// Ad1_Cir_FlexFunc_RptTmr;
	
	NO,							// Ad1_Cir_FlexFunc_Heat;
	NO, 						// Ad1_Cir_FlexFunc_Cool;
	NO,							// Ad1_Cir_FlexFunc_Hum;
	NO, 						// Ad1_Cir_FlexFunc_DeHum;
	NO, 						// Ad1_Cir_FlexFunc_CO2;
	NO, 						// Ad1_Cir_FlexFunc_Follow;
	
	NO, 						// Ad1_Cir_FlexFunc_Flip;
	NO,							// Ad1_Cir_VentLoc_YesNo;
	
	{0, 5, 0},			// Ad1_Cir_Tmr_LC_CclTime;
	{1, 30, 0},			// Ad1_Cir_Tmr_LC_RptAftr;
	{0, 5, 0},			// Ad1_Cir_Tmr_DC_CclTime;
	{1, 30, 0},			// Ad1_Cir_Tmr_DC_RptAftr;
	
	18.0,						// Ad1_Cir_Htr_LC_OnTemp;
	21.0,						// Ad1_Cir_Htr_LC_OffTemp;
	18.0,						// Ad1_Cir_Htr_DC_OnTemp;
	21.0,						// Ad1_Cir_Htr_DC_OffTemp;
	21.0,						// Ad1_Cir_Cool_LC_OnTemp;
	18.0,						// Ad1_Cir_Cool_LC_OffTemp;
	21.0,						// Ad1_Cir_Cool_DC_OnTemp;
	18.0,						// Ad1_Cir_Cool_DC_OffTemp;
	
	50.0,						// Ad1_Cir_Hum_LC_OnHum;
	60.0,						// Ad1_Cir_Hum_LC_OffHum;
	50.0,						// Ad1_Cir_Hum_DC_OnHum;
	60.0,						// Ad1_Cir_Hum_DC_OffHum;
	60.0,						// Ad1_Cir_DeH_LC_OnHum;
	50.0,						// Ad1_Cir_DeH_LC_OffHum;
	60.0,						// Ad1_Cir_DeH_DC_OnHum;
	50.0,						// Ad1_Cir_DeH_DC_OffHum;
	
	{0, 3, 0},			// Ad1_Cir_Co2_Opnlp_InjTime;
	CYL,						// Ad1_Cir_Co2_CylGen;
	
	1500,						// Ad1_Cir_Co2_Cyl_StPtPPM;
	1500,						// Ad1_Cir_Co2_Gen_OnPPM;
	100,						// Ad1_Cir_Co2_Gen_OffPPM;
	
	ON,							// Ad1_Ven_OnOff;
	ON,							// Ad1_Ven_LC_OnOff;
	
	{0, 0, 0},			// Ad1_Ven_LC_SrtDly;
	
	ON,							// Ad1_Ven_RptVnt_LC_OnOff;
	
	{0, 5, 0},			// Ad1_Ven_RptVnt_LC_CclTime;
	{1, 30, 0},			// Ad1_Ven_RptVnt_LC_RptAftr;
	
	ON,							// Ad1_Ven_TempVnt_OnOff;
	27.0,						// Ad1_Ven_TempVnt_LC_OnTemp;
	3.0,						// Ad1_Ven_TempVnt_LC_OffTemp;
	
	ON,							// Ad1_Ven_HumVnt_OnOff;
	
	50.0,						// Ad1_Ven_LC_HumVnt_OnHum;
	10.0,						// Ad1_Ven_LC_HumVnt_OffHum;
	
	ON,							// Ad1_Ven_DC_OnOff;
	
	{0, 0, 0},			// Ad1_Ven_DC_SrtDly;
	
	ON,							// Ad1_Ven_RptVnt_DC_OnOff;
	
	{0, 5, 0},			// Ad1_Ven_RptVnt_DC_CclTime;
	
	{1, 30, 0}, 		// Ad1_Ven_RptVnt_DC_RptAftr;
	
	// ------------ Repeated Varible -----------
	//	BOOL Ad1_Ven_TempVnt_OnOff;
	
	27.0,					// Ad1_Ven_TempVnt_DC_OnTemp;
	3.0,					// Ad1_Ven_TempVnt_DC_OffTemp;
	
	// ---- Repeated Variable ------
	//	BOOL Ad1_Ven_HumVnt_OnOff;
	
	50.0,					// Ad1_Ven_HumVnt_DC_OnHum;
	10.0,					// Ad1_Ven_HumVnt_DC_OffHum;
	
	ON,						// Ad1_FXP1_OnOff;
	ON,						// Ad1_FXP1_LC_OnOff;
	
	{0, 0, 0},		// Ad1_FXP1_LC_SrtDly;
	ON,						// Ad1_FXP1_DC_OnOff;
	
	{0, 0, 0},		// Ad1_FXP1_DC_SrtDly;     
	
	NO, 					// Ad1_FXP1_FlexFunc_YesNo;
	YES,					// Ad1_FXP1_FlexFunc_RptTmr;
	NO, 					// Ad1_FXP1_FlexFunc_Heat;
	NO,						// Ad1_FXP1_FlexFunc_Cool;
	NO,						// Ad1_FXP1_FlexFunc_Hum;
	NO,						// Ad1_FXP1_FlexFunc_DeHum;
	NO,						// Ad1_FXP1_FlexFunc_CO2;
	NO,						// Ad1_FXP1_FlexFunc_Follow;
	NO, 					// Ad1_FXP1_FlexFunc_Flip;
	NO, 					// Ad1_FXP1_VentLoc_YesNo;
	
	{0, 5, 0},		// Ad1_FXP1_Tmr_LC_CclTime;
	{1, 30, 0},		// Ad1_FXP1_Tmr_LC_RptAftr;
	{0, 5, 0},		// Ad1_FXP1_Tmr_DC_CclTime;
	{1, 30, 0},		// Ad1_FXP1_Tmr_DC_RptAftr;
	
	18.0,						// Ad1_FXP1_Htr_LC_OnTemp;
	21.0,						// Ad1_FXP1_Htr_LC_OffTemp;
	18.0,						// Ad1_FXP1_Htr_DC_OnTemp;
	21.0,						// Ad1_FXP1_Htr_DC_OffTemp;
	21.0,						// Ad1_FXP1_Cool_LC_OnTemp;
	18.0,						// Ad1_FXP1_Cool_LC_OffTemp;
	21.0,						// Ad1_FXP1_Cool_DC_OnTemp;
	18.0,						// Ad1_FXP1_Cool_DC_OffTemp;
	
	50.0,						// Ad1_FXP1_Hum_LC_OnHum;
	60.0,						// Ad1_FXP1_Hum_LC_OffHum;
	50.0,						// Ad1_FXP1_Hum_DC_OnHum;
	60.0,						// Ad1_FXP1_Hum_DC_OffHum;
	60.0,						// Ad1_FXP1_DeH_LC_OnHum;
	50.0,						// Ad1_FXP1_DeH_LC_OffHum;
	60.0,						// Ad1_FXP1_DeH_DC_OnHum;
	50.0,						// Ad1_FXP1_DeH_DC_OffHum;
	
	{0, 3, 0},			// Ad1_FXP1_Co2_Opnlp_InjTime;
	
	CYL,						// Ad1_FXP1_Co2_CylGen;
	
	1500,						// Ad1_FXP1_Co2_Cyl_StPtPPM;
	1500,						// Ad1_FXP1_Co2_Gen_OnPPM;
	100,						// Ad1_FXP1_Co2_Gen_OffPPM;
	
	ON,							// Ad1_FXP2_OnOff;
	ON,							// Ad1_FXP2_LC_OnOff;
	
	{0, 0, 0},			// Ad1_FXP2_LC_SrtDly;
	
	ON,							// Ad1_FXP2_DC_OnOff;
	
	{0, 0, 0},			// Ad1_FXP2_DC_SrtDly;      
	
	NO,							// Ad1_FXP2_FlexFunc_YesNo;
	YES,						// Ad1_FXP2_FlexFunc_RptTmr;
	NO,							// Ad1_FXP2_FlexFunc_Heat;
	NO,							// Ad1_FXP2_FlexFunc_Cool;
	NO,							// Ad1_FXP2_FlexFunc_Hum;
	NO,							// Ad1_FXP2_FlexFunc_DeHum;
	NO,							// Ad1_FXP2_FlexFunc_CO2;
	NO,							// Ad1_FXP2_FlexFunc_Follow;
	NO,							// Ad1_FXP2_FlexFunc_Flip;
	NO,							// Ad1_FXP2_VentLoc_YesNo;
	
	{0, 5, 0},			// Ad1_FXP2_Tmr_LC_CclTime;
	{1, 30, 0},			// Ad1_FXP2_Tmr_LC_RptAftr;
	{0, 5, 0},			// Ad1_FXP2_Tmr_DC_CclTime;
	{1, 30, 0},			// Ad1_FXP2_Tmr_DC_RptAftr;
	
	18.0,						// Ad1_FXP2_Htr_LC_OnTemp;
	21.0,						// Ad1_FXP2_Htr_LC_OffTemp;
	18.0,						// Ad1_FXP2_Htr_DC_OnTemp;
	21.0,						// Ad1_FXP2_Htr_DC_OffTemp;
	21.0,						// Ad1_FXP2_Cool_LC_OnTemp;
	18.0,						// Ad1_FXP2_Cool_LC_OffTemp;
	21.0,						// Ad1_FXP2_Cool_DC_OnTemp;
	18.0,						// Ad1_FXP2_Cool_DC_OffTemp;
							
	50.0,						// Ad1_FXP2_Hum_LC_OnHum;
	60.0,						// Ad1_FXP2_Hum_LC_OffHum;
	50.0,						// Ad1_FXP2_Hum_DC_OnHum;
	60.0,						// Ad1_FXP2_Hum_DC_OffHum;
	60.0,						// Ad1_FXP2_DeH_LC_OnHum;
	50.0,						// Ad1_FXP2_DeH_LC_OffHum;
	60.0,						// Ad1_FXP2_DeH_DC_OnHum;
	50.0,						// Ad1_FXP2_DeH_DC_OffHum;
	
	{0, 3, 0},			// Ad1_FXP2_Co2_Opnlp_InjTime;
	CYL,						// Ad1_FXP2_Co2_CylGen;
	
	1500,						// Ad1_FXP2_Co2_Cyl_StPtPPM;
	1500,						// Ad1_FXP2_Co2_Gen_OnPPM;
	100							// Ad1_FXP2_Co2_Gen_OffPPM;
};

PROFILE *profile = &dummyInitProfile;

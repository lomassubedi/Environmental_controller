// File Name: eeprom_data.c
// Author: Lomas
// Date: 07-10-2017

#include "eeprom_data.h"

PROFILE dummyInit = {
	NORMAL,				// Ad1_Light_Operation_Mode
	{0, 0, 0},		// Ad1_Light_OnTime
	{1, 0, 0},		// Ad1_Light_OffTime
	{0, 0, 0},		// Ad1_Light_LC_Duration
	{0, 0, 0},		// Ad1_Light_DC_Duration
	{0, 0, 0},		// Ad1_Light_LC_TimeRemain
	{0, 0, 0},		// Ad1_Light_DC_TimeRemain
	
	ON,						// Ad1_HdV_OnOff
	ON,						// Ad1_HdV_LC_OnOff
	
	{0, 0, 0},		// Ad1_HdV_LC_SrtDly
	
	ON,						// Ad1_HdV_DC_OnOff
	
	{0, 0, 0},    // Ad1_HdV_DC_SrtDly
	
	NO,						// Ad1_HdV_FlexFunc_YesNo
	YES,					// Ad1_HdV_FlexFunc_RptTmr
	NO,						// Ad1_HdV_FlexFunc_Heat
	NO,						// Ad1_HdV_FlexFunc_Cool
	NO,						// Ad1_HdV_FlexFunc_Hum
	NO,						// Ad1_HdV_FlexFunc_DeHum
	NO,						// Ad1_HdV_FlexFunc_CO2
	NO,						// Ad1_HdV_FlexFunc_Follow
	
	NO,						// Ad1_HdV_FlexFunc_Flip
	
	NO,						// Ad1_Pr1_HdV_VentLoc_YesNo
	
	{0, 5, 0},		// Ad1_Pr1_HdV_Tmr_LC_CclTime
	{1, 30, 0},		// Ad1_Pr1_HdV_Tmr_LC_RptAftr
	{0, 5, 0},		// Ad1_Pr1_HdV_Tmr_DC_CclTime
	{1, 30, 0},		// Ad1_Pr1_HdV_Tmr_DC_RptAftr

	18.0,  					// Ad1_Pr1_HdV_Htr_LC_OnTemp
	21.0,						// Ad1_Pr1_HdV_Htr_LC_OffTemp
	18.0,						// Ad1_Pr1_HdV_Htr_DC_OnTemp
	21.0,						// Ad1_Pr1_HdV_Htr_DC_OffTemp
	21.0,						// Ad1_Pr1_HdV_Cool_LC_OnTemp
	18.0,						// Ad1_Pr1_HdV_Cool_LC_OffTemp
	21.0,						// Ad1_Pr1_HdV_Cool_DC_OnTemp
	18.0,						// Ad1_Pr1_HdV_Cool_DC_OffTemp
	
	50.0,						// Ad1_Pr1_HdV_Hum_LC_OnHum
	60.0,						// Ad1_Pr1_HdV_Hum_LC_OffHum
	50.0,						// Ad1_Pr1_HdV_Hum_DC_OnHum
	60.0,						// Ad1_Pr1_HdV_Hum_DC_OffHum
	60.0,						// Ad1_Pr1_HdV_DeH_LC_OnHum
	50.0,						// Ad1_Pr1_HdV_DeH_LC_OffHum
	60.0,						// Ad1_Pr1_HdV_DeH_DC_OnHum
	50.0,						// Ad1_Pr1_HdV_DeH_DC_OffHum
	
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
	
	{1, 30, 0}, 			// Ad1_Ven_RptVnt_DC_RptAftr;
	
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

PROFILE *profile = &dummyInit;


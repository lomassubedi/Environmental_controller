// File Name: eeprom_data.h
// Author: Lomas
// Date: 07-10-2017

#ifndef VAR_CODES_H_
#define VAR_CODES_H_

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

#endif // VAR_CODES_H_

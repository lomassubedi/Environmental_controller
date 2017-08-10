#ifndef REG_LIST_H_
#define REG_LIST_H_

enum ROM_PERMANENT_PAGE1 {
	
	Ad1_Tools_Units_EnglishMetric = 0,
	Ad1_Tools_Sensor_Fault,
	Ad1_Tools_ACFault_Message_YesNo,
	Ad1_Tools_LoTemp_Warning_YesNo,
	Ad1_Tools_LoTemp_Warning_StPt,
	Ad1_Tools_HiTemp_Warning_YesNo,
	Ad1_Tools_HiTemp_Warning_StPt,
	Ad1_Tools_LoHum_Warning_YesNo,
	Ad1_Tools_LoHum_Warning_StPt,
	Ad1_Tools_HiHum_Warning_YesNo = Ad1_Tools_LoHum_Warning_StPt + 4,
	Ad1_Tools_HiHum_Warning_StPt,
	Ad1_Tools_Critical_OverTemp_Fault_YesNo = Ad1_Tools_HiHum_Warning_StPt + 4,	
	Ad1_Tools_Critical_OverTemp_StPt,
	
	Ad1_Tools_Critical_OverTemp_Response = Ad1_Tools_Critical_OverTemp_StPt + 4,
	
	Ad1_Tools_Critical_OverTemp_Message_YesNo,
	Ad1_Tools_ReStrike_Fault_YesNo,
	Ad1_Tools_ReStrike_Missing_Pulse,	
	Ad1_Tools_ReStrike_Message_YesNo = Ad1_Tools_ReStrike_Missing_Pulse + 4,
	Ad1_Tools_LoBat_Fault_Message_YesNo,
	Ad1_Tools_Batt_Current_Volt,
	Ad1_Tools_Light_Relay_Cycle_Counter = Ad1_Tools_Batt_Current_Volt + 4,
	Ad1_Tools_HdVent_Relay_Cycle_Counter = Ad1_Tools_Light_Relay_Cycle_Counter + 2,
	Ad1_Tools_Circ_Relay_Cycle_Counter = Ad1_Tools_HdVent_Relay_Cycle_Counter + 2,
	Ad1_Tools_Vent_Relay_Cycle_Counter = Ad1_Tools_Circ_Relay_Cycle_Counter + 2, 
	Ad1_Tools_FXP1_Relay_Cycle_Counter = Ad1_Tools_Vent_Relay_Cycle_Counter + 2,
	Ad1_Tools_FXP2_Relay_Cycle_Counter = Ad1_Tools_FXP1_Relay_Cycle_Counter + 2,
	Ad1_Tools_Switch_YesNo = Ad1_Tools_FXP2_Relay_Cycle_Counter + 2,
	Ad1_Tools_HdVent_DC_DeAct_FactSet_Delay,
	Ad1_Tools_CO2_PVA_PostVent_FactSet_Delay = Ad1_Tools_HdVent_DC_DeAct_FactSet_Delay + 4,
	Ad1_Pr1_Light_Operation_Mode = Ad1_Tools_CO2_PVA_PostVent_FactSet_Delay + 4,
	Ad1_Pr1_Light_OnTime,
	Ad1_Pr1_Light_OffTime = Ad1_Pr1_Light_OnTime + 4,
	Ad1_Pr1_Light_LC_Duration = Ad1_Pr1_Light_OffTime + 4,
	Ad1_Pr1_Light_DC_Duration = Ad1_Pr1_Light_LC_Duration + 4,
	Ad1_Pr1_Light_LC_TimeRemain = Ad1_Pr1_Light_DC_Duration + 4,
	Ad1_Pr1_Light_DC_TimeRemain = Ad1_Pr1_Light_LC_TimeRemain + 4,
	Ad1_Pr1_HdV_OnOff = Ad1_Pr1_Light_DC_TimeRemain + 4,
	Ad1_Pr1_HdV_LC_OnOff,
	Ad1_Pr1_HdV_LC_SrtDly,
	Ad1_Pr1_HdV_DC_OnOff = Ad1_Pr1_HdV_LC_SrtDly + 4, 
	Ad1_Pr1_HdV_DC_SrtDly,   
	Ad1_Pr1_HdV_VentLoc_YesNo = Ad1_Pr1_HdV_DC_SrtDly + 4,

// These variables are redefined
//	Ad1_Pr1_HdV_LC_OnOff,
//	Ad1_Pr1_HdV_DC_OnOff,

	Ad1_Pr1_HdV_FlexFunc,
	Ad1_Pr1_HdV_Tmr_LC_CclTime,
	Ad1_Pr1_HdV_Tmr_LC_RptAftr = Ad1_Pr1_HdV_Tmr_LC_CclTime + 4,
	Ad1_Pr1_HdV_Tmr_DC_CclTime = Ad1_Pr1_HdV_Tmr_LC_RptAftr + 4,
	Ad1_Pr1_HdV_Tmr_DC_RptAftr = Ad1_Pr1_HdV_Tmr_DC_CclTime + 4,
	Ad1_Pr1_HdV_Htr_LC_OnTemp = Ad1_Pr1_HdV_Tmr_DC_RptAftr + 4,
	Ad1_Pr1_HdV_Htr_LC_OffTemp = Ad1_Pr1_HdV_Htr_LC_OnTemp + 4,
	Ad1_Pr1_HdV_Htr_DC_OnTemp = Ad1_Pr1_HdV_Htr_LC_OffTemp + 4,	
	Ad1_Pr1_HdV_Htr_DC_OffTemp = Ad1_Pr1_HdV_Htr_DC_OnTemp + 4
};

enum ROM_PERMANENT_VAR_PAGE2 {
	
	Ad1_Pr1_HdV_Cool_LC_OnTemp = 0,
	Ad1_Pr1_HdV_Cool_LC_OffTemp = Ad1_Pr1_HdV_Cool_LC_OnTemp + 4,	
	Ad1_Pr1_HdV_Cool_DC_OnTemp = Ad1_Pr1_HdV_Cool_LC_OffTemp + 4,
	Ad1_Pr1_HdV_Cool_DC_OffTemp = Ad1_Pr1_HdV_Cool_DC_OnTemp + 4,
	Ad1_Pr1_HdV_Hum_LC_OnHum = Ad1_Pr1_HdV_Cool_DC_OffTemp + 4,
	Ad1_Pr1_HdV_Hum_LC_OffHum = Ad1_Pr1_HdV_Hum_LC_OnHum + 4,
	Ad1_Pr1_HdV_Hum_DC_OnHum = Ad1_Pr1_HdV_Hum_LC_OffHum + 4,
	Ad1_Pr1_HdV_Hum_DC_OffHum = Ad1_Pr1_HdV_Hum_DC_OnHum + 4,
	Ad1_Pr1_HdV_DeH_LC_OnHum = Ad1_Pr1_HdV_Hum_DC_OffHum + 4,
	Ad1_Pr1_HdV_DeH_LC_OffHum = Ad1_Pr1_HdV_DeH_LC_OnHum + 4,
	Ad1_Pr1_HdV_DeH_DC_OnHum = Ad1_Pr1_HdV_DeH_LC_OffHum + 4,
	Ad1_Pr1_HdV_DeH_DC_OffHum = Ad1_Pr1_HdV_DeH_DC_OnHum + 4,
	Ad1_Pr1_HdV_Co2_Opnlp_InjTime = Ad1_Pr1_HdV_DeH_DC_OffHum + 4,
	Ad1_Pr1_HdV_Co2_CylGen = Ad1_Pr1_HdV_Co2_Opnlp_InjTime + 4,
	Ad1_Pr1_HdV_Co2_Cyl_StPtPPM,
	Ad1_Pr1_HdV_Co2_Gen_OnPPM = Ad1_Pr1_HdV_Co2_Cyl_StPtPPM + 2,
	Ad1_Pr1_HdV_Co2_Gen_OffPPM = Ad1_Pr1_HdV_Co2_Gen_OnPPM + 2,
	Ad1_Pr1_Cir_OnOff = Ad1_Pr1_HdV_Co2_Gen_OffPPM + 2,
	Ad1_Pr1_Cir_LC_OnOff,
	Ad1_Pr1_Cir_LC_SrtDly,    
	Ad1_Pr1_Cir_DC_OnOff = Ad1_Pr1_Cir_LC_SrtDly + 4,    
	Ad1_Pr1_Cir_DC_SrtDly,
	Ad1_Pr1_Cir_VentLoc_YesNo = Ad1_Pr1_Cir_DC_SrtDly + 4,
	Ad1_Pr1_Cir_FlexFunc, //70
	
	Ad1_Pr1_Cir_Tmr_LC_CclTime = Ad1_Pr1_Cir_FlexFunc + 4,
	Ad1_Pr1_Cir_Tmr_LC_RptAftr = Ad1_Pr1_Cir_Tmr_LC_CclTime + 4,
	Ad1_Pr1_Cir_Tmr_DC_CclTime = Ad1_Pr1_Cir_Tmr_LC_RptAftr + 4,
	Ad1_Pr1_Cir_Tmr_DC_RptAftr = Ad1_Pr1_Cir_Tmr_DC_CclTime + 4,
	Ad1_Pr1_Cir_Htr_LC_OnTemp = Ad1_Pr1_Cir_Tmr_DC_RptAftr + 4,
	Ad1_Pr1_Cir_Htr_LC_OffTemp = Ad1_Pr1_Cir_Htr_LC_OnTemp + 4,
	Ad1_Pr1_Cir_Htr_DC_OnTemp = Ad1_Pr1_Cir_Htr_LC_OffTemp + 4,
	Ad1_Pr1_Cir_Htr_DC_OffTemp = Ad1_Pr1_Cir_Htr_DC_OnTemp + 4,
	Ad1_Pr1_Cir_Cool_LC_OnTemp = Ad1_Pr1_Cir_Htr_DC_OffTemp + 4,
	Ad1_Pr1_Cir_Cool_LC_OffTemp = Ad1_Pr1_Cir_Cool_LC_OnTemp + 4,
	Ad1_Pr1_Cir_Cool_DC_OnTemp = Ad1_Pr1_Cir_Cool_LC_OffTemp + 4,
	Ad1_Pr1_Cir_Cool_DC_OffTemp = Ad1_Pr1_Cir_Cool_DC_OnTemp + 4,
	Ad1_Pr1_Cir_Hum_LC_OnHum = Ad1_Pr1_Cir_Cool_DC_OffTemp + 4,	
};

enum ROM_PERMANENT_VAR_PAGE3 {
	
	Ad1_Pr1_Cir_Hum_LC_OffHum = 0,
	Ad1_Pr1_Cir_Hum_DC_OnHum = Ad1_Pr1_Cir_Hum_LC_OffHum + 4,
	Ad1_Pr1_Cir_Hum_DC_OffHum = Ad1_Pr1_Cir_Hum_DC_OnHum + 4,
	Ad1_Pr1_Cir_DeH_LC_OnHum = Ad1_Pr1_Cir_Hum_DC_OffHum + 4,
	Ad1_Pr1_Cir_DeH_LC_OffHum = Ad1_Pr1_Cir_DeH_LC_OnHum + 4,
	Ad1_Pr1_Cir_DeH_DC_OnHum = Ad1_Pr1_Cir_DeH_LC_OffHum + 4,
	Ad1_Pr1_Cir_DeH_DC_OffHum = Ad1_Pr1_Cir_DeH_DC_OnHum + 4,
	Ad1_Pr1_Cir_Co2_Opnlp_InjTime = Ad1_Pr1_Cir_DeH_DC_OffHum + 4,
	Ad1_Pr1_Cir_Co2_CylGen = Ad1_Pr1_Cir_Co2_Opnlp_InjTime + 4,
	
	Ad1_Pr1_Cir_Co2_Cyl_StPtPPM,
	Ad1_Pr1_Cir_Co2_Gen_OnPPM = Ad1_Pr1_Cir_Co2_Cyl_StPtPPM + 2,
	Ad1_Pr1_Cir_Co2_Gen_OffPPM = Ad1_Pr1_Cir_Co2_Gen_OnPPM + 2,
	Ad1_Pr1_Ven_OnOff = Ad1_Pr1_Cir_Co2_Gen_OffPPM + 2,
	Ad1_Pr1_Ven_LC_OnOff,
	Ad1_Pr1_Ven_LC_SrtDly,
	Ad1_Pr1_Ven_RptVnt_LC_OnOff = Ad1_Pr1_Ven_LC_SrtDly + 4,
	Ad1_Pr1_Ven_RptVnt_LC_CclTime,
	Ad1_Pr1_Ven_RptVnt_LC_RptAftr = Ad1_Pr1_Ven_RptVnt_LC_CclTime + 4,
	Ad1_Pr1_Ven_TempVnt_OnOff = Ad1_Pr1_Ven_RptVnt_LC_RptAftr + 4,
	
	Ad1_Pr1_Ven_TempVnt_LC_OnTemp,
	Ad1_Pr1_Ven_TempVnt_LC_OffTemp = Ad1_Pr1_Ven_TempVnt_LC_OnTemp + 4,
	Ad1_Pr1_Ven_HumVnt_OnOff = Ad1_Pr1_Ven_TempVnt_LC_OffTemp + 4,
	Ad1_Pr1_Ven_LC_HumVnt_OnHum,
	Ad1_Pr1_Ven_LC_HumVnt_OffHum = Ad1_Pr1_Ven_LC_HumVnt_OnHum + 4,
	Ad1_Pr1_Ven_DC_OnOff = Ad1_Pr1_Ven_LC_HumVnt_OffHum + 4,
	Ad1_Pr1_Ven_DC_SrtDly,
	Ad1_Pr1_Ven_RptVnt_DC_OnOff = Ad1_Pr1_Ven_DC_SrtDly + 4,
	Ad1_Pr1_Ven_RptVnt_DC_CclTime,
	Ad1_Pr1_Ven_RptVnt_DC_RptAftr = Ad1_Pr1_Ven_RptVnt_DC_CclTime + 4,
//	Ad1_Pr1_Ven_TempVnt_OnOff,			// Repeated Variables
	Ad1_Pr1_Ven_TempVnt_DC_OnTemp = Ad1_Pr1_Ven_RptVnt_DC_RptAftr + 4,
	Ad1_Pr1_Ven_TempVnt_DC_OffTemp,
//	Ad1_Pr1_Ven_HumVnt_OnOff,				// Repeated Variables
	Ad1_Pr1_Ven_HumVnt_DC_OnHum = Ad1_Pr1_Ven_TempVnt_DC_OffTemp + 4,
	Ad1_Pr1_Ven_HumVnt_DC_OffHum = Ad1_Pr1_Ven_HumVnt_DC_OnHum + 4,
	Ad1_Pr1_FXP1_OnOff = Ad1_Pr1_Ven_HumVnt_DC_OffHum + 4,
	Ad1_Pr1_FXP1_LC_OnOff,
	Ad1_Pr1_FXP1_LC_SrtDly,
	Ad1_Pr1_FXP1_DC_OnOff = Ad1_Pr1_FXP1_LC_SrtDly + 4,
	Ad1_Pr1_FXP1_DC_SrtDly,      
	Ad1_Pr1_FXP1_VentLoc_YesNo = Ad1_Pr1_FXP1_DC_SrtDly + 4,
	Ad1_Pr1_FXP1_FlexFunc,
	Ad1_Pr1_FXP1_Tmr_LC_CclTime = Ad1_Pr1_FXP1_FlexFunc + 4,	
	Ad1_Pr1_FXP1_Tmr_LC_RptAftr = Ad1_Pr1_FXP1_Tmr_LC_CclTime + 4,
	Ad1_Pr1_FXP1_Tmr_DC_CclTime = Ad1_Pr1_FXP1_Tmr_LC_RptAftr + 4
};

enum ROM_PERMANENT_VAR_PAGE4 {	
	
	Ad1_Pr1_FXP1_Tmr_DC_RptAftr = 0,
	Ad1_Pr1_FXP1_Htr_LC_OnTemp = Ad1_Pr1_FXP1_Tmr_DC_RptAftr + 4,
	Ad1_Pr1_FXP1_Htr_LC_OffTemp = Ad1_Pr1_FXP1_Htr_LC_OnTemp + 4,
	Ad1_Pr1_FXP1_Htr_DC_OnTemp = Ad1_Pr1_FXP1_Htr_LC_OffTemp + 4,
	Ad1_Pr1_FXP1_Htr_DC_OffTemp = Ad1_Pr1_FXP1_Htr_DC_OnTemp + 4,
	Ad1_Pr1_FXP1_Cool_LC_OnTemp = Ad1_Pr1_FXP1_Htr_DC_OffTemp + 4,
	Ad1_Pr1_FXP1_Cool_LC_OffTemp = Ad1_Pr1_FXP1_Cool_LC_OnTemp + 4,
	Ad1_Pr1_FXP1_Cool_DC_OnTemp = Ad1_Pr1_FXP1_Cool_LC_OffTemp + 4,
	Ad1_Pr1_FXP1_Cool_DC_OffTemp = Ad1_Pr1_FXP1_Cool_DC_OnTemp + 4,
	Ad1_Pr1_FXP1_Hum_LC_OnHum = Ad1_Pr1_FXP1_Cool_DC_OffTemp + 4,
	Ad1_Pr1_FXP1_Hum_LC_OffHum = Ad1_Pr1_FXP1_Hum_LC_OnHum + 4,
	Ad1_Pr1_FXP1_Hum_DC_OnHum = Ad1_Pr1_FXP1_Hum_LC_OffHum + 4,
	Ad1_Pr1_FXP1_Hum_DC_OffHum = Ad1_Pr1_FXP1_Hum_DC_OnHum + 4,
	Ad1_Pr1_FXP1_DeH_LC_OnHum = Ad1_Pr1_FXP1_Hum_DC_OffHum + 4,
	Ad1_Pr1_FXP1_DeH_LC_OffHum = Ad1_Pr1_FXP1_DeH_LC_OnHum + 4,
	Ad1_Pr1_FXP1_DeH_DC_OnHum = Ad1_Pr1_FXP1_DeH_LC_OffHum + 4,
	Ad1_Pr1_FXP1_DeH_DC_OffHum = Ad1_Pr1_FXP1_DeH_DC_OnHum  + 4,
	Ad1_Pr1_FXP1_Co2_Opnlp_InjTime = Ad1_Pr1_FXP1_DeH_DC_OffHum + 4,
	Ad1_Pr1_FXP1_Co2_CylGen = Ad1_Pr1_FXP1_Co2_Opnlp_InjTime + 4,
	
	Ad1_Pr1_FXP1_Co2_Cyl_StPtPPM = Ad1_Pr1_FXP1_Co2_CylGen + 4,
	Ad1_Pr1_FXP1_Co2_Gen_OnPPM = Ad1_Pr1_FXP1_Co2_Cyl_StPtPPM + 4,
	Ad1_Pr1_FXP1_Co2_Gen_OffPPM = Ad1_Pr1_FXP1_Co2_Gen_OnPPM + 4
	
//	Ad1_Pr1_FXP2_OnOff
//	Ad1_Pr1_FXP2_LC_OnOff
//	Ad1_Pr1_FXP2_LC_SrtDly
//	Ad1_Pr1_FXP2_DC_OnOff
//	Ad1_Pr1_FXP2_DC_SrtDly      
//	Ad1_Pr1_FXP2_VentLoc_YesNo
//	Ad1_Pr1_FXP2_FlexFunc
//	Ad1_Pr1_FXP2_Tmr_LC_CclTime
//	Ad1_Pr1_FXP2_Tmr_LC_RptAftr
//	Ad1_Pr1_FXP2_Tmr_DC_CclTime
//	Ad1_Pr1_FXP2_Tmr_DC_RptAftr
//	Ad1_Pr1_FXP2_Htr_LC_OnTemp
//	Ad1_Pr1_FXP2_Htr_LC_OffTemp
//	Ad1_Pr1_FXP2_Htr_DC_OnTemp
//	Ad1_Pr1_FXP2_Htr_DC_OffTemp
//	Ad1_Pr1_FXP2_Cool_LC_OnTemp
//	Ad1_Pr1_FXP2_Cool_LC_OffTemp
//	Ad1_Pr1_FXP2_Cool_DC_OnTemp
//	Ad1_Pr1_FXP2_Cool_DC_OffTemp
//	Ad1_Pr1_FXP2_Hum_LC_OnHum
//	Ad1_Pr1_FXP2_Hum_LC_OffHum
//	Ad1_Pr1_FXP2_Hum_DC_OnHum
//	Ad1_Pr1_FXP2_Hum_DC_OffHum
//	Ad1_Pr1_FXP2_DeH_LC_OnHum
//	Ad1_Pr1_FXP2_DeH_LC_OffHum
//	Ad1_Pr1_FXP2_DeH_DC_OnHum
//	Ad1_Pr1_FXP2_DeH_DC_OffHum
//	Ad1_Pr1_FXP2_Co2_Opnlp_InjTime
//	Ad1_Pr1_FXP2_Co2_CylGen

};

#endif // REG_LIST_H_

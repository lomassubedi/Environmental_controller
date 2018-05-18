
varCodeTools = [
	"DeviceType",
	"Tools_Units_EnglishMetric",
	"Tools_Sensor_Fault",
	"Tools_ACFault_Message_YesNo",
	"Tools_LoTemp_Warning_YesNo",	
	"Tools_LoTemp_Warning_StPt",
	"Tools_HiTemp_Warning_YesNo",	
	"Tools_HiTemp_Warning_StPt",
	"Tools_LoHum_Warning_YesNo",	
	"Tools_LoHum_Warning_StPt",
	"Tools_HiHum_Warning_YesNo",	
	"Tools_HiHum_Warning_StPt",	
	"Tools_Critical_OverTemp_Fault_YesNo",
	"Tools_Critical_OverTemp_Fault_Flag",	
	"Tools_Critical_OverTemp_StPt",	
	"Tools_Critical_OverTemp_Response",
	"Tools_Critical_OverTemp_Message_YesNo",
	"Tools_ReStrike_Fault_YesNo",			
	"Tools_ReStrike_Delay_Time",	
	"Tools_ReStrike_Message_YesNo",
	"Tools_LoBat_Fault_Message_YesNo",	
	"Tools_Batt_Current_Volt",	
	"Tools_Light_Relay_Cycle_Counter",
	"Tools_HdVent_Relay_Cycle_Counter",
	"Tools_Circ_Relay_Cycle_Counter",
	"Tools_Vent_Relay_Cycle_Counter",
	"Tools_FXP1_Relay_Cycle_Counter",
	"Tools_FXP2_Relay_Cycle_Counter",	
	"Tools_Switch_YesNo",
	"Tools_HdVent_DC_DeAct_FactSet_Delay",
	"Tools_CO2_PVA_PostVent_FactSet_Delay",
	"Tools_LED_OnOff"
]

varCodeProfile = [
	"Light_Operation_Mode",	
	"Light_OnTime",
	"Light_OffTime",

	"Light_LC_Duration",
	"Light_DC_Duration",
	"Light_LC_TimeRemain",
	"Light_DC_TimeRemain",
	
	"HdV_OnOff",
	"HdV_LC_OnOff",
	
	"HdV_LC_SrtDly",
	
	"HdV_DC_OnOff", 
	
	"HdV_DC_SrtDly",   
	
	"HdV_FlexFunc_YesNo",
	"HdV_FlexFunc_RptTmr",
	"HdV_FlexFunc_Heat",
	"HdV_FlexFunc_Cool",
	"HdV_FlexFunc_Hum",
	"HdV_FlexFunc_DeHum",
	"HdV_FlexFunc_CO2",
	"HdV_FlexFunc_Follow",
	"HdV_FlexFunc_Flip",
	"HdV_VentLoc_YesNo",
	
	"HdV_Tmr_LC_CclTime",
	"HdV_Tmr_LC_RptAftr",
	"HdV_Tmr_DC_CclTime",
	"HdV_Tmr_DC_RptAftr",
	
	"HdV_Htr_LC_OnTemp",
	"HdV_Htr_LC_OffTemp",
	"HdV_Htr_DC_OnTemp",
	"HdV_Htr_DC_OffTemp",
	"HdV_Cool_LC_OnTemp",
	"HdV_Cool_LC_OffTemp",
	"HdV_Cool_DC_OnTemp",
	"HdV_Cool_DC_OffTemp",
	"HdV_Hum_LC_OnHum",
	"HdV_Hum_LC_OffHum",
	"HdV_Hum_DC_OnHum",
	"HdV_Hum_DC_OffHum",
	"HdV_DeH_LC_OnHum",
	"HdV_DeH_LC_OffHum",
	"HdV_DeH_DC_OnHum",
	"HdV_DeH_DC_OffHum",
	
	"HdV_Co2_Opnlp_InjTime",
	
	"HdV_Co2_CylGen",
	
	"HdV_Co2_Cyl_StPtPPM",
	"HdV_Co2_Gen_OnPPM",
	"HdV_Co2_Gen_OffPPM",
	
	"Cir_OnOff",
	"Cir_LC_OnOff",
	
	"Cir_LC_SrtDly",
	
	"Cir_DC_OnOff",
	
	"Cir_DC_SrtDly",
	
	"Cir_FlexFunc_YesNo",
	"Cir_FlexFunc_RptTmr",
	"Cir_FlexFunc_Heat",
	"Cir_FlexFunc_Cool",
	"Cir_FlexFunc_Hum",
	"Cir_FlexFunc_DeHum",
	"Cir_FlexFunc_CO2",
	"Cir_FlexFunc_Follow",
	
	"Cir_FlexFunc_Flip",
	"Cir_VentLoc_YesNo",
	
	"Cir_Tmr_LC_CclTime",
	"Cir_Tmr_LC_RptAftr",
	"Cir_Tmr_DC_CclTime",
	"Cir_Tmr_DC_RptAftr",
	
	"Cir_Htr_LC_OnTemp",
	"Cir_Htr_LC_OffTemp",
	"Cir_Htr_DC_OnTemp",
	"Cir_Htr_DC_OffTemp",
	"Cir_Cool_LC_OnTemp",
	"Cir_Cool_LC_OffTemp",
	"Cir_Cool_DC_OnTemp",
	"Cir_Cool_DC_OffTemp",
	"Cir_Hum_LC_OnHum",
	"Cir_Hum_LC_OffHum",
	"Cir_Hum_DC_OnHum",
	"Cir_Hum_DC_OffHum",
	"Cir_DeH_LC_OnHum",
	"Cir_DeH_LC_OffHum",
	"Cir_DeH_DC_OnHum",
	"Cir_DeH_DC_OffHum",
	
	"Cir_Co2_Opnlp_InjTime",
	"Cir_Co2_CylGen",
	
	"Cir_Co2_Cyl_StPtPPM",
	"Cir_Co2_Gen_OnPPM",
	"Cir_Co2_Gen_OffPPM",
	
	"Ven_OnOff",
	"Ven_LC_OnOff",
	
	"Ven_LC_SrtDly",
	
	"Ven_RptVnt_LC_OnOff",
	
	"Ven_RptVnt_LC_CclTime",
	"Ven_RptVnt_LC_RptAftr",
	
	"Ven_TempVnt_OnOff",
	"Ven_TempVnt_LC_OnTemp",
	"Ven_TempVnt_LC_OffTemp",
	
	"Ven_HumVnt_OnOff",
	
	"Ven_LC_HumVnt_OnHum",
	"Ven_LC_HumVnt_OffHum",
	
	"Ven_DC_OnOff",
	
	"Ven_DC_SrtDly",
	
	"Ven_RptVnt_DC_OnOff",
	
	"Ven_RptVnt_DC_CclTime",
	
	"Ven_RptVnt_DC_RptAftr",
	
	"Ven_TempVnt_DC_OnTemp",
	"Ven_TempVnt_DC_OffTemp",
	
	"Ven_HumVnt_DC_OnHum",
	"Ven_HumVnt_DC_OffHum",
	
	"FXP1_OnOff",
	"FXP1_LC_OnOff",
	
	"FXP1_LC_SrtDly",
	"FXP1_DC_OnOff",
	
	"FXP1_DC_SrtDly",     
	
	"FXP1_FlexFunc_YesNo",
	"FXP1_FlexFunc_RptTmr",
	"FXP1_FlexFunc_Heat",
	"FXP1_FlexFunc_Cool",
	"FXP1_FlexFunc_Hum",
	"FXP1_FlexFunc_DeHum",
	"FXP1_FlexFunc_CO2",
	"FXP1_FlexFunc_Follow",
	"FXP1_FlexFunc_Flip",
	"FXP1_VentLoc_YesNo",
	
	"FXP1_Tmr_LC_CclTime",
	"FXP1_Tmr_LC_RptAftr",
	"FXP1_Tmr_DC_CclTime",
	"FXP1_Tmr_DC_RptAftr",
	
	"FXP1_Htr_LC_OnTemp",
	"FXP1_Htr_LC_OffTemp",
	"FXP1_Htr_DC_OnTemp",
	"FXP1_Htr_DC_OffTemp",
	"FXP1_Cool_LC_OnTemp",
	"FXP1_Cool_LC_OffTemp",
	"FXP1_Cool_DC_OnTemp",
	"FXP1_Cool_DC_OffTemp",
	"FXP1_Hum_LC_OnHum",
	"FXP1_Hum_LC_OffHum",
	"FXP1_Hum_DC_OnHum",
	"FXP1_Hum_DC_OffHum",
	"FXP1_DeH_LC_OnHum",
	"FXP1_DeH_LC_OffHum",
	"FXP1_DeH_DC_OnHum",
	"FXP1_DeH_DC_OffHum",
	
	"FXP1_Co2_Opnlp_InjTime",
	
	"FXP1_Co2_CylGen",
	
	"FXP1_Co2_Cyl_StPtPPM",
	"FXP1_Co2_Gen_OnPPM",
	"FXP1_Co2_Gen_OffPPM",
	
	"FXP2_OnOff",
	"FXP2_LC_OnOff",
	
	"FXP2_LC_SrtDly",
	
	"FXP2_DC_OnOff",
	
	"FXP2_DC_SrtDly",      
	
	"FXP2_FlexFunc_YesNo",
	"FXP2_FlexFunc_RptTmr",
	"FXP2_FlexFunc_Heat",
	"FXP2_FlexFunc_Cool",
	"FXP2_FlexFunc_Hum",
	"FXP2_FlexFunc_DeHum",
	"FXP2_FlexFunc_CO2",
	"FXP2_FlexFunc_Follow",
	"FXP2_FlexFunc_Flip",
	"FXP2_VentLoc_YesNo",
	
	"FXP2_Tmr_LC_CclTime",
	"FXP2_Tmr_LC_RptAftr",
	"FXP2_Tmr_DC_CclTime",
	"FXP2_Tmr_DC_RptAftr",
	
	"FXP2_Htr_LC_OnTemp",
	"FXP2_Htr_LC_OffTemp",
	"FXP2_Htr_DC_OnTemp",
	"FXP2_Htr_DC_OffTemp",
	"FXP2_Cool_LC_OnTemp",
	"FXP2_Cool_LC_OffTemp",
	"FXP2_Cool_DC_OnTemp",
	"FXP2_Cool_DC_OffTemp",
	"FXP2_Hum_LC_OnHum",
	"FXP2_Hum_LC_OffHum",
	"FXP2_Hum_DC_OnHum",
	"FXP2_Hum_DC_OffHum",
	"FXP2_DeH_LC_OnHum",
	"FXP2_DeH_LC_OffHum",
	"FXP2_DeH_DC_OnHum",
	"FXP2_DeH_DC_OffHum",
	
	"FXP2_Co2_Opnlp_InjTime",
	"FXP2_Co2_CylGen",
	
	"FXP2_Co2_Cyl_StPtPPM",
	"FXP2_Co2_Gen_OnPPM",
	"FXP2_Co2_Gen_OffPPM"
]
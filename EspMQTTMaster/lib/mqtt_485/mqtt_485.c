#include "mqtt_485.h"

static const char * varCodeTools[] = {
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
};

static const char * varNameProfile [] = {
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
};

static uint8_t getIntArg(char * arg) {

	if(
		 (!strcmp(arg, "YES")) || (!strcmp(arg, "yes")) 	||
		(!strcmp(arg, "ON")) || (!strcmp(arg, "on"))		||
		(!strcmp(arg, "DARK")) || (!strcmp(arg, "dark"))	||
		(!strcmp(arg, "TRUE")) || (!strcmp(arg, "true"))	||
		(!strcmp(arg, "ALWAYS_ON")) || (!strcmp(arg, "always_on"))	||
		(!strcmp(arg, "CYL")) || (!strcmp(arg, "cyl"))		||
		(!strcmp(arg, "METRIC")) || (!strcmp(arg, "metric"))		||
		(!strcmp(arg, "OPEN")) || (!strcmp(arg, "open"))
		) {
		return YES | ON | DARK | TRUE | ALWAYS_ON | CYL | METRIC | OPEN;
	} else if(
		(!strcmp(arg, "NO")) || (!strcmp(arg, "no")) 		||
		(!strcmp(arg, "LIGHT")) || (!strcmp(arg, "light"))	||
		(!strcmp(arg, "OFF")) || (!strcmp(arg, "off"))		||
		(!strcmp(arg, "FALSE")) || (!strcmp(arg, "false"))	||
		(!strcmp(arg, "ALWAYS_OFF")) || (!strcmp(arg, "always_off"))||
		(!strcmp(arg, "GEN")) || (!strcmp(arg, "gen"))		||
		(!strcmp(arg, "ENGLISH")) || (!strcmp(arg, "english"))		||
		(!strcmp(arg, "CLOSE")) || (!strcmp(arg, "close"))
		) {
		return NO | LIGHT | OFF | FALSE | ALWAYS_OFF | GEN | ENGLISH | CLOSE;
	} else if((!strcmp(arg, "NORMAL")) || (!strcmp(arg, "normal"))) {
		return NORMAL;
	} else {
		return INVALID;
	}
}

unsigned int mqttToFrame(char * prof_num, char * profile_var_name, char * var_command, uint8_t * f, uint16_t * fLen) {
	
	uint16_t indx = 0;
	uint8_t profNum = 0;
	uint8_t i = 0;
	int profInt = 0;

	do {
		uint8_t cVal = (uint8_t)prof_num[i] - 48;
		profInt = profInt * 10;
		profInt = profInt + cVal;	
		i++;	
	} while(prof_num[i]);

	f[indx++] = SLAVE_ID;			// Slave ID 
	f[indx++] = FUNC_WRITE_VAR;		// Function Code
	f[indx++] = profInt;			// Profile Number

	if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_Operation_Mode])) {

		f[indx++] = 1;						// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);	// data Byte
		else
			return INVALID;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_OnTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_OffTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_LC_Duration])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_DC_Duration])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_LC_TimeRemain])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_DC_TimeRemain])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_LC_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_LC_SrtDly])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DC_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DC_SrtDly])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_YesNo])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_RptTmr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Heat])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Cool])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Hum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_DeHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_CO2])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Follow])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Flip])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_VentLoc_YesNo])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Tmr_LC_CclTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Tmr_LC_RptAftr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Tmr_DC_CclTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Tmr_DC_RptAftr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Htr_LC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Htr_LC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Htr_DC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Htr_DC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Cool_LC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Cool_LC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Cool_DC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Cool_DC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Hum_LC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Hum_LC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Hum_DC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Hum_DC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DeH_LC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DeH_LC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DeH_DC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DeH_DC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_Opnlp_InjTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_CylGen])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_Cyl_StPtPPM])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_Gen_OnPPM])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_Gen_OffPPM])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_LC_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_LC_SrtDly])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DC_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DC_SrtDly])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_YesNo])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_RptTmr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Heat])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Cool])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Hum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_DeHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_CO2])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Follow])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Flip])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_VentLoc_YesNo])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Tmr_LC_CclTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Tmr_LC_RptAftr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Tmr_DC_CclTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Tmr_DC_RptAftr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Htr_LC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Htr_LC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Htr_DC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Htr_DC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Cool_LC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Cool_LC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Cool_DC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Cool_DC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Hum_LC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Hum_LC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Hum_DC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Hum_DC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DeH_LC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DeH_LC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DeH_DC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DeH_DC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_Opnlp_InjTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_CylGen])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_Cyl_StPtPPM])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_Gen_OnPPM])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_Gen_OffPPM])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_LC_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_LC_SrtDly])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_LC_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_LC_CclTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_LC_RptAftr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_LC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_LC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_HumVnt_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_LC_HumVnt_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_LC_HumVnt_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_DC_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_DC_SrtDly])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_DC_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_DC_CclTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_DC_RptAftr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_DC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_DC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_HumVnt_DC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_HumVnt_DC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_LC_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_LC_SrtDly])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DC_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DC_SrtDly])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_YesNo])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_RptTmr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Heat])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Cool])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Hum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_DeHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_CO2])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Follow])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Flip])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_VentLoc_YesNo])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Tmr_LC_CclTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Tmr_LC_RptAftr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Tmr_DC_CclTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Tmr_DC_RptAftr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Htr_LC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Htr_LC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Htr_DC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Htr_DC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Cool_LC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Cool_LC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Cool_DC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Cool_DC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Hum_LC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Hum_LC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Hum_DC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Hum_DC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DeH_LC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DeH_LC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DeH_DC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DeH_DC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Co2_Opnlp_InjTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Co2_CylGen])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Co2_Cyl_StPtPPM])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Co2_Gen_OnPPM])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Co2_Gen_OffPPM])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_LC_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_LC_SrtDly])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_DC_OnOff])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_DC_SrtDly])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_YesNo])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_RptTmr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_Heat])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_Cool])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_Hum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_DeHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_CO2])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_Follow])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_Flip])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_VentLoc_YesNo])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Tmr_LC_CclTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Tmr_LC_RptAftr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Tmr_DC_CclTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Tmr_DC_RptAftr])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Htr_LC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Htr_LC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Htr_DC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Htr_DC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Cool_LC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Cool_LC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Cool_DC_OnTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Cool_DC_OffTemp])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Hum_LC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Hum_LC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Hum_DC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Hum_DC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_DeH_LC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_DeH_LC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_DeH_DC_OnHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_DeH_DC_OffHum])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Co2_Opnlp_InjTime])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Co2_CylGen])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Co2_Cyl_StPtPPM])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Co2_Gen_OnPPM])) {

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Co2_Gen_OffPPM])) {

	} else {
		return INVALID;
	}
	uint16_t crc16_val = CRC16(f, indx);
	f[indx++] = (uint8_t)(crc16_val >> 8);
	f[indx++] = (uint8_t)(crc16_val & 0xFF);
	*fLen = indx;
	return 0;
}

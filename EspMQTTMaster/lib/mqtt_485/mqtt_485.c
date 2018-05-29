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

static int8_t getIntArg(char * arg) {

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

static int8_t getIntTime(char * t, uint8_t * ft) {

	if(strlen(t) == 8) {
		ft[0] = ((t[0] - 48) * 10) + (t[1] - 48);
		ft[1] = ((t[3] - 48) * 10) + (t[4] - 48);
		ft[2] = ((t[6] - 48) * 10) + (t[7] - 48);

		if((ft[0] >= 0 && ft[0] <= 23) | (ft[1] >= 0 && ft[1] <= 59) && (ft[2] >= 0 && ft[2] <= 59)) {	
			return 0;	
		} else {
			return INVALID;
		}
	} else {
		return INVALID;
	}
	
}

int8_t mqttToFrame(char * prof_num, char * profile_var_name, char * var_command, uint8_t * f, uint16_t * fLen) {
	
	uint16_t indx = 0;
	uint8_t profNum = 0;
	uint8_t profInt = 0;
	uint8_t bytes_n = 0;
	uint8_t i = 0;

	uint8_t timeBuff[sizeof(TIME_M)];

	union {
		float floatVar;
		uint8_t floatArry[sizeof(float)];
  	} floatVal;

	union {
		uint16_t intVar;
		uint8_t intArry[sizeof(uint16_t)];
	} intVal;

	do {
		uint8_t cVal = (uint8_t)prof_num[i] - 48;
		profInt = profInt * 10;
		profInt = profInt + cVal;	
		i++;	
	} while(prof_num[i]);

	if((profInt < 0) || (profInt > 20))
		return PRF_ERROR;

	f[indx++] = SLAVE_ID;			// Slave ID 
	f[indx++] = FUNC_WRITE_VAR;		// Function Code
	f[indx++] = profInt;			// Profile Number

	if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_Operation_Mode])) {

		f[indx++] = var_code_Ad1_Light_Operation_Mode;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_OnTime])) {

		f[indx++] = var_code_Ad1_Light_OnTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}		

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_OffTime])) {
		f[indx++] = var_code_Ad1_Light_OffTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}		

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_LC_Duration])) {
		f[indx++] = var_code_Ad1_Light_LC_Duration;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}				

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_DC_Duration])) {
		f[indx++] = var_code_Ad1_Light_DC_Duration;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}			

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_LC_TimeRemain])) {
		f[indx++] = var_code_Ad1_Light_LC_TimeRemain;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}				

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_DC_TimeRemain])) {
		
		f[indx++] = var_code_Ad1_Light_DC_TimeRemain;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}	

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_OnOff])) {
		f[indx++] = var_code_Ad1_HdV_OnOff;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_LC_OnOff])) {
		f[indx++] = var_code_Ad1_HdV_LC_OnOff;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_LC_SrtDly])) {
		
		f[indx++] = var_code_Ad1_HdV_LC_SrtDly;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DC_OnOff])) {
		f[indx++] = var_code_Ad1_HdV_DC_OnOff;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DC_SrtDly])) {

		f[indx++] = var_code_Ad1_HdV_DC_SrtDly;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_YesNo])) {
		f[indx++] = var_code_Ad1_HdV_FlexFunc_YesNo;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_RptTmr])) {
		f[indx++] = var_code_Ad1_HdV_FlexFunc_RptTmr;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Heat])) {
		f[indx++] = var_code_Ad1_HdV_FlexFunc_Heat;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Cool])) {
		f[indx++] = var_code_Ad1_HdV_FlexFunc_Cool;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Hum])) {
		f[indx++] = var_code_Ad1_HdV_FlexFunc_Hum;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_DeHum])) {
		f[indx++] = var_code_Ad1_HdV_FlexFunc_DeHum;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_CO2])) {
		f[indx++] = var_code_Ad1_HdV_FlexFunc_CO2;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Follow])) {
		f[indx++] = var_code_Ad1_HdV_FlexFunc_Follow;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Flip])) {
		f[indx++] = var_code_Ad1_HdV_FlexFunc_Flip;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_VentLoc_YesNo])) {
		f[indx++] = var_code_Ad1_HdV_VentLoc_YesNo;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Tmr_LC_CclTime])) {
		f[indx++] = var_code_Ad1_HdV_Tmr_LC_CclTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Tmr_LC_RptAftr])) {
		f[indx++] = var_code_Ad1_HdV_Tmr_LC_RptAftr;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Tmr_DC_CclTime])) {
		f[indx++] = var_code_Ad1_HdV_Tmr_DC_CclTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Tmr_DC_RptAftr])) {
		f[indx++] = var_code_Ad1_HdV_Tmr_DC_RptAftr;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Htr_LC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_Htr_LC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Htr_LC_OffTemp])) {
		
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_Htr_LC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Htr_DC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_Htr_DC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Htr_DC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_Htr_DC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Cool_LC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_Cool_LC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Cool_LC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_Cool_LC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Cool_DC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_Cool_DC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Cool_DC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_Cool_DC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Hum_LC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_Hum_LC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Hum_LC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_Hum_LC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;				
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Hum_DC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_Hum_DC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Hum_DC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_Hum_DC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DeH_LC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_DeH_LC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DeH_LC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_DeH_LC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DeH_DC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_DeH_DC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DeH_DC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_HdV_DeH_DC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += 4;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_Opnlp_InjTime])) {
		f[indx++] = var_code_Ad1_HdV_Co2_Opnlp_InjTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx = indx + 3;
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_CylGen])) {
		f[indx++] = var_code_Ad1_HdV_Co2_CylGen;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_Cyl_StPtPPM])) {
		uint16_t iv = 0;
		f[indx++] = var_code_Ad1_HdV_Co2_Cyl_StPtPPM;
		bytes_n = sizeof(uint16_t);
		f[indx++] = bytes_n;

		sscanf(var_command, "%d", &iv);
		intVal.intVar = iv;
		memcpy(&f[indx], intVal.intArry, sizeof(uint16_t));

		indx += sizeof(uint16_t);

	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_Gen_OnPPM])) {
		uint16_t iv = 0;
		f[indx++] = var_code_Ad1_HdV_Co2_Gen_OnPPM;
		bytes_n = sizeof(uint16_t);
		f[indx++] = bytes_n;

		sscanf(var_command, "%d", &iv);
		intVal.intVar = iv;
		memcpy(&f[indx], intVal.intArry, sizeof(uint16_t));

		indx += sizeof(uint16_t);		
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_Gen_OffPPM])) {
		uint16_t iv = 0;
		f[indx++] = var_code_Ad1_HdV_Co2_Gen_OffPPM;
		bytes_n = sizeof(uint16_t);
		f[indx++] = bytes_n;

		sscanf(var_command, "%d", &iv);
		intVal.intVar = iv;
		memcpy(&f[indx], intVal.intArry, sizeof(uint16_t));

		indx += sizeof(uint16_t);	
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_OnOff])) {
		f[indx++] = var_code_Ad1_Cir_OnOff;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_LC_OnOff])) {
		f[indx++] = var_code_Ad1_Cir_LC_OnOff;	
		f[indx++] = 1;								// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_LC_SrtDly])) {
		f[indx++] = var_code_Ad1_Cir_LC_SrtDly;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DC_OnOff])) {
		f[indx++] = var_code_Ad1_Cir_DC_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DC_SrtDly])) {
		f[indx++] = var_code_Ad1_Cir_DC_SrtDly;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_YesNo])) {
		f[indx++] = var_code_Ad1_Cir_FlexFunc_YesNo;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_RptTmr])) {
		f[indx++] = var_code_Ad1_Cir_FlexFunc_RptTmr;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Heat])) {
		f[indx++] = var_code_Ad1_Cir_FlexFunc_Heat;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Cool])) {
		f[indx++] = var_code_Ad1_Cir_FlexFunc_Cool;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Hum])) {
		f[indx++] = var_code_Ad1_Cir_FlexFunc_Hum;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_DeHum])) {
		f[indx++] = var_code_Ad1_Cir_FlexFunc_DeHum;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_CO2])) {
		f[indx++] = var_code_Ad1_Cir_FlexFunc_CO2;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Follow])) {
		f[indx++] = var_code_Ad1_Cir_FlexFunc_Follow;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Flip])) {
		f[indx++] = var_code_Ad1_Cir_FlexFunc_Flip;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_VentLoc_YesNo])) {
		f[indx++] = var_code_Ad1_Cir_VentLoc_YesNo;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Tmr_LC_CclTime])) {
		f[indx++] = var_code_Ad1_Cir_Tmr_LC_CclTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Tmr_LC_RptAftr])) {
		f[indx++] = var_code_Ad1_Cir_Tmr_LC_RptAftr;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Tmr_DC_CclTime])) {
		f[indx++] = var_code_Ad1_Cir_Tmr_DC_CclTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Tmr_DC_RptAftr])) {
		f[indx++] = var_code_Ad1_Cir_Tmr_DC_RptAftr;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Htr_LC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_Htr_LC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Htr_LC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_Htr_LC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Htr_DC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_Htr_DC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Htr_DC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_Htr_DC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Cool_LC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_Cool_LC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Cool_LC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_Cool_LC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Cool_DC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_Cool_DC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Cool_DC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_Cool_DC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Hum_LC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_Hum_LC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Hum_LC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_Hum_LC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Hum_DC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_Hum_DC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Hum_DC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_Hum_DC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DeH_LC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_DeH_LC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DeH_LC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_DeH_LC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DeH_DC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_DeH_DC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DeH_DC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Cir_DeH_DC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_Opnlp_InjTime])) {
		f[indx++] = var_code_Ad1_Cir_Co2_Opnlp_InjTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_CylGen])) {
		f[indx++] = var_code_Ad1_Cir_Co2_CylGen;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_Cyl_StPtPPM])) {
		uint16_t iv = 0;
		f[indx++] = var_code_Ad1_Cir_Co2_Cyl_StPtPPM;
		bytes_n = sizeof(uint16_t);
		f[indx++] = bytes_n;

		sscanf(var_command, "%d", &iv);
		intVal.intVar = iv;
		memcpy(&f[indx], intVal.intArry, sizeof(uint16_t));

		indx += sizeof(uint16_t);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_Gen_OnPPM])) {
		uint16_t iv = 0;
		f[indx++] = var_code_Ad1_Cir_Co2_Gen_OnPPM;
		bytes_n = sizeof(uint16_t);
		f[indx++] = bytes_n;

		sscanf(var_command, "%d", &iv);
		intVal.intVar = iv;
		memcpy(&f[indx], intVal.intArry, sizeof(uint16_t));

		indx += sizeof(uint16_t);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_Gen_OffPPM])) {
		uint16_t iv = 0;
		f[indx++] = var_code_Ad1_Cir_Co2_Gen_OffPPM;
		bytes_n = sizeof(uint16_t);
		f[indx++] = bytes_n;

		sscanf(var_command, "%d", &iv);
		intVal.intVar = iv;
		memcpy(&f[indx], intVal.intArry, sizeof(uint16_t));

		indx += sizeof(uint16_t);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_OnOff])) {
		f[indx++] = var_code_Ad1_Ven_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_LC_OnOff])) {
		f[indx++] = var_code_Ad1_Ven_LC_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_LC_SrtDly])) {
		f[indx++] = var_code_Ad1_Ven_LC_SrtDly;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_LC_OnOff])) {
		f[indx++] = var_code_Ad1_Ven_RptVnt_LC_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_LC_CclTime])) {
		f[indx++] = var_code_Ad1_Ven_RptVnt_LC_CclTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_LC_RptAftr])) {
		f[indx++] = var_code_Ad1_Ven_RptVnt_LC_RptAftr;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_OnOff])) {
		f[indx++] = var_code_Ad1_Ven_TempVnt_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_LC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Ven_TempVnt_LC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_LC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Ven_TempVnt_LC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_HumVnt_OnOff])) {
		f[indx++] = var_code_Ad1_Ven_HumVnt_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_LC_HumVnt_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Ven_LC_HumVnt_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_LC_HumVnt_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Ven_LC_HumVnt_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_DC_OnOff])) {
		f[indx++] = var_code_Ad1_Ven_DC_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_DC_SrtDly])) {
		f[indx++] = var_code_Ad1_Ven_DC_SrtDly;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_DC_OnOff])) {
		f[indx++] = var_code_Ad1_Ven_RptVnt_DC_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_DC_CclTime])) {
		f[indx++] = var_code_Ad1_Ven_RptVnt_DC_CclTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_DC_RptAftr])) {
		f[indx++] = var_code_Ad1_Ven_RptVnt_DC_RptAftr;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_DC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Ven_TempVnt_DC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_DC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Ven_TempVnt_DC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_HumVnt_DC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Ven_HumVnt_DC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_HumVnt_DC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_Ven_HumVnt_DC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_OnOff])) {
		f[indx++] = var_code_Ad1_FXP1_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_LC_OnOff])) {
		f[indx++] = var_code_Ad1_FXP1_LC_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_LC_SrtDly])) {
		f[indx++] = var_code_Ad1_FXP1_LC_SrtDly;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DC_OnOff])) {
		f[indx++] = var_code_Ad1_FXP1_DC_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DC_SrtDly])) {
		f[indx++] = var_code_Ad1_FXP1_DC_SrtDly;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_YesNo])) {
		f[indx++] = var_code_Ad1_FXP1_FlexFunc_YesNo;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_RptTmr])) {
		f[indx++] = var_code_Ad1_FXP1_FlexFunc_RptTmr;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Heat])) {
		f[indx++] = var_code_Ad1_FXP1_FlexFunc_Heat;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Cool])) {
		f[indx++] = var_code_Ad1_FXP1_FlexFunc_Cool;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Hum])) {
		f[indx++] = var_code_Ad1_FXP1_FlexFunc_Hum;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_DeHum])) {
		f[indx++] = var_code_Ad1_FXP1_FlexFunc_DeHum;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_CO2])) {
		f[indx++] = var_code_Ad1_FXP1_FlexFunc_CO2;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Follow])) {
		f[indx++] = var_code_Ad1_FXP1_FlexFunc_Follow;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Flip])) {
		f[indx++] = var_code_Ad1_FXP1_FlexFunc_Flip;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_VentLoc_YesNo])) {
		f[indx++] = var_code_Ad1_FXP1_VentLoc_YesNo;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Tmr_LC_CclTime])) {
		f[indx++] = var_code_Ad1_FXP1_Tmr_LC_CclTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Tmr_LC_RptAftr])) {
		f[indx++] = var_code_Ad1_FXP1_Tmr_LC_RptAftr;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Tmr_DC_CclTime])) {
		f[indx++] = var_code_Ad1_FXP1_Tmr_DC_CclTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Tmr_DC_RptAftr])) {
		f[indx++] = var_code_Ad1_FXP1_Tmr_DC_RptAftr;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Htr_LC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_Htr_LC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Htr_LC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_Htr_LC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Htr_DC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_Htr_DC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Htr_DC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_Htr_DC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Cool_LC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_Cool_LC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Cool_LC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_Cool_LC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Cool_DC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_Cool_DC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Cool_DC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_Cool_DC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Hum_LC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_Hum_LC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Hum_LC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_Hum_LC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Hum_DC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_Hum_DC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Hum_DC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_Hum_DC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DeH_LC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_DeH_LC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DeH_LC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_DeH_LC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DeH_DC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_DeH_DC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DeH_DC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP1_DeH_DC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Co2_Opnlp_InjTime])) {
		f[indx++] = var_code_Ad1_FXP1_Co2_Opnlp_InjTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Co2_CylGen])) {
		f[indx++] = var_code_Ad1_FXP1_Co2_CylGen;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Co2_Cyl_StPtPPM])) {
		uint16_t iv = 0;
		f[indx++] = var_code_Ad1_FXP1_Co2_Cyl_StPtPPM;
		bytes_n = sizeof(uint16_t);
		f[indx++] = bytes_n;

		sscanf(var_command, "%d", &iv);
		intVal.intVar = iv;
		memcpy(&f[indx], intVal.intArry, sizeof(uint16_t));

		indx += sizeof(uint16_t);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Co2_Gen_OnPPM])) {
		uint16_t iv = 0;
		f[indx++] = var_code_Ad1_FXP1_Co2_Gen_OnPPM;
		bytes_n = sizeof(uint16_t);
		f[indx++] = bytes_n;

		sscanf(var_command, "%d", &iv);
		intVal.intVar = iv;
		memcpy(&f[indx], intVal.intArry, sizeof(uint16_t));

		indx += sizeof(uint16_t);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Co2_Gen_OffPPM])) {
		uint16_t iv = 0;
		f[indx++] = var_code_Ad1_FXP1_Co2_Gen_OffPPM;
		bytes_n = sizeof(uint16_t);
		f[indx++] = bytes_n;

		sscanf(var_command, "%d", &iv);
		intVal.intVar = iv;
		memcpy(&f[indx], intVal.intArry, sizeof(uint16_t));

		indx += sizeof(uint16_t);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_OnOff])) {
		f[indx++] = var_code_Ad1_FXP2_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_LC_OnOff])) {
		f[indx++] = var_code_Ad1_FXP2_LC_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_LC_SrtDly])) {
		f[indx++] = var_code_Ad1_FXP2_LC_SrtDly;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_DC_OnOff])) {
		f[indx++] = var_code_Ad1_FXP2_DC_OnOff;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_DC_SrtDly])) {
		f[indx++] = var_code_Ad1_FXP2_DC_SrtDly;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_YesNo])) {
		f[indx++] = var_code_Ad1_FXP2_FlexFunc_YesNo;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_RptTmr])) {
		f[indx++] = var_code_Ad1_FXP2_FlexFunc_RptTmr;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_Heat])) {
		f[indx++] = var_code_Ad1_FXP2_FlexFunc_Heat;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_Cool])) {
		f[indx++] = var_code_Ad1_FXP2_FlexFunc_Cool;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_Hum])) {
		f[indx++] = var_code_Ad1_FXP2_FlexFunc_Hum;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_DeHum])) {
		f[indx++] = var_code_Ad1_FXP2_FlexFunc_DeHum;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_CO2])) {
		f[indx++] = var_code_Ad1_FXP2_FlexFunc_CO2;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_Follow])) {
		f[indx++] = var_code_Ad1_FXP2_FlexFunc_Follow;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_FlexFunc_Flip])) {
		f[indx++] = var_code_Ad1_FXP2_FlexFunc_Flip;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_VentLoc_YesNo])) {
		f[indx++] = var_code_Ad1_FXP2_VentLoc_YesNo;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Tmr_LC_CclTime])) {
		f[indx++] = var_code_Ad1_FXP2_Tmr_LC_CclTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Tmr_LC_RptAftr])) {
		f[indx++] = var_code_Ad1_FXP2_Tmr_LC_RptAftr;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Tmr_DC_CclTime])) {
		f[indx++] = var_code_Ad1_FXP2_Tmr_DC_CclTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Tmr_DC_RptAftr])) {
		f[indx++] = var_code_Ad1_FXP2_Tmr_DC_RptAftr;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Htr_LC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_Htr_LC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Htr_LC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_Htr_LC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Htr_DC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_Htr_DC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Htr_DC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_Htr_DC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Cool_LC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_Cool_LC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Cool_LC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_Cool_LC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Cool_DC_OnTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_Cool_DC_OnTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Cool_DC_OffTemp])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_Cool_DC_OffTemp;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Hum_LC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_Hum_LC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Hum_LC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_Hum_LC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Hum_DC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_Hum_DC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Hum_DC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_Hum_DC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_DeH_LC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_DeH_LC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_DeH_LC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_DeH_LC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_DeH_DC_OnHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_DeH_DC_OnHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_DeH_DC_OffHum])) {
		float fv = 0.0;
		f[indx++] = var_code_Ad1_FXP2_DeH_DC_OffHum;
		bytes_n = sizeof(float);
		f[indx++] = bytes_n;

		sscanf(var_command, "%f", &fv);
		floatVal.floatVar = fv;
		memcpy(&f[indx], floatVal.floatArry, sizeof(float));

		indx += sizeof(float);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Co2_Opnlp_InjTime])) {
		f[indx++] = var_code_Ad1_FXP2_Co2_Opnlp_InjTime;	
		bytes_n = sizeof(TIME_M);
		f[indx++] = bytes_n;						// number of Bytes

		if(getIntTime(var_command, &f[indx]) < 0) {
			return MSG_ERROR;
		} else {
			indx += sizeof(TIME_M);
		}
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Co2_CylGen])) {
		f[indx++] = var_code_Ad1_FXP2_Co2_CylGen;	
		f[indx++] = sizeof(BOOL);					// number of Bytes
		if(getIntArg(var_command) >= 0) 
			f[indx++] = getIntArg(var_command);		// data Byte
		else
			return MSG_ERROR;
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Co2_Cyl_StPtPPM])) {
		uint16_t iv = 0;
		f[indx++] = var_code_Ad1_FXP2_Co2_Cyl_StPtPPM;
		bytes_n = sizeof(uint16_t);
		f[indx++] = bytes_n;

		sscanf(var_command, "%d", &iv);
		intVal.intVar = iv;
		memcpy(&f[indx], intVal.intArry, sizeof(uint16_t));

		indx += sizeof(uint16_t);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Co2_Gen_OnPPM])) {
		uint16_t iv = 0;
		f[indx++] = var_code_Ad1_FXP2_Co2_Gen_OnPPM;
		bytes_n = sizeof(uint16_t);
		f[indx++] = bytes_n;

		sscanf(var_command, "%d", &iv);
		intVal.intVar = iv;
		memcpy(&f[indx], intVal.intArry, sizeof(uint16_t));

		indx += sizeof(uint16_t);
	} else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP2_Co2_Gen_OffPPM])) {
		uint16_t iv = 0;
		f[indx++] = var_code_Ad1_FXP2_Co2_Gen_OffPPM;
		bytes_n = sizeof(uint16_t);
		f[indx++] = bytes_n;

		sscanf(var_command, "%d", &iv);
		intVal.intVar = iv;
		memcpy(&f[indx], intVal.intArry, sizeof(uint16_t));

		indx += sizeof(uint16_t);
	} else {
		return MSG_ERROR;
	}
	uint16_t crc16_val = CRC16(f, indx);
	f[indx++] = (uint8_t)(crc16_val & 0xFF);
	f[indx++] = (uint8_t)(crc16_val >> 8);
	*fLen = indx;
	return 0;
}

int8_t mqttToPrfFrame(char * prof_num, uint8_t * f, uint16_t * fLen) {
	uint8_t profInt = 0;
	uint8_t i = 0;	
	uint8_t indx = 0;

	do {
		uint8_t cVal = (uint8_t)prof_num[i] - 48;
		profInt = profInt * 10;
		profInt = profInt + cVal;	
		i++;	
	} while(prof_num[i]);	

	if((profInt < 0) || (profInt > 20))
		return PRF_ERROR;

	f[indx++] = SLAVE_ID;			// Slave ID 
	f[indx++] = FUNC_READ_PROF;		// Function Code
	f[indx++] = profInt;			// Profile Number

	uint16_t crc16_val = CRC16(f, indx);
	f[indx++] = (uint8_t)(crc16_val & 0xFF);
	f[indx++] = (uint8_t)(crc16_val >> 8);
	*fLen = indx;

	return 0;
}
#include "stm32f0xx.h"

#include "flags_timers.h"
#include "reg_list.h"
#include <stdint.h>

uint16_t hr, mn, sec;
uint16_t testEnumP1, testEnumP2, testEnumP3, testEnumP5, testEnumP6, testEnumP7;
uint16_t testEnumP10, testEnumP11 , testEnumP12, testEnumP13, testEnumP14, testEnumP15, testEnumP16;
uint16_t testEnum17, testEnum18, testEnum19, testEnum20, testEnum21, testEnum22, testEnum23, testEnum24;
uint16_t testEnum25, testEnum26;

uint16_t testEnumTools, testEnumPr1;
uint16_t i;

int main(void)
{	
  while (1) {				
		hr = timePreviousLightOn.hour;
		mn = timePreviousLightOn.minute;
		sec = timePreviousLightOn.second;
		
//		testEnumP1 = Ad1_Pr1_HdV_Htr_DC_OffTemp;		
//		testEnumP2 = Ad1_Pr1_Cir_Hum_LC_OffHum;
//		testEnumP3 = Ad1_Pr1_FXP1_Tmr_DC_CclTime;
//		testEnumP5 = Ad1_Pr2_FXP1_DC_SrtDly;
//		testEnumP6 = Ad1_Pr2_FXP2_Tmr_DC_CclTime;
//		testEnumP7 = Ad1_Pr3_HdV_Tmr_LC_CclTime;
//		
//		testEnumP10 = Ad1_Pr3_Cir_Htr_LC_OffTemp;				
//		testEnumP11 = Ad1_Pr3_Ven_HumVnt_DC_OnHum;
//		testEnumP12 = Ad1_Pr3_FXP2_FlexFunc;
//		testEnumP13 = Ad1_Pr4_HdV_DC_SrtDly;
//		testEnumP14 = Ad1_Pr4_Cir_Tmr_DC_CclTime;
//		testEnumP15 = Ad1_Pr4_Ven_RptVnt_DC_RptAftr;
//		testEnumP16 = Ad1_Pr4_FXP2_LC_OnOff;
//		
//		testEnum17 = Ad1_Pr5_Light_LC_TimeRemain;
//		testEnum18 = Ad1_Pr5_Cir_VentLoc_YesNo;
//		testEnum19 = Ad1_Pr5_Ven_LC_HumVnt_OffHum;
//		testEnum20 = Ad1_Pr5_FXP1_DeH_DC_OffHum;
//		testEnum21 = Ad1_Pr6_Light_OffTime;
//		testEnum22 = Ad1_Pr6_Cir_LC_OnOff;
//		testEnum23 = Ad1_Pr6_Ven_TempVnt_LC_OnTemp;
//		testEnum24 = Ad1_Pr6_FXP1_Hum_DC_OffHum;
//		testEnum25 = Ad1_Pr6_FXP2_Co2_CylGen;
//		testEnum26 = Ad1_Pr7_HdV_DeH_DC_OnHum;

	testEnumTools = Ad1_Tools_CO2_PVA_PostVent_FactSet_Delay;
	i = Ad1_Pr1_Light_Operation_Mode;
	testEnumPr1 = Ad1_Pr1_FXP2_Co2_Gen_OffPPM;
	testEnum25 = Ad1_Pr20_FXP2_Co2_Gen_OffPPM;
//	Ad1_Pr1_FXP2_Co2_Gen_OffPPM
  }
}

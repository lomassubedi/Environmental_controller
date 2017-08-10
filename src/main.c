#include "stm32f0xx.h"

#include "flags_timers.h"
#include "reg_list.h"

uint16_t hr, mn, sec;
uint16_t testEnumP1, testEnumP2, testEnumP3, testEnumP5, testEnumP6, testEnumP7;

int main(void)
{	
  while (1) {				
		hr = timePreviousLightOn.hour;
		mn = timePreviousLightOn.minute;
		sec = timePreviousLightOn.second;
		
		testEnumP1 = Ad1_Pr1_HdV_Htr_DC_OffTemp;		
		testEnumP2 = Ad1_Pr1_Cir_Hum_LC_OffHum;
		testEnumP3 = Ad1_Pr1_FXP1_Tmr_DC_CclTime;
		testEnumP5 = Ad1_Pr2_FXP1_DC_SrtDly;
		testEnumP6 = Ad1_Pr2_FXP2_Tmr_DC_CclTime;
		testEnumP7 = Ad1_Pr3_HdV_Tmr_LC_CclTime;
		
		
  }
}

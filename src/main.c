#include "stm32f0xx.h"

#include "flags_timers.h"
#include "reg_list.h"

uint16_t hr, mn, sec;
uint16_t testEnumP1, testEnumP2, testEnumP3;

int main(void)
{	
  while (1) {				
		hr = timePreviousLightOn.hour;
		mn = timePreviousLightOn.minute;
		sec = timePreviousLightOn.second;
		
		testEnumP1 = Ad1_Pr1_HdV_Htr_DC_OffTemp;		
		testEnumP2 = Ad1_Pr1_Cir_Hum_LC_OffHum;
		testEnumP3 = Ad1_Pr1_FXP1_Tmr_DC_CclTime;
		
		
  }
}

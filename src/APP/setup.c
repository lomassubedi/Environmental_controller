#include "setup.h"

void set_flag_light_light_yes(void) {
	flagCurrentCycle = LIGHT;
	flagAd1PreviousCycle = LIGHT;
	flagCycleFlipToLightCycle = YES;
	return;
}

void set_flag_dark_dark_yes(void) {
	flagCurrentCycle = DARK;
	flagAd1PreviousCycle = DARK;
	flagCycleFlipToDarkCycle = YES;	
	return;
}

void set_light_dark_duration(void) {
	if((profile->Ad1_Light_OffTime.HH) > (profile->Ad1_Light_OnTime.HH) || \
		(profile->Ad1_Light_OffTime.MM) > (profile->Ad1_Light_OnTime.MM) || \
		(profile->Ad1_Light_OffTime.SS) > (profile->Ad1_Light_OnTime.SS)) {
			
			profile->Ad1_Light_LC_Duration.HH = profile->Ad1_Light_OffTime.HH - profile->Ad1_Light_OnTime.HH;
			profile->Ad1_Light_LC_Duration.MM = profile->Ad1_Light_OffTime.MM - profile->Ad1_Light_OnTime.MM;
			profile->Ad1_Light_LC_Duration.SS = profile->Ad1_Light_OffTime.SS - profile->Ad1_Light_OnTime.SS;
			
			profile->Ad1_Light_DC_Duration.HH = profile->Ad1_Light_LC_Duration.HH;
			profile->Ad1_Light_DC_Duration.MM = profile->Ad1_Light_LC_Duration.MM;
			profile->Ad1_Light_DC_Duration.SS = profile->Ad1_Light_LC_Duration.SS;
			
		} else {
			
			profile->Ad1_Light_LC_Duration.HH = profile->Ad1_Light_OnTime.HH - profile->Ad1_Light_OffTime.HH;
			profile->Ad1_Light_LC_Duration.MM = profile->Ad1_Light_OnTime.MM - profile->Ad1_Light_OffTime.MM;
			profile->Ad1_Light_LC_Duration.SS = profile->Ad1_Light_OnTime.SS - profile->Ad1_Light_OffTime.SS;
			
			profile->Ad1_Light_LC_Duration.HH = profile->Ad1_Light_DC_Duration.HH;
			profile->Ad1_Light_LC_Duration.MM = profile->Ad1_Light_DC_Duration.MM;
			profile->Ad1_Light_LC_Duration.SS = profile->Ad1_Light_DC_Duration.SS;		
		}	
	return;
}

void initial_setup(void) {
	
	RTC_TimeTypeDef nowRTCTime;
	
	if(profile->Ad1_Light_Operation_Mode == ALWAYS_ON) {	
		set_flag_light_light_yes();
		goto Set_Light_Dark_Duration;		
	}
	
	if(profile->Ad1_Light_Operation_Mode == ALWAYS_OFF){		
		set_flag_dark_dark_yes();
		goto Set_Light_Dark_Duration;
	}
		
	if(\
		(nowRTCTime.RTC_Hours == profile->Ad1_Light_OnTime.HH) || \
		(nowRTCTime.RTC_Minutes == profile->Ad1_Light_OnTime.MM) || \
		(nowRTCTime.RTC_Seconds == profile->Ad1_Light_OnTime.SS)) {
		
			set_flag_light_light_yes();
			goto Set_Light_Dark_Duration;
	}
		
	if(\
		(nowRTCTime.RTC_Hours == profile->Ad1_Light_OffTime.HH) || \
		(nowRTCTime.RTC_Minutes == profile->Ad1_Light_OffTime.MM) || \
		(nowRTCTime.RTC_Seconds == profile->Ad1_Light_OffTime.SS)) {
			
			set_flag_light_light_yes();
			goto Set_Light_Dark_Duration;
	}
		
	if(\
		(profile->Ad1_Light_OnTime.HH == profile->Ad1_Light_OffTime.HH) || \
		(profile->Ad1_Light_OnTime.MM == profile->Ad1_Light_OffTime.MM) || \
		(profile->Ad1_Light_OnTime.MM == profile->Ad1_Light_OffTime.SS)) {
		
			set_flag_dark_dark_yes();
			
	}
	
	
	// Set Light dark duration
	Set_Light_Dark_Duration:
	
}
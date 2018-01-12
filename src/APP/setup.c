#include "setup.h"

static void set_flag_light_light_yes(void) {
	flagCurrentCycle = LIGHT;
	flagAd1PreviousCycle = LIGHT;
	flagCycleFlipToLightCycle = YES;
	return;
}

static void set_flag_dark_dark_yes(void) {
	flagCurrentCycle = DARK;
	flagAd1PreviousCycle = DARK;
	flagCycleFlipToDarkCycle = YES;	
	return;
}

static void set_light_dark_duration(void) {
	
	TIME_M highest_time = {24, 0, 0};
	
	// Is Ad1_Light_OffTime > Ad1_Light_OnTime ??
	if(time_cmpr(&profile->Ad1_Light_OffTime, &profile->Ad1_Light_OnTime) == TIME_GREATOR) {
		// Get Ad1_Light_LC_Duration
		time_diff(&profile->Ad1_Light_OffTime, &profile->Ad1_Light_OnTime, &profile->Ad1_Light_LC_Duration);
		
		// Get Ad1_Light_DC_Duration
		time_diff(&highest_time, &profile->Ad1_Light_LC_Duration, &profile->Ad1_Light_DC_Duration);

	} else {
		// Get Ad1_Light_DC_Duration
		time_diff(&profile->Ad1_Light_OnTime, &profile->Ad1_Light_OffTime, &profile->Ad1_Light_DC_Duration);	
		
		// Get Ad1_Light_LC_Duration
		time_diff(&highest_time, &profile->Ad1_Light_DC_Duration, &profile->Ad1_Light_LC_Duration);
	
		}	
	return;
}

void initial_setup(void) {
	
	RTC_TimeTypeDef nowRTCTime;
	TIME_M rtcTime;
	flagAd1CO2Inj = NO;
	
	RTC_GetTime(RTC_Format_BIN, &nowRTCTime);
	
	rtcTime.HH = nowRTCTime.RTC_Hours;
	rtcTime.MM = nowRTCTime.RTC_Minutes;
	rtcTime.SS = nowRTCTime.RTC_Seconds;
	
	// if Ad1_Light_Operation_Mode is always ON
	if(profile->Ad1_Light_Operation_Mode == ALWAYS_ON) {
		set_flag_light_light_yes();	
		set_light_dark_duration();
		
	// If Ad1_Light_Operation_Mode is Always OFF
	} else if(profile->Ad1_Light_Operation_Mode == ALWAYS_OFF){
		set_flag_dark_dark_yes();
		set_light_dark_duration();
		
	// If current time equals Ad1 Light Normal operation On Time
	} else if(time_cmpr(&rtcTime, &profile->Ad1_Light_OnTime) == TIME_EQUAL) {	
		
			set_flag_light_light_yes();
			set_light_dark_duration();
		
	// If current time equals Ad1 Light Normal operation Off Time
	} else if(time_cmpr(&rtcTime, &profile->Ad1_Light_OffTime) == TIME_EQUAL) {
			
			set_flag_dark_dark_yes();
			set_light_dark_duration();
		
	// If Current time is greater than Light Normal Operation ON time
	} else if(time_cmpr(&rtcTime, &profile->Ad1_Light_OnTime) == TIME_GREATOR){
			
			// If Normal Operation OFF time is greater than Normal Operation ON time
			if(time_cmpr(&profile->Ad1_Light_OffTime, &profile->Ad1_Light_OnTime) == TIME_GREATOR) {
				
				// If Current time is greator than Normal Operation OFF time
				if(time_cmpr(&rtcTime, &profile->Ad1_Light_OffTime) == TIME_GREATOR) {
						
						set_flag_dark_dark_yes();
						set_light_dark_duration();
						
				} else {
					set_flag_light_light_yes();
					set_light_dark_duration();
				}				
			} else {
				set_flag_light_light_yes();
				set_light_dark_duration();		
			}
		
	} else if(time_cmpr(&profile->Ad1_Light_OffTime, &profile->Ad1_Light_OnTime) == TIME_EQUAL) {
		
			set_flag_dark_dark_yes();
			set_light_dark_duration();
			
	} else {
		
		if(time_cmpr(&rtcTime, &profile->Ad1_Light_OffTime) == TIME_GREATOR) {
				set_flag_dark_dark_yes();
				set_light_dark_duration();
			} else {
				set_flag_light_light_yes();
				set_light_dark_duration();
			}
	}
}
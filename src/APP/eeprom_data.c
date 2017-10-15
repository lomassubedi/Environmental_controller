// File Name: eeprom_data.c
// Author: Lomas
// Date: 07-10-2017

#include "eeprom_data.h"

//PROFILE profile1 = {
//	NORMAL,
//	
//	
//};

/* 
PROFILE profile2;
PROFILE profile3;
PROFILE profile4;
PROFILE profile5;
PROFILE profile6;
PROFILE profile7;
PROFILE profile8;
PROFILE profile9;
PROFILE profile10;
PROFILE profile11;
PROFILE profile12;
PROFILE profile13;
PROFILE profile14;
PROFILE profile15;
PROFILE profile16;
PROFILE profile17;
PROFILE profile18;
PROFILE profile19;
PROFILE profile20;
*/

// ---- Function to initialize the profile1 data with defaul
//void initProfile1(PROFILE *profile) {
//	profile->Ad1_Light_Operation_Mode = NORMAL;
//	
//	profile->Ad1_Light_OnTime.HH = 0;
//	profile->Ad1_Light_OnTime.MM = 0;
//	profile->Ad1_Light_OnTime.SS = 0;
//	
//	profile->Ad1_Light_OffTime.HH = 0;
//	profile->Ad1_Light_OffTime.MM = 1;
//	profile->Ad1_Light_OffTime.SS = 0;
//	
//}

//void init_profile1(void) {
//	profile1->Ad1_Light_Operation_Mode = NORMAL;
//	
//	profile1->Ad1_Light_OnTime.HH = 2;
//	profile1->Ad1_Light_OnTime.MM = 3;
//	profile1->Ad1_Light_OnTime.SS = 4;
//	
//	
//	profile1->Ad1_Light_OffTime.HH = 5;
//	profile1->Ad1_Light_OffTime.MM = 6;
//	profile1->Ad1_Light_OffTime.SS = 7;
//	
//}

//void init_profile2(void) {
//	
//	profile2->Ad1_Light_Operation_Mode = 1;
//	
//	profile2->Ad1_Light_OnTime.HH = 10;
//	profile2->Ad1_Light_OnTime.MM = 11;
//	profile2->Ad1_Light_OnTime.SS = 12;
//	
//	
//	profile2->Ad1_Light_OffTime.HH = 15;
//	profile2->Ad1_Light_OffTime.MM = 16;
//	profile2->Ad1_Light_OffTime.SS = 17;
//	
//}

PROFILE xyz = {
	NORMAL,
	{2, 3, 4},
	{5, 6, 7}
};

PROFILE *profile1 = &xyz;

PROFILE abc = {
	1,
	{42, 41, 43},
	{61, 62, 73}
};

PROFILE *profile2 = &abc;


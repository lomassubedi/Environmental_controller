
#include "util_prj.h"

void get_ct_date_time(date_time * date_time_struct) {
	uint16_t y;
	uint8_t m;
	uint8_t d;
	
	date_time_struct->year = CMPL_YEAR;
	
	y = CMPL_YEAR;
	
	if(__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
			date_time_struct->month = 1;
	else if(__DATE__[0] == 'F' && __DATE__[1] == 'e' && __DATE__[2] == 'b')
			date_time_struct->month = 2;
	else if(__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
			date_time_struct->month = 3;
	else if(__DATE__[0] == 'A' && __DATE__[1] == 'p' && __DATE__[2] == 'r')
			date_time_struct->month = 4;
	else if(__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
			date_time_struct->month = 5;
	else if(__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
			date_time_struct->month = 6;
	else if(__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
			date_time_struct->month = 7;
	else if(__DATE__[0] == 'A' && __DATE__[1] == 'u' && __DATE__[2] == 'g')
			date_time_struct->month = 8; 
	else if(__DATE__[0] == 'S' && __DATE__[1] == 'e' && __DATE__[2] == 'p')
			date_time_struct->month = 9;
	else if(__DATE__[0] == 'O' && __DATE__[1] == 'c' && __DATE__[2] == 't')
			date_time_struct->month = 10;
	else if(__DATE__[0] == 'N' && __DATE__[1] == 'o' && __DATE__[2] == 'v')
			date_time_struct->month = 11;
	else if(__DATE__[0] == 'D' && __DATE__[1] == 'e' && __DATE__[2] == 'c')
			date_time_struct->month = 12;
	else { /* Do nothing  */ }
	
	m = date_time_struct->month;
	
	if(__DATE__[5] > '0' && __DATE__[5] <= '9') {
		
		if(__DATE__[4] > '0' && __DATE__[4] <= '9') {
			date_time_struct->mday = (__DATE__[4] - '0') * 10 + (__DATE__[5] - '0');
		} else {
			date_time_struct->mday = __DATE__[5] - '0';
		}
	} else {
		date_time_struct->mday = 1;
	}
			
	d = date_time_struct->mday;
		
	date_time_struct->wday = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7; 
	
	date_time_struct->hour = CMPL_HOUR;
	date_time_struct->min = CMPL_MIN;
	date_time_struct->sec = CMPL_SEC;		
}

uint8_t time_cmpr(TIME_M * time_first, TIME_M * time_second) {
		
	if(((time_first->HH * 60 * 60) + (time_first->MM * 60) + time_first->SS) \
		> \
	((time_second->HH * 60 * 60) + (time_second->MM * 60) + time_second->SS)) {		
		return TIME_GREATOR;		// If greator return 1
	} else if(((time_first->HH * 60 * 60) + (time_first->MM * 60) + time_first->SS) \
		== \
	((time_second->HH * 60 * 60) + (time_second->MM * 60) + time_second->SS)){
		return TIME_EQUAL;		// If Equal return 2
	} else {
		return TIME_LESS;		// If Less return 0
	}
}

void time_diff(TIME_M * time_first, TIME_M * time_second, TIME_M * time_dest) {
	
	uint32_t total_second_first = 0, total_second_second = 0, total_second_diff = 0;
	int8_t diff_ind;
	
	total_second_first = (time_first->HH * 60 * 60) + (time_first->MM * 60) + time_first->SS;
	total_second_second = (time_second->HH * 60 * 60) + (time_second->MM * 60) + time_second->SS;
	
//	if(total_second_first > total_second_second) {		
//		total_second_diff = total_second_first - total_second_second;
//		diff_ind = 1;
//	} else {
//		total_second_diff = total_second_second - total_second_first;
//		diff_ind = 0;
//	}
	
	total_second_diff = total_second_first - total_second_second;
	
	time_dest->HH = (total_second_diff / 60) / 60;
	time_dest->MM = (total_second_diff / 60) % 60;
	time_dest->SS = total_second_diff % 60;
	
//	return diff_ind;
	
}
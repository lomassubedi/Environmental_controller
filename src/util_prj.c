
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
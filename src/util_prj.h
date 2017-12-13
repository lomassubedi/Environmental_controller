#ifndef UTIL_PRJ_H_
#define UTIL_PRJ_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>


#define CMPL_YEAR ((__DATE__[7] - '0') * 1000 +  (__DATE__[8] - '0') * 100 + (__DATE__[9] - '0') * 10 + __DATE__[10] - '0')

#define CMPL_DATE ((__DATE__[4] - '0') * 10 + __DATE__[5] - '0')

#if 0
#if (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
    #define CMPL_MONTH  1
#elif (__DATE__[0] == 'F' && __DATE__[1] == 'e' && __DATE__[2] == 'b')
    #define CMPL_MONTH  2
#elif (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
    #define CMPL_MONTH  3
#elif (__DATE__[0] == 'A' && __DATE__[1] == 'p' && __DATE__[2] == 'r')
    #define CMPL_MONTH  4
#elif (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
    #define CMPL_MONTH  5
#elif (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
    #define CMPL_MONTH  6
#elif (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
    #define CMPL_MONTH  7
#elif (__DATE__[0] == 'A' && __DATE__[1] == 'u' && __DATE__[2] == 'g')
    #define CMPL_MONTH  8
#elif (__DATE__[0] == 'S' && __DATE__[1] == 'e' && __DATE__[2] == 'p')
    #define CMPL_MONTH  9
#elif (__DATE__[0] == 'O' && __DATE__[1] == 'c' && __DATE__[2] == 't')
    #define CMPL_MONTH 10
#elif (__DATE__[0] == 'N' && __DATE__[1] == 'o' && __DATE__[2] == 'v')
    #define CMPL_MONTH 11
#elif (__DATE__[0] == 'D' && __DATE__[1] == 'e' && __DATE__[2] == 'c')
    #define CMPL_MONTH 12
#else
    #error "Could not figure out month"
#endif
#endif

#define CMPL_HOUR ((__TIME__[0] - '0') * 10 + __TIME__[1] - '0')
#define CMPL_MIN ((__TIME__[3] - '0') * 10 + __TIME__[4] - '0')
#define CMPL_SEC ((__TIME__[6] - '0') * 10 + __TIME__[7] - '0')

typedef struct {
	uint16_t	year;	/* 1970..2106 */
	uint8_t		month;	/* 1..12 */
	uint8_t		mday;	/* 1..31 */
	uint8_t		hour;	/* 0..23 */
	uint8_t		min;	/* 0..59 */
	uint8_t		sec;	/* 0..59 */
	uint8_t		wday;	/* 0..6 (Sun..Sat) */
} date_time;

void get_ct_date_time(date_time *);

#endif // UTIL_PRJ_H_

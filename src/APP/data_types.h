#ifndef DATA_TYPES_H_
#define DATA_TYPES_H_

#include <stdint.h>

#define 		YES 	1
#define 		NO		0

#define 		OFF		0
#define 		ON		1

#define 		LIGHT		0
#define 		DARK		1

#define 		AM			0
#define 		PM			1

typedef struct mTIME {
	uint8_t HH;
	uint8_t MM;
	uint8_t SS;
} TIME_M;

typedef struct timer {
	uint8_t mn;
	uint8_t sec;
} TIMER;

typedef struct time {
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t amPm;
} TIME;

#endif // DATA_TYPES_H_

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

#define			TRUE		1
#define 		FALSE		0

#define			ALWAYS_OFF	0
#define			ALWAYS_ON		1
#define			NORMAL			2

#define 		CYL					1
#define 		GEN					0

typedef 		uint8_t		BOOL;
typedef			uint8_t 	TRISTATE_OPERATION_MODE;
typedef			uint8_t		CYL_GEN;

typedef __packed struct mTIME {
	uint8_t HH;
	uint8_t MM;
	uint8_t SS;
} TIME_M;

typedef __packed struct timer {
	uint8_t mn;
	uint8_t sec;
} TIMER;

typedef __packed struct time {
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t amPm;
} TIME;

#endif // DATA_TYPES_H_

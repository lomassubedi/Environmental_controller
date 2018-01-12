#ifndef DATA_TYPES_H_
#define DATA_TYPES_H_

#include <stdint.h>

// Decisions constants 
#define 		YES 	1
#define 		NO		0

// Status Constants 
#define 		OFF		0
#define 		ON		1

// --- Light Status Constants ---
#define 		LIGHT		0
#define 		DARK		1

// AM-PM constants
#define 		AM			0
#define 		PM			1

// --- BOOL constants ---
#define			TRUE		1
#define 		FALSE		0

// --- Tri state operation constants -- 
#define			ALWAYS_OFF	0
#define			ALWAYS_ON		1
#define			NORMAL			2

// -- CYCL or GEN Constants ---
#define 		CYL					1
#define 		GEN					0

// --- Unit Standard Flag Constants
#define 		ENGLISH			0
#define 		METRIC			1

// Open / Close Constants
#define 		CLOSE				0
#define			OPEN				1

// Invalid or unknown

#define			INVALID			-1
#define			UNKNOWN			-1

// ---- Typedefs --
typedef 		uint8_t		BOOL;
typedef			uint8_t 	TRISTATE_OPERATION_MODE;
typedef			uint8_t		CYL_GEN;
typedef 		uint8_t 	UNIT_S;
typedef			uint8_t   CYCL_STATE;

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

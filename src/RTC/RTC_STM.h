// File Name: RTC_STM.h
// Author: Lomas
// Date 25 Sept 2017

/* *** Details ***
 * Handling internal RTC of STM Controller 
 * ***/

#ifndef RTC_STM_H_
#define RTC_STM_H_

#include "config.h"
#include "util_prj.h"

// Random Magic Value
#define 	BKP_VALUE		0x32F0

// Use external 32.768KHz low frequency crystal
extern void RTC_Config_LSE(void);

// Use internal low frequency clock
extern void RTC_Config_LSI(void);

#endif // RTC_STM_H_

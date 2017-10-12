// File Name: RTC_STM.h
// Author: Lomas
// Date 25 Sept 2017

/* *** Details ***
 * Handling internal RTC of STM Controller 
 * ***/

#ifndef RTC_STM_H_
#define RTC_STM_H_

#include "stm32f0xx_rtc.h"
#include "stm32f0xx_pwr.h"
#include "stm32f0xx_rcc.h"

#include "util_prj.h"

// Use external 32.768KHz low frequency crystal
extern void RTC_Config_LSE(void);

// Use internal low frequency clock
extern void RTC_Config_LSI(void);

extern RTC_InitTypeDef RTC_InitStructure;

#endif // RTC_STM_H_

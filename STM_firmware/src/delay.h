// File Name: delay.h
// Author: Lomas
// Date 1 jan 2017

#ifndef DELAY_H_
#define DELAY_H_

#include "config.h"

extern volatile uint32_t TimingDelay;	

void Delay(__IO uint32_t nTime);

void TimingDelay_Decrement(void);

#endif 	// End of DELAY_H_


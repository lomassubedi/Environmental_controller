#include <stdint.h>
#include "stm32f0xx.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"

#include "flags_timers.h"
#include "reg_list.h"
#include "stm32f0_discovery.h"

#include "modbus_slave.h"

GPIO_InitTypeDef GPIO_InitStructure;

static __IO uint32_t TimingDelay;

#define LEDToggleValue ((uint16_t) 3000)

extern void Delay(__IO uint32_t nTime) {
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

extern void TimingDelay_Decrement(void) {
  if (TimingDelay != 0x00) {
    TimingDelay--;
  }
}


int main(void) {		
//	uint16_t CurrentCountValue = 0;
//	int timerValue = 0;

	
//	InitializeTimer();
	SysTick_Config(SystemCoreClock / 1000);
	
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	
	init_modbus();
		
  while (1) {			
//		dispFrame();
//		modbus_update();
	}
}

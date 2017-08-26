#include <stdint.h>
#include "stm32f0xx.h"
#include "flags_timers.h"
#include "reg_list.h"
#include "stm32f0_discovery.h"

GPIO_InitTypeDef GPIO_InitStructure;

static __IO uint32_t TimingDelay;

#define LEDToggleValue ((uint16_t) 3000)

void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

extern void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00) {
    TimingDelay--;
  }
}

void init_usart(void) {	
//	/ USART periferial initialization settings
	  USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef	GPIO_InitStructure;

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

	  //Configure USART1 pins: Rx (PA10) and Tx (PA9)
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  //Configure USART1 setting: ----------------------------
	  USART_InitStructure.USART_BaudRate = 115200;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  USART_Init(USART1, &USART_InitStructure);
	  USART_Cmd(USART1,ENABLE);
		
		// USART1 receive Interrupt Enable
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		NVIC_EnableIRQ(USART1_IRQn);
}

/*
init_timer1(void) {
	TIM_TimeBaseInitTypeDef TTB;
	
	TTB.TIM_ClockDivision = TIM_CKD_DIV1;
	TTB.TIM_CounterMode = TIM_CounterMode_Up;
	TTB.TIM_Period = 0xFFFF;
	TTB.TIM_Prescaler = 1000;
	TTB.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TTB);
	TIM_Cmd(TIM1, ENABLE);
	
}
void init_timer6() {
//	RCC_APB1ENR_TIM6EN
//	TIM_TypeDef TIMER6;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	TIM_ARRPreloadConfig(TIM6, ENABLE);
//	TIM_UpdateRequestConfig(TIM6, )
	TIM6->CR1 = TIM_CR1_ARPE | TIM_CR1_URS | TIM_CR1_CEN;
//	TIM6->CR2 = 
//	TIMER6->TIM6_CR1 = 
	TIM6->DIER = TIM_DIER_UIE;
//	TIM6->SR = 
	TIM6->ARR = 240000;
//	TIM_ITConfig();
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	
}

void TIM6_DAC_IRQHandler() {
	STM_EVAL_LEDToggle(LED4);
}*/

void InitializeTimer()
{
	 TIM_TimeBaseInitTypeDef timerInitStructure; 
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
    timerInitStructure.TIM_Prescaler = 47;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 3646;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInitStructure);
    TIM_Cmd(TIM2, ENABLE);
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
		NVIC_EnableIRQ(TIM2_IRQn);
}

static void usart_putc(unsigned char c) {
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, c);
}

static void usart_puts(unsigned char *c) {
	while(*c) {
		usart_putc(*c);
		c++;
	}
}

void USART1_IRQHandler(void) {
	uint8_t rxByte;
    /* RXNE handler */
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {

    	rxByte = (uint8_t)USART_ReceiveData(USART1);
    	usart_putc(rxByte);
    }
}

void TIM2_IRQHandler(){
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
				STM_EVAL_LEDToggle(LED3);
    }
}


int main(void){		
	uint16_t CurrentCountValue = 0;
	int timerValue = 0;
	
	InitializeTimer();
	SysTick_Config(SystemCoreClock / 1000);
	
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	init_usart();  
		
  while (1) {			

	CurrentCountValue = TIM2->CNT;
		
	usart_puts((unsigned char *)"Is this appearing on the screen ?\n");	
//	STM_EVAL_LEDOn(LED3);
//	STM_EVAL_LEDOff(LED4);
//	Delay(1000);
////	usart_puts("How you doing ?\n");	
//	STM_EVAL_LEDOff(LED3);
//	STM_EVAL_LEDOn(LED4);
//	Delay(1000);
		
//		CurrentTimerVal = TIM_GetCounter(TIM1);
//		if(CurrentTimerVal > LEDToggleValue) {
//			STM_EVAL_LEDToggle(LED3);
//			STM_EVAL_LEDToggle(LED4);
//		}		
//			timerValue = TIM_GetCounter(TIM2);
//        if (timerValue == 500)
//            STM_EVAL_LEDToggle(LED3);
//        else if (timerValue == 500)
//            GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_RESET);
		
  }
}

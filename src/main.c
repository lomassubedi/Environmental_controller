#include <stdint.h>
#include "stm32f0xx.h"
#include "flags_timers.h"
#include "reg_list.h"
#include "stm32f0_discovery.h"

GPIO_InitTypeDef GPIO_InitStructure;

static __IO uint32_t TimingDelay;

void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

extern void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
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


uint16_t hr, mn, sec;


int main(void){		
	SysTick_Config(SystemCoreClock / 1000);
	
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	init_usart();
		
  while (1) {				
		
	usart_puts("Hello there Laxman !\n");	
	STM_EVAL_LEDOn(LED3);
	STM_EVAL_LEDOff(LED4);
	Delay(1000);
	usart_puts("How you doing ?\n");	
	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOn(LED4);
	Delay(1000);
		
  }
}

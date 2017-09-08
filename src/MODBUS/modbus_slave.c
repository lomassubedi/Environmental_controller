// File Name: modbus_slave.c
// Author: Lomas
// Date:

#include "modbus_slave.h"
#include "stm32f0_discovery.h"

#define 	BUFFER_SIZE 	100

TIM_TimeBaseInitTypeDef timerInitStructure; 

volatile unsigned char frame[BUFFER_SIZE];
volatile unsigned int buffer = 0;
volatile unsigned char flag_rx_complete = 0;


void initUsartModbus(void) {
		// USART periferial initialization settings
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

	  // Configure USART1 setting: ----------------------------
	  USART_InitStructure.USART_BaudRate = 9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  USART_Init(USART1, &USART_InitStructure);
	  USART_Cmd(USART1,ENABLE);
		
		// USART1 only receive Interrupt Enable
//		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		NVIC_EnableIRQ(USART1_IRQn);
}

void InitializeTimerRxTimeout() {
	
//	TIM_TimeBaseInitTypeDef timerInitStructure; 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	NVIC_EnableIRQ(TIM2_IRQn);
}

void usartPutc(unsigned char c) {
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, c);
}

void usartPuts(unsigned char *c) {
	while(*c) {
		usartPutc(*c);
		c++;
	}
}

void TIM2_IRQHandler(){
	
	uint8_t counter = 0;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
//		Disable interrupts
		TIM_Cmd(TIM2, DISABLE);	
		TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
		TIM_DeInit(TIM2);

		flag_rx_complete = 1;

		STM_EVAL_LEDToggle(LED4);
		
    }
}

void USART1_IRQHandler(void) {
		/* RXNE handler */	
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		
		if(flag_rx_complete != 1) {
			
			frame[buffer++] = USART_ReceiveData(USART1);
			
			TIM_DeInit(TIM2);
			
			timerInitStructure.TIM_Prescaler = 47;
			timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
			timerInitStructure.TIM_Period = 3880; // for T3.5 Char
			timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseInit(TIM2, &timerInitStructure);
			
			TIM_ClearFlag(TIM2, TIM_FLAG_Update);
			TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
			TIM_Cmd(TIM2, ENABLE);
			
		} else {
			USART_ReceiveData(USART1);
		}
	}
}

void init_modbus() {
	initUsartModbus();	
	InitializeTimerRxTimeout();
}

void dispFrame() {
	
	uint8_t char_ctr = 0;
	
	if(flag_rx_complete == 1) {
			
			for(char_ctr = 0; char_ctr < buffer; char_ctr++) {
				usartPutc(frame[char_ctr]);
			}
			
			buffer = 0;
			flag_rx_complete = 0;
//			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		}
}

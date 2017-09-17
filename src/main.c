#include <stdint.h>
#include <stdio.h>
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"

#include "stm32f0xx_tim.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_rtc.h"
#include "stm32f0xx_pwr.h"

#include "flags_timers.h"
#include "reg_list.h"
#include "stm32f0_discovery.h"

#include "modbus_slave.h"
#include "util_prj.h"

#define 		TMP_BUFFER_SIZE			200
uint8_t buffr[TMP_BUFFER_SIZE];

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

static void RTC_Config_LSE(void) {
	
  RTC_InitTypeDef  RTC_InitStructure;
  RTC_TimeTypeDef  RTC_TimeStruct;

  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
//  PWR_BackupAccessCmd(ENABLE);

  /* Reset RTC Domain */
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);

  /* Enable the LSE OSC */
  RCC_LSEConfig(RCC_LSE_ON);

  /* Wait till LSE is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Configure the RTC data register and RTC prescaler */
  /* ck_spre(1Hz) = RTCCLK(LSI) /(AsynchPrediv + 1)*(SynchPrediv + 1)*/
  RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
  RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
  RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);
  
  /* Set the time to 00h 00mn 00s AM */
  RTC_TimeStruct.RTC_H12     = RTC_H12_AM;
  RTC_TimeStruct.RTC_Hours   = 0x00;
  RTC_TimeStruct.RTC_Minutes = 0x00;
  RTC_TimeStruct.RTC_Seconds = 0x00;  
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStruct);
	
	RTC_TimeStructInit(&RTC_TimeStruct); 
}

RTC_InitTypeDef   RTC_InitStructure;

static void RTC_Config_LSI(void)
{
  RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	
  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  
  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);

/* LSI used as RTC source clock */
/* The RTC Clock may varies due to LSI frequency dispersion. */   
  /* Enable the LSI OSC */ 
  RCC_LSICmd(ENABLE);

  /* Wait till LSI is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
   
  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();

  /* Calendar Configuration */
  RTC_InitStructure.RTC_AsynchPrediv = 99;
  RTC_InitStructure.RTC_SynchPrediv	=  399; /* (40KHz / 100) - 1 = 399*/
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);  
  
	
  /* Set the time to 00h 00mn 00s AM */
  RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
  RTC_TimeStructure.RTC_Hours   = CMPL_HOUR;
  RTC_TimeStructure.RTC_Minutes = CMPL_MIN;
  RTC_TimeStructure.RTC_Seconds = CMPL_SEC;  
	
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
	
// Date is not necessary 
//	RTC_DateStructure.RTC_Year = CMPL_YEAR;
//	RTC_DateStructure.RTC_Month = getmonth();
//	RTC_DateStructure.RTC_Date = CMPL_DATE;
//	
//	RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure);
}

void init_usart2(void) {
//	/ USART periferial initialization settings
	  USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef	GPIO_InitStructure;

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);

	  //Configure USART2 pins: TX (PA2) and RX (PA3)
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  //Configure USART2 setting: ----------------------------
	  USART_InitStructure.USART_BaudRate = 9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  USART_Init(USART2, &USART_InitStructure);
	  USART_Cmd(USART2,ENABLE);
}

void usart2_putchar(uint8_t c) {
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2, c);
	return;
}

void usart2_puts(uint8_t *str) {
	while(*str) {
		usart2_putchar(*str);
		str++;
	}
	return;
}


int main(void) {
	
	RTC_TimeTypeDef myRTCTime;
	RTC_DateTypeDef myRTCDate;
	
	SysTick_Config(SystemCoreClock / 1000);
	
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	
	init_usart2();
	init_modbus();
	
	RTC_Config_LSI();
	
  while (1) {
		
		if(flagLEDIndi) {
			flagLEDIndi = 0;
			STM_EVAL_LEDToggle(LED3);
		}
//		modbus_update();
		RTC_GetTime(RTC_Format_BIN, &myRTCTime);
		sprintf((char *)buffr, "Hour: %d\tMinute: %d\tSec: %d\r\n", myRTCTime.RTC_Hours, myRTCTime.RTC_Minutes, myRTCTime.RTC_Seconds);
		usart2_puts(buffr);
		
//		RTC_GetDate(RTC_Format_BIN, &myRTCDate);
//		sprintf((char *)buffr, "Year: %d\tMonths: %d\tDay: %d\r\n", myRTCDate.RTC_Year, myRTCDate.RTC_Month, myRTCDate.RTC_Date);
//		usart2_puts(buffr);
//		
//		sprintf((char *)buffr, "Current Date: %s\r\n", __DATE__);
//		usart2_puts(buffr);
//		
//		sprintf((char *)buffr, "Year: %d\t Months: %d\t Date: %d\t\r\n", CMPL_YEAR, getmonth(), CMPL_DATE);
//		usart2_puts(buffr);
	
		Delay(1000);
	}
}

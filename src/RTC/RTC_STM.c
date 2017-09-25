#include "RTC_STM.h"

RTC_InitTypeDef RTC_InitStructure;

void RTC_Config_LSE(void) {
	
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

void RTC_Config_LSI(void)
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
  
	
  /* Set the time to code compiled time*/
  RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
  RTC_TimeStructure.RTC_Hours   = CMPL_HOUR;
  RTC_TimeStructure.RTC_Minutes = CMPL_MIN;
  RTC_TimeStructure.RTC_Seconds = CMPL_SEC;  
	
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
}
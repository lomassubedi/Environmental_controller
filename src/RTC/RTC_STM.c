#include "RTC_STM.h"

RTC_InitTypeDef RTC_InitStructure;

void RTC_Config_LSE(void) {
	
	date_time my_date_time_LSE;
  RTC_InitTypeDef  RTC_InitStructure;
  RTC_TimeTypeDef  RTC_TimeStruct;
	RTC_DateTypeDef  RTC_DateStruct;
	
	volatile uint32_t BackUpVal = RTC_ReadBackupRegister(RTC_BKP_DR0);
	
	if (BackUpVal != BKP_VALUE) {
		/* Enable the PWR clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

		/* Allow access to RTC */
		PWR_BackupAccessCmd(ENABLE);		

		/* Reset RTC Domain */
//		RCC_BackupResetCmd(ENABLE);
//		RCC_BackupResetCmd(DISABLE);

		/* Enable the LSE OSC */
		RCC_LSEConfig(RCC_LSE_ON);

		/* Wait till LSE is ready */  
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

		/* Select the RTC Clock Source */
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		
		/* Enable RTC clock */
		RCC_RTCCLKCmd(ENABLE);
		
		/* Wait for RTC APB registers synchronization */
		RTC_WaitForSynchro();
		
		/* Configure the RTC data register and RTC prescaler */
		/* ck_spre(1Hz) = RTCCLK(LSI) /(AsynchPrediv + 1)*(SynchPrediv + 1)*/
		RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
		RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
		RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
		RTC_Init(&RTC_InitStructure);
		
		get_ct_date_time(&my_date_time_LSE);
		
		/* Set the time to code compiled time*/
		RTC_TimeStruct.RTC_H12     = RTC_H12_AM;
		RTC_TimeStruct.RTC_Hours   = my_date_time_LSE.hour;
		RTC_TimeStruct.RTC_Minutes = my_date_time_LSE.min;
		RTC_TimeStruct.RTC_Seconds = my_date_time_LSE.sec;
		
		RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
		
		// Set the RTC date. compile time Date.
		RTC_DateStruct.RTC_Year = my_date_time_LSE.year - 2000;
		RTC_DateStruct.RTC_Month = my_date_time_LSE.month;
		RTC_DateStruct.RTC_Date = my_date_time_LSE.mday;
		RTC_DateStruct.RTC_WeekDay = my_date_time_LSE.wday;
		RTC_DateStruct.RTC_WeekDay = my_date_time_LSE.wday;
		
		RTC_SetDate(RTC_Format_BIN, &RTC_DateStruct);
			
		RTC_TimeStructInit(&RTC_TimeStruct);

		RTC_WriteBackupRegister(RTC_BKP_DR0, BKP_VALUE);
		
		PWR_BackupAccessCmd(DISABLE);
	} else {
		/* Check if the Power On Reset flag is set */
		if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET) {
			printf("RTC: Power On Reset occurred....\n\r");
		}
		/* Check if the Pin Reset flag is set */
		else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET) {
			printf("RTC: External Reset occurred....\n\r");
		}
	}	
}

void RTC_Config_LSI(void) {
	
  RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	date_time my_date_time;
	
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
//  RTC_InitStructure.RTC_AsynchPrediv = 0xFF;
//  RTC_InitStructure.RTC_SynchPrediv	=  0x7F; /* (40KHz / 100) - 1 = 399*/
	
	RTC_InitStructure.RTC_AsynchPrediv = 99;
	RTC_InitStructure.RTC_SynchPrediv	=  399; /* (40KHz / 100) - 1 = 399*/
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);  
  
	get_ct_date_time(&my_date_time);
	
  /* Set the time to code compiled time*/
  RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
  RTC_TimeStructure.RTC_Hours   = my_date_time.hour;
  RTC_TimeStructure.RTC_Minutes = my_date_time.min;
  RTC_TimeStructure.RTC_Seconds = my_date_time.sec;
	
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
	
	// Set the RTC date. compile time Date.
	RTC_DateStructure.RTC_Year = my_date_time.year - 2000;
	RTC_DateStructure.RTC_Month = my_date_time.month;
	RTC_DateStructure.RTC_Date = my_date_time.mday;
	RTC_DateStructure.RTC_WeekDay = my_date_time.wday;
	
	RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure);
}
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "stm32f0_discovery.h"

#include "stm32f0xx_tim.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_spi.h"
#include "stm32f0xx_misc.h"
#include "stm32f0xx_adc.h"

#include "flags_timers.h"
//#include "reg_list.h"
#include "modbus_slave.h"
#include "RTC_STM.h"
#include "eeprom_data.h"
#include "util_usart.h"
#include "iso_i2c_ee.h"

#include "ff.h"

#define			INTERVAL		100		// Define data log interval of 100ms
FATFS FatFs;
FIL logfile;

GPIO_InitTypeDef GPIO_InitStructure;

static __IO uint32_t TimingDelay;
__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
__IO uint32_t logging = 0, intrval_time = 1;

struct __FILE {
    int dummy;
};

FILE __stdout;

extern void Delay(__IO uint32_t nTime) {
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

extern void TimingDelay_Decrement(void) {
  if (TimingDelay != 0x00) {
    TimingDelay--;
  }
}

DWORD get_fattime (void)
{	
	RTC_TimeTypeDef FATRTCTime;
	RTC_DateTypeDef FATRTCDate;
	
	/* Get local date and time */
	RTC_GetTime(RTC_Format_BIN, &FATRTCTime);
	RTC_GetDate(RTC_Format_BIN, &FATRTCDate);
	

	/* Pack date and time into a DWORD variable */
	return ((DWORD)((FATRTCDate.RTC_Year) + 20) << 25)
			| ((DWORD)FATRTCDate.RTC_Month << 21)
			| ((DWORD)FATRTCDate.RTC_Date << 16)
			| ((DWORD)FATRTCTime.RTC_Hours<< 11)
			| ((DWORD)FATRTCTime.RTC_Minutes << 5)
			| ((DWORD)FATRTCTime.RTC_Seconds>> 1);
}

void init_TIM3(void) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* Enable the TIM3 gloabal Interrupt */
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	NVIC_EnableIRQ(TIM3_IRQn);

	TIM_TimeBaseStruct.TIM_Prescaler = INTERVAL;		// Colck division in milli second
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;
	TIM_TimeBaseStruct.TIM_Period = 48000;			// Clock Source in KHz
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_CenterAligned1; //TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM3, ENABLE);
}

void ADC_Config(void) {
	
  ADC_InitTypeDef     ADC_InitStructure;
  GPIO_InitTypeDef    GPIO_InitStructure;
  
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  
  /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* Configure ADC Channel11 as analog input */

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  /* ADCs DeInit */  
  ADC_DeInit(ADC1);
  
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continuous mode with a resolution equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
  
  /* Convert the ADC1 Channel 11 with 239.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_11 , ADC_SampleTime_239_5Cycles);

  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable the ADC peripheral */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADRDY flag */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
  
}
void start_logging(void) {
	FRESULT rc;
	
	rc = f_mount(&FatFs, "", 1);
	if(rc == FR_OK) {
			rc = f_open(&logfile, "real_log.csv", FA_WRITE | FA_CREATE_ALWAYS);
			if(rc == FR_OK){
					f_printf(&logfile,
						"SD card example\n"
						"S.N., Timp Laps (in ms), Time Adc Val, Time Stamp\n");
			}
	}	
}

void stop_logging(void) {
	
	f_sync(&logfile);				// Clear the catched information
	f_close(&logfile);			// Close the file
	TIM_Cmd(TIM3, DISABLE);	// Disable the interval generator
}

RTC_TimeTypeDef fileRTCTime;
RTC_DateTypeDef fileRTCDate;	
char time_buffr[100];
uint16_t ctr = 0;

void TIM3_IRQHandler() {
	
	STM_EVAL_LEDOn(LED4);

	/* Test EOC flag */
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

	/* Get ADC1 converted data */
	ADC1ConvertedValue = ADC_GetConversionValue(ADC1);

	/* Compute the voltage */
	ADC1ConvertedVoltage = (ADC1ConvertedValue *3300)/0xFFF;
	
	RTC_GetTime(RTC_Format_BIN, &fileRTCTime);
	RTC_GetDate(RTC_Format_BIN, &fileRTCDate);
	
	sprintf(time_buffr, "%d-%02d-%02dT%02d-%02d-%02d", (fileRTCDate.RTC_Year + 2000), fileRTCDate.RTC_Month, fileRTCDate.RTC_Date, fileRTCTime.RTC_Hours, fileRTCTime.RTC_Minutes, fileRTCTime.RTC_Seconds);	
	
	f_printf(&logfile, "%d, %08d, %d, %s\n", ++ctr, intrval_time * INTERVAL, ADC1ConvertedVoltage, time_buffr);	
	intrval_time++;
	printf("%d, %08d, %d, %s\n", ctr, intrval_time * INTERVAL, ADC1ConvertedVoltage, time_buffr);
	
	STM_EVAL_LEDOff(LED4);
	
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	
	if(ctr > 500) {
		stop_logging();
	}
}

int main(void) {
	
	RTC_TimeTypeDef myRTCTime;
	RTC_DateTypeDef myRTCDate;	

//	uint8_t flag_EEPROM_status;	
	
	SysTick_Config(SystemCoreClock / 1000);
	
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	
	ADC_Config();
	init_usart2();
	init_modbus();
	
	RTC_Config_LSI();
	
	start_logging();
	init_TIM3();
	

//	RTC_Config_LSE();
	
	I2C_EEPROM_24C0x_Init();		
	
//	printf("STM32F051 SD CARD TEST !!! \r\n");	
	
	/*
	sEE_ReadBuffer(&flag_EEPROM_status, ADDRESS_EPRM_STATUS_FLAG, BYTES_EEPRM_STATUS_FLAG);
//	flag_EEPROM_status = 0;
	if(flag_EEPROM_status != 1) { // Data not written
		// Write Tools Default value
		I2C_EEPROM_24C0x_WriteStructTools(tools, EEPROM_ADDRESS_TOOLS, TOOLS_SIZE);
		
		// Write profile 1 default data
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_1, PROFILE_SIZE);
		
		// Write profile 2 default data
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_2, PROFILE_SIZE);
		
		// Write profile 3 default data 
		I2C_EEPROM_24C0x_WriteStructProfile(profile, EEPROM_ADDRESS_PROFILE_3, PROFILE_SIZE);
		
		// Write the flag status so as to indicate that default data has been already written to EEPROM
		flag_EEPROM_status = 1;
		sEE_WriteBuffer(&flag_EEPROM_status, ADDRESS_EPRM_STATUS_FLAG, BYTES_EEPRM_STATUS_FLAG);
		
		printf("Written default tools and profile values to EEPROM.\r\n");
	} else {
		printf("Default data already available at EEPROM.\r\n");
	}		
	*/
	
  while (1) {
		
//		modbus_update();		
		if(flagLEDIndi) {		
			flagLEDIndi = 0;
			STM_EVAL_LEDToggle(LED3);
			RTC_GetTime(RTC_Format_BIN, &myRTCTime);
			RTC_GetDate(RTC_Format_BIN, &myRTCDate);
			/*printf("Year: %d, \tMonth: %d, \tDay: %d, \t", (myRTCDate.RTC_Year + 2000), myRTCDate.RTC_Month, myRTCDate.RTC_Date);
			printf("Hour: %d, \tMinute: %d, \tSec: %d\r\n", myRTCTime.RTC_Hours, myRTCTime.RTC_Minutes, myRTCTime.RTC_Seconds);				
			*/
			}		
	}	
}

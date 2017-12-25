#include "config.h"
#include "flags_timers.h"
#include "modbus_slave.h"
#include "RTC_STM.h"
#include "eeprom_data.h"
#include "util_usart.h"
#include "iso_i2c_ee.h"
#include "sdlog.h"

static __IO uint32_t TimingDelay;	

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

//void start_logging(void) {
	/*
	RTC_DateTypeDef RTCDate;
	RTC_TimeTypeDef RTCTime;
	
	RTC_GetTime(RTC_Format_BIN, &RTCTime); // Get initial date and time
	RTC_GetDate(RTC_Format_BIN, &RTCDate);	
	
	logging = 1; // logging started
	
	sprintf(file_name, "file_%d-%02d-%02dT%02d-%02d-%02d.csv", // name the initial logfile
				(RTCDate.RTC_Year + 2000), RTCDate.RTC_Month, RTCDate.RTC_Date, RTCTime.RTC_Hours, RTCTime.RTC_Minutes, RTCTime.RTC_Seconds);	
	
	if(rc == FR_OK) {
		printf("SD card successfully mounted !!\r\n");
		printf("Data logging just started, File name : %s\r\n", file_name);
		rc = f_open(&logfile, file_name, FA_WRITE | FA_CREATE_ALWAYS); // Create a file
		f_sync(&logfile);
	} else {
		printf("Failed mounting SD card\r\n");
	} */
//}

int main(void) {
		
	SysTick_Config(SystemCoreClock / 1000);	
	
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);	
	
	init_pushbtn();
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
	
	ADC_Config();
	
	init_usart2();
	init_modbus();	
	
	RTC_Config_LSI();		
	
	init_sd();
//	init_TIM3();
	
//	I2C_EEPROM_24C0x_Init();	
	
//	// Initial file work
//	rc = f_mount(&FatFs, "SD", 1); /* Mount the default drive */
////	RTC_GetTime(RTC_Format_BIN, &myRTCTime);
////	prev_min = myRTCTime.RTC_Minutes;
//	f_mkdir("New_Folder");
////	f_chdir("New_Folder");
//	if(rc == FR_OK) {
//			printf("Disk mounted successfully !!\r\n");
//			rc = f_open(&logfile, "/New_Folder/Test_file1.txt", FA_WRITE | FA_CREATE_ALWAYS);
////			f_sync(&logfile);
////			f_printf(&logfile, "This is a test file. \r\n");
//	} else {
//		printf("Error mounting the disk!!\r\n");
//	}
	
  while (1) {
				
//		modbus_update();						
	
	}	
}

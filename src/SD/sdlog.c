
#include "sdlog.h"

static uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
static float ADCAnalogVoltage = 0.0; 
volatile uint8_t button_prev = 0;

static char path_buffer[LOG_MAX_FILE_PATH_SIZE];

// Fat FS global variables for ISR
static FATFS FatFs;
static FIL logfile, getfile;
static FRESULT rc, rd;
uint8_t flag_disk_mount = 1;

char fileReadBuffr[100];
UINT readBytes = 0;
uint16_t ctr = 0;

static uint8_t logging = 0;

volatile uint8_t flag_file_open = 0;

char *months_lookup[12] = {
	"January",	// months_lookup[0] == January
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

volatile uint8_t file_prev_year = 0;
volatile uint8_t file_current_month = 0, file_prev_month = 0;
volatile uint8_t file_current_day = 0, file_prev_day = 0;
volatile uint8_t file_prev_min = 0;
volatile uint8_t file_prev_sec = 0;


/* Fat FS Utility funtion to setup RTC time */
DWORD get_fattime (void) {
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

	TIM_TimeBaseStruct.TIM_Prescaler = LOG_INTERVAL;		// Colck division in milli second
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;
	TIM_TimeBaseStruct.TIM_Period = 48000;							// Clock Source in KHz depends upon TIM_Prescaler
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

void init_pushbtn(void) {
	GPIO_InitTypeDef Gp;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	
  Gp.GPIO_Pin = PushButton_Pin; //Set pins inside the struct
  Gp.GPIO_Mode = GPIO_Mode_IN; //Set GPIO pins as output
  Gp.GPIO_PuPd = GPIO_PuPd_NOPULL; //No pullup required as pullup is external
  GPIO_Init(PushButton_GPIO, &Gp); //Assign struct to LED_GPIO 	
}

void init_sd(void){
	
	FRESULT err;
	uint8_t mnth_ctr = 0;
	RTC_TimeTypeDef RTCTime;
	RTC_DateTypeDef RTCDate;
		
	err = f_mount(&FatFs, "", 1); /* Mount the default drive */

	
	if (err != FR_OK) {
		printf("FS: f_mount() failed. Is the SD card inserted?\r\n");
		flag_disk_mount = 0;
		return;
	}
	
	
	printf("FS: f_mount() succeeded\r\n");
	flag_disk_mount = 1;
	
	
	// Get local date and time
	RTC_GetTime(RTC_Format_BIN, &RTCTime);
	RTC_GetDate(RTC_Format_BIN, &RTCDate);
	
	if(RTCDate.RTC_Year > 0) {
		sprintf(path_buffer, "%d",(RTCDate.RTC_Year + RTC_YOFFSET));
		
		// Create necessary directories		
		f_mkdir(path_buffer);						// Create a directories for year
		printf("Created directoriy %s.\r\n",path_buffer); 
		
		f_chdir(path_buffer);						// Enter into the year directory
		// Make directories for each months
		for(mnth_ctr = 0; mnth_ctr < 12; mnth_ctr++) {
			sprintf(path_buffer, "%s", months_lookup[mnth_ctr]);
			f_mkdir(path_buffer);			
			STM_EVAL_LEDToggle(LED3);
			printf("Created directoriy %s.\r\n",path_buffer); 
			Delay(100);
		}
		f_chdir("..");						// Exit from the year directory
		// Now control is withing the main directory
	} else {
		printf("RTC not configured !!\r\n");
	}	
	// f_mount(0, "", 1);                     // Unmount the SD drive 
	return;
}

void start_logging(void) {
	
	// Get the current date 
	RTC_DateTypeDef R_Date;
	RTC_TimeTypeDef R_Time;
	RTC_GetTime(RTC_Format_BIN, &R_Time);
	RTC_GetDate(RTC_Format_BIN, &R_Date);

	// Create file path
	sprintf(path_buffer, "/%04d/%s/D%02d.csv", \
	(R_Date.RTC_Year + RTC_YOFFSET), months_lookup[R_Date.RTC_Month - 1], R_Date.RTC_Date);

	// Open a file in create/append and write mode
	rc = f_open(&logfile, path_buffer, FA_WRITE | FA_CREATE_ALWAYS) || f_lseek(&logfile, f_size(&logfile));

	// If opeaning file is successfull
	if(rc == FR_OK) {
		printf("Opeaned file %s!\r\n", path_buffer);
		flag_file_open = 1;
	} else {
		printf("Failed opening file %s!\r\n", path_buffer);
	}
}

void stop_logging(void) {
	
	f_sync(&logfile);				// Clear the catched information 
	f_close(&logfile);			// Close the file if it is open
	
	flag_file_open = 0;			// Clear the flag
	
	printf("Closed file %s!\r\n", path_buffer);
	TIM_Cmd(TIM3, DISABLE);	// Disable the interval generator
	STM_EVAL_LEDOff(LED4);
}

void cont_logging(void) {
	
	char tmp_bfr[20];
	// RTC variables
	RTC_TimeTypeDef RTCTimeLog;
	RTC_DateTypeDef RTCDateLog;
	
	/* Test EOC flag */
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	/* Get ADC1 converted data */
	ADC1ConvertedValue = ADC_GetConversionValue(ADC1);
	/* Compute the voltage (Millivolt)*/
	ADC1ConvertedVoltage = (ADC1ConvertedValue *3300)/0xFFF;
	/* Compute the voltage (volts) */
	ADCAnalogVoltage = ADC1ConvertedVoltage/1000.0;
	
	/* Aquire RTC Time */
	RTC_GetTime(RTC_Format_BIN, &RTCTimeLog);
	RTC_GetDate(RTC_Format_BIN, &RTCDateLog);
	
//	if((RTCTimeLog.RTC_Seconds % 20) == 0)		flag_file_open = 0;
		
	if(!flag_file_open) {		// If file name has changed or its initial start
		start_logging();
	}
	
	// Data log task
	sprintf(tmp_bfr, "%.5f", ADCAnalogVoltage);
	f_printf(&logfile, "%02d:%02d:%02d, %06d, %s\r\n", 
		RTCTimeLog.RTC_Hours, RTCTimeLog.RTC_Minutes, RTCTimeLog.RTC_Seconds, 
		ADC1ConvertedVoltage, tmp_bfr);	

	printf("Logged line on file : %02d-%02d-%02d, %06d, %.5f\r\n",\
		RTCTimeLog.RTC_Hours, RTCTimeLog.RTC_Minutes, RTCTimeLog.RTC_Seconds, 
		ADC1ConvertedVoltage, ADCAnalogVoltage);

	f_sync(&logfile);
}

void TIM3_IRQHandler() {
	
	if(!flag_disk_mount)	{ // Proceed only when the disk is mounted successfully
		printf("failed mounting SD card. Make sure that proper SD card is inserted.\r\n");
		return;
	}
	
	STM_EVAL_LEDOn(LED4);
	cont_logging();	
	STM_EVAL_LEDOff(LED4);
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	return;
	
}

// Push button IRQ Handler
void EXTI0_1_IRQHandler(void) {
	
	if(EXTI_GetITStatus(USER_BUTTON_EXTI_LINE) != RESET) {
				
		if(button_prev) {
			stop_logging();
			button_prev = 0;
			printf("Logging stopped!\r\n");
			
			// ----- Read the file logged and display the content ----- //			
			rd = f_open(&getfile, path_buffer, FA_OPEN_EXISTING | FA_READ);
			
			if(rd == FR_OK) {				
				printf("file content are : \r\n");	
				memset(fileReadBuffr, 0x00, sizeof(fileReadBuffr));
				do {								
					f_gets (fileReadBuffr, sizeof(fileReadBuffr), &getfile);
					printf(fileReadBuffr);
					f_lseek(&getfile, strlen(fileReadBuffr));
				} while (f_eof(&getfile));
			}
			f_close(&getfile);
			
		} else {
			init_TIM3(); 		// Start logging 
			printf("Logging Started!\r\n");
			button_prev = 1;
		} 
		EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
	}
}

void read_file(void) {
	
	if(flag_disk_mount) { 	// If the disk was successfully mounted
			rd = f_open(&getfile, "BOOTEX.LOG", FA_OPEN_EXISTING | FA_READ);
			if(rd == FR_OK) {
				memset(fileReadBuffr, 0x00, sizeof(fileReadBuffr));
				
//				while(f_read(&getfile, fileReadBuffr, sizeof(fileReadBuffr), &readBytes));
				
//				do {
//					f_gets (fileReadBuffr, sizeof(fileReadBuffr), &getfile);
//				} while (!f_eof(&getfile));
//				while (f_gets(fileReadBuffr,sizeof fileReadBuffr, &getfile))
//					printf(fileReadBuffr);
				f_gets (fileReadBuffr, sizeof(fileReadBuffr), &getfile);
				printf(fileReadBuffr);
			}
		}
}


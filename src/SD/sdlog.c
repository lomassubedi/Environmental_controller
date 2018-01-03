
#include "sdlog.h"

static uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
static float ADCAnalogVoltage = 0.0; 
volatile uint8_t button_prev = 0;

static char path_buffer[LOG_MAX_FILE_PATH_SIZE];

// Fat FS global variables for ISR
static FATFS FatFs;
static FIL logfile, getfile;

// FRESULT for writing into the file, initialize with not okay result
static FRESULT res_disk_mount = ~FR_OK, res_check_file = ~FR_OK, res_open_file = ~FR_OK;

// FRESULT for reading from the file, initialize with not okay result
static FRESULT res_open_file_read = ~FR_OK;

static FILINFO fno;
char fileReadBuffr[LOG_RD_FILE_SIZE];
uint16_t line_no = 0;

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
			
	res_disk_mount = f_mount(&FatFs, "", 1); /* Mount the default drive */
	
	if (res_disk_mount == FR_OK) {
		printf("SD card mounted successfully !!\r\n");		
	} else {
		printf("SD card mounting failed !! Make sure a SD card is inserted.\r\n");
	}	
	return;
}

void start_logging(void) {
	
	// Get the current date 
	RTC_DateTypeDef R_Date;
	RTC_TimeTypeDef R_Time;
	RTC_GetTime(RTC_Format_BIN, &R_Time);
	RTC_GetDate(RTC_Format_BIN, &R_Date);

	// Create file path
	memset(path_buffer, 0x00, sizeof path_buffer); // Empty the file path buffer
	sprintf(path_buffer, "%04d_%02d_D%02d.csv", \
	(R_Date.RTC_Year + RTC_YOFFSET), R_Date.RTC_Month, R_Date.RTC_Date);
	printf("Current file : %s.\r\n", path_buffer);
			
	res_check_file = f_stat(path_buffer, &fno); // Get the status where file is present or not
	
		
	if(res_check_file != FR_OK) {	// If file doesnot exists
		
		// Open a file in create and write mode
		res_open_file = f_open(&logfile, path_buffer, FA_WRITE | FA_CREATE_NEW) || f_lseek(&logfile, f_size(&logfile));		
		
		// If opeaning file is successfull
		if(res_open_file == FR_OK) {
			printf("Opeaned file %s!\r\n", path_buffer);
			f_printf(&logfile, "S.N., Timestamp, analog val (mv), analog val(v)\r\n");
			f_sync(&logfile);
			
			printf("Placed header : S.N., Timestamp, analog val (mv), analog val(v).\r\n");
		} else {
			printf("Failed opening file \'%s\'!\r\n", path_buffer);
		}
				
	} else {
		// Open a file in create/append and write mode 
		// and move file pointer to the end of file for appending
		res_open_file = f_open(&logfile, path_buffer, FA_WRITE | FA_OPEN_APPEND);			
		
		// If opeaning file is successfull
		if(res_open_file == FR_OK) {
			printf("Opeaned file \'%s\'!\r\n", path_buffer);
		} else {
			printf("Failed opening file \'%s\'!\r\n", path_buffer);
		}		
	}
}

void stop_logging(void) {
	// Clear the catched information 
	f_sync(&logfile);				
	
	// Close the file if it is open
	f_close(&logfile);	
	res_open_file	= ~FR_OK;
		
	printf("Closed file \'%s\'!\r\n", path_buffer);
	
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
		
	
	if(res_open_file == FR_OK) {
		
		// Data log task
		sprintf(tmp_bfr, "%.5f", ADCAnalogVoltage);
		if(f_printf(&logfile, "%d, %02d:%02d:%02d, %06d, %s\r\n", 
			++line_no, RTCTimeLog.RTC_Hours, RTCTimeLog.RTC_Minutes, RTCTimeLog.RTC_Seconds, 
			ADC1ConvertedVoltage, tmp_bfr)) {

			printf("Logged line on file : %d,%02d-%02d-%02d, %06d, %.5f\r\n",\
				line_no, RTCTimeLog.RTC_Hours, RTCTimeLog.RTC_Minutes, RTCTimeLog.RTC_Seconds, 
				ADC1ConvertedVoltage, ADCAnalogVoltage);
			}
		f_sync(&logfile);		
	} else {
		printf("Error: Failed opeaning file \'%s\'!!\r\n", path_buffer);
	}
}

void TIM3_IRQHandler() {
		
	if(res_disk_mount == FR_OK) {		// if disk is mounted proceed to check the file
		if(res_open_file == FR_OK) {	// if file is open proceed writing into it
			STM_EVAL_LEDOn(LED4);
			cont_logging();	
			STM_EVAL_LEDOff(LED4);
		} else {
			printf("ERROR: Failed opeaning file: \'%s\' .\r\n", path_buffer);
		}
	} else {
		printf("ERROR: SD card not mounted. Make sure that SD card is inserted properly!\r\n");
	}
		
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
			res_open_file_read = f_open(&getfile, path_buffer, FA_OPEN_EXISTING | FA_READ);
			
			if(res_open_file_read == FR_OK) {
				printf("File content  the file \'%s\' are : \r\n", path_buffer);	
				memset(fileReadBuffr, 0x00, sizeof(fileReadBuffr));
				
				// Read line by line till the end of file
				while(!f_eof(&getfile)) {
					STM_EVAL_LEDToggle(LED4);
					f_gets (fileReadBuffr, sizeof(fileReadBuffr), &getfile);
					printf(fileReadBuffr);
				}
				STM_EVAL_LEDOff(LED4);
			}
			f_close(&getfile);
			res_open_file_read = ~FR_OK;
			
		} else {	
			// Enable the interval generator
			printf("Trigger data logging!\r\n");			
			if(res_disk_mount == FR_OK) {		// proceed only if disk is mounted
				start_logging();
				init_TIM3(); 		// Start Interval generator 	
				button_prev = 1;
			} else {
					printf("ERROR: SD card not mounted. Make sure that SD card is inserted properly!\r\n");
			}
		} 
		EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
	}
}


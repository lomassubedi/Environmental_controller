// File Name: sdlog.h
// Author: Lomas
// Date 24 Sept 2017

#ifndef SDLOG_H_
#define SDLOG_H_

#include "config.h"
#include "ff.h"
#include "util_prj.h"
#include "RTC_STM.h"

// Define log file name size in bytes
#define 		LOG_MAX_FILE_NAME_SIZE					50
#define			LOG_MAX_FILE_PATH_SIZE					200
#define			RTC_YOFFSET											2000

#define			LOG_INTERVAL										100		// Define data log interval of 100ms

extern uint8_t flag_disk_mount;

void init_TIM3(void);
void ADC_Config(void);
void init_pushbtn(void);

void init_sd(void);
//void get_path(char * path);
void start_logging(void);
void stop_logging(void);
void cont_logging(void);

void read_file(void);


#endif // SDLOG_H_
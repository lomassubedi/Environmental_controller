#ifndef _SETUP_H
#define _SETUP_H

#include "config.h"
#include "flags_timers.h"
#include "RTC_STM.h"
#include "eeprom_data.h"
#include "util_usart.h"

void initial_setup(void);

void set_flag_light_light_yes(void);

void set_flag_dark_dark_yes(void);

void set_light_dark_duration(void);

#endif // End of _SETUP_H
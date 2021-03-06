// File Name: eeprom_profile.h
// Author: Lomas
// Date 24 Oct 2017

#ifndef EEPROM_PROFILE_H_
#define EEPROM_PROFILE_H_

#include "eeprom_data.h"
#include "iso_i2c_ee.h"

// ------ function to manipulate EEPROM data along with profile -----
void eeprom_get_var(uint8_t profNum, uint8_t varCode, uint8_t * bytesCount, uint8_t * bytesArry);

void eeprom_set_var(uint8_t profNum, uint8_t varCode, uint8_t bytesCount, uint8_t * bytesArry);

// ------------ Function to modify profile before writing to EEPROM -------------------
void set_profile_vals(PROFILE * profile, uint8_t varCode, uint8_t * bytesArry);

#endif // EEPROM_PROFILE_H_


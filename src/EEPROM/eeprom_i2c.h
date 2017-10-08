// File Name: eeprom_i2c.h
// Author: Lomas
// Date: 08-10-2017

#ifndef EEPROM_I2C_H_
#define EEPROM_I2C_H_

#include "stm32f0xx_i2c.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

/* defines ----------------------------------------------------------------- */
#define OWN_ADDRESS 			0x00
#define MAX_I2C_BUF_LEN 	64
#define I2C_TIMEOUT				0x1800	// 0x1800 / 48MHz (SystemCoreClock) = 0.12 ms

extern void i2c_init(void);
uint8_t i2c_busy(void);

#endif // EEPROM_I2C_H_



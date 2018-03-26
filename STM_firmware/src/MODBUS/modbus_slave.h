// Header: modbus slave
// File Name: modbus_slave.h
// Author: Lomas
// Date:

#ifndef MODBUS_SLAVE_H_
#define MODBUS_SLAVE_H_

#include <stdint.h>
#include "stm32f0xx.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"

// function definitions

extern void init_modbus(void);

extern uint8_t modbus_update(void);

#endif // MODBUS_SLAVE_H_

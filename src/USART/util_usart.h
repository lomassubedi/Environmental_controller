// File Name: util_usart.h
// Author: Lomas
// Date 10 Oct 2017

#ifndef UTIL_USART_H_
#define UTIL_USART_H_

#include <stdio.h>
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"

extern void init_usart2(void);

extern void usart2_putchar(uint8_t c);

extern int fputc(int ch, FILE *f);

#endif // UTIL_USART_H_
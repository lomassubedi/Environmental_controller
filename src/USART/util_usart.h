// File Name: util_usart.h
// Author: Lomas
// Date 10 Oct 2017

#ifndef UTIL_USART_H_
#define UTIL_USART_H_

#include "config.h"

void init_usart2(void);

void usart2_putchar(uint8_t c);

int fputc(int ch, FILE *f);

#endif // UTIL_USART_H_

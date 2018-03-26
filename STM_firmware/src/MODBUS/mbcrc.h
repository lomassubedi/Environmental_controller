// Header: Modbus CRC
// File Name: mbcrc.h
// Author: Lomas
// Date: 12-09-2017

#ifndef MBCRC_H_
#define MBCRC_H_

#include <stdint.h>

extern uint16_t CRC16(uint8_t *data_array, uint16_t length_of_array);

#endif // MBCRC_H_


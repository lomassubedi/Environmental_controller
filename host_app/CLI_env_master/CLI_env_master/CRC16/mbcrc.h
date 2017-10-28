#pragma once
#ifndef __MBCRC_H_
#define __MBCRC_H_

#include <stdint.h>

class CRC {
    public:
    uint16_t CRC16(uint8_t *data_array, uint16_t length_of_array);
};

#endif // MBCRC_H_

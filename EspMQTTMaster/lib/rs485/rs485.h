#ifndef     RS485_H_
#define     RS485_H_

#include <inttypes.h>
#include "Arduino.h"
#include "SoftwareSerial.h"

// Software Serial port for RS485 application
#define     RX      12      // D6
#define     TX      14      // D5
#define     RE_DE   2       // RS485 Receive and Data Enable pin

#define     RS485_F_LEN           100

#ifdef __cplusplus
extern "C" {
#endif

// uint8_t frame[RS485_F_LEN];
// uint8_t f_back[RS485_F_LEN];

// void rs485_init(uint32_t baud);

// uint8_t rs485_write_frame(uint8_t *f, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif      // End of RS485_H_
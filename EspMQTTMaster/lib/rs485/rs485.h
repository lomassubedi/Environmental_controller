#ifndef     RS485_H_
#define     RS485_H_

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t rs485_write_frame(uint8_t *f, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif      // End of RS485_H_
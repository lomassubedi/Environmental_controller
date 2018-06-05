#ifndef     MQTT_485_H_
#define     MQTT_485_H_

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "var_codes.h"
#include "data_types.h"
#include "mbcrc.h"
// #include "RS485.h"


#define   RS485_SLAVE_ENV_CTRL      1
#define   SLAVE_ID                  RS485_SLAVE_ENV_CTRL

#define     FUNC_READ_VAR           20      // Function code 20 for reading data from EEPROM
#define     FUNC_WRITE_VAR          40      // Function code 40 for writing data to EEPROM
#define     FUNC_READ_PROF          60      // Function code 60 for reading profile from EEPROM


#ifdef __cplusplus
extern "C" {
#endif


int8_t mqttToFrameSetProf(char * prof_num, char * profile_var_name, char * var_command, uint8_t * f, uint16_t * fLen);

int8_t mqttToFrameGetProf(char * prof_num, char * profile_var_name, uint8_t * f, uint16_t * fLen);

// uint16_t frameToMqtt(uint8_t * f, uint16_t flen, uint8_t * profNo, char * varName, char * arg);
uint16_t frameToMqtt(uint8_t * f, uint16_t flen);

#ifdef __cplusplus
}
#endif

#endif      // End of MQTT_485_H_      
#ifndef     MQTT_485_H_
#define     MQTT_485_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "var_codes.h"

extern unsigned char mqttToFrame(char * prof_num, char * profile_var_name, char * var_command, char * f);

#ifdef __cplusplus
}
#endif

#endif      // End of MQTT_485_H_      
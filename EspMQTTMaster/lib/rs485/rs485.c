// #include "rs485.h"
// #include "Arduino.h"
// #include "SoftwareSerial.h"


// SoftwareSerial RS485Ser(RX, TX, false, 256);


// void rs485_init(uint32_t baud) {
//     RS485Ser.begin(baud);
// }


// uint8_t rs485_write_frame(uint8_t *f, uint16_t len) {  
//   uint16_t indx = 0;  
//   // Make the RE/DE pin High
//   for(uint16_t flen = 0; flen < len; flen++) {
//     RS485Ser.write(f[flen]);
//   }
//   // Make the RE/DE pin Low
// }



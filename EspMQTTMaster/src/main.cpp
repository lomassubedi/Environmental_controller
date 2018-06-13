#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SoftwareSerial.h"
#include <stdlib.h>
#include <string.h>

#include "data_types.h"
#include "mqtt_485.h"
#include "rs485.h"
#include "mbcrc.h"

// #define       HOME
#define       OFFICE

// String match
#define     STR_MATCH       0

// #define   INTERNET
#define   LOCALHOST

// #define   SW_SER
#define   HW_SER

#define   DEBUG_ON
// Update these with values suitable for your network.

#ifdef HOME
  const char* ssid = "yangobahal";
  const char* password = "43A74C699A";
  // const char* mqtt_server = "192.168.100.81";
#endif

#ifdef HOME_
  const char* ssid = "Bee";
  const char* password = "p@ssw0rd";
  const char* mqtt_server = "192.168.1.104";
#endif

#ifdef OFFICE
  const char* ssid = "internets";
  const char* password = "CLFA4ABD38";
  const char* mqtt_server = "192.168.1.89";
#endif

#ifdef INTERNET
  const char* mqtt_server = "m14.cloudmqtt.com";
  const char* mqttUser = "icqulyad";
  const char* mqttPassword = "Fyk1fuYGR_PO";
  const int mqtt_port = 18772;
#endif

#define     TIME_BUS_CAPTURE      5000UL
#define     SIZE_MQTT_MESSAGE     200
#define     SIZE_MQTT_PAYLOAD     50
#define     F_LEN                 100


// Software Serial port for RS485 application
#define     RX      12      // D6
#define     TX      14      // D5
#define     RE_DE   2       // RS485 Receive and Data Enable pin

#define     RS485_F_LEN           100

// WiFi Client
WiFiClient espClient;

// MQTT Client
PubSubClient client(espClient);

#ifdef    SW_SER
  // RS485 Serial
  SoftwareSerial RS485Ser(RX, TX, false, 256);
#endif


#ifdef    HW_SER
  // Softwar Debug port 
  SoftwareSerial DebugSerial(RX, TX, false, 256);
#endif

/**
 * Variables to store MQTT information
 **/

long lastMsg = 0;
char msg[50];
int value = 0;
const int LED = D0;

uint8_t frame[F_LEN];
uint8_t rxFrame[F_LEN];

char * mqttMsg[SIZE_MQTT_MESSAGE];
char mqttPayLoad[SIZE_MQTT_PAYLOAD];
char str_mqtt[SIZE_MQTT_MESSAGE];

/*
 * Flags definations :
 */
bool flag_mqtt_read_prof_var = false;
bool flag_mqtt_write_prof_var = false;
bool flag_modbus_write_done = false;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  #ifdef    DEBUG_ON
    DebugSerial.println();
    DebugSerial.print("Connecting to ");
    DebugSerial.println(ssid);
  #endif

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    #ifdef    DEBUG_ON
      DebugSerial.print(".");
    #endif
  }

  randomSeed(micros());

  #ifdef    DEBUG_ON
    DebugSerial.println("");
    DebugSerial.println("WiFi connected");
    DebugSerial.println("IP address: ");
    DebugSerial.println(WiFi.localIP());
  #endif
}

void reconnect() {

  #ifdef LOCALHOST
    // Loop until we're reconnected
    while (!client.connected()) {

      #ifdef    DEBUG_ON
        DebugSerial.print("Attempting MQTT connection...");
      #endif

      // Create a random client ID
      String clientId = "ESP8266Client-";
      clientId += String(random(0xffff), HEX);
          
      // Attempt to connect
      if (client.connect(clientId.c_str())) {
        #ifdef    DEBUG_ON
          DebugSerial.println("connected");
        #endif
        // ... and resubscribe
        client.subscribe("setProf/+/+");
        client.subscribe("getProf/+");
      } else {

        #ifdef    DEBUG_ON
          DebugSerial.print("failed, rc=");
          DebugSerial.print(client.state());
          DebugSerial.println(" try again in 5 seconds");
        #endif
        // Wait 5 seconds before retrying
        delay(5000);
      }  
    }
  #endif

  #ifdef INTERNET
    while (!client.connected()) {
      #ifdef    DEBUG_ON
        DebugSerial.println("Connecting to MQTT...");
      #endif

      if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
        #ifdef    DEBUG_ON
          DebugSerial.println("connected");  
        #endif
        // client.publish("esp/test", "Hello from ESP8266 and its Lomas !!!");
        client.subscribe("setProf/+/+");
        client.subscribe("getProf/+");
      } else { 
        #ifdef    DEBUG_ON
          DebugSerial.print("failed with state ");
          DebugSerial.print(client.state());
        #endif
        delay(2000);  
      }
    }
  #endif
}


uint8_t rs485_write_frame(uint8_t *f, uint16_t len) {
  uint16_t flen;  
  // Make the RE/DE pin High
  for(flen = 0; flen < len; flen++) {
    Serial.write(f[flen]);
  }
  // Make the RE/DE pin Low
  return 0;
}

uint8_t rs485_read_frame(uint8_t *f) {
  uint16_t indx = 0; 
  uint16_t serialTry = 300;
  
  memset(f, 0, F_LEN);

  Serial.flush();
  while(serialTry > 0) {
    serialTry--;

    while(Serial.available()) {
    f[indx++] = Serial.read();
      if(indx > F_LEN) {
        break;
      }
    }
    delay(1);
  }
  return indx;
}

// ----------------- Custom functions Codes -------------
void callback(char* topic, byte* payload, unsigned int length) {

  unsigned char cnt = 0;
    
  for (unsigned int i = 0; i < length; i++) {
    mqttPayLoad[i] = (char)payload[i];
  }

  mqttPayLoad[length] = '\0';

  char *p = strtok(topic, "/");
  while(p != NULL) {
    mqttMsg[cnt++] = p;
    p = strtok(NULL, "/");
  }

  mqttMsg[cnt] = mqttPayLoad;
  #ifdef    DEBUG_ON
  // for(int i = 0; i <= cnt; i++) {
  //   DebugSerial.print(i);
  //   DebugSerial.print(". ");
  //   DebugSerial.print(mqttMsg[i]); 
  //   DebugSerial.write("\t");
  // }

  // DebugSerial.println();
  #endif

  cnt = 0;

  if(strcmp(mqttMsg[0], "setProf") == 0) {
    flag_mqtt_write_prof_var = true;
  } else if(strcmp(mqttMsg[0], "getProf") == 0) {
    flag_mqtt_read_prof_var = true;  
  } else {
    DebugSerial.println("Unknown topic !!");
  }

  // Toggle LED on each call back !!!
  digitalWrite(LED, !digitalRead(LED)); 
}

void setup() {

  pinMode(LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output

  // #ifdef    DEBUG_ON
    DebugSerial.begin(115200);
    DebugSerial.println("Debug serial started !!! ");
  // #endif

  #ifdef    SW_SER
    RS485Ser.begin(9600);
  #endif

  #ifdef    HW_SER
    Serial.begin(9600);
  #endif

  setup_wifi();
  
  #ifdef LOCALHOST
    client.setServer(mqtt_server, 1883);
  #endif

  #ifdef INTERNET
    client.setServer(mqtt_server, mqtt_port);
  #endif
  client.setCallback(callback);
}

void loop() {

  #if 1
    if (!client.connected()) {
      reconnect();
    }
  #endif

  if(flag_mqtt_write_prof_var) {
    
    uint16_t flen;
    flag_mqtt_write_prof_var = false;

    if(mqttToFrameSetProf(mqttMsg[1], mqttMsg[2], mqttPayLoad, frame, &flen) == 0) {
      for(int i = 0; i < flen; i++) {
        #ifdef    DEBUG_ON
          DebugSerial.write(frame[i]);
        #endif
      }

      #ifdef    DEBUG_ON
        DebugSerial.println();
      #endif

      rs485_write_frame(frame, flen);

    } else {

      #ifdef    DEBUG_ON
        DebugSerial.println("Error: Invalid profile received !!!");
      #endif

    }
  }

  // In case of MQTT read profile value command 
  if(flag_mqtt_read_prof_var) {
    
    uint16_t fln = 0;
    // static uint8_t k = 0;    
    flag_mqtt_read_prof_var = false;

    #ifdef    DEBUG_ON
      DebugSerial.println("Get Profile received !!");
    #endif

    if(mqttToFrameGetProf(mqttMsg[1], mqttPayLoad, frame, &fln) == 0) {
      
      // uint8_t frame_itr = 0;
      // do {
        // RS485Ser.flush();
        rs485_write_frame(frame, fln);
        // flag_modbus_write_done = true;
        fln = rs485_read_frame(rxFrame);
        // DebugSerial.println("Hello World!!!");
        // while(Serial.available() > 0) {
        // f[indx++] = Serial.read();
          // DebugSerial.write(Serial.read());
        // }

        // DebugSerial.println("Reading RS485 frame !!!");
        // frame_itr++;
      // } while((!fln) && (frame_itr <= 5));

      for(int i = 0; i < fln; i++) {
        #ifdef    DEBUG_ON
          DebugSerial.write(rxFrame[i]);
        #endif
      }

      if(fln) {
        uint16_t crc16_val_calc = CRC16(rxFrame, fln-2);
        uint16_t crc16_val_frm = ((rxFrame[fln - 1] << 8) | (rxFrame[fln - 2]));

        if(crc16_val_calc != crc16_val_frm) {

          #ifdef    DEBUG_ON
            DebugSerial.println("CRC Error !!!");
          #endif

          return;
        } 
      } else {

        #ifdef    DEBUG_ON
          DebugSerial.println("No frame read !!!");
        #endif

      }

      strcat(str_mqtt, "sendProf");
      strcat(str_mqtt, "/");  
      strcat(str_mqtt, mqttMsg[1]);
      strcat(str_mqtt, "/");  
      strcat(str_mqtt, mqttPayLoad);  
      mqttPayLoad[0] = '\0';

      frameToPayload(rxFrame, fln, mqttPayLoad);

      #ifdef    DEBUG_ON
        DebugSerial.print("MQTT String :");
        DebugSerial.print(str_mqtt);
        DebugSerial.print(" ");
        DebugSerial.println(mqttPayLoad);
      #endif

      // Send the read value over MQTT again 
      client.publish(str_mqtt, mqttPayLoad);

      mqttPayLoad[0] = '\0';
      str_mqtt[0] = '\0';
      fln = 0;
      
    } else {
      
      #ifdef    DEBUG_ON
        DebugSerial.println("Error: Invalid profile received !!!");
      #endif

    }  
  }

  /*
  if(flag_modbus_write_done) {      
    if(Serial.available()) {
      while(Serial.available()) {
        DebugSerial.write(Serial.read());
      }
      flag_modbus_write_done = false;
    }
  }
  */
  // if(!(millis() % TIME_BUS_CAPTURE)) {
  //   RS485Ser.write(56);
  // }
  client.loop();

  // DebugSerial.print();

  /*
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "hello world #%ld", value);
    DebugSerial.print("Publish messageS: ");
    DebugSerial.println(msg);
    client.publish("outTopic", msg);
  }
  */
}
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


WiFiClient espClient;
PubSubClient client(espClient);

// RS485 Serial
SoftwareSerial RS485Ser(RX, TX, false, 256);


/**
 * Variables to store MQTT information
 **/
long lastMsg = 0;
char msg[50];
int value = 0;
const int LED = D0;

uint8_t frame[F_LEN];

char * mqttMsg[SIZE_MQTT_MESSAGE];
char mqttPayLoad[SIZE_MQTT_PAYLOAD];
char str_mqtt[SIZE_MQTT_MESSAGE];

/*
 * Flags definations :
 */
bool flag_mqtt_read_prof_var = false;
bool flag_mqtt_write_prof_var = false;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {

  #ifdef LOCALHOST
    // Loop until we're reconnected
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      // Create a random client ID
      String clientId = "ESP8266Client-";
      clientId += String(random(0xffff), HEX);
          
      // Attempt to connect
      if (client.connect(clientId.c_str())) {
        Serial.println("connected");
        // ... and resubscribe
        client.subscribe("setProf/+/+");
        client.subscribe("getProf/+");
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }  
    }
  #endif

  #ifdef INTERNET
    while (!client.connected()) {
      Serial.println("Connecting to MQTT...");

      if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
        Serial.println("connected");  
        // client.publish("esp/test", "Hello from ESP8266 and its Lomas !!!");
        client.subscribe("profile/+/+");
      } else {  
        Serial.print("failed with state ");
        Serial.print(client.state());
        delay(2000);  
      }
    }
  #endif
}


uint8_t rs485_write_frame(uint8_t *f, uint16_t len) {
  // Make the RE/DE pin High
  for(uint16_t flen = 0; flen < len; flen++) {
    RS485Ser.write(f[flen]);
  }
  // Make the RE/DE pin Low
  return 0;
}

uint8_t rs485_read_frame(uint8_t *f) {
  uint16_t indx = 0;  

  while(RS485Ser.available()) {
    f[indx++] = RS485Ser.read();
  }
  return indx;
}

// ----------------- Custom functions Codes -------------
void callback(char* topic, byte* payload, unsigned int length) {

  unsigned char cnt = 0;
    
  for (int i = 0; i < length; i++) {
    mqttPayLoad[i] = (char)payload[i];
  }

  mqttPayLoad[length] = '\0';

  char *p = strtok(topic, "/");
  while(p != NULL) {
    mqttMsg[cnt++] = p;
    p = strtok(NULL, "/");
  }

  mqttMsg[cnt] = mqttPayLoad;

  for(int i = 0; i <= cnt; i++) {
    Serial.print(i);
    Serial.print(". ");
    Serial.print(mqttMsg[i]); 
    Serial.write("\t");
  }

  Serial.println();
  cnt = 0;

  if(strcmp(mqttMsg[0], "setProf") == 0) {
    flag_mqtt_write_prof_var = true;
  } else if(strcmp(mqttMsg[0], "getProf") == 0) {
    flag_mqtt_read_prof_var = true;  
  } else {
    Serial.println("Unknown topic !!");
  }

  // Toggle LED on each call back !!!
  digitalWrite(LED, !digitalRead(LED)); 
}

void setup() {

  // systerm_soft_wdt_stop();

  pinMode(LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  RS485Ser.begin(9600);
  setup_wifi();
  
  #ifdef LOCALHOST
    client.setServer(mqtt_server, 1883);
  #endif

  #ifdef INTERNET
    client.setServer(mqtt_server, mqtt_port);
  #endif
  client.setCallback(callback);
}

int i = 0;

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
        Serial.write(frame[i]);
      }
      Serial.println();
      rs485_write_frame(frame, flen);
    } else {
      Serial.println("Error: Invalid profile received !!!");
    }
  }

  // In case of MQTT read profile value command 
  if(flag_mqtt_read_prof_var) {
    
    uint16_t fln;
    // static uint8_t k = 0;

    flag_mqtt_read_prof_var = false;

    Serial.println("Get Profile received !!");
    if(mqttToFrameGetProf(mqttMsg[1], mqttPayLoad, frame, &fln) == 0) {

      rs485_write_frame(frame, fln);
      
      fln = rs485_read_frame(frame);

      if(fln) {
        
        uint16_t crc16_val_calc = CRC16(frame, fln-2);
        uint16_t crc16_val_frm = ((frame[fln - 1] << 8) | (frame[fln - 2]));

        if(crc16_val_calc != crc16_val_frm) {
          Serial.println("CRC Error !!!");
          return;
        }

        // Serial.print("CRCC: ");
        // Serial.print(crc16_val_calc);
        // Serial.print("   CRCF: ");
        // Serial.println(crc16_val_frm);        
      } else {
        Serial.println("No frame read !!!");
      }

      // f[indx++] = (uint8_t)(crc16_val & 0xFF);
      // f[indx++] = (uint8_t)(crc16_val >> 8);
      

      // for(int i = 0; i < fln; i++) {
      //   Serial.write(frame[i]);
      // }
      // str_mqtt[0] = '\0';
      strcat(str_mqtt, "sendProf");
      strcat(str_mqtt, "/");  
      strcat(str_mqtt, mqttMsg[1]);
      strcat(str_mqtt, "/");  
      strcat(str_mqtt, mqttPayLoad);  
      mqttPayLoad[0] = '\0';

      frameToPayload(frame, fln, mqttPayLoad);

      Serial.print("MQTT String :");
      Serial.print(str_mqtt);
      Serial.print(" ");
      Serial.println(mqttPayLoad);

      // Send the read value over MQTT again 
      client.publish(str_mqtt, mqttPayLoad);

      mqttPayLoad[0] = '\0';
      str_mqtt[0] = '\0';
      // fln = 0;
      
    } else {
      Serial.println("Error: Invalid profile received !!!");
    }  
  }

  // if(!(millis() % TIME_BUS_CAPTURE)) {
  //   RS485Ser.write(56);
  // }
  client.loop();

  // Serial.print();

  /*
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "hello world #%ld", value);
    Serial.print("Publish messageS: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }
  */
}
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SoftwareSerial.h"
#include <stdlib.h>
#include <string.h>

#include "data_types.h"
#include "mqtt_485.h"
#include "rs485.h"

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
#define     SIZE_MQTT_PAYLOAD     20
#define     F_LEN                 600


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

uint8_t frame[F_LEN];

char * mqttMsg[SIZE_MQTT_MESSAGE];
char mqttPayLoad[SIZE_MQTT_PAYLOAD];


bool flag_read_prof = false;

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
        client.subscribe("profile/+/+");
        client.subscribe("get_prof");
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
  uint16_t indx = 0;  
  // Make the RE/DE pin High
  for(uint16_t flen = 0; flen < len; flen++) {
    RS485Ser.write(f[flen]);
  }
  // Make the RE/DE pin Low
}

uint8_t rs485_read_frame(uint8_t *f) {
  uint16_t indx = 0;  

  while(RS485Ser.available()) {
    f[indx++] = RS485Ser.read();
  }
  return 0;
}

// ----------------- Custom functions Codes -------------
void callback(char* topic, byte* payload, unsigned int length) {
  
  unsigned char cnt = 0;
    
  for (int i = 0; i < length; i++) {
    mqttPayLoad[i] = (char)payload[i];
  }

  mqttPayLoad[length] = '\0';

  if(strcmp(topic, "get_prof")) {

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

    uint16_t flen;
    
    if(mqttToFrame(mqttMsg[1], mqttMsg[2], mqttPayLoad, frame, &flen) == 0) {
      for(int i = 0; i < flen; i++) {
        Serial.write(frame[i]);
      }
      Serial.println();
      rs485_write_frame(frame, flen);
    } else { 
      Serial.println("Error: Invalid profile received !!!");
    }
  } else {
    uint16_t fln;

    Serial.println("Get Profile received !!");

    if(mqttToPrfFrame(mqttPayLoad, frame, &fln) == 0) {
      for(int i = 0; i < fln; i++) {
        Serial.write(frame[i]);
      }
      Serial.println();
      rs485_write_frame(frame, fln);
      if(!rs485_read_frame(frame)) {
        flag_read_prof = true;
      }
    } else {
      Serial.println("Error: Invalid profile received !!!");
    }
  }

  // Toggle LED on each call back !!!
  digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED)); 

}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
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

  
  // if(!(millis() % TIME_BUS_CAPTURE)) {
  //   RS485Ser.write(56);
  // }
  client.loop();

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

 if(flag_read_prof) {
   
   flag_read_prof = false;

 }
}
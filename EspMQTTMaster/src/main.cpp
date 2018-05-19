#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SoftwareSerial.h"
#include <stdlib.h>
#include <string.h>

#include "data_types.h"
#include "mqtt_485.h"

// #define   HOME
#define   OFFICE

// String match
#define     STR_MATCH       0

//#define   INTERNET
#define   LOCALHOST
// Update these with values suitable for your network.



#ifdef HOME
  const char* ssid = "yangobahal";
  const char* password = "43A74C699A";
  const char* mqtt_server = "192.168.100.81";
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

// Software Serial port for RS485 application
#define     RX      12
#define     TX      14
#define     RE_DE   2     // RS485 Receive and Data Enable pin

#define     TIME_BUS_CAPTURE      5000UL
#define     SIZE_MQTT_MESSAGE     200
#define     SIZE_MQTT_PAYLOAD     20

WiFiClient espClient;
PubSubClient client(espClient);
SoftwareSerial RS485Ser(RX, TX, false, 256);

/**
 * Variables to store MQTT information
 **/
long lastMsg = 0;
uint8_t frame[100];
char msg[50];
int value = 0;
char * mqttMsg[SIZE_MQTT_MESSAGE];
char mqttPayLoad[SIZE_MQTT_PAYLOAD];

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

// ----------------- Custom functions Codes -------------
void callback(char* topic, byte* payload, unsigned int length) {

  unsigned char cnt = 0;
  char *p = strtok(topic, "/");

  while(p != NULL) {
    mqttMsg[cnt++] = p;
    p = strtok(NULL, "/");
  }

  for (int i = 0; i < length; i++) {
    mqttPayLoad[i] = (char)payload[i];
  }

  mqttPayLoad[length] = '\0';  
  mqttMsg[cnt] = mqttPayLoad;

  for(int i = 0; i <= cnt; i++) {
    Serial.print(i);
    Serial.print(". ");
    Serial.print(mqttMsg[i]); 
    Serial.write("\t");
  }

  Serial.println();

  cnt = 0;

	// char * profName = mqttMsg[1];
	// uint8_t i = 0;
	// int profInt = 0;

	// do {
	// 	uint8_t cVal = (uint8_t)profName[i] - 48;
	// 	profInt = profInt * 10;
	// 	profInt = profInt + cVal;	
	// 	i++;	
	// }
	// while(profName[i]);

  // Serial.println("Profilenumber value !!");
  // Serial.println(profName);
  // Serial.println(profInt);
  uint16 flen;
  
  if(!mqttToFrame(mqttMsg[1], mqttMsg[2], mqttPayLoad, frame, &flen)) {
    Serial.print("Length of frame: ");
    Serial.println(flen);
    for(int j = 0; j < flen; j++)
      Serial.write(frame[j]);
  }    

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  RS485Ser.begin(115200);
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

  
  if(!(millis() % TIME_BUS_CAPTURE)) {
    RS485Ser.write(56);
  }
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
}
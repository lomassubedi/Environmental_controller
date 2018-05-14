#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SoftwareSerial.h"
#include <stdlib.h>

//#define   HOME
#define   OFFICE

//#define   INTERNET
#define   LOCALHOST
// Update these with values suitable for your network.

#ifdef HOME
  const char* ssid = "yangobahal";
  const char* password = "43A74C699A";
  const char* mqtt_server = "192.168.100.81";
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

WiFiClient espClient;
PubSubClient client(espClient);
SoftwareSerial RS485Ser(RX, TX, false, 256);

long lastMsg = 0;
char msg[50];
int value = 0;


// void parse_mqtt(char * mqttTopic) {
//     char * token;
//     char delim = '/';

//     token = strtok(mqttTopic, delim);
    
//     // varName = &token;
//     Serial.println((char *)token);
    
//     token = strtok(mqttTopic, delim);

//     // dataTypes = &token;
//     Serial.println((char *)token);
  
// }


int split(char * result[], const char * str, unsigned int strSize, char tok) {
  char buff[strSize]; // it's better to use length of str instead of 1024
  int idx = 0;
  int len = 0;
  int ent_cnt = 0;
  int st = 0;

  // parse string
  while (1) {
    char ch = str[len++]; // need checking len to avoid overflow

    // end of string?
    if (ch == '\0')
      break;

    switch (st) {
    case 0:
      {
        if (ch == tok)
          st++;
        else
          buff[idx++] = ch;

        break;
      }

    case 1:
      {
        if (idx) {
          char * entry = (char * ) malloc(idx + 1);
          // char entry[idx+1];
          int i;

          for (i = 0; i < idx; i++)
            entry[i] = buff[i];

          entry[i] = '\0';
          result[ent_cnt++] = entry;
          idx = 0;
        }

        // normal char?
        if (ch != tok)
          buff[idx++] = ch;

        st--;
        break;
      }

    default:
      break;
    }
  }

  // process last part if any
  if (idx) {
    char * entry = (char * ) malloc(idx + 1);

    int i = 0;
    for (i = 0; i < idx; i++)
      entry[i] = buff[i];

    entry[i] = '\0';
    result[ent_cnt++] = entry;
  }

  return ent_cnt;
}


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

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");

    char * results[100];
    char payLoad[50];
    int cnt = split(results, topic, sizeof(topic), '/'); 

  for (int i = 0; i < length; i++) {
    payLoad[i] = (char)payload[i];
  }

  payLoad[length] = '\0';

  Serial.println(payLoad);
  
  /*
  results[cnt] = payLoad;

  for(int i = 0; i < 100; i++)
    Serial.println(results[i]);   

  */

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
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
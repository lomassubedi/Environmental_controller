#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SoftwareSerial.h"
#include <stdlib.h>
#include <string.h>

// #include "data_types.h"
#include "mqttT.h"

// #define   HOME
#define   OFFICE

// String match
#define     STR_MATCH       0

//#define   INTERNET
#define   LOCALHOST
// Update these with values suitable for your network.

#ifdef HOME_
  const char* ssid = "yangobahal";
  const char* password = "43A74C699A";
  const char* mqtt_server = "192.168.100.81";
#endif

#ifdef HOME
  const char* ssid = "Bee";
  const char* password = "p@ssw0rd";
  const char* mqtt_server = "192.168.1.100";
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
#define     SIZE_MQTT_MESSAGE     100
#define     SIZE_MQTT_PAYLOAD     20

WiFiClient espClient;
PubSubClient client(espClient);
SoftwareSerial RS485Ser(RX, TX, false, 256);

/**
 * Variables to store MQTT information
 **/
long lastMsg = 0;
char msg[50];
int value = 0;
char * mqttMsg[SIZE_MQTT_MESSAGE];
char mqttPayLoad[SIZE_MQTT_PAYLOAD];


char * varCodeTools[] = {
	"DeviceType",
	"Tools_Units_EnglishMetric",
	"Tools_Sensor_Fault",
	"Tools_ACFault_Message_YesNo",
	"Tools_LoTemp_Warning_YesNo",	
	"Tools_LoTemp_Warning_StPt",
	"Tools_HiTemp_Warning_YesNo",	
	"Tools_HiTemp_Warning_StPt",
	"Tools_LoHum_Warning_YesNo",	
	"Tools_LoHum_Warning_StPt",
	"Tools_HiHum_Warning_YesNo",	
	"Tools_HiHum_Warning_StPt",	
	"Tools_Critical_OverTemp_Fault_YesNo",
	"Tools_Critical_OverTemp_Fault_Flag",	
	"Tools_Critical_OverTemp_StPt",	
	"Tools_Critical_OverTemp_Response",
	"Tools_Critical_OverTemp_Message_YesNo",
	"Tools_ReStrike_Fault_YesNo",			
	"Tools_ReStrike_Delay_Time",	
	"Tools_ReStrike_Message_YesNo",
	"Tools_LoBat_Fault_Message_YesNo",	
	"Tools_Batt_Current_Volt",	
	"Tools_Light_Relay_Cycle_Counter",
	"Tools_HdVent_Relay_Cycle_Counter",
	"Tools_Circ_Relay_Cycle_Counter",
	"Tools_Vent_Relay_Cycle_Counter",
	"Tools_FXP1_Relay_Cycle_Counter",
	"Tools_FXP2_Relay_Cycle_Counter",	
	"Tools_Switch_YesNo",
	"Tools_HdVent_DC_DeAct_FactSet_Delay",
	"Tools_CO2_PVA_PostVent_FactSet_Delay",
	"Tools_LED_OnOff"
};

char * varNameProfile [] = {
	"Light_Operation_Mode",	
	"Light_OnTime",
	"Light_OffTime",
	"Light_LC_Duration",
	"Light_DC_Duration",
	"Light_LC_TimeRemain",
	"Light_DC_TimeRemain",
	"HdV_OnOff",
	"HdV_LC_OnOff",
	"HdV_LC_SrtDly",
	"HdV_DC_OnOff",
	"HdV_DC_SrtDly",
	"HdV_FlexFunc_YesNo",
	"HdV_FlexFunc_RptTmr",
	"HdV_FlexFunc_Heat",
	"HdV_FlexFunc_Cool",
	"HdV_FlexFunc_Hum",
	"HdV_FlexFunc_DeHum",
	"HdV_FlexFunc_CO2",
	"HdV_FlexFunc_Follow",
	"HdV_FlexFunc_Flip",
	"HdV_VentLoc_YesNo",
	"HdV_Tmr_LC_CclTime",
	"HdV_Tmr_LC_RptAftr",
	"HdV_Tmr_DC_CclTime",
	"HdV_Tmr_DC_RptAftr",
	"HdV_Htr_LC_OnTemp",
	"HdV_Htr_LC_OffTemp",
	"HdV_Htr_DC_OnTemp",
	"HdV_Htr_DC_OffTemp",
	"HdV_Cool_LC_OnTemp",
	"HdV_Cool_LC_OffTemp",
	"HdV_Cool_DC_OnTemp",
	"HdV_Cool_DC_OffTemp",
	"HdV_Hum_LC_OnHum",
	"HdV_Hum_LC_OffHum",
	"HdV_Hum_DC_OnHum",
	"HdV_Hum_DC_OffHum",
	"HdV_DeH_LC_OnHum",
	"HdV_DeH_LC_OffHum",
	"HdV_DeH_DC_OnHum",
	"HdV_DeH_DC_OffHum",
	"HdV_Co2_Opnlp_InjTime",
	"HdV_Co2_CylGen",
	"HdV_Co2_Cyl_StPtPPM",
	"HdV_Co2_Gen_OnPPM",
	"HdV_Co2_Gen_OffPPM",
	"Cir_OnOff",
	"Cir_LC_OnOff",
	"Cir_LC_SrtDly",
	"Cir_DC_OnOff",
	"Cir_DC_SrtDly",
	"Cir_FlexFunc_YesNo",
	"Cir_FlexFunc_RptTmr",
	"Cir_FlexFunc_Heat",
	"Cir_FlexFunc_Cool",
	"Cir_FlexFunc_Hum",
	"Cir_FlexFunc_DeHum",
	"Cir_FlexFunc_CO2",
	"Cir_FlexFunc_Follow",
	"Cir_FlexFunc_Flip",
	"Cir_VentLoc_YesNo",
	"Cir_Tmr_LC_CclTime",
	"Cir_Tmr_LC_RptAftr",
	"Cir_Tmr_DC_CclTime",
	"Cir_Tmr_DC_RptAftr",
	"Cir_Htr_LC_OnTemp",
	"Cir_Htr_LC_OffTemp",
	"Cir_Htr_DC_OnTemp",
	"Cir_Htr_DC_OffTemp",
	"Cir_Cool_LC_OnTemp",
	"Cir_Cool_LC_OffTemp",
	"Cir_Cool_DC_OnTemp",
	"Cir_Cool_DC_OffTemp",
	"Cir_Hum_LC_OnHum",
	"Cir_Hum_LC_OffHum",
	"Cir_Hum_DC_OnHum",
	"Cir_Hum_DC_OffHum",
	"Cir_DeH_LC_OnHum",
	"Cir_DeH_LC_OffHum",
	"Cir_DeH_DC_OnHum",
	"Cir_DeH_DC_OffHum",
	"Cir_Co2_Opnlp_InjTime",
	"Cir_Co2_CylGen",
	"Cir_Co2_Cyl_StPtPPM",
	"Cir_Co2_Gen_OnPPM",
	"Cir_Co2_Gen_OffPPM",	
	"Ven_OnOff",
	"Ven_LC_OnOff",	
	"Ven_LC_SrtDly",    
	"Ven_RptVnt_LC_OnOff",
	"Ven_RptVnt_LC_CclTime",
	"Ven_RptVnt_LC_RptAftr",	
	"Ven_TempVnt_OnOff",
	"Ven_TempVnt_LC_OnTemp",
	"Ven_TempVnt_LC_OffTemp",	
	"Ven_HumVnt_OnOff",	
	"Ven_LC_HumVnt_OnHum",
	"Ven_LC_HumVnt_OffHum",	
	"Ven_DC_OnOff",	
	"Ven_DC_SrtDly",	
	"Ven_RptVnt_DC_OnOff",	
	"Ven_RptVnt_DC_CclTime",	
	"Ven_RptVnt_DC_RptAftr",	
	"Ven_TempVnt_DC_OnTemp",
	"Ven_TempVnt_DC_OffTemp",	
	"Ven_HumVnt_DC_OnHum",
	"Ven_HumVnt_DC_OffHum",	
	"FXP1_OnOff",
	"FXP1_LC_OnOff",	
	"FXP1_LC_SrtDly",
	"FXP1_DC_OnOff",	
	"FXP1_DC_SrtDly",    
	"FXP1_FlexFunc_YesNo",
	"FXP1_FlexFunc_RptTmr",
	"FXP1_FlexFunc_Heat",
	"FXP1_FlexFunc_Cool",
	"FXP1_FlexFunc_Hum",
	"FXP1_FlexFunc_DeHum",
	"FXP1_FlexFunc_CO2",
	"FXP1_FlexFunc_Follow",
	"FXP1_FlexFunc_Flip",
	"FXP1_VentLoc_YesNo",	
	"FXP1_Tmr_LC_CclTime",
	"FXP1_Tmr_LC_RptAftr",
	"FXP1_Tmr_DC_CclTime",
	"FXP1_Tmr_DC_RptAftr",	
	"FXP1_Htr_LC_OnTemp",
	"FXP1_Htr_LC_OffTemp",
	"FXP1_Htr_DC_OnTemp",
	"FXP1_Htr_DC_OffTemp",
	"FXP1_Cool_LC_OnTemp",
	"FXP1_Cool_LC_OffTemp",
	"FXP1_Cool_DC_OnTemp",
	"FXP1_Cool_DC_OffTemp",
	"FXP1_Hum_LC_OnHum",
	"FXP1_Hum_LC_OffHum",
	"FXP1_Hum_DC_OnHum",
	"FXP1_Hum_DC_OffHum",
	"FXP1_DeH_LC_OnHum",
	"FXP1_DeH_LC_OffHum",
	"FXP1_DeH_DC_OnHum",
	"FXP1_DeH_DC_OffHum",	
	"FXP1_Co2_Opnlp_InjTime",	
	"FXP1_Co2_CylGen",	
	"FXP1_Co2_Cyl_StPtPPM",
	"FXP1_Co2_Gen_OnPPM",
	"FXP1_Co2_Gen_OffPPM",	
	"FXP2_OnOff",
	"FXP2_LC_OnOff",
	"FXP2_LC_SrtDly",	
	"FXP2_DC_OnOff",	
	"FXP2_DC_SrtDly",     
	"FXP2_FlexFunc_YesNo",
	"FXP2_FlexFunc_RptTmr",
	"FXP2_FlexFunc_Heat",
	"FXP2_FlexFunc_Cool",
	"FXP2_FlexFunc_Hum",
	"FXP2_FlexFunc_DeHum",
	"FXP2_FlexFunc_CO2",
	"FXP2_FlexFunc_Follow",
	"FXP2_FlexFunc_Flip",
	"FXP2_VentLoc_YesNo",	
	"FXP2_Tmr_LC_CclTime",
	"FXP2_Tmr_LC_RptAftr",
	"FXP2_Tmr_DC_CclTime",
	"FXP2_Tmr_DC_RptAftr",	
	"FXP2_Htr_LC_OnTemp",
	"FXP2_Htr_LC_OffTemp",
	"FXP2_Htr_DC_OnTemp",
	"FXP2_Htr_DC_OffTemp",
	"FXP2_Cool_LC_OnTemp",
	"FXP2_Cool_LC_OffTemp",
	"FXP2_Cool_DC_OnTemp",
	"FXP2_Cool_DC_OffTemp",
	"FXP2_Hum_LC_OnHum",
	"FXP2_Hum_LC_OffHum",
	"FXP2_Hum_DC_OnHum",
	"FXP2_Hum_DC_OffHum",
	"FXP2_DeH_LC_OnHum",
	"FXP2_DeH_LC_OffHum",
	"FXP2_DeH_DC_OnHum",
	"FXP2_DeH_DC_OffHum",	
	"FXP2_Co2_Opnlp_InjTime",
	"FXP2_Co2_CylGen",	
	"FXP2_Co2_Cyl_StPtPPM",
	"FXP2_Co2_Gen_OnPPM",
	"FXP2_Co2_Gen_OffPPM"
};

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

unsigned char mqttToFrame(char * prof_num, char * profile_var_name, char * var_command, char * f) {

  if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_Operation_Mode])) {
    int i = 0;
    for(i = 0; i < 10; i++) {
        f[i] = 48+i;
    }
    f[i] = '\0';
    Serial.println("I am here !!!");
  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_OnTime])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_OffTime])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_LC_Duration])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_DC_Duration])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_LC_TimeRemain])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Light_DC_TimeRemain])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_LC_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_LC_SrtDly])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DC_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DC_SrtDly])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_YesNo])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_RptTmr])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Heat])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Cool])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Hum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_DeHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_CO2])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Follow])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_FlexFunc_Flip])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_VentLoc_YesNo])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Tmr_LC_CclTime])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Tmr_LC_RptAftr])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Tmr_DC_CclTime])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Tmr_DC_RptAftr])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Htr_LC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Htr_LC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Htr_DC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Htr_DC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Cool_LC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Cool_LC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Cool_DC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Cool_DC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Hum_LC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Hum_LC_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Hum_DC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Hum_DC_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DeH_LC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DeH_LC_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DeH_DC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_DeH_DC_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_Opnlp_InjTime])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_CylGen])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_Cyl_StPtPPM])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_Gen_OnPPM])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_HdV_Co2_Gen_OffPPM])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_LC_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_LC_SrtDly])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DC_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DC_SrtDly])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_YesNo])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_RptTmr])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Heat])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Cool])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Hum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_DeHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_CO2])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Follow])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_FlexFunc_Flip])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_VentLoc_YesNo])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Tmr_LC_CclTime])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Tmr_LC_RptAftr])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Tmr_DC_CclTime])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Tmr_DC_RptAftr])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Htr_LC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Htr_LC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Htr_DC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Htr_DC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Cool_LC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Cool_LC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Cool_DC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Cool_DC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Hum_LC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Hum_LC_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Hum_DC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Hum_DC_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DeH_LC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DeH_LC_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DeH_DC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_DeH_DC_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_Opnlp_InjTime])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_CylGen])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_Cyl_StPtPPM])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_Gen_OnPPM])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Cir_Co2_Gen_OffPPM])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_LC_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_LC_SrtDly])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_LC_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_LC_CclTime])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_LC_RptAftr])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_LC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_LC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_HumVnt_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_LC_HumVnt_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_LC_HumVnt_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_DC_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_DC_SrtDly])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_DC_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_DC_CclTime])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_RptVnt_DC_RptAftr])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_DC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_TempVnt_DC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_HumVnt_DC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_Ven_HumVnt_DC_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_LC_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_LC_SrtDly])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DC_OnOff])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DC_SrtDly])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_YesNo])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_RptTmr])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Heat])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Cool])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Hum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_DeHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_CO2])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Follow])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_FlexFunc_Flip])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_VentLoc_YesNo])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Tmr_LC_CclTime])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Tmr_LC_RptAftr])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Tmr_DC_CclTime])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Tmr_DC_RptAftr])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Htr_LC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Htr_LC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Htr_DC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Htr_DC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Cool_LC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Cool_LC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Cool_DC_OnTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Cool_DC_OffTemp])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Hum_LC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Hum_LC_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Hum_DC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_Hum_DC_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DeH_LC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DeH_LC_OffHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DeH_DC_OnHum])) {

  } else if(!strcmp(profile_var_name, varNameProfile[var_code_Ad1_FXP1_DeH_DC_OffHum])) {

  } else {

  }
  return 0;
}
    
    /*
    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {

    } else if(!strcmp(profile_var_name, varNameProfile[])) {
*/

void callback(char* topic, byte* payload, unsigned int length) {

  uint8_t cnt = 0;
  char *p = strtok(topic, "/");

  while(p != NULL) {
    mqttMsg[cnt++] = p;
    p = strtok(NULL, "/");
  }

  for (int i = 0; i < length; i++) {
    mqttPayLoad[i] = (char)mqttPayLoad[i];
  }

  mqttPayLoad[length] = '\0';
  mqttMsg[cnt] = mqttPayLoad;

  for(int i = 0; i <= cnt; i++) {
    Serial.print(mqttMsg[i]); 
    Serial.write("\t");
  }

  Serial.println();

  cnt = 0;

  char frame[100];

  mqttToFrame(mqttMsg[1], mqttMsg[2], mqttPayLoad, frame);

  Serial.println(frame);
  // Serial.println(varNameProfile[var_code_Ad1_Light_OnTime]);
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
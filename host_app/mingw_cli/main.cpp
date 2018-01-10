#include <iostream>
#include<stdio.h>
#include "SerialPort.h"

using namespace std;

char* portName = "\\\\.\\COM9";

#define MAX_DATA_LENGTH 255

char incomingData[MAX_DATA_LENGTH];

//Blinking Delay
const unsigned int BLINKING_DELAY = 1000;

//Arduino SerialPort object
SerialPort *RS485Port;

char stringArrya[] = "This is a test string!";


void exampleReceiveData(void) {
    int readResult = RS485Port->readSerialPort(incomingData, MAX_DATA_LENGTH);
    if(readResult) {
        printf("%s", incomingData);
        memset(incomingData, 0, sizeof incomingData);
    }
}

void exampleWriteData(unsigned int delayTime) {
    RS485Port->writeSerialPort(ledON, MAX_DATA_LENGTH);
    Sleep(delayTime);
    RS485Port->writeSerialPort(ledOFF, MAX_DATA_LENGTH);
    Sleep(delayTime);
}


int main() {

    RS485Port = new SerialPort(portName);

    //Checking if RS485Port is connected or not
    if (RS485Port->isConnected()){
        std::cout << "Connection established at port " << portName << endl;
    }

return 0;
}

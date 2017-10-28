// CLI_env_master.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"

#include <tchar.h>
#include <windows.h>
#include "Serial.h"

#include "mbcrc.h"

using namespace std;


int main() {
	//CRC crc;
	//uint8_t dataArry[] = {2, 3, 4, 5, 6, 7};
	//cout << "CRC : " << hex << uppercase << crc.CRC16(dataArry, sizeof(dataArry)) << endl;
	//cout << "Hello world!" << endl;

	CSerial serial;

	serial.Open(_T("COM8"));

	// Setup the serial port (9600,N81) using hardware handshaking
	serial.Setup(CSerial::EBaud9600, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);
	serial.SetupHandshaking(CSerial::EHandshakeHardware);

	// The serial port is now ready and we can send/receive data. If
	// the following call blocks, then the other side doesn't support
	// hardware handshaking.
	serial.Write("Hello world!\n");

	// Close the port again
	serial.Close();

	return 0;
}

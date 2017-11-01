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

	serial.Open(_T("COM9"));

	// Setup the serial port (9600,N81) using hardware handshaking
	serial.Setup(CSerial::EBaud9600, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);
	/*serial.SetupHandshaking(CSerial::EHandshakeHardware);*/

	// The serial port is now ready and we can send/receive data. If
	// the following call blocks, then the other side doesn't support
	// hardware handshaking.
	serial.Write("Hello world!\n");

	// Use 'non-blocking' reads, because we don't know how many bytes
	// will be received. This is normally the most convenient mode
	// (and also the default mode for reading data).
	serial.SetupReadTimeouts(CSerial::EReadTimeoutNonblocking);

	// Read data, until there is nothing left
	DWORD dwBytesRead = 0;
	BYTE  abBuffer[100];
	do
	{
		// Read data from the COM-port
		serial.Read(abBuffer, sizeof(abBuffer), &dwBytesRead);
		if (dwBytesRead > 0)
		{
			cout << "This is the data which has been received from the Serial : " << abBuffer << endl;
			// TODO: Process the data
		}
	} while (dwBytesRead == sizeof(abBuffer));

	/*while (1);*/

	/*cout << "This is the data which has been received from the data: " << abBuffer << endl;*/
	
	/*SetupReadTimeouts*/

	// Close the port again
	serial.Close();

	return 0;
}

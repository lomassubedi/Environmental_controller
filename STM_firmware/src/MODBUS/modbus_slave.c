// File Name: modbus_slave.c
// Author: Lomas
// Date:

#include "modbus_slave.h"
#include "mbcrc.h"
#include "reg_list.h"
#include "stm32f0_discovery.h"
#include "eeprom_profile.h"

#define 	BUFFER_SIZE 			600
#define 	DEVICE_SLAVE_ID			1

TIM_TimeBaseInitTypeDef timerInitStructure; 

uint8_t frame[BUFFER_SIZE];
uint16_t dummyHoldingReg[BUFFER_SIZE];

volatile uint16_t buffer = 0;
volatile uint16_t flag_rx_complete = 0;

// Size of register array is assumed to be the highest location 
// up to which data is stored in the EEPROM
// EEPROM space is being treated as a Modbus register 
const uint16_t holdingRegsSize = EEPROM_DATA_TOP;

volatile uint8_t broadcastFlag;
volatile uint8_t slaveID = DEVICE_SLAVE_ID;
volatile uint8_t function;
volatile uint16_t errorCount;
volatile uint8_t timerInit = 0;

void initUsartModbus(void) {
		// USART periferial initialization settings
	  USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef	GPIO_InitStructure;

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

	  //Configure USART1 pins: Rx (PA10) and Tx (PA9)
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  // ------------- Configure USART1 setting: ---------------
	  USART_InitStructure.USART_BaudRate = 9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  USART_Init(USART1, &USART_InitStructure);
	  USART_Cmd(USART1,ENABLE);
		
		// USART1 only receive Interrupt Enable
//		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		NVIC_EnableIRQ(USART1_IRQn);
}

void InitializeTimerRxTimeout() {
	
//	TIM_TimeBaseInitTypeDef timerInitStructure; 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	NVIC_EnableIRQ(TIM2_IRQn);
}

void usartPutc(unsigned char c) {
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, c);
}

void TIM2_IRQHandler(){
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		// Disable interrupts
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
		TIM_Cmd(TIM2, DISABLE);	
		TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
		TIM_DeInit(TIM2);

		flag_rx_complete = 1;
		STM_EVAL_LEDToggle(LED4);
    }
}

void USART1_IRQHandler(void) {			/* RXNE handler */	

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		
		if(flag_rx_complete != 1) {
			
			frame[buffer++] = USART_ReceiveData(USART1);
			
			TIM_DeInit(TIM2);
			
			timerInitStructure.TIM_Prescaler = 47;
			timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
			timerInitStructure.TIM_Period = 3880; // for T3.5 Char
			timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseInit(TIM2, &timerInitStructure);
			
			TIM_ClearFlag(TIM2, TIM_FLAG_Update);
			TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
			TIM_Cmd(TIM2, ENABLE);
			
		} else {
			USART_ReceiveData(USART1);
		}
	}
}

void sendPacket(uint8_t bufferSize) {
	unsigned char i;
    
  for (i = 0; i < bufferSize; i++) {
		usartPutc(frame[i]);
		
		// TODO
		// Implement DE/RE for RS485
		
		// TODO
		// Put space of about 1.5 characters while sending each bytes from a frame
	} 
		// TODO
		// Put space of about 3.5 characters as the end of the transmission
		// Or utilize the timer 2
		
}

void exceptionResponse(unsigned char exception) {
	unsigned int crc16;
	
  errorCount++; 				// each call to exceptionResponse() will increment the errorCount
	
  if (!broadcastFlag) {	// don't respond if its a broadcast message
  
    frame[0] = slaveID;
    frame[1] = (function | 0x80); 	// set the MSB bit high, informs the master of an exception
    frame[2] = exception;
    crc16 = CRC16(frame, 3); 	// ID, function + 0x80, exception code == 3 bytes
    frame[3] = crc16 >> 8;
    frame[4] = crc16 & 0xFF;
    sendPacket(5); 						// exception response is always 5 bytes ID, function + 0x80, exception code, 2 bytes crc
  }
}

uint8_t modbus_update() {
	
	uint8_t id;
	uint16_t crc = 0;
	uint16_t startingAddress;
	uint16_t no_of_registers;
	uint16_t maxData;
	uint16_t index;
	uint16_t address;
	uint16_t crc16;
	uint16_t noOfBytes;
	uint16_t responseFrameSize;
	
	uint16_t byteCountProfRd;
	
	uint16_t temp;
	uint16_t tmpCRC = 0;
	
	// EEPROM management Vars
	uint8_t profileNo;
	uint8_t varCode;
	uint8_t byteCount = 0;
	uint8_t bytesArry[4];
	uint8_t byteIndex = 0;
	

//  The minimum request packet is 8 bytes for function 3 & 16
	if(flag_rx_complete) {

		if(buffer > 4) {
			
			id = frame[0];
			broadcastFlag = 0;
			
			if (id == 0)
				broadcastFlag = 1;
			
			if (id == slaveID || broadcastFlag) { // if the recieved ID matches the slaveID or broadcasting id (0), continue
				// crc = ((frame[buffer - 2] << 8) | frame[buffer - 1]); // combine the crc Low & High bytes
				crc = ((frame[buffer - 1] << 8) | frame[buffer - 2]);
				tmpCRC = CRC16(frame, (buffer - 2));
				
		    if (tmpCRC == crc) { // if the calculated crc matches the recieved crc continue
					
					// STM_EVAL_LEDToggle(LED3);
					function = frame[1];
					startingAddress = ((frame[2] << 8) | frame[3]); // combine the starting address bytes
					no_of_registers = ((frame[4] << 8) | frame[5]); // combine the number of register bytes  
					maxData = startingAddress + no_of_registers;
					
					// broadcasting is not supported for function 3 
					if (!broadcastFlag && (function == 3)) {

						if (startingAddress < holdingRegsSize) { // check exception 2 ILLEGAL DATA ADDRESS

						  if (maxData <= holdingRegsSize) { // check exception 3 ILLEGAL DATA VALUE
			
								noOfBytes = no_of_registers * 2;
								responseFrameSize = 5 + noOfBytes; // ID, function, noOfBytes, (dataLo + dataHi) * number of registers, crcLo, crcHi
								frame[0] = slaveID;
								frame[1] = function;
								frame[2] = noOfBytes;
								address = 3; // PDU starts at the 4th byte					
								
								for (index = startingAddress; index < maxData; index++) {
									temp = 0x4567; // Just a dummy value 
									// TODO
									// Insert code that reads specified data from EEPROM
									// and feed in this value
									// IMPORTANT: Read Write error exception encorporating EEPROM read write drivers
									frame[address] = temp >> 8; // split the register into 2 bytes
									address++;
									frame[address] = temp & 0xFF;
									address++;
								}
								
								crc16 = CRC16(frame, (responseFrameSize - 2));
								frame[responseFrameSize - 2] = crc16 & 0xFF; // split crc into 2 bytes
								frame[responseFrameSize - 1] = crc16 >> 8;
								sendPacket(responseFrameSize);
							} else {
								exceptionResponse(3); // exception 3 ILLEGAL DATA VALUE
							}
						} else {
							exceptionResponse(2); // exception 2 ILLEGAL DATA ADDRESS
						}
						
					// Function 16 write to holding registers
					} else if(function == 16) {

						// check if the recieved number of bytes matches the calculated bytes minus the request bytes
						// id + function + (2 * address bytes) + (2 * no of register bytes) + byte count + (2 * CRC bytes) = 9 bytes
						if (frame[6] == (buffer - 9)) {

							if (startingAddress < holdingRegsSize) { // check exception 2 ILLEGAL DATA ADDRESS
							
								if (maxData <= holdingRegsSize) { // check exception 3 ILLEGAL DATA VALUE
								
									address = 7; // start at the 8th byte in the frame

									for (index = startingAddress; index < maxData; index++) {
										// Just a dummy write test
										dummyHoldingReg[index] = ((frame[address] << 8) | frame[address + 1]);
										address += 2;
										// TODO
										// Implement mechanism to write bytes to the EEPROM to specified address
										// IMPORTANT : Add Read/Write exceptions
										// holdingRegs[index] = ((frame[address] << 8) | frame[address + 1]);
										// address += 2;
									} 

									// only the first 6 bytes are used for CRC calculation
									crc16 = CRC16(frame, 6); 
									frame[6] = crc16 & 0xFF; // split crc into 2 bytes
									frame[7] = crc16 >> 8;

									// a function 16 response is an echo of the first 6 bytes from the request + 2 crc bytes
									if (!broadcastFlag) // don't respond if it's a broadcast message
										sendPacket(8); 

								} else {
									exceptionResponse(3); // exception 3 ILLEGAL DATA VALUE
								} 
							} else {
								exceptionResponse(2); // exception 2 ILLEGAL DATA ADDRESS
							}
						} else {
							errorCount++; // corrupted packet
						}   
					} else if (function == 20) {	// If the function Code is 20 i.e. read EEPRM Registers
						
						profileNo = frame[2];					// Get profile Number
						varCode = frame[3];						// Get variable code
						
						eeprom_get_var(profileNo, varCode, &byteCount, bytesArry);
						
						frame[4] = byteCount;
						
						address = 5;
						
						for(byteIndex = 0; byteIndex < byteCount; byteIndex++) {
							frame[address++] = bytesArry[byteIndex];
						}
						
						tmpCRC = CRC16(frame, address);
						frame[address++] = (uint8_t)(tmpCRC & 0x00FF);					// LSB
						frame[address++] = (uint8_t)((tmpCRC >> 8) & 0x00FF);		// MSB						
						
						sendPacket(address);
						
					} 
					else if(function == 40) {				// function code 40 for writing data to EEPROM
						
						profileNo = frame[2];					// Get profile Number
						varCode = frame[3];						// Get variable code 
						byteCount = frame[4];
						
						address = 5;
						
						for(byteIndex = 0; byteIndex < byteCount; byteIndex++) {
							bytesArry[byteIndex] = frame[address++];
						}
						
						// Write data to EEPROM
						eeprom_set_var(profileNo, varCode, byteCount, bytesArry);
						
						// Create a reply packate and send back to master
						eeprom_get_var(profileNo, varCode, &byteCount, bytesArry);
						
						address = 5;
						
						for(byteIndex = 0; byteIndex < byteCount; byteIndex++) {
							frame[address++] = bytesArry[byteIndex];
						}
						
						tmpCRC = CRC16(frame, address);
						
						frame[address++] = (uint8_t)(tmpCRC & 0x00FF);					// LSB
						frame[address++] = (uint8_t)((tmpCRC >> 8) & 0x00FF);		// MSB						
						
						sendPacket(address);
						// ------------------- End of Reply -------------------------
					
					} else if(function == 60) {		// function code 60 for reading a complete profile
						profileNo = frame[2];				// Get profile Number
						
						byteCountProfRd = sizeof(PROFILE);						
						// MSB n bytes
						frame[3] = (uint8_t)(byteCountProfRd >> 8);
						
						// LSB n bytes
						frame[4] = (uint8_t)(byteCountProfRd & 0xFF);
						
						address = 5;
						
						get_profile(profileNo);					
						
						memcpy(&frame[address], (void *)profile, byteCountProfRd);
						
						address += byteCountProfRd;
						
						tmpCRC = CRC16(frame, address);
						
						frame[address++] = (uint8_t)(tmpCRC & 0x00FF);					// LSB
						frame[address++] = (uint8_t)((tmpCRC >> 8) & 0x00FF);		// MSB						
						
						sendPacket(address);

						
					} else {
						exceptionResponse(1); // exception 1 ILLEGAL FUNCTION
					}
				} else { // Checksum failed 
					errorCount++;
					// No response on CRC error !!
				}
			}
		} else if (buffer > 0 && buffer < 6) {
			errorCount++; // corrupted packet
		}
		buffer = 0;						// Reset the queue
		flag_rx_complete = 0; // Reset the receive complete flag for new reception
		// Ready for next data reception on the bus
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	}
  return errorCount;
}

void init_modbus() {
	initUsartModbus();	
	InitializeTimerRxTimeout();
}


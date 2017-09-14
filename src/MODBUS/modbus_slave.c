// File Name: modbus_slave.c
// Author: Lomas
// Date:

#include "modbus_slave.h"
#include "mbcrc.h"
#include "stm32f0_discovery.h"

#define 	BUFFER_SIZE 			100
#define 	DEVICE_SLAVE_ID			1
#define		EEPROM_MAX_SIZE			65535	

TIM_TimeBaseInitTypeDef timerInitStructure; 

uint8_t frame[BUFFER_SIZE];

volatile uint16_t buffer = 0;
volatile uint16_t flag_rx_complete = 0;

// Size of register array is assumed to be equal to the EEPROM Size
// EEPROM space is being treated as a Modbus register 
const uint16_t holdingRegsSize = EEPROM_MAX_SIZE; 

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
	
	uint8_t counter = 0;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
//		Disable interrupts
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
	
	uint16_t temp;
	uint16_t tmpCRC = 0;
	
  
//  The minimum request packet is 8 bytes for function 3 & 16
	if(flag_rx_complete) {

		if(buffer > 6) {
			
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
							frame[address] = temp >> 8; // split the register into 2 bytes
							address++;
							frame[address] = temp & 0xFF;
							address++;
						}
						
						crc16 = CRC16(frame, (responseFrameSize - 2));
						frame[responseFrameSize - 2] = crc16 & 0xFF; // split crc into 2 bytes
						frame[responseFrameSize - 1] = crc16 >> 8;
						sendPacket(responseFrameSize);
					} 
				} else { // Checksum failed 
					errorCount++;
				}
			}
		} else if (buffer > 0 && buffer < 8) {
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
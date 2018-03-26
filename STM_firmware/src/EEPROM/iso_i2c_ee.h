/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ISO_I2C_EE_H
#define __ISO_I2C_EE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "eeprom_data.h"

/*  ----- Defines for profile ----------- */
// Profile size 522 Bytes 
//#define			PROFILE_SIZE		522
	 
/** @addtogroup Utilities
  * @{
  */

/** @addtogroup ISO_M0 Board
  * @{
  */ 

/** @addtogroup ISO_M0 Board
  * @{
  */
  
/** @addtogroup ISO_I2C_EE
  * @brief      This file includes the I2C EEPROM driver of ISO-M0 board.
  * @{
  */  

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  I2C1_SCL   = GPIO_Pin_6, 
  I2C1_SDA   = GPIO_Pin_7
}ISO_I2C1_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Uncomment the following line to use the default sEE_TIMEOUT_UserCallback() 
   function implemented in stm32072b_eval_i2c_ee.c file.
   sEE_TIMEOUT_UserCallback() function is called whenever a timeout condition 
   occurs during communication (waiting on an event that doesn't occur, bus 
   errors, busy devices ...). */   
 #define USE_DEFAULT_TIMEOUT_CALLBACK 
   

#define sEE_I2C1_PORT  GPIOB
#define sEE_I2C        I2C1

#define sEE_M24C64_32
   
#if !defined (sEE_AT24C02) && !defined (sEE_M24C08) && !defined (sEE_M24C64_32) && !defined (sEE_M24LR64)
/* Use the defines below the choose the EEPROM type */
 #define sEE_AT24C02  /* Support the device: AT24C02. */
/* #define sEE_M24C08*/  /* Support the device: M24C08. */
/* note: Could support: M24C01, M24C02, M24C04 and M24C16 if the blocks and 
   HW address are correctly defined*/
/*#define sEE_M24C64_32*/  /* Support the devices: M24C32 and M24C64 */
/*#define sEE_M24LR64 */ /*Support the devices: M24LR64 */ 
#endif

#ifdef sEE_M24C64_32
/* For M24C32 and M24C64 devices, E0,E1 and E2 pins are all used for device 
  address selection (ne need for additional address lines). According to the 
  Harware connection on the board. */

 #define sEE_HW_ADDRESS         0xA0   /* E0 = E1 = E2 = 0 */ 

#elif defined (sEE_M24C08)
/* The M24C08W contains 4 blocks (128byte each) with the adresses below: E2 = 0 
   EEPROM Addresses defines */
 #define sEE_HW_ADDRESS     0xA0   /* E2 = 0 */ 
 /*#define sEE_HW_ADDRESS     0xA2*/ /* E2 = 0 */  
 /*#define sEE_HW_ADDRESS     0xA4*/ /* E2 = 0 */
 /*#define sEE_HW_ADDRESS     0xA6*/ /* E2 = 0 */

#elif defined (sEE_AT24C02)
/* The M24C02 contains 4 blocks (128byte each) with the adresses below: E2 = 0 
   EEPROM Addresses defines */
 #define sEE_HW_ADDRESS     0xA0   /* E2 = 0 */ 
 /*#define sEE_HW_ADDRESS     0xA2*/ /* E2 = 0 */  
 /*#define sEE_HW_ADDRESS     0xA4*/ /* E2 = 0 */
 /*#define sEE_HW_ADDRESS     0xA6*/ /* E2 = 0 */

#elif defined (sEE_M24LR64)
 #define sEE_HW_ADDRESS         0xA0

#endif /* sEE_M24C64_32 */

#define sEE_I2C_TIMING          0x00100444
//0x00210507//0x00100000//0x00700818//0x00700818//0x00100444/*100khz*/ //  0x40B22536/*17khz*/

#if defined (sEE_AT24C02)
 #define sEE_PAGESIZE           8
#elif defined (sEE_M24C64_32)
 #define sEE_PAGESIZE           32
#elif defined (sEE_M24LR64)
 #define sEE_PAGESIZE           4
#elif defined (sEE_M24C02)
 #define sEE_PAGESIZE           8
#endif
   
#define  countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize     (countof(Write_Buffer)-1)
   
/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will 
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define sEE_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define sEE_LONG_TIMEOUT         ((uint32_t)(10 * sEE_FLAG_TIMEOUT))

/* Maximum number of trials for sEE_WaitEepromStandbyState() function */
#define sEE_MAX_TRIALS_NUMBER     300
      
#define sEE_OK                    0
#define sEE_FAIL                  1   

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
void     I2C_EEPROM_24C0x_DeInit(void);
void     I2C_EEPROM_24C0x_Init(void);
uint32_t sEE_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);
uint32_t sEE_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t NumByteToWrite);
void     sEE_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
uint32_t sEE_WaitEepromStandbyState(void);
void     I2C_EEPROM_24C0x_WriteAndRead(void);

// Function later added to write a structure

// For Tools Data
void I2C_EEPROM_24C0x_WriteStructTools(TOOLS * tool, uint16_t WriteAddr, uint16_t NumByteToWrite);
void I2C_EEPROM_24C0x_ReadStructTools(TOOLS * tool, uint16_t ReadAddr, uint16_t NumByteToRead);

// For Profile Data
void I2C_EEPROM_24C0x_WriteStructProfile(PROFILE * profile, uint16_t WriteAddr, uint16_t NumByteToWrite);
void I2C_EEPROM_24C0x_ReadStructProfile(PROFILE * profile, uint16_t ReadAddr, uint16_t NumByteToRead);

/* USER Callbacks: These are functions for which prototypes only are declared in
   EEPROM driver and that should be implemented into user application. */  
/* sEE_TIMEOUT_UserCallback() function is called whenever a timeout condition 
   occurs during communication (waiting on an event that doesn't occur, bus 
   errors, busy devices ...).
   You can use the default timeout callback implementation by uncommenting the 
   define USE_DEFAULT_TIMEOUT_CALLBACK in stm32072b_eval_i2c_ee.h file.
   Typically the user implementation of this callback should reset I2C peripheral
   and re-initialize communication or in worst case reset all the application. */
uint32_t sEE_TIMEOUT_UserCallback(void);

#ifdef __cplusplus
}
#endif

#endif /* __ISO_I2C_EE_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */

/**********************************END OF FILE********************************/

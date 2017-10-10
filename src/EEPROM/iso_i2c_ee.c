	/******************** (C) COPYRIGHT  风驰嵌入式开发工作室 ********************
 * 文件名  ：iso_i2c_ee.c
 * 描述    ：STM32F0-LED       
 * 实验平台：M0-ISO开发板
 * 库版本  ：V1.3.0
 * 作者    ：风驰 QQ:779814207/2366260464
 * 博客    ：
 * 淘宝    ：http://shop71177993.taobao.com/
 * 修改时间: 2014-12-15
**********************************************************************************/	
/**
  ******************************************************************************
  * @file    iso_i2c_ee.c 
  * @author  Fengchi  Technology Team
  * @version V1.3.0
  * @date    15-December-2014
  * @brief   led
  ******************************************************************************
  * @attention
  * I2C1_SCL<----->PB6
  * I2C1_SDA<----->PB7
  ******************************************************************************
	*/
/* Includes ------------------------------------------------------------------*/
#include "iso_i2c_ee.h"
#include "util_usart.h"

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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t  sEEAddress = 0;   
__IO uint32_t  sEETimeout = sEE_LONG_TIMEOUT;
__IO uint16_t  sEEDataNum;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @defgroup ISO_I2C_EE_Private_Functions
  * @{
  */ 

void I2C_EEPROM_24C0x_DeInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
   
  /* sEE_I2C Peripheral Disable */
  I2C_Cmd(sEE_I2C, DISABLE);
 
  /* sEE_I2C DeInit */
  I2C_DeInit(sEE_I2C);

  /* sEE_I2C Periph clock disable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, DISABLE);
    
  /* GPIO configuration */  
  /* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = I2C1_SCL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(sEE_I2C1_PORT, &GPIO_InitStructure);

  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = I2C1_SDA;
  GPIO_Init(sEE_I2C1_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  * @param  None
  * @retval None
  */
void I2C_EEPROM_24C0x_Init(void)
{ 
  I2C_InitTypeDef  I2C_InitStructure;
  
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	I2C_EEPROM_24C0x_DeInit();
  
  /* sEE_I2C_SCL_GPIO_CLK and sEE_I2C_SDA_GPIO_CLK Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  
  /* sEE_I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  
  /* Connect PXx to I2C_SCL*/
  GPIO_PinAFConfig(sEE_I2C1_PORT, GPIO_PinSource6, GPIO_AF_1);
  
  /* Connect PXx to I2C_SDA*/
  GPIO_PinAFConfig(sEE_I2C1_PORT, GPIO_PinSource7, GPIO_AF_1);
  
  /* GPIO configuration */  
  /* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = I2C1_SCL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(sEE_I2C1_PORT, &GPIO_InitStructure);
  
  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = I2C1_SDA;
  GPIO_Init(sEE_I2C1_PORT, &GPIO_InitStructure);
  
  /* I2C configuration */
  /* sEE_I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
  I2C_InitStructure.I2C_DigitalFilter = 0x00;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_Timing = sEE_I2C_TIMING;
  /* sEE_I2C Peripheral Enable */
  I2C_Cmd(I2C1, ENABLE);
  /* Apply sEE_I2C configuration after enabling it */
  I2C_Init(I2C1, &I2C_InitStructure);
  
  /* Select the EEPROM address */
  sEEAddress = sEE_HW_ADDRESS;      
}

/**
  * @brief  Reads a block of data from the EEPROM.
  * @param  pBuffer: pointer to the buffer that receives the data read from 
  *         the EEPROM.
  * @param  ReadAddr: EEPROM's internal address to start reading from.
  * @param  NumByteToRead: pointer to the variable holding number of bytes to 
  *         be read from the EEPROM.
  *
  * @retval sEE_OK (0) if operation is correctly performed, else return value 
  *         different from sEE_OK (0) or the timeout user callback.
  */
uint32_t sEE_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead)
{  
  uint32_t NumbOfSingle = 0, Count = 0, DataNum = 0, StartCom = 0;
  
  /* Get number of reload cycles */
  Count = NumByteToRead / 255;  
  NumbOfSingle = NumByteToRead % 255;
  
#if defined (sEE_M24C08) || defined (sEE_AT24C02) 
  
  /* Configure slave address, nbytes, reload and generate start */
  I2C_TransferHandling(sEE_I2C, sEEAddress, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
  
  /* Wait until TXIS flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
  }
  
  /* Send memory address */
  I2C_SendData(sEE_I2C, (uint8_t)ReadAddr);
  
#elif defined(sEE_M24M01) || defined(sEE_M24C64_32) || defined (sEE_M24LR64) 
  
  /* Configure slave address, nbytes, reload and generate start */
  I2C_TransferHandling(sEE_I2C, sEEAddress, 2, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
  
  /* Wait until TXIS flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
  }
  
  /* Send MSB of memory address */
  I2C_SendData(sEE_I2C, (uint8_t)((ReadAddr & 0xFF00) >> 8));
  
  /* Wait until TXIS flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;  
  while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
  }
  
  /* Send LSB of memory address  */
  I2C_SendData(sEE_I2C, (uint8_t)(ReadAddr & 0x00FF));
  
#endif /* sEE_M24C08 */ 
  
  /* Wait until TC flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_TC) == RESET)
  {
    if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
  }  
  
  /* If number of Reload cycles is not equal to 0 */
  if (Count != 0)
  {
    /* Starting communication */
    StartCom = 1;
    
    /* Wait until all reload cycles are performed */
    while( Count != 0)
    { 
      /* If a read transfer is performed */
      if (StartCom == 0)      
      {
        /* Wait until TCR flag is set */
        sEETimeout = sEE_LONG_TIMEOUT; 
        while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_TCR) == RESET)
        {
          if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
        }
      }      
      
      /* if remains one read cycle */
      if ((Count == 1) && (NumbOfSingle == 0))
      {
        /* if starting communication */
        if (StartCom != 0)
        {
          /* Configure slave address, end mode and start condition */
          I2C_TransferHandling(sEE_I2C, sEEAddress, 255, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
        }
        else
        {
          /* Configure slave address, end mode */
          I2C_TransferHandling(sEE_I2C, sEEAddress, 255, I2C_AutoEnd_Mode, I2C_No_StartStop);          
        }
      }
      else 
      {
        /* if starting communication */
        if (StartCom != 0)
        {
          /* Configure slave address, end mode and start condition */
          I2C_TransferHandling(sEE_I2C, sEEAddress, 255, I2C_Reload_Mode, I2C_Generate_Start_Read);
        }
        else
        {
          /* Configure slave address, end mode */
          I2C_TransferHandling(sEE_I2C, sEEAddress, 255, I2C_Reload_Mode, I2C_No_StartStop);          
        } 
      }
      
      /* Update local variable */
      StartCom = 0;      
      DataNum = 0;
      
      /* Wait until all data are received */
      while (DataNum != 255)
      {        
        /* Wait until RXNE flag is set */
        sEETimeout = sEE_LONG_TIMEOUT;
        while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_RXNE) == RESET)
        {
          if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
        }
        
        /* Read data from RXDR */
        pBuffer[DataNum]= I2C_ReceiveData(sEE_I2C);
        
        /* Update number of received data */
        DataNum++;
        NumByteToRead--;
      }      
      /* Update Pointer of received buffer */ 
      pBuffer += DataNum;  
      
      /* update number of reload cycle */
      Count--;
    }
    
    /* If number of single data is not equal to 0 */
    if (NumbOfSingle != 0)
    {            
      /* Wait until TCR flag is set */
      sEETimeout = sEE_LONG_TIMEOUT;   
      while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_TCR) == RESET)
      {
        if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
      }
      
      /* Update CR2 : set Nbytes and end mode */
      I2C_TransferHandling(sEE_I2C, sEEAddress, (uint8_t)(NumbOfSingle), I2C_AutoEnd_Mode, I2C_No_StartStop);
      
      /* Reset local variable */
      DataNum = 0;
      
      /* Wait until all data are received */
      while (DataNum != NumbOfSingle)
      {        
        /* Wait until RXNE flag is set */
        sEETimeout = sEE_LONG_TIMEOUT;
        while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_RXNE) == RESET)
        {
          if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
        }
        
        /* Read data from RXDR */
        pBuffer[DataNum]= I2C_ReceiveData(sEE_I2C);
        
        /* Update number of received data */
        DataNum++;
        NumByteToRead--;
      } 
    }
  }
  else
  {
    /* Update CR2 : set Slave Address , set read request, generate Start and set end mode */
    I2C_TransferHandling(sEE_I2C, sEEAddress, (uint32_t)(NumbOfSingle), I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
    
    /* Reset local variable */
    DataNum = 0;
    
    /* Wait until all data are received */
    while (DataNum != NumbOfSingle)
    {
      /* Wait until RXNE flag is set */
      sEETimeout = sEE_LONG_TIMEOUT; 
      while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_RXNE) == RESET)
      {
        if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
      }
      
      /* Read data from RXDR */
      pBuffer[DataNum]= I2C_ReceiveData(sEE_I2C);
      
      /* Update number of received data */
      DataNum++;
      NumByteToRead--;
    }    
  }  
  
  /* Wait until STOPF flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_STOPF) == RESET)
  {
    if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
  }
  
  /* Clear STOPF flag */
  I2C_ClearFlag(sEE_I2C, I2C_ICR_STOPCF);
  
  /* If all operations OK, return sEE_OK (0) */
  return sEE_OK;
}

/**
  * @brief  Writes more than one byte to the EEPROM with a single WRITE cycle.
  *
  * @note   The number of bytes (combined to write start address) must not 
  *         cross the EEPROM page boundary. This function can only write into
  *         the boundaries of an EEPROM page.
  * @note   This function doesn't check on boundaries condition (in this driver 
  *         the function sEE_WriteBuffer() which calls sEE_WritePage() is 
  *         responsible of checking on Page boundaries).
  * 
  * @param  pBuffer: pointer to the buffer containing the data to be written to 
  *         the EEPROM.
  * @param  WriteAddr: EEPROM's internal address to write to.
  * @param  NumByteToWrite: pointer to the variable holding number of bytes to 
  *         be written into the EEPROM.
  *
  * @retval sEE_OK (0) if operation is correctly performed, else return value 
  *         different from sEE_OK (0) or the timeout user callback.
  */
uint32_t sEE_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t NumByteToWrite)
{   
  uint32_t DataNum = 0;
  
#if defined (sEE_M24C08) || defined (sEE_AT24C02) 
  
  /* Configure slave address, nbytes, reload and generate start */
  I2C_TransferHandling(sEE_I2C, sEEAddress, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);
  
  /* Wait until TXIS flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;  
  while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
  }
  
  /* Send memory address */
  I2C_SendData(sEE_I2C, (uint8_t)WriteAddr);
  
#elif defined(sEE_M24M01) || defined(sEE_M24C64_32) || defined (sEE_M24LR64)
  
  /* Configure slave address, nbytes, reload and generate start */
  I2C_TransferHandling(sEE_I2C, sEEAddress, 2, I2C_Reload_Mode, I2C_Generate_Start_Write);
  
  /* Wait until TXIS flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
  }
  
  /* Send MSB of memory address */
  I2C_SendData(sEE_I2C, (uint8_t)((WriteAddr & 0xFF00) >> 8));  
  
  /* Wait until TXIS flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
  }
  
  /* Send LSB of memory address  */
  I2C_SendData(sEE_I2C, (uint8_t)(WriteAddr & 0x00FF));
  
#endif /* sEE_M24C08 */
  
  /* Wait until TCR flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_TCR) == RESET)
  {
    if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
  }
  
  /* Update CR2 : set Slave Address , set write request, generate Start and set end mode */
  I2C_TransferHandling(sEE_I2C, sEEAddress, (uint8_t)NumByteToWrite, I2C_AutoEnd_Mode, I2C_No_StartStop);
  
  while (DataNum != NumByteToWrite)
  {      
    /* Wait until TXIS flag is set */
    sEETimeout = sEE_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_TXIS) == RESET)
    {
      if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
    }  
    
    /* Write data to TXDR */
    I2C_SendData(sEE_I2C, (uint8_t)(pBuffer[DataNum]));
    
    /* Update number of transmitted data */
    DataNum++;   
  }  
  
  /* Wait until STOPF flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_STOPF) == RESET)
  {
    if((sEETimeout--) == 0) return sEE_TIMEOUT_UserCallback();
  }   
  
  /* Clear STOPF flag */
  I2C_ClearFlag(sEE_I2C, I2C_ICR_STOPCF);
  
  /* If all operations OK, return sEE_OK (0) */
  return sEE_OK;
}

/**
  * @brief  Writes buffer of data to the I2C EEPROM.
  * @param  pBuffer: pointer to the buffer  containing the data to be written 
  *         to the EEPROM.
  * @param  WriteAddr: EEPROM's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the EEPROM.
  * @retval None
  */
void sEE_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
  uint16_t NumOfPage = 0, NumOfSingle = 0, count = 0;
  uint16_t Addr = 0;
  
  Addr = WriteAddr % sEE_PAGESIZE;
  count = sEE_PAGESIZE - Addr;
  NumOfPage =  NumByteToWrite / sEE_PAGESIZE;
  NumOfSingle = NumByteToWrite % sEE_PAGESIZE;
  
  /* If WriteAddr is sEE_PAGESIZE aligned  */
  if(Addr == 0) 
  {
    /* If NumByteToWrite < sEE_PAGESIZE */
    if(NumOfPage == 0) 
    {
      /* Store the number of data to be written */
      sEEDataNum = NumOfSingle;
      /* Start writing data */
      sEE_WritePage(pBuffer, WriteAddr, sEEDataNum);
      sEE_WaitEepromStandbyState();
    }
    /* If NumByteToWrite > sEE_PAGESIZE */
    else  
    {
      while(NumOfPage--)
      {
        /* Store the number of data to be written */
        sEEDataNum = sEE_PAGESIZE;        
        sEE_WritePage(pBuffer, WriteAddr, sEEDataNum); 
        sEE_WaitEepromStandbyState();
        WriteAddr +=  sEE_PAGESIZE;
        pBuffer += sEE_PAGESIZE;
      }
      
      if(NumOfSingle!=0)
      {
        /* Store the number of data to be written */
        sEEDataNum = NumOfSingle;          
        sEE_WritePage(pBuffer, WriteAddr, sEEDataNum);
        sEE_WaitEepromStandbyState();
      }
    }
  }
  /* If WriteAddr is not sEE_PAGESIZE aligned  */
  else 
  {
    /* If NumByteToWrite < sEE_PAGESIZE */
    if(NumOfPage== 0) 
    {
      /* If the number of data to be written is more than the remaining space 
      in the current page: */
      if (NumByteToWrite > count)
      {
        /* Store the number of data to be written */
        sEEDataNum = count;        
        /* Write the data contained in same page */
        sEE_WritePage(pBuffer, WriteAddr, sEEDataNum);
        sEE_WaitEepromStandbyState();      
        
        /* Store the number of data to be written */
        sEEDataNum = (NumByteToWrite - count);          
        /* Write the remaining data in the following page */
        sEE_WritePage((uint8_t*)(pBuffer + count), (WriteAddr + count), sEEDataNum);
        sEE_WaitEepromStandbyState();        
      }      
      else      
      {
        /* Store the number of data to be written */
        sEEDataNum = NumOfSingle;         
        sEE_WritePage(pBuffer, WriteAddr, sEEDataNum);
        sEE_WaitEepromStandbyState();        
      }     
    }
    /* If NumByteToWrite > sEE_PAGESIZE */
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / sEE_PAGESIZE;
      NumOfSingle = NumByteToWrite % sEE_PAGESIZE;
      
      if(count != 0)
      {  
        /* Store the number of data to be written */
        sEEDataNum = count;         
        sEE_WritePage(pBuffer, WriteAddr, sEEDataNum);
        sEE_WaitEepromStandbyState();
        WriteAddr += count;
        pBuffer += count;
      } 
      
      while(NumOfPage--)
      {
        /* Store the number of data to be written */
        sEEDataNum = sEE_PAGESIZE;          
        sEE_WritePage(pBuffer, WriteAddr, sEEDataNum);
        sEETimeout = sEE_LONG_TIMEOUT;
        sEE_WaitEepromStandbyState();
        WriteAddr +=  sEE_PAGESIZE;
        pBuffer += sEE_PAGESIZE;  
      }
      if(NumOfSingle != 0)
      {
        /* Store the number of data to be written */
        sEEDataNum = NumOfSingle;           
        sEE_WritePage(pBuffer, WriteAddr, sEEDataNum); 
        sEE_WaitEepromStandbyState();
      }
    }
  }  
}

/**
  * @brief  Wait for EEPROM Standby state.
  * 
  * @note  This function allows to wait and check that EEPROM has finished the 
  *        last operation. It is mostly used after Write operation: after receiving
  *        the buffer to be written, the EEPROM may need additional time to actually
  *        perform the write operation. During this time, it doesn't answer to
  *        I2C packets addressed to it. Once the write operation is complete
  *        the EEPROM responds to its address.
  * 
  * @param  None
  *
  * @retval sEE_OK (0) if operation is correctly performed, else return value 
  *         different from sEE_OK (0) or the timeout user callback.
  */
uint32_t sEE_WaitEepromStandbyState(void)      
{
  __IO uint32_t sEETrials = 0;
  
  /* Keep looping till the slave acknowledge his address or maximum number 
  of trials is reached (this number is defined by sEE_MAX_TRIALS_NUMBER define
  in stm32373c_eval_i2c_ee.h file) */
  
  /* Configure CR2 register : set Slave Address and end mode */
  I2C_TransferHandling(sEE_I2C, sEEAddress, 0, I2C_AutoEnd_Mode, I2C_No_StartStop);  
  
  do
  { 
    /* Initialize sEETimeout */
    sEETimeout = sEE_FLAG_TIMEOUT;
    
    /* Clear NACKF */
    I2C_ClearFlag(sEE_I2C, I2C_ICR_NACKCF | I2C_ICR_STOPCF);
    
    /* Generate start */
    I2C_GenerateSTART(sEE_I2C, ENABLE);
    
    /* Wait until timeout elapsed */
    while (sEETimeout-- != 0); 
    
    /* Check if the maximum allowed number of trials has bee reached */
    if (sEETrials++ == sEE_MAX_TRIALS_NUMBER)
    {
      /* If the maximum number of trials has been reached, exit the function */
      return sEE_TIMEOUT_UserCallback();
    }
  }
  while(I2C_GetFlagStatus(sEE_I2C, I2C_ISR_NACKF) != RESET);
  
  /* Clear STOPF */
  I2C_ClearFlag(sEE_I2C, I2C_ICR_STOPCF);
  
  /* Return sEE_OK if device is ready */
  return sEE_OK;
}

#ifdef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval 0.
  */
uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* The following code allows I2C error recovery and return to normal communication
     if the error source doesn抰 still exist (ie. hardware issue..) */
  
  /* Reinitialize all resources */
	I2C_EEPROM_24C0x_DeInit();
  I2C_EEPROM_24C0x_Init();

  /* At this stage the I2C error should be recovered and device can communicate
     again (except if the error source still exist).
     User can implement mechanism (ex. test on max trial number) to manage situation
     when the I2C can't recover from current error. */
  
  return 0;
}
#endif /* USE_DEFAULT_TIMEOUT_CALLBACK */

/*-------------------------------------------------------------------------------------*/


void I2C_EEPROM_24C0x_WriteAndRead(void)
{
	uint8_t i;
	uint8_t Write_Buffer[] = "Thank you for choosing the M0-ISO STM32F0 development board\r\ http://shop71177993.taobao.com";
	uint8_t Read_Buffer[BufferSize];
	printf("\r\n This is the hardware I2C on AT24C02 read and write experiments \r\n");
	sEE_WriteBuffer(Write_Buffer,0x00,(uint16_t)BufferSize);
	printf("\r\n Write the data for AT24C02 \r\n :%s", Write_Buffer);
	sEE_ReadBuffer(Read_Buffer,0x00,(uint16_t)BufferSize);
	for (i = 0; i < BufferSize; i++)
	{
		if(Read_Buffer[i] != Write_Buffer[i])
		{
			printf(" %c", Read_Buffer[i]);
			printf("\r\n Error: EEPROM AT24C02 read and write data inconsistent ");
			return;
		}	
	}
	printf("\r\n EEPROM AT24C02 read and write test success \r\n");
	printf("\r\n The data read from AT24C02 is: %s \r\n\r\n", Read_Buffer);
	
}


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

/**
  * @}
  */  

/*****************************************END OF FILE******************************/

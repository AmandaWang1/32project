#ifndef _IIC_H
#define _IIC_H

#include "stm32f10x.h"

//EEPROM�豸��ַ��8λ��
#define EEPROM_ADDR    						0XA0

#define STM32_I2C_OWN_ADDR           		0X5F     


//IIC
#define EEPROM_I2C                  		I2C1
#define EEPROM_I2C_CLK                		RCC_APB1Periph_I2C1
#define EEPROM_I2C_APBxClkCmd         		RCC_APB1PeriphClockCmd
#define EEPROM_I2C_BAUDRATE           		400000                       

//IIC GPIO ���Ŷ���
#define EEPROM_I2C_SCL_GPIO_CLK         (RCC_APB2Periph_GPIOB)
#define EEPROM_I2C_SDA_GPIO_CLK         (RCC_APB2Periph_GPIOB)

#define EEPROM_I2C_GPIO_APBxClkCmd   		RCC_APB2PeriphClockCmd

#define EEPROM_I2C_SCL_GPIO_PORT        GPIOB
#define EEPROM_I2C_SCL_GPIO_PIN		      GPIO_Pin_6

#define EEPROM_I2C_SDA_GPIO_PORT        GPIOB
#define EEPROM_I2C_SDA_GPIO_PIN         GPIO_Pin_7

void I2C_EE_Config(void);
void EEPROM_Byte_Write(uint8_t addr,uint8_t data);
void EEPROM_Read(uint8_t addr,uint8_t *data,uint8_t numByteToRead);
void EEPROM_WaitForWriteEnd(void);
void EEPROM_Page_Write(uint8_t addr,uint8_t *data,uint8_t numByteToWrite);

#endif /*_IIC_H*/




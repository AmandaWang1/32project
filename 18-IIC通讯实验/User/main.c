#include "stm32f10x.h"
#include "usart.h"
#include "IIC.h"

uint8_t readData[10]={0};
uint8_t writeData[8]={1,2,3,4,5,6,7,8};
	
int main (void)
{
	uint8_t i=0;
	
	USART_Config();
	
	printf ("IIC通讯实验\n");
	
	//初始化IIC
	I2C_EE_Config();
	
	//写入一个字节
	EEPROM_Byte_Write(11,55);
	
	//等待写入操作完成
	EEPROM_WaitForWriteEnd();
	
	//写入一个字节
	EEPROM_Byte_Write(12,52);
	
	//等待写入操作完成
	EEPROM_WaitForWriteEnd();
	
	//addr%8 == 0,即为地址对齐
	EEPROM_Page_Write(0,writeData,8);//8个是最大值
	
	//读取数据
	EEPROM_Read(0,readData,8);
	
	for(i=0;i<10;i++)
	{	
		printf("%d ",readData[i]);
	}
	while(1)
	{
	}
}


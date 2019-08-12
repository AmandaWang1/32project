#include "stm32f10x.h"
#include "usart.h"
#include "IIC.h"

uint8_t readData[10]={0};
uint8_t writeData[8]={1,2,3,4,5,6,7,8};
	
int main (void)
{
	uint8_t i=0;
	
	USART_Config();
	
	printf ("IICͨѶʵ��\n");
	
	//��ʼ��IIC
	I2C_EE_Config();
	
	//д��һ���ֽ�
	EEPROM_Byte_Write(11,55);
	
	//�ȴ�д��������
	EEPROM_WaitForWriteEnd();
	
	//д��һ���ֽ�
	EEPROM_Byte_Write(12,52);
	
	//�ȴ�д��������
	EEPROM_WaitForWriteEnd();
	
	//addr%8 == 0,��Ϊ��ַ����
	EEPROM_Page_Write(0,writeData,8);//8�������ֵ
	
	//��ȡ����
	EEPROM_Read(0,readData,8);
	
	for(i=0;i<10;i++)
	{	
		printf("%d ",readData[i]);
	}
	while(1)
	{
	}
}


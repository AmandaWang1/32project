#include "stm32f10x.h"
#include "bsp_led.h"
#include "usart.h"
#include "ili9341_lcd.h"

extern int Read_Pixel_Format(void);

int main (void)
{
	ILI9341_Init();//Һ������ʼ��������ڴ��ڳ�ʼ��֮ǰ
	
	led();
	
	USART_Config();
	
	ILI9341_Draw_Rec();
	
//	uint32_t temp = 0x60000000;
//	uint16_t lcd_read_temp;
	
	
//	//��lcd��������
//	*ILI9341_CMD_ADDR = 0xABCD;//�൱�ڰ�0xABCD������䵱������͸���Һ����������Ϊ�͵�ƽ
//	
//	//��lcd��������
//	*ILI9341_DATA_ADDR = 0x1234;//����������д�뵽Һ������
//	
//	//��Һ������ȡ����
//	lcd_read_temp = *ILI9341_DATA_ADDR;//ʹNOE���Ų����͵�ƽ��NWE���Ų����ߵ�ƽ
//	
//	
//	
//	temp = temp | (1<<(16+1));
//	printf("A16Ϊ�ߵ�ƽ����ַ=0x%x",temp);
//	
//	temp &= ~(1<<(16+1));
//	printf("A16Ϊ�͵�ƽ����ַ0x%x",temp);	
	
	while(1);
}


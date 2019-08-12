#include "stm32f10x.h"
#include "bsp_led.h"
#include "usart.h"
#include "ili9341_lcd.h"

extern int Read_Pixel_Format(void);

int main (void)
{
	ILI9341_Init();//液晶屏初始化必须放在串口初始化之前
	
	led();
	
	USART_Config();
	
	ILI9341_Draw_Rec();
	
//	uint32_t temp = 0x60000000;
//	uint16_t lcd_read_temp;
	
	
//	//向lcd发送命令
//	*ILI9341_CMD_ADDR = 0xABCD;//相当于把0xABCD这条语句当成命令发送给了液晶屏，引脚为低电平
//	
//	//向lcd发送数据
//	*ILI9341_DATA_ADDR = 0x1234;//会把这个参数写入到液晶屏中
//	
//	//从液晶屏读取数据
//	lcd_read_temp = *ILI9341_DATA_ADDR;//使NOE引脚产生低电平，NWE引脚产生高电平
//	
//	
//	
//	temp = temp | (1<<(16+1));
//	printf("A16为高电平，地址=0x%x",temp);
//	
//	temp &= ~(1<<(16+1));
//	printf("A16为低电平，地址0x%x",temp);	
	
	while(1);
}


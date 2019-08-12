
#include "stm32f10x.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./usart/bsp_usart.h" 
#include <stdio.h>

static void LCD_Test(void);	
static void Delay ( __IO uint32_t nCount );
void Printf_Charater(void)   ;


/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
	
	
	
	
int main ( void )
{

	ILI9341_Init ();         //LCD 初始化

	USART_Config();		
	
	printf("\r\n ********** 液晶屏英文显示程序*********** \r\n"); 
	printf("\r\n 本程序不支持中文，显示中文的程序请学习下一章 \r\n"); 
	
 //其中0、3、5、6 模式适合从左至右显示文字，
 //不推荐使用其它模式显示文字	其它模式显示文字会有镜像效果			
 //其中 6 模式为大部分液晶例程的默认显示方向  
  ILI9341_GramScan ( 6 );
	
	while ( 1 )
	{
		LCD_Test();
	}
}

void LCD_Test(void)
{
	
		LCD_SetFont(&Font8x16);//设置字体大小（8*16）
	LCD_SetColors(RED,BLACK);//设置字体颜色，红色为前景色，黑色为背景色
	
	ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* 清屏，显示全黑 */
	  ILI9341_DispStringLine_EN(LINE(0),"HPU MIDD");
	
	LCD_SetFont(&Font16x24);//(16X24)
	LCD_SetColors(BLUE,BLACK);
	ILI9341_DispStringLine_EN(LINE(1),"HPU MIDD");
	
		LCD_SetFont(&Font24x32);//(24X32)
	LCD_SetColors(GREEN,BLACK);
	ILI9341_DispStringLine_EN(LINE(2),"HPU MIDD");
	
	  Delay(0xFFFFFFFFFF);
	ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* 清屏，显示全黑 */
	
}


/*用于测试各种液晶的函数*/
//void LCD_Test(void)
//{
//	/*演示显示变量*/
//	static uint8_t testCNT = 0;	
//	char dispBuff[100];
//	
//	testCNT++;	
//	
//	LCD_SetFont(&Font8x16);//设置字体大小（8*16）
//	LCD_SetColors(RED,BLACK);//设置字体颜色，红色为前景色，黑色为背景色

//  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* 清屏，显示全黑 */
//	/********显示字符串示例*******/
//  ILI9341_DispStringLine_EN(LINE(0),"HPU MIDD");
////  ILI9341_DispStringLine_EN(LINE(1),"let us start");
////  ILI9341_DispStringLine_EN(LINE(2)," ");
////  ILI9341_DispStringLine_EN(LINE(3),"");
//  
//	/********显示变量示例*******/
//	LCD_SetFont(&Font16x24);//演示16X24的字体
//	LCD_SetTextColor(GREEN);//把字体改为绿色
//	
//	/*使用c标准库把变量转化成字符串*/
//	//sprintf(dispBuff,"count : %d ",testCNT);
//  LCD_ClearLine(LINE(4));	/* 清除单行文字 */
//	
//	/*然后显示该字符串即可，其它变量也是这样处理*/
////	ILI9341_DispStringLine_EN(LINE(4),dispBuff);

//	/*******显示图形示例******/
//	LCD_SetFont(&Font24x32);//演示24X32的字体
//  /* 画直线 */
//  
//  LCD_ClearLine(LINE(4));/* 清除单行文字 */
//	LCD_SetTextColor(BLUE);

//  ILI9341_DispStringLine_EN(LINE(4),"HPU MIDD");
//  
////	LCD_SetTextColor(RED);
////  ILI9341_DrawLine(50,170,210,230);  
////  ILI9341_DrawLine(50,200,210,240);
////  
////	LCD_SetTextColor(GREEN);
////  ILI9341_DrawLine(100,170,200,230);  
////  ILI9341_DrawLine(200,200,220,240);
////	
////	LCD_SetTextColor(BLUE);
////  ILI9341_DrawLine(110,170,110,230);  
////  ILI9341_DrawLine(130,200,220,240);
//  
////  Delay(0xFFFFFF);
//  
//  ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* 清屏，显示全黑 */
//  
//  
//  /*画矩形*/

//  LCD_ClearLine(LINE(4));	/* 清除单行文字 */
//	LCD_SetTextColor(BLUE);

//  ILI9341_DispStringLine_EN(LINE(4),"HPU MIDD");

////	LCD_SetTextColor(RED);
////  ILI9341_DrawRectangle(50,200,100,30,1);
////	
////	LCD_SetTextColor(GREEN);
////  ILI9341_DrawRectangle(160,200,20,40,0);
////	
////	LCD_SetTextColor(BLUE);
////  ILI9341_DrawRectangle(170,200,50,20,1);
//  
//  
//  Delay(0xFFFFFF);
//	
//	ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* 清屏，显示全黑 */

////  /* 画圆 */
////  LCD_ClearLine(LINE(4));	/* 清除单行文字 */
////	LCD_SetTextColor(BLUE);
////	
////  ILI9341_DispStringLine_EN(LINE(4),"Draw Cir:");

////	LCD_SetTextColor(RED);
////  ILI9341_DrawCircle(100,200,20,0);
////	
////	LCD_SetTextColor(GREEN);
////  ILI9341_DrawCircle(100,200,10,1);
////	
////	LCD_SetTextColor(BLUE);
////	ILI9341_DrawCircle(140,200,20,0);

////  Delay(0xFFFFFF);
////  
////  ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* 清屏，显示全黑 */

//}


/**
  * @brief  简单延时函数
  * @param  nCount ：延时计数值
  * @retval 无
  */	
static void Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}

/* ------------------------------------------end of file---------------------------------------- */


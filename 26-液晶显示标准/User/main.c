
#include "stm32f10x.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./usart/bsp_usart.h" 
#include <stdio.h>

static void LCD_Test(void);	
static void Delay ( __IO uint32_t nCount );
void Printf_Charater(void)   ;


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
	
	
	
	
int main ( void )
{

	ILI9341_Init ();         //LCD ��ʼ��

	USART_Config();		
	
	printf("\r\n ********** Һ����Ӣ����ʾ����*********** \r\n"); 
	printf("\r\n ������֧�����ģ���ʾ���ĵĳ�����ѧϰ��һ�� \r\n"); 
	
 //����0��3��5��6 ģʽ�ʺϴ���������ʾ���֣�
 //���Ƽ�ʹ������ģʽ��ʾ����	����ģʽ��ʾ���ֻ��о���Ч��			
 //���� 6 ģʽΪ�󲿷�Һ�����̵�Ĭ����ʾ����  
  ILI9341_GramScan ( 6 );
	
	while ( 1 )
	{
		LCD_Test();
	}
}

void LCD_Test(void)
{
	
		LCD_SetFont(&Font8x16);//���������С��8*16��
	LCD_SetColors(RED,BLACK);//����������ɫ����ɫΪǰ��ɫ����ɫΪ����ɫ
	
	ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */
	  ILI9341_DispStringLine_EN(LINE(0),"HPU MIDD");
	
	LCD_SetFont(&Font16x24);//(16X24)
	LCD_SetColors(BLUE,BLACK);
	ILI9341_DispStringLine_EN(LINE(1),"HPU MIDD");
	
		LCD_SetFont(&Font24x32);//(24X32)
	LCD_SetColors(GREEN,BLACK);
	ILI9341_DispStringLine_EN(LINE(2),"HPU MIDD");
	
	  Delay(0xFFFFFFFFFF);
	ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* ��������ʾȫ�� */
	
}


/*���ڲ��Ը���Һ���ĺ���*/
//void LCD_Test(void)
//{
//	/*��ʾ��ʾ����*/
//	static uint8_t testCNT = 0;	
//	char dispBuff[100];
//	
//	testCNT++;	
//	
//	LCD_SetFont(&Font8x16);//���������С��8*16��
//	LCD_SetColors(RED,BLACK);//����������ɫ����ɫΪǰ��ɫ����ɫΪ����ɫ

//  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */
//	/********��ʾ�ַ���ʾ��*******/
//  ILI9341_DispStringLine_EN(LINE(0),"HPU MIDD");
////  ILI9341_DispStringLine_EN(LINE(1),"let us start");
////  ILI9341_DispStringLine_EN(LINE(2)," ");
////  ILI9341_DispStringLine_EN(LINE(3),"");
//  
//	/********��ʾ����ʾ��*******/
//	LCD_SetFont(&Font16x24);//��ʾ16X24������
//	LCD_SetTextColor(GREEN);//�������Ϊ��ɫ
//	
//	/*ʹ��c��׼��ѱ���ת�����ַ���*/
//	//sprintf(dispBuff,"count : %d ",testCNT);
//  LCD_ClearLine(LINE(4));	/* ����������� */
//	
//	/*Ȼ����ʾ���ַ������ɣ���������Ҳ����������*/
////	ILI9341_DispStringLine_EN(LINE(4),dispBuff);

//	/*******��ʾͼ��ʾ��******/
//	LCD_SetFont(&Font24x32);//��ʾ24X32������
//  /* ��ֱ�� */
//  
//  LCD_ClearLine(LINE(4));/* ����������� */
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
//  ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* ��������ʾȫ�� */
//  
//  
//  /*������*/

//  LCD_ClearLine(LINE(4));	/* ����������� */
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
//	ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* ��������ʾȫ�� */

////  /* ��Բ */
////  LCD_ClearLine(LINE(4));	/* ����������� */
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
////  ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* ��������ʾȫ�� */

//}


/**
  * @brief  ����ʱ����
  * @param  nCount ����ʱ����ֵ
  * @retval ��
  */	
static void Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}

/* ------------------------------------------end of file---------------------------------------- */


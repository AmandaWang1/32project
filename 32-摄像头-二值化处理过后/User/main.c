/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����ͷ����ov7725��������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */  
#include "stm32f10x.h"
#include "./ov7725/bsp_ov7725.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./led/bsp_led.h"   
#include "./usart/bsp_usart.h"
#include "./key/bsp_key.h"  
#include "./systick/systick.h"
#include "./CV/cv.h"



extern uint16_t Ov7725_vsync;
extern OV7725_MODE_PARAM cam_mode;

uint16_t Camera_Data[CAM_WIDTH][CAM_HEIGHT]={0,};
/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void) 	
{		
	
	float frame_count = 0;
	uint32_t n=0;
	
	/*Һ������ʼ��*/
	cv_tft_init();
	
	/*���ڳ�ʼ��*/
	USART_Config();
	
	/*��ʱ����ʼ��*/
//	SysTick_Init();
	
	/* ov7725 ��ʼ�� */
	cv_cam_init();
	
	/*֡ͬ���źű�־*/	
	Ov7725_vsync = 0;
	
	while(1)
	{
		/*���յ���ͼ�������ʾ*/
		printf("\r\n���յ���ͼ�������ʾ%d\r\n",n++);
		
		if( Ov7725_vsync == 2 )//fifo�Ѿ��������µ�ͼ��
		{
			frame_count++;  /*ͼ��֡��*/
			
			cv_imread();		/*ͼ���ȡ*/
			
			cv_cv();				/*ͼ����*/
			
			cv_imshow_normal();
						
//			ILI9341_GramScan ( 3 ); 
			
			
		/*��ȡ��һ֡ͼ������°�Ov7725_vsync���ó�0 �ȴ�һ���µ�VSYNC�ź�*/
			Ov7725_vsync = 0;		
		}
	}
}




/*********************************************END OF FILE**********************/


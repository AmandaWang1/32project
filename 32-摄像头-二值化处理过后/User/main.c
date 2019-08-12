/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   摄像头火眼ov7725测试例程
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
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
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void) 	
{		
	
	float frame_count = 0;
	uint32_t n=0;
	
	/*液晶屏初始化*/
	cv_tft_init();
	
	/*串口初始化*/
	USART_Config();
	
	/*定时器初始化*/
//	SysTick_Init();
	
	/* ov7725 初始化 */
	cv_cam_init();
	
	/*帧同步信号标志*/	
	Ov7725_vsync = 0;
	
	while(1)
	{
		/*接收到新图像进行显示*/
		printf("\r\n接收到新图像进行显示%d\r\n",n++);
		
		if( Ov7725_vsync == 2 )//fifo已经缓存了新的图像，
		{
			frame_count++;  /*图像帧数*/
			
			cv_imread();		/*图像读取*/
			
			cv_cv();				/*图像处理*/
			
			cv_imshow_normal();
						
//			ILI9341_GramScan ( 3 ); 
			
			
		/*读取完一帧图像后，重新把Ov7725_vsync配置成0 等待一个新的VSYNC信号*/
			Ov7725_vsync = 0;		
		}
	}
}




/*********************************************END OF FILE**********************/


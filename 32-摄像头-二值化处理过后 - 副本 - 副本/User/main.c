/**
  ******************************************************************************
  * @file    main.c
  * @author  王晨
  * @version V1.0
  * @date    2019_7_X
  * @brief   摄像头循迹程序
  ******************************************************************************
  * @attention
  *
  * 实验平台:尼莫m3s开发板，野火火眼ov7725摄像头，野火3.2寸液晶屏
	*
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
		if( Ov7725_vsync == 2 )//fifo已经缓存了新的图像，
		{
			frame_count++;  /*图像帧数*/
			
			cv_imread();		/*图像读取*/
			
			cv_cv();				/*图像处理*/
			
			cv_imshow_normal();/*图像显示*/			
			
		/*读取完一帧图像后，重新把Ov7725_vsync配置成0 等待一个新的VSYNC信号*/
			Ov7725_vsync = 0;		
		}
	}
}




/*********************************************END OF FILE**********************/


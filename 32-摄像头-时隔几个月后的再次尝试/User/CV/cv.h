#ifndef __CV_H
#define __CV_H 
	   
#include "stm32f10x.h"
#include "./ov7725/bsp_ov7725.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./led/bsp_led.h"   
#include "./usart/bsp_usart.h"
#include "./key/bsp_key.h"  
#include <math.h>
#include <stdio.h>
#include "./ov7725/bsp_ov7725.h"

  
#define CAM_WIDTH  180 
#define CAM_HEIGHT 160

extern uint16_t Ov7725_vsync;
extern uint16_t Camera_Data[CAM_WIDTH][CAM_HEIGHT];
//extern uint16_t Camera_Data[80][10];

#define GRAY_BREAK_RANGE      1    //阈值允许参数


#define GRAY_TO_RGB(MUX)         ((MUX>>3<<11)|(MUX>>2<<5)|(MUX>>3))

//获取颜色的字节值
#define GETR_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )RGB565) >>11)<<3))		  			//返回8位 R
#define GETG_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x7ff)) >>5)<<2)) 	//返回8位 G
#define GETB_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x1f))<<3)))       	//返回8位 B
 
#define GETGRAY_FROM_RGB16(R,G,B)  ((unsigned char)((R<<5+G<<8+B<<3)>>7))


void cv_cam_init(void);
void cv_tft_init(void);
void cv_imread(void);
void cv_imshow_normal(void);
void cv_imshow_binarization(void);
void cv_cv(void);
uint8_t xunxian1(void);


#endif /*__CV_H */

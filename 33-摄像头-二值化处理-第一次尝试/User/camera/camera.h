#ifndef __CAMERA_H
#define __CAMERA_H 
	   

#include "stm32f10x.h"
#include "bsp_ili9341_lcd.h"
#include "bsp_usart.h"
#include "bsp_ov7725.h"
#include <math.h>
#include <stdio.h>
 

#define GRAY_TEST


#define GRAY_TO_RGB(MUX)         ((MUX>>3<<11)|(MUX>>2<<5)|(MUX>>3))
//获取颜色的字节值
#define GETR_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )RGB565) >>11)<<3))		  			//返回8位 R
#define GETG_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x7ff)) >>5)<<2)) 	//返回8位 G
#define GETB_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x1f))<<3)))       	//返回8位 B
 
//#define GETGRAY_FROM_RGB16(RGB565)  ((unsigned char)( (((RGB565>>11)<<8)+((RGB565&0x7FF)<<5)+((RGB565&0x1F)<<7))>>7 ))
#define GETGRAY_FROM_RGB16(R,G,B)  ((unsigned char)((R<<5+G<<8+B<<3)>>7))

void ImagDisp_T(void);
void Itera_Threshold(void);

#endif 




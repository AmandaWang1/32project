#include "camera.h"

#define PIXEL_W      180
#define PIXEL_H      320


//灰度直方图数值，用来判断按图像质量
u32 gray_test_value[26];   //像素点数数据
u8 gray_test_send[28];     //发送给上位机的数据


//阈值分割灰度图
u8 gray_itera_threshold[256];
u16 threshold_h[256];
#define GRAY_BREAK_RANGE     1    //阈值允许参数


static u8 pixel[PIXEL_H][PIXEL_W];



 void ImagDisp_T(void)
{
	uint16_t i=0, j=0;
	uint16_t Camera_Data;
	uint16_t R,G,B,mux;
 
  ILI9341_GramScan ( 3 );

	for(i = 0; i<PIXEL_H; i++)
	{
		for(j = 0; j<PIXEL_W; j++)
		{
		 //转换成灰度图	
      READ_FIFO_PIXEL(Camera_Data);		/* 从FIFO读出一个rgb565像素到Camera_Data变量 */      
			R = (uint16_t)GETR_FROM_RGB16(Camera_Data);
			G = (uint16_t)GETG_FROM_RGB16(Camera_Data);
			B = (uint16_t)GETB_FROM_RGB16(Camera_Data);
			mux = (R*30+G*59+B*11)/100;         //读取到的灰度值
      
			pixel[i][j] = mux;         //把读取到的灰度值放到320*240的
			
		}

	}
}


/*迭代阈值法，能够找到灰度图的最佳二值化点*/

void Itera_Threshold(void)
{
  u16 i=0,j=0,k=0,cnt=0,mux=0,Camera_Data=0;
	u8 newthreshold=0;
	u16 Pmax=0,Pmin=0;
	u32 sum_h1=0,sum_h2=0;
	
	
	//数据清空
	for( i=0; i<256; i++ )
	{
	  gray_test_value[i] = 0;
	}
	
	//扫描
	for( i=0; i<PIXEL_H; i++ )
	{
	  for( j=0; j<PIXEL_W; j++ )
		{
		  mux = pixel[i][j];//获取灰度图的数据	
			
			//像素点数自增     
			gray_itera_threshold[mux]++;	
		}
	}
	
	Pmin = gray_itera_threshold[0];
	Pmax = gray_itera_threshold[0];
	for( cnt=0; cnt<256; cnt++ )  //256个像素点
	{
      if( Pmin>gray_itera_threshold[cnt] )
      {
        Pmin = gray_itera_threshold[cnt];
      }
      if( Pmax<gray_itera_threshold[cnt] )
      {
        Pmax = gray_itera_threshold[cnt];
      }
	}
	
	printf("the Pmax is %d\r \n",Pmax);
	printf("the Pmin is %d \r\n",Pmin);
	
	//初始阈值
	threshold_h[0] = ( Pmax + Pmin ) / 2;
	
	//寻找最佳阈值
	for( k=0; k<256; k++ )
	{
		
		//分割前景和背景
		for( cnt=0; cnt<threshold_h[k]; cnt++ )
		{
			sum_h1 += gray_itera_threshold[cnt];
		}
		for( cnt=threshold_h[k]; cnt<256; cnt++ )
		{
			sum_h2 += gray_itera_threshold[cnt];
		}
		sum_h1 /= threshold_h[k];
		sum_h2 /= (256-threshold_h[k]);
		
		//计算出新的阈值
		threshold_h[k+1] = ( sum_h1 + sum_h2 ) / 2; 
		
		if( fabs(threshold_h[k]-threshold_h[k+1]) <= GRAY_BREAK_RANGE )
    {
			newthreshold = threshold_h[k+1];
		  break;
		}
		
		sum_h1 = 0;
		sum_h2 = 0;
	}

	printf("新阈值是 %d\r\n",newthreshold);
	
	//准备写入数据

	//根据最佳阈值将图像二值化
  ILI9341_GramScan ( 3 );   
	
	
	for( i=0; i<PIXEL_H; i++ )
	{
	  for( j=0; j<PIXEL_W; j++ )
		{
		  mux = pixel[i][j];                     //获取灰度图的数据
			
		  //图像二值化
			if( mux > newthreshold )
      {
			  mux = 255;
			}
			else
      {
				mux = 0;
			}
			
			//printf("%d",mux);
			Camera_Data =  GRAY_TO_RGB(mux);
      ILI9341_Write_Data(Camera_Data);
			
		}
	}

}



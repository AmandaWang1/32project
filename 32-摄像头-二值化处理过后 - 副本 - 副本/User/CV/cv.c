#include "./CV/cv.h"

extern OV7725_MODE_PARAM cam_mode;
uint16_t mux=0;	
uint16_t newthreshold = 0;

//转化为灰度图
static void cv_gray(void)
{
	uint16_t R=0,G=0,B=0;
	uint16_t Data = 0;
	
	for(int i = 0; i<cam_mode.cam_width; i++)
	{
		for(int j = 0; j<cam_mode.cam_height; j++)
		{
		 //转换成灰度图	
      Data = Camera_Data[i][j];		    /* 从FIFO读出一个rgb565像素到Camera_Data变量 */      
			R = (uint16_t)GETR_FROM_RGB16(Data);
			G = (uint16_t)GETG_FROM_RGB16(Data);
			B = (uint16_t)GETB_FROM_RGB16(Data);
			Camera_Data[i][j] = (R*30+G*59+B*11)/100;         //读取到的灰度值//把读取到的灰度值放到数组		         
		}
	}
}



//二值化处理
static void cv_binarization(void)
{
  uint16_t cnt=0;
	uint16_t Pmax=0,Pmin=0;
	uint16_t sum_h1=0,sum_h2=0;
//	uint16_t num = 0;
	//阈值分割灰度图
	uint16_t gray_itera_threshold[256]={188,};
	uint16_t threshold_h[256]={0,};
	
	gray_itera_threshold[4]=23;
	
	//扫描
//	for( i=0; i<cam_mode.cam_width; i++ )
//	{
//	  for( j=0; j<cam_mode.cam_height; j++ )
//		{
////			num = Camera_Data[i][j];
////			gray_itera_threshold[num] +=1;	//获取灰度图的数据//像素点数自增 
////			printf("num=%d\n",num);
//		}
//	}
	
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
	
//	printf("the Pmax is %d\r \n",Pmax);
//	printf("the Pmin is %d \r\n",Pmin);
	
	//初始阈值
	newthreshold = threshold_h[0] = ( Pmax + Pmin ) / 2;
	
	//寻找最佳阈值
	for( int k=0; k<256; k++ )
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

//	printf("新阈值是 %d\r\n",newthreshold);
	
	
	//获取灰度图的数据//图像二值化
	for(int i=0;i<CAM_WIDTH;i++)
		for(int j =0;j<CAM_HEIGHT;j++)
	
			if( Camera_Data[i][j]> newthreshold )
				Camera_Data[i][j] = 65535;
			else
				Camera_Data[i][j] = 0;
}

	//摄像头初始化
void cv_cam_init(void)
{
	uint8_t retry = 0;
	
	OV7725_GPIO_Config();
	
	/* ov7725 寄存器默认配置初始化 */
	while(OV7725_Init() != SUCCESS)
	{
		retry++;
		if(retry>5)
		{
		//	printf("\r\n没有检测到OV7725摄像头\r\n");
			ILI9341_DispStringLine_EN(LINE(2),"No OV7725 module detected!");
			while(1);
		}
	}
	
	/*根据摄像头参数组配置模式*/
	OV7725_Special_Effect(cam_mode.effect);
	/*光照模式*/
	OV7725_Light_Mode(cam_mode.light_mode);
	/*饱和度*/
	OV7725_Color_Saturation(cam_mode.saturation);
	/*光照度*/
	OV7725_Brightness(cam_mode.brightness);
	/*对比度*/
	OV7725_Contrast(cam_mode.contrast);
	/*特殊效果*/
	OV7725_Special_Effect(cam_mode.effect);
	
	/*设置图像采样及模式大小*/
	OV7725_Window_Set(cam_mode.cam_sx,
										cam_mode.cam_sy,
										cam_mode.cam_width,
										cam_mode.cam_height,
										cam_mode.QVGA_VGA);
	
}

//屏初始化
void cv_tft_init(void)
{
	ILI9341_Init();
	ILI9341_GramScan ( 3 );
	
	LCD_SetFont(&Font8x16);
	LCD_SetColors(RED,BLACK);

	ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* 清屏，显示全黑 */
	
	ILI9341_DispStringLine_EN(LINE(0),"         Fighting!    ^-^");
	
	/* 设置液晶扫描模式 */
	ILI9341_GramScan( cam_mode.lcd_scan );
	
}


//图像读取
void cv_imread(void)
{
	
//	printf("\r\nFIFO准备开始\r\n");
	FIFO_PREPARE;  			/*FIFO准备*/	
//	printf("\r\nFIFO准备完毕\r\n");
	
	ImagDisp(cam_mode.lcd_sx,
					 cam_mode.lcd_sy,
					 cam_mode.cam_width,
					 cam_mode.cam_height);		
}

//图像显示
void cv_imshow_normal(void)
{
	for(int i = 0; i < cam_mode.cam_width; i++)
		{
			for(int j = 0; j < cam_mode.cam_height; j++)
			{
				ILI9341_Write_Data(Camera_Data[i][j]);			
			}
		}
}



//循单线
void cv_drawline(void)
{
	uint16_t i=0,j=0;
	uint16_t a=0,b=0;
	
	for( i = 80; i < (cam_mode.cam_width-80) ; i++ ) //共计20个点
		{
			for( j = 0; j < cam_mode.cam_height; j++ )
			{
				if( Camera_Data[i][j] != Camera_Data[i][j+1] && Camera_Data[i][j+1] == Camera_Data[i][j+2] && Camera_Data[i][j+2] == Camera_Data[i][j+3]  )
				{
					if( Camera_Data[i][j] == 0 && Camera_Data[i][j+1] == 65535 )
					{
						Camera_Data[i][j] = 255;
						a+=0;
					}
					if( Camera_Data[i][j] == 65535 && Camera_Data[i][j+1] == 0 )
					{
						Camera_Data[i][j] = 255;
						a+=i;
					}
					while(1)
					{
						j=j+1;
						if( Camera_Data[i][j] == 65535 && j<cam_mode.cam_height )
						{
							b+=( cam_mode.cam_height - j );
							break;
						}
						if( j == cam_mode.cam_height )
						{
							b+=0;
							break;
						}		
					}
				}	
			}	
		}
		
	printf("距离左边%d\n",a/20);	
	printf("距离右边%d\n\n",b/20);					
}



//图像处理
void cv_cv(void)
{
	cv_gray();
	cv_binarization();//二值化处理
	cv_drawline();
}

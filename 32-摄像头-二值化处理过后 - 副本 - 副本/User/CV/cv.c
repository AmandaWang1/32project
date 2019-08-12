#include "./CV/cv.h"

extern OV7725_MODE_PARAM cam_mode;
uint16_t mux=0;	
uint16_t newthreshold = 0;

//ת��Ϊ�Ҷ�ͼ
static void cv_gray(void)
{
	uint16_t R=0,G=0,B=0;
	uint16_t Data = 0;
	
	for(int i = 0; i<cam_mode.cam_width; i++)
	{
		for(int j = 0; j<cam_mode.cam_height; j++)
		{
		 //ת���ɻҶ�ͼ	
      Data = Camera_Data[i][j];		    /* ��FIFO����һ��rgb565���ص�Camera_Data���� */      
			R = (uint16_t)GETR_FROM_RGB16(Data);
			G = (uint16_t)GETG_FROM_RGB16(Data);
			B = (uint16_t)GETB_FROM_RGB16(Data);
			Camera_Data[i][j] = (R*30+G*59+B*11)/100;         //��ȡ���ĻҶ�ֵ//�Ѷ�ȡ���ĻҶ�ֵ�ŵ�����		         
		}
	}
}



//��ֵ������
static void cv_binarization(void)
{
  uint16_t cnt=0;
	uint16_t Pmax=0,Pmin=0;
	uint16_t sum_h1=0,sum_h2=0;
//	uint16_t num = 0;
	//��ֵ�ָ�Ҷ�ͼ
	uint16_t gray_itera_threshold[256]={188,};
	uint16_t threshold_h[256]={0,};
	
	gray_itera_threshold[4]=23;
	
	//ɨ��
//	for( i=0; i<cam_mode.cam_width; i++ )
//	{
//	  for( j=0; j<cam_mode.cam_height; j++ )
//		{
////			num = Camera_Data[i][j];
////			gray_itera_threshold[num] +=1;	//��ȡ�Ҷ�ͼ������//���ص������� 
////			printf("num=%d\n",num);
//		}
//	}
	
	Pmin = gray_itera_threshold[0];
	Pmax = gray_itera_threshold[0];
	for( cnt=0; cnt<256; cnt++ )  //256�����ص�
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
	
	//��ʼ��ֵ
	newthreshold = threshold_h[0] = ( Pmax + Pmin ) / 2;
	
	//Ѱ�������ֵ
	for( int k=0; k<256; k++ )
	{
		//�ָ�ǰ���ͱ���
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
		
		//������µ���ֵ
		threshold_h[k+1] = ( sum_h1 + sum_h2 ) / 2; 
		
		if( fabs(threshold_h[k]-threshold_h[k+1]) <= GRAY_BREAK_RANGE )
    {
			newthreshold = threshold_h[k+1];
		  break;
		}
		
		sum_h1 = 0;
		sum_h2 = 0;
	}

//	printf("����ֵ�� %d\r\n",newthreshold);
	
	
	//��ȡ�Ҷ�ͼ������//ͼ���ֵ��
	for(int i=0;i<CAM_WIDTH;i++)
		for(int j =0;j<CAM_HEIGHT;j++)
	
			if( Camera_Data[i][j]> newthreshold )
				Camera_Data[i][j] = 65535;
			else
				Camera_Data[i][j] = 0;
}

	//����ͷ��ʼ��
void cv_cam_init(void)
{
	uint8_t retry = 0;
	
	OV7725_GPIO_Config();
	
	/* ov7725 �Ĵ���Ĭ�����ó�ʼ�� */
	while(OV7725_Init() != SUCCESS)
	{
		retry++;
		if(retry>5)
		{
		//	printf("\r\nû�м�⵽OV7725����ͷ\r\n");
			ILI9341_DispStringLine_EN(LINE(2),"No OV7725 module detected!");
			while(1);
		}
	}
	
	/*��������ͷ����������ģʽ*/
	OV7725_Special_Effect(cam_mode.effect);
	/*����ģʽ*/
	OV7725_Light_Mode(cam_mode.light_mode);
	/*���Ͷ�*/
	OV7725_Color_Saturation(cam_mode.saturation);
	/*���ն�*/
	OV7725_Brightness(cam_mode.brightness);
	/*�Աȶ�*/
	OV7725_Contrast(cam_mode.contrast);
	/*����Ч��*/
	OV7725_Special_Effect(cam_mode.effect);
	
	/*����ͼ�������ģʽ��С*/
	OV7725_Window_Set(cam_mode.cam_sx,
										cam_mode.cam_sy,
										cam_mode.cam_width,
										cam_mode.cam_height,
										cam_mode.QVGA_VGA);
	
}

//����ʼ��
void cv_tft_init(void)
{
	ILI9341_Init();
	ILI9341_GramScan ( 3 );
	
	LCD_SetFont(&Font8x16);
	LCD_SetColors(RED,BLACK);

	ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */
	
	ILI9341_DispStringLine_EN(LINE(0),"         Fighting!    ^-^");
	
	/* ����Һ��ɨ��ģʽ */
	ILI9341_GramScan( cam_mode.lcd_scan );
	
}


//ͼ���ȡ
void cv_imread(void)
{
	
//	printf("\r\nFIFO׼����ʼ\r\n");
	FIFO_PREPARE;  			/*FIFO׼��*/	
//	printf("\r\nFIFO׼�����\r\n");
	
	ImagDisp(cam_mode.lcd_sx,
					 cam_mode.lcd_sy,
					 cam_mode.cam_width,
					 cam_mode.cam_height);		
}

//ͼ����ʾ
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



//ѭ����
void cv_drawline(void)
{
	uint16_t i=0,j=0;
	uint16_t a=0,b=0;
	
	for( i = 80; i < (cam_mode.cam_width-80) ; i++ ) //����20����
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
		
	printf("�������%d\n",a/20);	
	printf("�����ұ�%d\n\n",b/20);					
}



//ͼ����
void cv_cv(void)
{
	cv_gray();
	cv_binarization();//��ֵ������
	cv_drawline();
}

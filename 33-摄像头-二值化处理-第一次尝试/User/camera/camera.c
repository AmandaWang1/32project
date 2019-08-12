#include "camera.h"

#define PIXEL_W      180
#define PIXEL_H      320


//�Ҷ�ֱ��ͼ��ֵ�������жϰ�ͼ������
u32 gray_test_value[26];   //���ص�������
u8 gray_test_send[28];     //���͸���λ��������


//��ֵ�ָ�Ҷ�ͼ
u8 gray_itera_threshold[256];
u16 threshold_h[256];
#define GRAY_BREAK_RANGE     1    //��ֵ�������


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
		 //ת���ɻҶ�ͼ	
      READ_FIFO_PIXEL(Camera_Data);		/* ��FIFO����һ��rgb565���ص�Camera_Data���� */      
			R = (uint16_t)GETR_FROM_RGB16(Camera_Data);
			G = (uint16_t)GETG_FROM_RGB16(Camera_Data);
			B = (uint16_t)GETB_FROM_RGB16(Camera_Data);
			mux = (R*30+G*59+B*11)/100;         //��ȡ���ĻҶ�ֵ
      
			pixel[i][j] = mux;         //�Ѷ�ȡ���ĻҶ�ֵ�ŵ�320*240��
			
		}

	}
}


/*������ֵ�����ܹ��ҵ��Ҷ�ͼ����Ѷ�ֵ����*/

void Itera_Threshold(void)
{
  u16 i=0,j=0,k=0,cnt=0,mux=0,Camera_Data=0;
	u8 newthreshold=0;
	u16 Pmax=0,Pmin=0;
	u32 sum_h1=0,sum_h2=0;
	
	
	//�������
	for( i=0; i<256; i++ )
	{
	  gray_test_value[i] = 0;
	}
	
	//ɨ��
	for( i=0; i<PIXEL_H; i++ )
	{
	  for( j=0; j<PIXEL_W; j++ )
		{
		  mux = pixel[i][j];//��ȡ�Ҷ�ͼ������	
			
			//���ص�������     
			gray_itera_threshold[mux]++;	
		}
	}
	
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
	
	printf("the Pmax is %d\r \n",Pmax);
	printf("the Pmin is %d \r\n",Pmin);
	
	//��ʼ��ֵ
	threshold_h[0] = ( Pmax + Pmin ) / 2;
	
	//Ѱ�������ֵ
	for( k=0; k<256; k++ )
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

	printf("����ֵ�� %d\r\n",newthreshold);
	
	//׼��д������

	//���������ֵ��ͼ���ֵ��
  ILI9341_GramScan ( 3 );   
	
	
	for( i=0; i<PIXEL_H; i++ )
	{
	  for( j=0; j<PIXEL_W; j++ )
		{
		  mux = pixel[i][j];                     //��ȡ�Ҷ�ͼ������
			
		  //ͼ���ֵ��
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



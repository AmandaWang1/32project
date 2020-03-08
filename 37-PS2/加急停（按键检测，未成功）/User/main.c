#include "stm32f10x.h"
#include "bsp_led.h"
#include "usart.h"
#include "ADC.h "
#include "systick.h"
#include "ps2.h"
#include "bsp_key.h"

extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[NOFCHANEL];      


int main (void)
{
	float x = 0;
	float y = 0;
	
	USART_Config();
		
	ADCx_Init();
	
	while (1)
	{	
		//��ֵת����ģ����
		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3; //y
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3; //x
		
		x = ADC_ConvertedValueLocal[1];
		y = ADC_ConvertedValueLocal[0];

		if(((x>1.7) && (x<1.9)) && ((y>1.6) && (y<1.8)))  //������ʻ
		{
			printf("������ʻ\n");
		}
	else	if(((x>3.2) && (x<3.4)) && ((y>1.6) && (y<1.8)))//ǰ��
		{
			printf("ǰ��\n");
		}	
	else	if(((x>0) && (x<0.1)) && ((y>1) && (y<2)))//����
		{
			printf("����\n");
		}
	else	if(((x>1.2) && (x<2)) && ((y>0) && (y<0.2)))//����
		{
			printf("����\n");
		}
	else	if(((x>1.7) && (x<1.9)) && ((y>3.2) && (y<3.4)))//����
		{
			printf("����\n");
		}
	else	if(((x>3) && (x<3.4)) && ((y>0) && (y<0.2)))//����ǰ��
		{
			printf("����ǰ��\n");
		}
	else	if(((x>0) && (x<0.1)) && ((y>0) && (y<1)))//�����
		{
			printf("�����\n");
		}
	else	if(((x>3.2) && (x<3.4)) && ((y>3.2) && (y<3.4)))//����ǰ��
		{
			printf("����ǰ��\n");
		}
	else if(((x>0) && (x<0.1)) && ((y>3) && (y<3.4)))//���Һ�
		{
			printf("���Һ�\n");
		}
		
//		if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )
//		{
//			printf("��ͣ\n");
//		}
		
					
		
//	  //��ֵ��ӡ����	
//	printf("\r\n CH0 value = %f V \r\n",ADC_ConvertedValueLocal[0]);   //y
//	printf("\r\n CH1 value = %f V \r\n",ADC_ConvertedValueLocal[1]);    //x
//		
//	printf("\r\n\r\n");
		delay_ms(500);		 
	}
}


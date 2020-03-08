#include "stm32f10x.h"
#include "bsp_led.h"
#include "usart.h"
#include "ADC.h "
#include "systick.h"
#include "ps2.h"
#include "bsp_key.h"

extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[NOFCHANEL];      


int main (void)
{
	float x = 0;
	float y = 0;
	
	USART_Config();
		
	ADCx_Init();
	
	while (1)
	{	
		//把值转换成模拟量
		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3; //y
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3; //x
		
		x = ADC_ConvertedValueLocal[1];
		y = ADC_ConvertedValueLocal[0];

		if(((x>1.7) && (x<1.9)) && ((y>1.6) && (y<1.8)))  //正常行驶
		{
			printf("正常行驶\n");
		}
	else	if(((x>3.2) && (x<3.4)) && ((y>1.6) && (y<1.8)))//前进
		{
			printf("前进\n");
		}	
	else	if(((x>0) && (x<0.1)) && ((y>1) && (y<2)))//后退
		{
			printf("后退\n");
		}
	else	if(((x>1.2) && (x<2)) && ((y>0) && (y<0.2)))//向左
		{
			printf("向左\n");
		}
	else	if(((x>1.7) && (x<1.9)) && ((y>3.2) && (y<3.4)))//向右
		{
			printf("向右\n");
		}
	else	if(((x>3) && (x<3.4)) && ((y>0) && (y<0.2)))//向左前方
		{
			printf("向左前方\n");
		}
	else	if(((x>0) && (x<0.1)) && ((y>0) && (y<1)))//向左后方
		{
			printf("向左后方\n");
		}
	else	if(((x>3.2) && (x<3.4)) && ((y>3.2) && (y<3.4)))//向右前方
		{
			printf("向右前方\n");
		}
	else if(((x>0) && (x<0.1)) && ((y>3) && (y<3.4)))//向右后方
		{
			printf("向右后方\n");
		}
		
//		if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )
//		{
//			printf("急停\n");
//		}
		
					
		
//	  //把值打印出来	
//	printf("\r\n CH0 value = %f V \r\n",ADC_ConvertedValueLocal[0]);   //y
//	printf("\r\n CH1 value = %f V \r\n",ADC_ConvertedValueLocal[1]);    //x
//		
//	printf("\r\n\r\n");
		delay_ms(500);		 
	}
}


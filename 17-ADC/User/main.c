#include "stm32f10x.h"
#include "bsp_led.h"
#include "usart.h"
#include "ADC.h "

extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[NOFCHANEL];      

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

int main (void)
{
	USART_Config();
		
	ADCx_Init();
	
	while (1)
	{	
		//把值转换成模拟量
		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
		
	  //把值打印出来	
		printf("\r\n CH0 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
		printf("\r\n CH2 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
		
		printf("\r\n\r\n");
		Delay(0xffffe);		 
	}
}


#include "stm32f10x.h"
#include "bsp_led.h"
#include "usart.h"
#include "ADC.h "

extern __IO uint16_t ADC_ConvertedValue;

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal;      

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

int main (void)
{
	USART_Config();
		
	ADCx_Init();
	
	while(1)
	{
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; 
	
		printf("\r\n The current AD value = 0x%04X \r\n",ADC_ConvertedValue); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 
		printf("\r\n\r\n");

		Delay(0xffffee);  
	}
}


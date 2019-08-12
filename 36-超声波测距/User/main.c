#include "stm32f10x.h"
#include "bsp_led.h"
#include "base.h"
#include "systick.h"
#include "usart.h"
#include "HC.h"
#include "weidai.h"
#include "TIM.h"



uint16_t time = 0;


int main (void)
{
	BASIC_TIM_Init();//基本定时器初始化
	
	USART_Config();  //串口初始化
	
	HC_Init();
	
	TIM_Init();							//高级定时器初始化
	
	while(1)
	{
		printf("距离为%3f厘米\n",Hcsr04GetLength());
		delay_ms(1000);
	}
	
}


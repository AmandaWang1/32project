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
	BASIC_TIM_Init();//������ʱ����ʼ��
	
	USART_Config();  //���ڳ�ʼ��
	
	HC_Init();
	
	TIM_Init();							//�߼���ʱ����ʼ��
	
	while(1)
	{
		printf("����Ϊ%3f����\n",Hcsr04GetLength());
		delay_ms(1000);
	}
	
}


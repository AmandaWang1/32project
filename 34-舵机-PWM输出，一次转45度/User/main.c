#include "stm32f10x.h"
#include "systick.h"
#include "TIM.h"


int main (void)
{
	TIM_Init();							//�߼���ʱ����ʼ��
	
//	while (1)
//	{
//		delay_ms(500);
//		TIM_SetCompare1(ADVANCE_TIM,175);//��Ӧ180��
//		delay_ms(500);
//		TIM_SetCompare1(ADVANCE_TIM,180);//��Ӧ135��
//		delay_ms(500);
//		TIM_SetCompare1(ADVANCE_TIM,185);//��Ӧ90��
//		delay_ms(500);
//		TIM_SetCompare1(ADVANCE_TIM,190);//��Ӧ45��
//		delay_ms(500);
		TIM_SetCompare1(ADVANCE_TIM,195);//��Ӧ0��
//		delay_ms(500);
//		TIM_SetCompare1(ADVANCE_TIM,190);//��Ӧ45��
//		delay_ms(500);
//		TIM_SetCompare1(ADVANCE_TIM,185);//��Ӧ90��
//		delay_ms(500);
//		TIM_SetCompare1(ADVANCE_TIM,180);//��Ӧ135��
		
		//������õ���PWM1ģʽ����ô��Ӧ��ռ�ձ�Ϊ25,20,15,10,5
//	}
	}


#include "HC.h"
#include "base.h"
#include "weidai.h"
#include "systick.h"

#define  TRIG_Send       PBout(5)
#define  ECHO_Receive    PBin(6)

extern uint16_t time;


void HC_Init (void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(HC_TRIG_CLK | HC_ECHO_CLK , ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = HC_TRIG_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HC_TRIG_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = HC_ECHO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HC_ECHO_PORT, &GPIO_InitStruct);
	
	
}


/* �򿪶�ʱ�� */
static void OpenTimerForHc(void)         
{  
	//����TIM�������Ĵ�����ֵ
	TIM_SetCounter(BASIC_TIM,0); //�������  
	time = 0;  
	TIM_Cmd(BASIC_TIM,ENABLE);  //ʹ��TIMX����  
}  
   
/* �رն�ʱ�� */
static void CloseTimerForHc(void)           
{  
	TIM_Cmd(BASIC_TIM,DISABLE); //ʹ��TIMX����  
}  


/*����Ǵ�֮ǰstmf10x_it.c���Ų������*/
void BASIC_TIM_IRQHandler(void)
{
	if( TIM_GetITStatus( BASIC_TIM,TIM_IT_Update) != RESET)
	{
		time++;
		TIM_ClearITPendingBit(BASIC_TIM,TIM_FLAG_Update);
	}
}


//��ȡ��ʱ��ʱ��  
uint32_t GetEchoTimer(void)  
{  
	uint32_t t = 0;  
	t = time * 1000;      //��msת��Ϊus 
  t = t + TIM_GetCounter(BASIC_TIM);    //�õ���us  
	TIM6-> CNT = 0;       //��TIM6�����Ĵ����ļ���ֵ���� ����һ����������ֵ��  
	delay_ms(50);
	return t;  
}  

  
//һ�λ�ȡ����������������β��֮����Ҫ���һ��ʱ�䣬���ϻ����ź�  
float Hcsr04GetLength(void)  
{  
	uint32_t t = 0;  
	int  i = 0;  
	float  lengthTemp = 0;  
	float  sum = 0; 
	
	while(i!= 5)  
	{ 
		TRIG_Send = 1;      //���Ϳڸߵ�ƽ���  
		delay_us(20);  
		TRIG_Send = 0;  
		
		
		while (ECHO_Receive == 0);      //�ȴ����տڸߵ�ƽ���  
    OpenTimerForHc();        //�򿪶�ʱ��  
		
    i = i + 1;  
		
     while (ECHO_Receive == 1);  
     CloseTimerForHc();        //�رն�ʱ�� 
		
     t = GetEchoTimer();        //��ȡʱ�䣬�ֱ���Ϊ1US  
     lengthTemp =((float )t / 58.3);   //����  
		
     sum = lengthTemp + sum;  
          
    }  
	lengthTemp = sum / 5.0;  
		
		return lengthTemp;
}  




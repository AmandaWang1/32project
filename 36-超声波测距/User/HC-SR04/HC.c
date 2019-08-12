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
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HC_TRIG_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = HC_ECHO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HC_ECHO_PORT, &GPIO_InitStruct);
	
	
}


/* 打开定时器 */
static void OpenTimerForHc(void)         
{  
	//设置TIM计数器寄存器的值
	TIM_SetCounter(BASIC_TIM,0); //清除计数  
	time = 0;  
	TIM_Cmd(BASIC_TIM,ENABLE);  //使能TIMX外设  
}  
   
/* 关闭定时器 */
static void CloseTimerForHc(void)           
{  
	TIM_Cmd(BASIC_TIM,DISABLE); //使能TIMX外设  
}  


/*这个是从之前stmf10x_it.c里边挪过来的*/
void BASIC_TIM_IRQHandler(void)
{
	if( TIM_GetITStatus( BASIC_TIM,TIM_IT_Update) != RESET)
	{
		time++;
		TIM_ClearITPendingBit(BASIC_TIM,TIM_FLAG_Update);
	}
}


//获取定时器时间  
uint32_t GetEchoTimer(void)  
{  
	uint32_t t = 0;  
	t = time * 1000;      //将ms转化为us 
  t = t + TIM_GetCounter(BASIC_TIM);    //得到总us  
	TIM6-> CNT = 0;       //将TIM6计数寄存器的计数值清零 （上一个函数返回值）  
	delay_ms(50);
	return t;  
}  

  
//一次获取超声波测距数据两次测距之间需要相隔一段时间，隔断回响信号  
float Hcsr04GetLength(void)  
{  
	uint32_t t = 0;  
	int  i = 0;  
	float  lengthTemp = 0;  
	float  sum = 0; 
	
	while(i!= 5)  
	{ 
		TRIG_Send = 1;      //发送口高电平输出  
		delay_us(20);  
		TRIG_Send = 0;  
		
		
		while (ECHO_Receive == 0);      //等待接收口高电平输出  
    OpenTimerForHc();        //打开定时器  
		
    i = i + 1;  
		
     while (ECHO_Receive == 1);  
     CloseTimerForHc();        //关闭定时器 
		
     t = GetEchoTimer();        //获取时间，分辨率为1US  
     lengthTemp =((float )t / 58.3);   //厘米  
		
     sum = lengthTemp + sum;  
          
    }  
	lengthTemp = sum / 5.0;  
		
		return lengthTemp;
}  




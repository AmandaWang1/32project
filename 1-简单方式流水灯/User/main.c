#include "stm32f10x.h"
#include "bsp_led.h"
#include "weidai.h"
#include "systick.h"
#include "bsp_key.h"
#include "usart.h"

void zhengxiang(uint16_t min , uint16_t max);
void nixiang(uint16_t max ,uint16_t min);


int main (void)
{
	uint16_t i=0;	
	
	
	/*LED GPIO初始化*/
	LED_GPIO_Config ();
	
	/*按键 GPIO初始化*/
	Key_GPIO_Config();
	
	USART_Config();
	
	
	/*设置八个小灯的默认状态*/
//	for(i=1;i<=8;i++)
//		PAout(i) = 0;
//	PEin(3) = 0;
	
	while(1)
	{	
		/*流水灯实现来回跑*/
		zhengxiang(1,8);
		nixiang(7,2);
		
		/*按键检测*/
		if( PEin(3) == 0 )
		{
			delay_ms(10);
			while( PEin(3) == 0 );
			printf("1-211111\n");
			delay_ms(10);

			while(1)
			{
				/*小灯只正向跑*/
				zhengxiang(1,8);
				
				if( PEin(3) == 0 )
				{
					delay_ms(10);
					while( PEin(3) == 0 );
					printf("2-333333\n");
					delay_ms(10);
					break;
				}
			}
			
			/*第二次按下后，小灯开始逆向跑*/
			while(1)
			{
				nixiang(8,1);
				if( PEin(3) == 0 )
				{
					delay_ms(10);
					while( PEin(3) == 0 );
					printf("3-444444\n");
					
					delay_ms(10);
					break;
				}
			}
			
			
			/*第三次按下后，小灯随便跑*/
			while(1)
			{
				zhengxiang(2,5);
				nixiang(8,6);
				zhengxiang(1,3);
				nixiang(5,4);
				
				if( PEin(3) == 0 )
				{
					delay_ms(10);
					while( PEin(3) == 0 );
					delay_ms(10);
					break;
				}
			}
			
			
			
			/*小灯第四次按下后，小灯恢复以前的前后跑*/
		}
	}
}


void zhengxiang(uint16_t min ,uint16_t max)
{
	uint16_t j;
	
	for(j=min ;j<=max;j++)
	{
		PAout(j)=1;
		delay_ms(200);
		PAout(j)=0;
	}
}
void nixiang(uint16_t max,uint16_t min)
{
	uint16_t k;
	
	for(k=max;k>=min;k--)
	{
		PAout(k)=1;
		delay_ms(200);
		PAout(k)=0;
	}
}


#include "ADC.h"

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 打开 ADC IO端口时钟
	ADC_GPIO_APBxClock_FUN ( ADC_GPIO_CLK, ENABLE );
	
	// 配置 ADC IO 引脚模式
	// 必须为模拟输入
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	// 初始化 ADC IO
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);				
}

static void ADCx_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );// 打开ADC时钟
	
	// ADC 模式配置
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;								 // 只使用一个ADC所以选择独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;											 // 扫描模式，多通道需要，单通道不需要
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;								 // 连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;// 软件触发，不使用外部触发，外部触发为定时器，GPIO
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;             // 转换结果右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;														 // 要转换的通道数目 转换通道1个
	ADC_Init(ADC_x, &ADC_InitStructure);													     // 初始化ADC
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 																 //9M
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);// 配置 ADC 通道转换顺序和采样时间

	ADC_ITConfig(ADC_x, ADC_IT_EOC, ENABLE);														// ADC 转换结束产生中断，选择规则通道，在中断服务程序中读取转换值
	ADC_Cmd(ADC_x, ENABLE);																						 // 开启ADC ，并开始转换
	
	ADC_ResetCalibration(ADC_x);                                       // 初始化ADC 校准寄存器  
	
	while(ADC_GetResetCalibrationStatus(ADC_x));                       // 等待校准寄存器初始化完成
		
	ADC_StartCalibration(ADC_x);																			 // ADC开始校准

	while(ADC_GetCalibrationStatus(ADC_x));	   											   // 等待校准完成

	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);														 // 由于没有采用外部触发，所以使用软件触发ADC转换 

}

static void ADCx_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);									  // 优先级分组

  // 配置中断优先级
  NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void ADCx_Init(void)
{
	ADCx_NVIC_Config();
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
}




#include "ADC.h"

__IO uint16_t ADC_ConvertedValue;

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
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);// 打开DMA时钟
	DMA_DeInit(ADC_DMA_CHANNEL);// 复位DMA控制器
	
	// 配置 DMA 初始化结构体
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADC_x->DR ) );// 外设基址为：ADC 数据寄存器地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;				// 存储器地址，实际上就是一个内部SRAM的变量
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;													// 数据源来自外设
	DMA_InitStructure.DMA_BufferSize = 1;																				// 缓冲区大小为1，缓冲区的大小应该等于存储器的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;						// 外设寄存器只有一个，地址不用递增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 										// 存储器地址固定
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 外设数据大小为半字，即两个字节
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;					// 存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		                          // 循环传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;										      // DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;												      	// 禁止存储器到存储器模式，因为是从外设到存储器
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);															// 初始化DMA
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);	                                        // 使能 DMA请求
	
	
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
	
	// 使能ADC DMA 请求
	ADC_DMACmd(ADC_x, ENABLE);

	ADC_Cmd(ADC_x, ENABLE);																						 // 开启ADC ，并开始转换
	
	ADC_ResetCalibration(ADC_x);                                       // 初始化ADC 校准寄存器  
	
	while(ADC_GetResetCalibrationStatus(ADC_x));                       // 等待校准寄存器初始化完成
		
	ADC_StartCalibration(ADC_x);																			 // ADC开始校准

	while(ADC_GetCalibrationStatus(ADC_x));	   											   // 等待校准完成

	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);													// 由于没有采用外部触发，所以使用软件触发ADC转换 

}


void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
}




#include "ADC.h"

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// �� ADC IO�˿�ʱ��
	ADC_GPIO_APBxClock_FUN ( ADC_GPIO_CLK, ENABLE );
	
	// ���� ADC IO ����ģʽ
	// ����Ϊģ������
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	// ��ʼ�� ADC IO
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);				
}

static void ADCx_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );// ��ADCʱ��
	
	// ADC ģʽ����
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;								 // ֻʹ��һ��ADC����ѡ�����ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;											 // ɨ��ģʽ����ͨ����Ҫ����ͨ������Ҫ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;								 // ����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;// �����������ʹ���ⲿ�������ⲿ����Ϊ��ʱ����GPIO
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;             // ת������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;														 // Ҫת����ͨ����Ŀ ת��ͨ��1��
	ADC_Init(ADC_x, &ADC_InitStructure);													     // ��ʼ��ADC
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 																 //9M
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);// ���� ADC ͨ��ת��˳��Ͳ���ʱ��

	ADC_ITConfig(ADC_x, ADC_IT_EOC, ENABLE);														// ADC ת�����������жϣ�ѡ�����ͨ�������жϷ�������ж�ȡת��ֵ
	ADC_Cmd(ADC_x, ENABLE);																						 // ����ADC ������ʼת��
	
	ADC_ResetCalibration(ADC_x);                                       // ��ʼ��ADC У׼�Ĵ���  
	
	while(ADC_GetResetCalibrationStatus(ADC_x));                       // �ȴ�У׼�Ĵ�����ʼ�����
		
	ADC_StartCalibration(ADC_x);																			 // ADC��ʼУ׼

	while(ADC_GetCalibrationStatus(ADC_x));	   											   // �ȴ�У׼���

	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);														 // ����û�в����ⲿ����������ʹ���������ADCת�� 

}

static void ADCx_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);									  // ���ȼ�����

  // �����ж����ȼ�
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




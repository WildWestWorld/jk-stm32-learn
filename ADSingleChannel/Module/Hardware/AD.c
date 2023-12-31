#include "stm32f10x.h"                  // Device header

void AD_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	//断开 GPIO_Mode_AIN GPIO
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_0,Rank,Any)
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;
	//设置为独立模式
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	//数据对齐方式
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	//设置触发模式
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	//单次转换
	ADC_InitStructure.ADC_ContinuousConvMode=	DISABLE;
	//是否为扫描模式 扫描模式多通道 非扫描模式单通道
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;
	
	
	ADC_InitStructure.ADC_NbrOfChannel=1;
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);
	
	//开启ADC电源
	//复位校准
	ADC_ResetCalibration(ADC1);
	//检测 是否复位校准 完成
	while(ADC_GetResetCalibrationStatus(ADC1) == SET){};
	
	//复位完毕 后开启校验
	ADC_StartCalibration(ADC1);
	//检测校准 是否完成
	while(ADC_GetCalibrationStatus(ADC1)== SET){};
}

uint16_t AD_GetValue(void){
	//开启 AD、转换器
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//检测是否完成开启完毕
	//ADC_GetFlagStatus(ADC1,需要检测的状态)
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET){};
	//我们在RegularChannelConfig设置了ADC_SampleTime_55Cycles5=> 采样周期是55.5
//转换周期是固定的12.5 =>68个周期
		//ADCCLK是72Mhz的6分频=>12MHz
		//执行一个周期时间=周期/频率  =>68/12MHz=5.6us
		//所以我们花了5.6us等待命令执行
		
		//取结果 获得AD转换的结果
		//ADC_GetConversionValue  = 直接读取DR寄存器
		return ADC_GetConversionValue(ADC1);
}

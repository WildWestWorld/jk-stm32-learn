#include "stm32f10x.h"                  // Device header

void PWM_Init(void){
		//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	/*//开启AFIO来开启重映射
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//设置重定向的类型 这样会重定向到P15口，但P15口是测试口 需要取消掉JTA测试口
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
	//取消掉P15口的JTA测试口
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);*/ 
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	//复用推挽模式  专门用于定时器控制引脚的模式
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	//配置默认时钟
	TIM_InternalClockConfig(TIM2);

	
	//配置时基电路
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	//设置分频TIM_CKD_DIV1 一分频
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	//计数器模式 向上计数模式
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
//定时频率 =72M/(PSC+1)/(ARR+1)
//因为预分频器和计数器都有一个数的偏差所以在这里减1	
  TIM_TimeBaseInitStructure.TIM_Period=100-1; //ARR
  TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;//PSC

	
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;

		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure); 
	

	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse=0; //CCR   //占空比:CRR/(ARR +1)
	
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	
	
	//启动定时器
	TIM_Cmd(TIM2,ENABLE);
	

}

//设置TIM的Pulse 也就是设置CCR
void PWM_SetCompare1(uint16_t Compare){
	TIM_SetCompare1(TIM2,Compare);
}


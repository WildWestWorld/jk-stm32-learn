#include "stm32f10x.h"                  // Device header

int main(void)
{
//开启GPIOA的时钟
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	

	//初始化对应的GPIO
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//GPIO引脚，赋值为第0号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);		
	//将赋值后的构体变量传递给GPIO_Init函数
										
	//设置低电平
	//GPIO_ResetBits(GPIOA, GPIO_Pin_0);					//将PA0引脚设置为低电平
	
	//WriteBit设置低电平或者高电平 Bit_RESET低电平 BIT_SET高电平
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	
	
	while(1){
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);

	}
	
}

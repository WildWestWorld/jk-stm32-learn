#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
//开启GPIOA的时钟
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	

	//初始化对应的GPIO
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	//为什么是或运算 因为Pin_0对应的二进制是0x0001 Pin_1 对应的0x0010
	//如果想同时打开 0x0011 所以直接或运算就行
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				//GPIO引脚，赋值为第0号引脚
	//开启所有引脚
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;				//GPIO引脚，赋值为第0号引脚
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);		

	
	while(1){
	
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(500);
		
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(500);
	}
	
}

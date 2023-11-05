#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
//开启GPIOA的时钟
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	

	//初始化对应的GPIO
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	//为什么是或运算 因为Pin_0对应的二进制是0x0001 Pin_1 对应的0x0010
	//如果想同时打开 0x0011 所以直接或运算就行
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;				//GPIO引脚，赋值为第0号引脚
	//开启所有引脚
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;				//GPIO引脚，赋值为第0号引脚
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);		
	//将赋值后的构体变量传递给GPIO_Init函数
										
	//设置低电平
	//GPIO_ResetBits(GPIOA, GPIO_Pin_0);					//将PA0引脚设置为低电平
	
		//设置高电平
	//GPIO_SetBits(GPIOA, GPIO_Pin_0);					//将PA0引脚设置为高电平
	
	//WriteBit设置低电平或者高电平 Bit_RESET低电平 BIT_SET高电平
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	
	
	while(1){
			//GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			//Delay_ms(500);
			//GPIO_SetBits(GPIOA,GPIO_Pin_0);
			//Delay_ms(500);

		
		
		
			//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
			//Delay_ms(500);
			//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
			//Delay_ms(500);
		
			//GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)0);
			//Delay_ms(500);
			//GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)1);
			//Delay_ms(500);
		
		//控制多个灯
		//为什么要取反，因为是低电平点亮
			GPIO_Write(GPIOA,~0x0001);//0000 0000 0000 0001
			Delay_ms(500);
			
			GPIO_Write(GPIOA,~0x0002);//0000 0000 0000 0010
			Delay_ms(500);
	
	
	}
	
}

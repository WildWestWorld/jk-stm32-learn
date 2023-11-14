#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint8_t KeyNum;
uint16_t Num;

int main(void)
{
			OLED_Init();
			Timer_Init();
	
	OLED_ShowString(1,1,"Num:");

	while(1){
		OLED_ShowNum(1,5,Num,5);
		//显示TIM2的CNT计数器
		//自增的范围是0- 我们自己填的数 本次填写的是10000  //对应的就是1s
		OLED_ShowNum(2,5,TIM_GetCounter(TIM2),5);
	}
	
}


void TIM2_IRQHandler(void){
	//获取中断标志位 
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){
		
		Num ++;
		
		//清楚中断标志位
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
	
}

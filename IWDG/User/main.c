#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"


int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Key_Init();							//按键初始化

	OLED_ShowString(1,1,"IWDG TEST");

	//如果独立看门狗复位标志位==SET
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST)==SET){
			OLED_ShowString(2,1,"IWDG REST");
			Delay_ms(500);
		
			OLED_ShowString(2,1,"           ");
			Delay_ms(100);
		
		
		//清除看门狗复位的标志位
		//看门狗复位标志位 不会因为你读取了就自动置0，所以得手动
		RCC_ClearFlag(); 
		
	}else{
				OLED_ShowString(3,1,"RST REST");
			Delay_ms(500);
		
			OLED_ShowString(3,1,"           ");
			Delay_ms(100);
		
	
	}
	

	/*IWDG初始化*/
	//解除写保护
	//超时时间T iwdg(1000ms) =T lsi(1/F lsi = 1/40kHz) *PR预分频系数*(RL +1)
	//PR预分频系数 越大 RL越小，RL越有可能出现小数，四舍五入，误差越大
	//所以我们尽可能选择 小的PR ，误差越小，但是 选择分频系数的最长时间得大于超时时间
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	//独立看门狗写使能
	IWDG_SetPrescaler(IWDG_Prescaler_16);			//设置预分频为16 16分频误差最小
	//1000ms怎么来的？1/40kHz * 16*（2499+1） = 1000ms 
	IWDG_SetReload(2499);							//设置重装值为2499，独立看门狗的超时时间为1000ms
	//先喂一次狗
	//喂狗/使能之后 会在键寄存器写入0x5555以外的值
	IWDG_ReloadCounter();							//重装计数器，喂狗
	IWDG_Enable();									//独立看门狗使能
	
	while (1)
	{
				Key_GetNum();								//调用阻塞式的按键扫描函数，模拟主循环卡死

		
			IWDG_ReloadCounter();							//重装计数器，喂狗
			
			OLED_ShowString(4, 1, "FEED");				//OLED闪烁FEED字符串
			Delay_ms(200);								//喂狗间隔为200+600=800ms
			OLED_ShowString(4, 1, "    ");
			Delay_ms(600);
		
			//高于1000ms 会触发看门狗机制
			//Delay_ms(1200);

	}
}

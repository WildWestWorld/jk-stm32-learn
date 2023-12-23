#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"


int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Key_Init();							//按键初始化

	OLED_ShowString(1,1,"WWDG TEST");

	//如果独立看门狗复位标志位==SET
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST)==SET){
			OLED_ShowString(2,1,"WWDG REST");
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
	
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	//开启WWDG的时钟

		
	/*WWDG初始化*/
	WWDG_SetPrescaler(WWDG_Prescaler_8);			//设置预分频为8
	//假设超时时间为50ms
	//Twwdg(50ms) = Tpclk1(1/36MHz) *4096 *WDGTB(2^3 为什么是3因为其他的最大时间不能达到50ms)*(T[5:0]+1)
	//(T[5:0]+1) = 50ms/(1/36MHz)/4096/8 =54.9 约55
	//T[5:0]  = 55-1=54 
	//写入重装值 54
	//为什么要或上 0x40 ，因为第6位要把置1，根据电路，第6位 若为0 会直接触发复位所以我们得或上0x40
	//其实还有一个第7位 WDGA，这个是开关位，我们Enable 之后会或上我们传入的数据 让他的第七位开启，也就是使能WWDG
		WWDG_Enable(0x40 | 54);							//使能并第一次喂狗，超时时间为50ms

	//假设窗口时间 为 30ms
	//Twin(30ms) =(1/36MHz) *4096 * 8 *(54-W[5:0])
	//W[5:0] = 54(T[5:0])-30ms/(1/36MHz)/4096/8 
	//W[5:0]=21
	WWDG_SetWindowValue(0x40 | 21);					//设置窗口值，窗口时间为30ms
	
	while (1)
	{
			Key_GetNum();								//调用阻塞式的按键扫描函数，模拟主循环卡死

		
			//IWDG_ReloadCounter();							//重装计数器，喂狗
			
			OLED_ShowString(4, 1, "FEED");				//OLED闪烁FEED字符串
			Delay_ms(20);								//喂狗间隔为200+600=800ms
			OLED_ShowString(4, 1, "    ");
			Delay_ms(20);
			
		//WWDG_SetCounter 传入数据 会默认与上BitMask 0x7F(0111 1111) 我们的传入的数据 最高有6位，与上7位，会导致第7位位0
		//也就是说喂狗的时候 使能位为0
		//但是说明书 说 开门狗开启后是无法关闭的，即使使能位为0 也关闭不掉，除非他被复位

		//为什么第一次喂狗 是在delay后面，因为第一次喂狗是在WWDG_Enable 使能看门狗时喂狗
		//如果不放到delay后面就会造成 两次喂狗时间太短 低于窗口时间，触发复位
		WWDG_SetCounter(0x40 | 54);					//重装计数器，喂狗

		
			//高于1000ms 会触发看门狗机制
			//Delay_ms(1200);

	}
}

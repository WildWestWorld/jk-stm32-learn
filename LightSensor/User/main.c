#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"


uint8_t KeyNum;

int main(void)
{
	//初始化区域
	Buzzer_Init();
	LightSensor_Init();
	while(1){
	/*	Buzzer_ON();
		Delay_ms(500);
		
		Buzzer_OFF();
		Delay_ms(500);
		
		Buzzer_Turn();
		Delay_ms(500);
		
		Buzzer_Turn();
		Delay_ms(500);*/
		
			//如果光敏电阻有光，蜂鸣器就响
			if(LightSensor_Get()==1){
				Buzzer_ON();
			}else{
				Buzzer_OFF();
			}
		
		
		
		
	}
	
}

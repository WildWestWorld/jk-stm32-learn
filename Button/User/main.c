#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"

uint8_t KeyNum;

int main(void)
{
	//来自于LED.h 的方法
	LED_Init();
	Key_Init();
	
	while(1){
			/*LED1_ON();
			Delay_ms(500);
		
			LED1_OFF();
			Delay_ms(500);
		
			
			LED2_ON();
			Delay_ms(500);
		
			LED2_OFF();
			Delay_ms(500);*/
		KeyNum = Key_GetNum();
			if(KeyNum==1){
				//LED1_ON();
				
				LED1_Turn();
			}
			
			if(KeyNum==2){
				//LED1_OFF();
				
				LED2_Turn();
			}
		
		
		
		
	}
	
}

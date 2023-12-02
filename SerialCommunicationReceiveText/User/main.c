#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

#include "LED.h"

//用于判断字符串
#include <string.h>

int main(void)
{
	OLED_Init();
	LED_Init();
	
	Serial_Init();
	
		OLED_ShowString(1,1,"TxPacket");
		OLED_ShowString(3,1,"RxPacket");
		
		while(1){
			if(Serial_RxFlag_Text ==1){
				OLED_ShowString(4,1,"                   ");

				OLED_ShowString(4,1,Serial_RxPacket_Text);
				
				//判断两个字符串是否相等
				if(strcmp(Serial_RxPacket_Text,"LED_ON")==0){
					LED1_ON();
					//发送完成的信号数据
					Serial_SendString("LED_ON_OK\r\n");
					OLED_ShowString(2,1,"                   ");
					OLED_ShowString(2,1,"LED_ON_OK");

				}
				else if(strcmp(Serial_RxPacket_Text,"LED_OFF")==0){
					LED1_OFF();
					//发送完成的信号数据
					Serial_SendString("LED_OFF_OK\r\n");
					OLED_ShowString(2,1,"                   ");
					OLED_ShowString(2,1,"LED_OFF_OK");

				}else{
					//如果指令不在我们的设置的范围内就显示ERROR

					Serial_SendString("ERROR\r\n");
					OLED_ShowString(2,1,"                   ");
					OLED_ShowString(2,1,"ERROR");
				}
				
				//执行完成 状态置0
				Serial_RxFlag_Text=0;
				
			}
		
		}
		
	
		//Delay_ms(1000);

	}


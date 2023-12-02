#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"


//用于存储接收到的数据
uint8_t RxData;

int main(void)
{
	OLED_Init();
	Serial_Init();
	
	OLED_ShowString(1,1,"RxData:");

	while(1){	
	/*		//是否收到数据
		//如果为SET
		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET){
			//获取发送过来的数据
			//正常情况下我们都需要清除对应的标志位
			//但是这个接口文档说明 只要你读了就默认会清空标志位
			RxData =USART_ReceiveData(USART1);
			//OLED 显示获取的数据
			OLED_ShowHexNum(1,1,RxData,2);
		}*/
		
		
					//是否收到数据
		//如果为SET
		if(Serial_GetRxFlag()==1){
			//获取发送过来的数据
			RxData =Serial_GetRxData();
			
			
			//数据回传到STM32 接收口
			Serial_SendByte(RxData);
			
			//OLED 显示获取的数据
			OLED_ShowHexNum(1,8,RxData,2);
		}

		
	
		//Delay_ms(1000);
	}	
	}


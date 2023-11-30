#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"


int main(void)
{
	OLED_Init();
	Serial_Init();
	
	//Serial_SendByte(0x41);
	
	//uint8_t MyArray[] ={0x42,0x43,0x44,0x45};
	//Serial_SendArray(MyArray,4);
	//Serial_SendString("HelloWorld!");
	
		//Serial_SendString("HelloWorld!");
		//Serial_SendNumber(12345,5);
		
	//	printf("Num=%d\r\n",666);
	
	/*//多串口使用sprintf	
	char String[100];
	//使用sprintf 答应到string 也就是string是个容器
	sprintf(String,"Num=%d\r\n",666);
	Serial_SendString(String);*/
	
	Serial_Printf("Num=%d\r\n",666);
	
	while(1){	
		

		
	
		Delay_ms(1000);
	}	
	}


#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"


uint8_t KeyNum;

int main(void)
{

	while(1){
			
			OLED_Init();
			//OLED_ShowChar(行，列，字符)
			OLED_ShowChar(1,1,'A');
			OLED_ShowString(1,3,"HelloWorld!");
		//showNum(行，列，显示的数字，要显示的数字的长度)
			OLED_ShowNum(2,1,12345,5);
		OLED_ShowSignedNum(2,7,-66,2);
		OLED_ShowHexNum(3,1,0xAA55,4);
		//
		OLED_ShowBinNum(4,1,0xAA55,16);
		
	}
	
}

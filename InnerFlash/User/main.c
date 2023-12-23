#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "MyFLASH.h"
#include "FlashStore.h"


uint8_t KeyNum;

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Key_Init();							//按键初始化
	//初始化闪存存储
	Store_Init();
	
	/*//FLASH 第一个内存地址是 0x08000000
	OLED_ShowHexNum(1,1, MyFLASH_ReadWord(0x08000000),8);
	
	OLED_ShowHexNum(2,1, MyFLASH_ReadHalfWord(0x08000000),4);
	OLED_ShowHexNum(3,1, MyFLASH_ReadByte(0x08000000),2);
	
	//先擦除再写入
	MyFLASH_ErasePage(0x0800FC00);
	MyFLASH_ProgramWord(0x0800FC00,0x12345678);
	MyFLASH_ProgramHalfWord(0x0800FC10,0xABCD);
	*/
	
	
		/*显示静态字符串*/
	OLED_ShowString(1, 1, "Flag:");
	OLED_ShowString(2, 1, "Data:");
	while (1)
	{
		KeyNum = Key_GetNum();
		if(KeyNum ==1){
			//如果按下按键，擦除闪存所有内容
			//MyFLASH_EraseAllPages();
			
			Store_Data[1] ++;		//变换测试数据
			Store_Data[2] += 2;
			Store_Data[3] += 3;
			Store_Data[4] += 4;
			Store_Save();			//将Store_Data的数据备份保存到闪存，实现掉电不丢失
			
		}
		//如果按下按键擦除第一页
		if(KeyNum ==2){
			//如果按下按键，擦除传入的地址的闪存内容
			//MyFLASH_ErasePage(0x08000000);
			Store_Clear();			//将Store_Data的数据全部清0

		}
		
		OLED_ShowHexNum(1, 6, Store_Data[0], 4);	//显示Store_Data的第一位标志位
		OLED_ShowHexNum(3, 1, Store_Data[1], 4);	//显示Store_Data的有效存储数据
		OLED_ShowHexNum(3, 6, Store_Data[2], 4);
		OLED_ShowHexNum(4, 1, Store_Data[3], 4);
		OLED_ShowHexNum(4, 6, Store_Data[4], 4);
		
	}
}

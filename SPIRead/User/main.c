#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
//#include "MyI2C.h"

//#include "MPU6050.h"
#include "W25Q64.h"

uint8_t MID;
uint16_t DID;

uint8_t ArrayWrite[] = {0x55,0x66,0x77,0x88};
uint8_t ArrayRead[4];

int main(void)
{
	OLED_Init();
	W25Q64_Init();

	
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "MID:   DID:");
	OLED_ShowString(2, 1, "W:");
	OLED_ShowString(3, 1, "R:");
	  
	//读取设备ID
	W25Q64_ReadID(&MID,&DID);
	OLED_ShowHexNum(1,5,MID,2);
  OLED_ShowHexNum(1,12,DID,4);
	
	/*W25Q64功能函数测试*/
	W25Q64_SectorErase(0x000000);					//扇区擦除
	
	W25Q64_PageProgram(0x000000, ArrayWrite, 4);	//将写入数据的测试数组写入到W25Q64中
	
	
	//读出的数据 =原始的数据&写入的数据
	W25Q64_ReadData(0x000000, ArrayRead, 4);		//读取刚写入的测试数据到读取数据的测试数组中

	
		/*显示数据*/
	OLED_ShowHexNum(2, 3, ArrayWrite[0], 2);		//显示写入数据的测试数组
	OLED_ShowHexNum(2, 6, ArrayWrite[1], 2);
	OLED_ShowHexNum(2, 9, ArrayWrite[2], 2);
	OLED_ShowHexNum(2, 12, ArrayWrite[3], 2);
	
	OLED_ShowHexNum(3, 3, ArrayRead[0], 2);			//显示读取数据的测试数组
	OLED_ShowHexNum(3, 6, ArrayRead[1], 2);
	OLED_ShowHexNum(3, 9, ArrayRead[2], 2);
	OLED_ShowHexNum(3, 12, ArrayRead[3], 2);
	
	 while(1){

		 
		 
	}

}

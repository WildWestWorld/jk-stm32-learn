#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
//#include "MyI2C.h"

#include "MPU6050.h"

uint8_t ID;
int16_t AX,AY,AZ,GX,GY,GZ;

int main(void)
{
	OLED_Init();
	
	MPU6050_Init_Hardware();
	
	OLED_ShowString(1,1,"ID:");
	ID = MPU6050_GetID_Hardware();
	OLED_ShowHexNum(1,4,ID,2);
	
	
/*	//重要 写寄存器 写寄存器的前提关闭 睡眠模式 也就是在电源管理寄存器 写入0x00 
	MPU6050_WriteReg(0x6B,0x00);
	
	MPU6050_WriteReg(0x19,0x66);
	
	
	
	//uint8_t ID = MPU6050_ReadReg(0x75);
	uint8_t ID = MPU6050_ReadReg(0x19);

	OLED_ShowHexNum(1,1,ID,2);*/
	
/*	MyI2C_Init();
	
	MyI2C_Start();
	//发送字节  最后一位是读写位
	MyI2C_SendByte(0xD0); //1101 000 0
	//接受 并且应答
	uint8_t Ack = MyI2C_ReceiveAck();
	MyI2C_Stop();

	OLED_ShowNum(1,1,Ack,3);*/
	

	
	 while(1){
		MPU6050_GetData_Hardware(&AX,&AY,&AZ,&GX,&GY,&GZ);
		OLED_ShowSignedNum(2, 1, AX, 5);					//OLED显示数据
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);
		 
		 
	}

}

#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Servo.h"
#include "Key.h"

uint8_t KeyNum;
float Angle;
int main(void)
{
			OLED_Init();
			PWM_Init();
			Key_Init();
			
			//设置ACC
			//500->0度 1500->90度 2500->180度
		  //PWM_SetCompare2(1500);
			
			Servo_SetAngle(90);
	OLED_ShowString(1,1,"Angle:");
	while(1){
			KeyNum = Key_GetNum();
			if(KeyNum == 1){
				Angle +=30;
				if(Angle >180){
					Angle =0;
				}
			}
		Servo_SetAngle(Angle);
			OLED_ShowNum(1,7,Angle,3);
}
}


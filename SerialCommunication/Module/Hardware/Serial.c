#include "stm32f10x.h"                  // Device header

//print 是输出到屏幕，单片机没有屏幕需要引入stdio.h 进行重定向
#include <stdio.h>
//用于封装sprint
#include <stdarg.h>

void Serial_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//开启USART1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA9引脚初始化为复用推挽输出
	
	/*USART初始化*/
	USART_InitTypeDef USART_InitStructure;					//定义结构体变量
	USART_InitStructure.USART_BaudRate = 9600;				//波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制，不需要
	USART_InitStructure.USART_Mode = USART_Mode_Tx;			//模式，选择为发送模式
	USART_InitStructure.USART_Parity = USART_Parity_No;		//奇偶校验，不需要
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//停止位，选择1位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//字长，选择8位
	USART_Init(USART1, &USART_InitStructure);				//将结构体变量交给USART_Init，配置USART1
	
	/*USART使能*/
	USART_Cmd(USART1, ENABLE);								//使能USART1，串口开始运行
}

void Serial_SendByte(uint8_t Byte){
	USART_SendData(USART1,Byte);
	//查看发送是否完成
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
		
	
}
//上传多条信息
void Serial_SendArray(uint8_t *Array,uint16_t Length){
	uint16_t i;
	for(i =0;i<Length;i++){
		Serial_SendByte(Array[i]);
	}
	
}
void Serial_SendString(char *String){
	uint8_t i;
	//'\0' = 空字符串
	for(i=0;String[i] !='\0';i++){
		Serial_SendByte(String[i]);
	}
	
}

//生成 10/100/1000 数 方便计算
uint32_t Serial_Pow(uint32_t X,uint32_t Y){
	uint32_t Result =1;
	while(Y--){
		Result *=X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number,uint8_t Length){
	uint8_t i;
	for(i=0;i<Length;i++){
		//Length -i -1 =>从最大位开始
		//+0 转成字符串
		Serial_SendByte(Number/(Serial_Pow(10,Length -i -1)) %10 +  '0') ;
	}
	
}

//print 是输出到屏幕，单片机没有屏幕需要引入stdio.h 进行重定向
//fputc是 printf 函数底层
int fputc(int ch,FILE *f){
	Serial_SendByte(ch);
	return ch;
	
}

//封装Sprint
///... 用来接受后面的可变参数列表
void Serial_Printf(char *format,...){
	char String[100];
	//va_list 类型名 arg 变量名
	va_list arg;
	//从format位置开始接受参数表 放在arg里面
	va_start(arg,format);
	//这里的sprintf 得改成vsprintf  因为sprintf无法携带参数
	vsprintf(String,format,arg);
	//释放参数表
	va_end(arg);
	Serial_SendString(String);
}


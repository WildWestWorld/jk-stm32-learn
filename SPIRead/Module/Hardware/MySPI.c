#include "stm32f10x.h"                  // Device header

/**
  * 函    数：SPI写SS引脚电平
  * 参    数：BitValue 协议层传入的当前需要写入SS的电平，范围0~1
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置SS为低电平，当BitValue为1时，需要置SS为高电平
  */
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);		//根据BitValue，设置SS引脚的电平
}

/**
  * 函    数：SPI写SCK引脚电平
  * 参    数：BitValue 协议层传入的当前需要写入SCK的电平，范围0~1
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置SCK为低电平，当BitValue为1时，需要置SCK为高电平
  */
void MySPI_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);		//根据BitValue，设置SCK引脚的电平
}

/**
  * 函    数：SPI写MOSI引脚电平
  * 参    数：BitValue 协议层传入的当前需要写入MOSI的电平，范围0~0xFF
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置MOSI为低电平，当BitValue非0时，需要置MOSI为高电平
  */
void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);		//根据BitValue，设置MOSI引脚的电平，BitValue要实现非0即1的特性
}

/**
  * 函    数：I2C读MISO引脚电平
  * 参    数：无
  * 返 回 值：协议层需要得到的当前MISO的电平，范围0~1
  * 注意事项：此函数需要用户实现内容，当前MISO为低电平时，返回0，当前MISO为高电平时，返回1
  */
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);			//读取MISO电平并返回
}



void MySPI_Init(void){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
		/*设置默认电平*/
	MySPI_W_SS(1);											//SS默认高电平
	MySPI_W_SCK(0);											//SCK默认低电平
	
}

/**
  * 函    数：SPI起始
  * 参    数：无
  * 返 回 值：无
  */
void MySPI_Start(void)
{
	MySPI_W_SS(0);				//拉低SS，开始时序
}

/**
  * 函    数：SPI终止
  * 参    数：无
  * 返 回 值：无
  */
void MySPI_Stop(void)
{
	MySPI_W_SS(1);				//拉高SS，终止时序
}

uint8_t MySPI_SwapByte(uint8_t ByteSend){
	uint8_t i;
	
	uint8_t  ByteReceive = 0x00;
	
	
	for(i=0;i<8;i++){
		//发送ByteSend的最高位 
	// 0x80 = 1000 0000
	// &0x80  如果最高位为1 就发送1 最高位为0 就发送0
	MySPI_W_MOSI(ByteSend& (0x80 >>i));

	//产生上升沿
	MySPI_W_SCK(1);
	//从机放到MISO的数据位 读进来
	//如果获取的MISO数据为1 也就是传入的数据为1 就把相应的位置置1
	if(MySPI_R_MISO() == 1){
		ByteReceive |= (0x80>>i);
	}
	//产生下降沿 移出下一位
	MySPI_W_SCK(0);	
	
	}
	


	
	
	return ByteReceive;

}


uint8_t MySPI_SwapByteV2(uint8_t ByteSend){
	uint8_t i;
	

	
	
	for(i=0;i<8;i++){
		//发送ByteSend的最高位 
	// 0x80 = 1000 0000
	// &0x80  如果最高位为1 就发送1 最高位为0 就发送0
	MySPI_W_MOSI(ByteSend& (0x80));
		//左移1位
	ByteSend<<=1;
	//产生上升沿
	MySPI_W_SCK(1);
	//从机放到MISO的数据位 读进来
	//如果获取的MISO数据为1 也就是传入的数据为1 就把相应的位置置1
	if(MySPI_R_MISO() == 1){
		//保持最低位
		ByteSend |= (0x01);
	}
	//产生下降沿 移出下一位
	MySPI_W_SCK(0);	
	
	}
	


	
	
	return ByteSend;

}




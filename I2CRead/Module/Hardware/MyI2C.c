#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void MyI2C_W_SCL(uint8_t BitValue){
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitValue){
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);
}

uint8_t MyI2C_R_SDA(void){
	uint8_t BitValue;
	BitValue =GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return BitValue;
}


void MyI2C_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	GPIO_InitTypeDef GPIO_InitStructure;
	//设置开漏输出
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//只为高电平
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);
}

void MyI2C_Start(void){
	//SCL和SDA释放 也就是全都置1
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);

	
	//先拉低SDA 再拉低SCL
	//这样就产生了下降沿，就开启了I2C
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);

}

void MyI2C_Stop(void){
	//正常情况下 SCL和SDA 都是低电平 所以我们只要拉高SCL SDA 就行
	//但是时序单元开始时，SCL可能是高电平 为了确保SDA能产生上升沿 也就是从0到1
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);

}

void MyI2C_SendByte(uint8_t Byte){
	//发送一个字节时序开始时，SCL是低电平
	//除了终止条件SCl会保持 高电平 ，其他情况都会以低电平结束
	
	//SCL高低电平变化1次相当于 一个位传输了
	//传输的内容 来自于SDA
	
	//SDA 写1还是写0 取决于Byte 的最高位
	//用位与方式 取出数据的某一位或某几位  0x80 = 1000 0000
 //得到的结果是0x00/0x80  因为	(BitAction)BitValue 非0即1特性，所以我们得到的就是 0/1
	//以此类推发送8位 也就是一个字节
	uint8_t i;
	for(i =0;i<8;i++){
		MyI2C_W_SDA(Byte&(0x80>>i));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}

//接收参数
uint8_t MyI2C_ReceiveByte(void){
	 
	uint8_t	 Byte =0x00;
	uint8_t i;
	
	
	//接收一个字节时序 进来之后SCL是低电平
	//主机释放SDA，从机把数据放到SDA
	//为了防止主机干扰从机写入数据
	//主机需要先释放SDA，释放SDA 相当于切换为输入模式
	//在SCL低电平时 从机 会把数据放到SDA
	//主机释放SCL 在SCL高电平读取SDA

	
	MyI2C_W_SDA(1);
	
	for(i=0;i<8;i++){
		//主机读取SDA
		MyI2C_W_SCL(1);

		if(MyI2C_R_SDA() == 1){
			//第一位置0
			//0x80 = 1000 0000 也就是把Byte 的最高位置1
			//也就是说SDA为1 就把Byte的对应位置 置1
			Byte |= (0x80>>i);
		}
			MyI2C_W_SCL(0);
		}	
	return Byte;
	

}


//发送应答
uint8_t MyI2C_SendAck(uint8_t AckBit){
	//主机把ACKBit放到SDA上
		MyI2C_W_SDA(AckBit);
	//高电平从机读取应答
		MyI2C_W_SCL(1);
	//低电平 进入下一个时序单元
		MyI2C_W_SCL(0);
}

//收发应答
uint8_t MyI2C_ReceiveAck(void){
	uint8_t AckBit;
	//主机释放SDA，防止干扰从机
	//从机把应答位放到SDA
	MyI2C_W_SDA(1);
	//SCL 高电平 主机读取应答位
	MyI2C_W_SCL(1);
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}


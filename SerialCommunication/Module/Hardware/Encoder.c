#include "stm32f10x.h"                  // Device header

void Encoder_Init(void){
		//因为PWM已经输出了TIM2了 所以我们在这需要输出TIM2
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);			//开启TIM3的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);			//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);							//将PA6引脚初始化为 上拉输入
																	//受外设控制的引脚，均需要配置为复用模式
	 
	/*配置时钟源*/
	TIM_InternalClockConfig(TIM3);		//选择TIM3为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式，选择向上计数
	//这里采用的是测周法测频率，前面讲过测周法测频率要N的值越大越好，这里N对应着CNT传给CCR的值
	//这里是通过输入捕获的方式，在上升沿时将时基单元里面CNT的值传递给CCR 
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;                 //计数周期，即ARR的值，尽可能要设置大的值，防止数值溢出
	//频率=72M/(PSC+1)/100
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;               //预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);             //将结构体变量交给TIM_TimeBaseInit，配置TIM2的时基单元



	//初始化IC
	TIM_ICInitTypeDef TIM_ICInitStructure;
	//初始化默认值 不然有些值我们没有赋，会报错
	TIM_ICStructInit(&TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	//滤波 越大滤波 越强
	TIM_ICInitStructure.TIM_ICFilter=0xF;


	
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	
		TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
	//滤波 越大滤波 越强
	TIM_ICInitStructure.TIM_ICFilter=0xF;
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_Cmd(TIM3,ENABLE);
}


int16_t Encoder_Get(void){
  //return TIM_GetCounter(TIM3);
	int16_t Temp;
	Temp =TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return Temp;
	
}

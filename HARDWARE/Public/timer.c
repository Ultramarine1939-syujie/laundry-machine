#include "timer.h"
#include "stepper.h"
#include "delay.h"
#include "ws2812.h"

extern u32 step_speed;
extern u8 step_reverse;
extern u32 step_reverse_time;
extern u32 temp_time;

void TIM4_Init(void)
{
    // 配置 TIM4
    TIM_TimeBaseInitTypeDef TIM_InitStruct;
    // 使能 TIM4 时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_InitStruct.TIM_Prescaler = 720  - 1; // 预分频器，72MHz / (71 + 1) = 1MHz
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
    TIM_InitStruct.TIM_Period = 1000 - 1;  // 自动重装载寄存器值，10ms
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

    // 启动计数器
    TIM_Cmd(TIM4, ENABLE);
}

void TIM4_EnableInterrupt(void)
{
    // 使能 TIM4 中断
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // 清除中断标志位
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

    // 使能 TIM4 更新中断
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
}

void TIM4_DisableInterrupt(void)
{
    // 禁止 TIM4 中断
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStruct);

    // 禁止 TIM4 更新中断
    TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE);
}

extern int step_cir;
extern u8 step_run;
extern u8 mode;
extern u16 timer_set;
u8 step = 0;  // 步序初始值
u32 i = 1;


//void delay(u32 i)
//{
//	while(i--);
//}

void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET )
    {
				if (RTC_GetCounter()%86400 >= step_reverse_time && mode != 0){
					step_reverse = !step_reverse;
					step_reverse_time = RTC_GetCounter()%86400 + temp_time;
				}
				
				
        if (step_run == 1)
        {
					if(step_reverse ==0){			//正转反转
            StepMotor_MoveOneStep(step); // 移动步进电机一步
						printf("step_speed:%d \n",step_speed);
						delay(step_speed);
						
            step = (step + 1) % 4;       // 计算下一步的步序
            step_cir--;
            if (step_cir <= 0)
                step_run = 0;
					}
					
					else if(step_reverse==1){		//正转反转
						StepMotor_MoveOneStep(step); // 移动步进电机一步
						printf("step_speed:%d",step_speed);
						delay(step_speed);
						
						if(i<step_speed){
							i++;
						}else if(i == step_speed){
							i = 0;
						}
						
            step = (step - 1);       // 计算下一步的步序
						
						if (step==255)
							step = 3;
						
            step_cir--;
            if (step_cir <= 0)
                step_run = 0;
					}
        }
        // 清除中断标志位
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}


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
    // ���� TIM4
    TIM_TimeBaseInitTypeDef TIM_InitStruct;
    // ʹ�� TIM4 ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_InitStruct.TIM_Prescaler = 720  - 1; // Ԥ��Ƶ����72MHz / (71 + 1) = 1MHz
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���ģʽ
    TIM_InitStruct.TIM_Period = 1000 - 1;  // �Զ���װ�ؼĴ���ֵ��10ms
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

    // ����������
    TIM_Cmd(TIM4, ENABLE);
}

void TIM4_EnableInterrupt(void)
{
    // ʹ�� TIM4 �ж�
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // ����жϱ�־λ
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

    // ʹ�� TIM4 �����ж�
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
}

void TIM4_DisableInterrupt(void)
{
    // ��ֹ TIM4 �ж�
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStruct);

    // ��ֹ TIM4 �����ж�
    TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE);
}

extern int step_cir;
extern u8 step_run;
extern u8 mode;
extern u16 timer_set;
u8 step = 0;  // �����ʼֵ
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
					if(step_reverse ==0){			//��ת��ת
            StepMotor_MoveOneStep(step); // �ƶ��������һ��
						printf("step_speed:%d \n",step_speed);
						delay(step_speed);
						
            step = (step + 1) % 4;       // ������һ���Ĳ���
            step_cir--;
            if (step_cir <= 0)
                step_run = 0;
					}
					
					else if(step_reverse==1){		//��ת��ת
						StepMotor_MoveOneStep(step); // �ƶ��������һ��
						printf("step_speed:%d",step_speed);
						delay(step_speed);
						
						if(i<step_speed){
							i++;
						}else if(i == step_speed){
							i = 0;
						}
						
            step = (step - 1);       // ������һ���Ĳ���
						
						if (step==255)
							step = 3;
						
            step_cir--;
            if (step_cir <= 0)
                step_run = 0;
					}
        }
        // ����жϱ�־λ
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}


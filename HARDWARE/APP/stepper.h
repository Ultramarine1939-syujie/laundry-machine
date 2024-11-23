// stepper.h

#ifndef __STEPPER_H
#define __STEPPER_H

#include "stm32f10x.h"

// 步进电机引脚定义
#define IN1_PIN GPIO_Pin_0
#define IN2_PIN GPIO_Pin_1
#define IN3_PIN GPIO_Pin_2
#define IN4_PIN GPIO_Pin_3
#define STEPPER_GPIO GPIOC

// 步进电机函数声明
void Stepper_Config(void);
void StepMotor_MoveOneStep(int step);

#endif // __STEPPER_H


// stepper.h

#ifndef __STEPPER_H
#define __STEPPER_H

#include "stm32f10x.h"

// ����������Ŷ���
#define IN1_PIN GPIO_Pin_0
#define IN2_PIN GPIO_Pin_1
#define IN3_PIN GPIO_Pin_2
#define IN4_PIN GPIO_Pin_3
#define STEPPER_GPIO GPIOC

// ���������������
void Stepper_Config(void);
void StepMotor_MoveOneStep(int step);

#endif // __STEPPER_H


// stepper.c

#include "stepper.h"



void Stepper_Config(void) {

    GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // ¿ªÆôGPIOCÊ±ÖÓ

    GPIO_InitStructure.GPIO_Pin = IN1_PIN | IN2_PIN | IN3_PIN | IN4_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(STEPPER_GPIO, &GPIO_InitStructure);
}

void StepMotor_MoveOneStep(int step) {
    switch(step) {
        case 0:
            GPIO_SetBits(STEPPER_GPIO, IN1_PIN);
            GPIO_ResetBits(STEPPER_GPIO, IN2_PIN | IN3_PIN | IN4_PIN);
            break;
        case 1:
            GPIO_SetBits(STEPPER_GPIO, IN2_PIN);
            GPIO_ResetBits(STEPPER_GPIO, IN1_PIN | IN3_PIN | IN4_PIN);
            break;
        case 2:
            GPIO_SetBits(STEPPER_GPIO, IN3_PIN);
            GPIO_ResetBits(STEPPER_GPIO, IN1_PIN | IN2_PIN | IN4_PIN);
            break;
        case 3:
            GPIO_SetBits(STEPPER_GPIO, IN4_PIN);
            GPIO_ResetBits(STEPPER_GPIO, IN1_PIN | IN2_PIN | IN3_PIN);
            break;
    }
}



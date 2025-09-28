#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f4xx_hal.h"
#include <encoder.hpp>
#include <pwm.hpp>
#include <timer.hpp>
#include "OLED_Driver.hpp"

//#define ENCODER_MAX 720
#define ENCODER_MAX 180

#define SERVO_MIN_PULSE 25
#define SERVO_MAX_PULSE 125

#define ENCODER TIM2
#define ENCODER_CHANNEL_A GPIO_PIN_0
#define ENCODER_CHANNEL_B GPIO_PIN_1
#define ENCODER_PORT GPIOA

#define TIMER TIM3

#define PWM TIM1
#define PWM_PIN GPIO_PIN_8
#define PWM_PORT GPIOA

void Error_Handler(void);

#endif

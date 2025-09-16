#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

HAL_StatusTypeDef Encoder_Init(TIM_HandleTypeDef *timHandle);

#ifdef __cplusplus
}
#endif

#endif

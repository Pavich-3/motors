#ifndef INC_I2C_HPP_
#define INC_I2C_HPP_

#include "stm32f4xx_hal.h"

class I2C_Bus {
public:
	I2C_Bus(I2C_HandleTypeDef* i2cHandle);
	HAL_StatusTypeDef i2cInit(void);
	HAL_StatusTypeDef write(uint8_t device_addr, uint8_t* data, uint16_t size);
	void Error_Handler(void);
public:
	I2C_HandleTypeDef* i2cHandle;
    bool isBusy();
};

#endif

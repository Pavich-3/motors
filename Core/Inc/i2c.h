#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "app_main.hpp"

class I2C_Bus {
public:
	I2C_Bus(I2C_HandleTypeDef* i2cHandle);
	HAL_StatusTypeDef i2cInit(void);
	HAL_StatusTypeDef i2cMspInit(void);
	HAL_StatusTypeDef write(uint8_t device_addr, uint8_t* data, uint16_t size);
	void Error_Handler(void);
public:
	I2C_HandleTypeDef* i2cHandle;
};

#endif

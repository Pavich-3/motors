#include "app_main.hpp"
#include "i2c.h"

extern I2C_HandleTypeDef i2cHandle;

void app_main_run()
{
	I2C_Bus i2cBus{&i2cHandle};
	i2cBus.i2cInit();
	i2cBus.i2cMspInit();
}

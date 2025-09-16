#pragma once

#include "stm32f4xx_hal.h"
#include "GFX.hpp"
#include "i2c.hpp"
#include <string.h>


#define OLED_I2C_ADDR 0x3C
#define OLED_WIDTH 124
#define OLED_HEIGHT 64


class OLED_Driver : public GFX
{
public:
	OLED_Driver(I2C_HandleTypeDef* i2cHandle);
	void begin(void);
	void display(void);
	void clearDisplay(void);
	void drawPixel(int16_t x, int16_t y, uint16_t color) override;
private:
	void sendCommand(uint8_t cmd);
	void sendData(uint8_t* data, uint16_t size);

	I2C_Bus bus;
	uint8_t framebuffer[OLED_WIDTH * OLED_HEIGHT / 8];;
};

#pragma once

#include "stm32f4xx_hal.h"
#include "math.h"

class GFX
{
public:
	GFX(int16_t w, int16_t h);
	virtual ~GFX() = default;

	virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;

	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
	void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

	int16_t width() const {return _width;}
	int16_t height() const {return _height;}

protected:
	const uint16_t _width, _height;
};

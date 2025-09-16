#include "GFX.hpp"

GFX::GFX(int16_t w, int16_t h) : _width(w), _height(h) {}

void GFX::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
	int16_t steep = abs(y1 - y0) > abs(x1 - y0);
	if (steep)
	{
		int16_t temp = x0; x0 = y0; y0 = temp;
		temp = x1; x1 = y1; y1 = temp;
	}

	if (x0 > x1)
	{
		int16_t temp = x0; x0 = x1; x1 = temp;
		temp = y0; y0 = y1; y1 = temp;
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1)
		ystep = 1;
	else
		ystep = -1;

	for (; x0 <= x1; x0++)
	{
		if (steep)
			this->drawPixel(y0, x0, color);
		else
			this->drawPixel(x0, y0, color);
		err -= dy;
		if (err < 0)
		{
			y0 += ystep;
			err += dx;
		}
	}
}

void GFX::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    this->drawLine(x, y, x + w - 1, y, color);
    this->drawLine(x, y + h - 1, x + w - 1, y + h - 1, color);
    this->drawLine(x, y, x, y + h - 1, color);
    this->drawLine(x + w - 1, y, x + w - 1, y + h - 1, color);
}

void GFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	for (int16_t i = x; i < x + w; i++)
	{
		for (int16_t j = y; j < y + h; j++)
		{
			this->drawPixel(i, j, color);
		}
	}
}

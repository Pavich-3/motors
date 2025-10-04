#include "GFX.hpp"

GFX::GFX(int16_t w, int16_t h) : _width(w), _height(h) {}

void GFX::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    int16_t dx = abs(x1 - x0);
    int16_t sx = x0 < x1 ? 1 : -1;
    int16_t dy = -abs(y1 - y0);
    int16_t sy = y0 < y1 ? 1 : -1;
    int16_t err = dx + dy;
    int16_t e2;

    for (;;) {
        drawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void GFX::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    drawLine(x, y, x + w - 1, y, color);
    drawLine(x, y + h - 1, x + w - 1, y + h - 1, color);
    drawLine(x, y, x, y + h - 1, color);
    drawLine(x + w - 1, y, x + w - 1, y + h - 1, color);
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


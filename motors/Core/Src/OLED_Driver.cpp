#include "OLED_Driver.hpp"

OLED_Driver::OLED_Driver(I2C_HandleTypeDef* i2cHandle) : GFX(OLED_WIDTH, OLED_HEIGHT), bus(i2cHandle)
{
	memset(framebuffer, 0 , sizeof(framebuffer));
}

void OLED_Driver::begin(void)
{
	this->sendCommand(0xAE);
	this->sendCommand(0xD5);
	this->sendCommand(0xA8);
	this->sendCommand(0xD3);
	this->sendCommand(0x40);
	this->sendCommand(0x8D);
	this->sendCommand(0x20);
	this->sendCommand(0xA1);
	this->sendCommand(0xC8);
	this->sendCommand(0xDA);
	this->sendCommand(0x81);
	this->sendCommand(0xD9);
	this->sendCommand(0xDB);
	this->sendCommand(0xA4);
	this->sendCommand(0xA6);
	this->sendCommand(0xAF);
	clearDisplay();
	display();
}

void OLED_Driver::display(void)
{
	this->sendCommand(0x21);
	this->sendCommand(0);
	this->sendCommand(OLED_WIDTH - 1);
	this->sendCommand(0x22);
	this->sendCommand(0);
	this->sendCommand(OLED_HEIGHT / 8 - 1);
	this->sendData(framebuffer, sizeof(framebuffer));
}

void OLED_Driver::clearDisplay()
{
	memset(framebuffer, 0, sizeof(framebuffer));
}

void OLED_Driver::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	uint16_t index = x + (y / 8) * OLED_WIDTH;

	if (color)
	   framebuffer[index] |= (1 << (y % 8));
	else
	   framebuffer[index] &= ~(1 << (y % 8));

}

void OLED_Driver::drawServo(uint16_t angle_deg)
{
	int16_t centerX = _width / 2;
	int16_t centerY = _height / 2;

	int16_t bodyWidth = 40;
	int16_t bodyHeight = 24;
	int16_t armLength = 28;

	this->clearDisplay();
	this->drawRect(centerX - bodyWidth / 2, centerY - bodyHeight / 2, bodyWidth, bodyHeight, 1);

	float angle_rad = (angle_deg - 90.0f) * (M_PI / 180.0f);
	int16_t endX = centerX + armLength * cos(angle_rad);
	int16_t endY = centerY + armLength * sin(angle_rad);

	this->drawLine(centerX, centerY, endX, endY, 1);

	this->display();
}

void OLED_Driver::sendCommand(uint8_t cmd)
{
	uint8_t buffer[2] = {0x00, cmd};
	this->bus.write(OLED_I2C_ADDR, buffer, 2);
}

void OLED_Driver::sendData(uint8_t* data, uint16_t size)
{
	uint8_t transmit_buffer[size + 1];
	transmit_buffer[0] = 0x40;
	memcpy(transmit_buffer + 1, data, size);
	this->bus.write(OLED_I2C_ADDR, transmit_buffer, size + 1);
}

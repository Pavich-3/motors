#include "OLED_Driver.hpp"
#include <math.h>

OLED_Driver::OLED_Driver(I2C_HandleTypeDef* i2cHandle) : GFX(OLED_WIDTH, OLED_HEIGHT), bus(i2cHandle)
{
	memset(framebuffer, 0 , sizeof(framebuffer));
}

void OLED_Driver::begin(void)
{
    sendCommand(0xAE);

    sendCommand(0xD5);
    sendCommand(0x80);

    sendCommand(0xA8);
    sendCommand(0x3F);

    sendCommand(0xD3);
    sendCommand(0x00);

    sendCommand(0x40 | 0x0);

    sendCommand(0x8D);
    sendCommand(0x14);

    sendCommand(0x20);
    sendCommand(0x00);

    sendCommand(0xA0 | 0x1);
    sendCommand(0xC8);

    sendCommand(0xDA);
    sendCommand(0x12);

    sendCommand(0x81);
    sendCommand(0xCF);

    sendCommand(0xD9);
    sendCommand(0xF1);

    sendCommand(0xDB);
    sendCommand(0x40);

    sendCommand(0xA4);
    sendCommand(0xA6);

    clearDisplay();
    display();

    sendCommand(0xAF);
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

void OLED_Driver::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }

    uint16_t index = x + (y / 8) * OLED_WIDTH;

    if (index >= sizeof(framebuffer)) {
        return;
    }

	if (color)
	   framebuffer[index] |= (1 << (y % 8));
	else
	   framebuffer[index] &= ~(1 << (y % 8));
}

void OLED_Driver::drawServo(uint16_t angle_deg) {
	clearDisplay();

    if (angle_deg > 180) {
        angle_deg = 180;
    }

    int16_t centerX = _width / 2;
    int16_t centerY = _height / 2;
    int16_t armLength = 28;

    drawRect(centerX - 20, centerY - 12, 40, 24, 1);

    float angle_rad = (180.0f - angle_deg) * 3.14159f / 180.0f;

    float endX_f = centerX + armLength * cosf(angle_rad);
    float endY_f = centerY + armLength * sinf(angle_rad);

    drawLine(centerX, centerY, (int16_t)endX_f, (int16_t)endY_f, 1);

    display();
}

void OLED_Driver::sendCommand(uint8_t cmd)
{
	uint8_t buffer[2] = {0x00, cmd};
	this->bus.writeBlocking(OLED_I2C_ADDR, buffer, 2, 100);
}

void OLED_Driver::sendData(uint8_t* data, uint16_t size)
{
    static uint8_t transmit_buffer[1025];
    transmit_buffer[0] = 0x40;
    memcpy(transmit_buffer + 1, data, size);

    this->bus.writeBlocking(OLED_I2C_ADDR, transmit_buffer, size + 1, 1000);
}

//void OLED_Driver::sendData(uint8_t* data, uint16_t size)
//{
//    static uint8_t transmit_buffer[1025];
//    transmit_buffer[0] = 0x40;
//    memcpy(transmit_buffer + 1, data, size);
//
//    while (HAL_I2C_GetState(bus.i2cHandle) != HAL_I2C_STATE_READY);
//
//    this->bus.writeDMA(OLED_I2C_ADDR, transmit_buffer, size + 1);
//
//    while (HAL_I2C_GetState(bus.i2cHandle) != HAL_I2C_STATE_READY);
//}

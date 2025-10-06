# STM32 Servo Control with Rotary Encoder and OLED Display

## Overview

This project is a real-time embedded system that demonstrates precise motor control and live data visualization. A standard rotary encoder is used to set the desired angle for a servo motor, and the servo's current position is rendered graphically on an I2C OLED display.

The core of this project is a highly efficient, **fully non-blocking I2C driver** that leverages DMA for both command and data transmissions. This ensures minimal CPU load and allows the system to remain responsive to other tasks.

***

## Demo

![Project Demo GIF](https://github.com/Pavich-3/motors/raw/main/IMG_3384-ezgif.com-resize.gif)

***

## Key Features

* **Real-time Position Tracking:** The servo's angle is updated instantly as the encoder is turned.
* **Smooth Servo Actuation:** PWM is used for precise and smooth control of the servo motor.
* **Live Data Visualization:** A custom graphical interface on the OLED display shows the servo's angle.
* **Efficient Performance:** The system operates with very low CPU overhead thanks to extensive use of DMA and interrupt-driven programming.

***

## Core Technical Concepts Demonstrated

This project showcases a deep understanding of modern embedded systems development practices and microcontroller peripherals.

### 1. Advanced Peripheral Management
* **Timers:** Configured multiple timers for three distinct tasks simultaneously:
    * `TIM2`: In **Encoder Mode** to read the rotary encoder's position.
    * `TIM1`: In **PWM Generation Mode** to control the servo motor.
    * `TIM3`: As a periodic trigger for DMA transfers.
* **I2C:** Used for communication with the OLED display.
* **GPIO:** Configured for alternate functions for all peripherals.

### 2. Direct Memory Access (DMA)
The CPU is offloaded from repetitive data transfer tasks by using DMA for:
* **Encoder Reading:** A timer-triggered DMA transfer (`TIM3`) continuously captures the encoder's counter value (`TIM2->CNT`) into memory without any CPU intervention. This is a peripheral-to-memory transfer.
* **I2C Display Driver:** A fully asynchronous I2C driver was developed.
    * It uses **memory-to-peripheral DMA** to send both short commands (2 bytes) and the entire framebuffer (1025 bytes) to the OLED display.
    * This frees the CPU from polling `TXE` flags, allowing it to perform other tasks while the screen updates in the background.

### 3. Interrupt Handling & System Architecture
* **Robust Interrupt Management:** The system relies on DMA and I2C event/error interrupts to handle all data transfers asynchronously.
* **Prevention of ISR Blocking:** Implemented a safe and robust software architecture using a **flag-and-poll mechanism**. The DMA completion callback (which runs in an ISR context) only sets a flag, while the "heavy" work of updating the display is handled in the main `while(1)` loop. This is a critical practice to avoid deadlocks and maintain system stability.

### 4. Hardware and Power Considerations
* The project demonstrates an understanding of hardware-level issues, such as mitigating electrical noise from the servo motor by lowering the I2C bus speed to enhance signal integrity.

***

## Hardware Components

* **Microcontroller:** STM32F4xx series
* **Motor:** SG90 micro servo or similar
* **Input:** KY-040 Rotary Encoder module
* **Display:** SSD1306 I2C OLED Display
* **Misc:** Breadboard, jumper wires, and a separate 5V power supply for the servo (recommended).

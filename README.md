# STM32f103C8T6 DHT11 LCD16x2 Project

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![STM32](https://img.shields.io/badge/STM32-F103C8T6-blue)
![CubeIDE](https://img.shields.io/badge/IDE-STM32CubeIDE-darkblue)

## Video Demonstration

https://github.com/user-attachments/assets/918d25ad-6c64-4fc3-ba8d-22d86707c7c0

## Project Overview

This project implements a temperature and humidity monitoring system using an **STM32F103C8T6 (Blue Pill)** microcontroller, a **DHT11 sensor**, and a **16x2 I2C LCD** display. The system reads environmental data from the DHT11 sensor and displays both temperature and humidity in real-time on the LCD screen. This project uses the **STM32 HAL Library** for coding. The system runs at **72 MHz** using HSE external crystal and PLL.

For a **Bare Metal version** of this project with **UART** output:<br>
🔗 [STM32_DHT11_UART_BareMetal](https://github.com/rubin-khadka/STM32_DHT11_UART_BareMetal)

### Hardware Components

| Component | Description | Notes |
|-----------|-------------|-------|
| **STM32F103C8T6** | "Blue Pill" board | 72MHz Cortex-M3 MCU |
| **DHT11 Sensor** | Temperature & Humidity | 3.3V-5V, 1-wire protocol |
| **16x2 LCD with I2C Module** | 16x2 Character Display | PCF8574 I2C backpack, 4-bit mode |

## Pin Configuration

### I2C LCD Connections

| LCD Pin | STM32 Pin |
|-----------|-------------|
| **VCC** | 5V |
| **GND** | GND | 
| **SDA** | PB9 (I2C1 SDA) |
| **SCL** | PB8 (I2C1 SCL) |

The I2C on STM32 is configured in **standard mode at 100kHz** for reliable communication with the PCF8574 backpack.

🔗 [View I2C LCD Driver Source Code](https://github.com/rubin-khadka/STM32_DHT11_LCD16x2/blob/main/Core/Src/i2c_lcd.c)

The **Slave Device Address** is set to **0x4E** (8-bit address) which corresponds to the common PCF8574 address 0x27 (7-bit).

### DHT11 Sensor Connections

| DHT11 Pin | STM32 Pin |
|-----------|-------------|
| **VCC** | 5V |
| **GND** | GND | 
| **DATA** | PA0 |

**Note**: The I2C lines (SDA/SCL) and DHT11 Data line require pull-up resistors to VCC. Both of these modules normally have the pull-up resistors built into the module.

### Timer Configuration

**TIMER2** is configured in microsecond precision mode to handle the precise timing requirements of the DHT11 sensor. This is critical because the DHT11 uses a single-wire protocol with microsecond-level timing.
```C
// Timer2 initialized for 1µs precision
htim2.Init.Prescaler = 72 - 1;  // 72MHz/72 = 1MHz,  1µs per tick
```

### DHT11 Sensor Driver
The DHT11 uses a **single-wire protocol** with precise timing:
| Phase | Duration | Description |
|-------|----------|-------------|
| **Start Signal** | 18ms LOW + 20µs HIGH | MCU wakes sensor |
| **Sensor Response** | 80µs LOW + 80µs HIGH | Sensor acknowledges |
| **Bit "0"** | 50µs LOW + 26-28µs HIGH | Logic 0 |
| **Bit "1"** | 50µs LOW + 70µs HIGH | Logic 1 |
| **Data Frame** | 40 bits | 5 bytes (humidity ×2 + temp ×2 + checksum) |

The conventional method for reading DHT11 involves measuring the exact width of the HIGH pulses:
- If HIGH pulse ≈ 28µs → logic 0
- If HIGH pulse ≈ 70µs → logic 1

This requires precise microsecond measurements and can be tricky to implement reliably.<br>
Instead of measuring pulse widths, I used a different approach based on the timing diagram:

For each bit:
1. Wait for line to go HIGH
2. Delay exactly 40µs
3. If line still HIGH → logic 1 and If line is LOW → logic 0

🔗 [View DHT11 Driver Source Code](https://github.com/rubin-khadka/STM32_DHT11_LCD16x2/blob/main/Core/Src/dht11.c)

## Setup

### Prerequisites
| Components | Details |
|------|---------|
| **MCU** | STM32F103C8T6 "Blue Pill" |
| **Sensor** | DHT11 Temperature & Humidity Sensor | 
| **Display** | 16x2 LCD with I2C module (PCF8574) |
| **Programmer** | ST-Link V2 |
| **IDE** | STM32cube |

1. Clone this repository
```bash
git clone https://github.com/rubin-khadka/STM32_DHT11_LCD16x2.git
```
2. Open **CubeMX** file `STM32_DHT11_LCD16x2.ioc` in STM32CubeMX

3. `Generate code` in CubeMX - this will open the project in `STM32CubeIDE`

4. Build the project and test it with Actual hardware.

### Expected Output
```bash
TEMP: 24.0 C
HUMD: 45.0 %
```
## Resources
- [STM32F103 Datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf)
- [STM32F103 Reference Manual](https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [DHT11 Sensor Datasheet](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf)

## Project Status
- **Status**: Complete
- **Version**: v1.0
- **Last Updated**: February 2026

## Contact
**Rubin Khadka Chhetri**  
📧 rubin.robotic@gmail.com  
🐙 GitHub: https://github.com/rubin-khadka

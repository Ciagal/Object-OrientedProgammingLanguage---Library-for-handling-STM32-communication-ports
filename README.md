# Library for handling STM32 Nucleo-L476RG communication ports

A generic C++ library for handling communication protocols on the **STM32 Nucleo-L476RG** microcontroller.

## Overview

This project implements a modular and extensible library that abstracts communication interfaces such as **UART**, **I2C**, and **SPI**. It is designed for use with the **STM32 HAL** library and was configured using **STM32CubeMX** within **STM32CubeIDE**.

Core functionalities include:
- Base class `CommunicationBase` for unified interface
- Derived classes for each protocol (UART, I2C, SPI)
- Basic methods for initialization, sending, and receiving data
- Example integrations with BME280 and SHT35 sensors for SPI and I2C (data parsing not included, used for transmission testing)
- Data output through UART for validation

## Setup & Configuration

To get started:

1. **Clone the repository**
2. Create a new project in **STM32CubeIDE** with:
   - Board: `Nucleo-L476RG`
   - Language: `C++`
3. Enable the following peripherals in `.ioc` configuration:
   - I2C1
   - SPI1
   - USART2 (set to asynchronous mode)
4. In **Clock Configuration** tab:
   - Use HSI (High Speed Internal)
   - Configure clocks as shown in the project screenshots (or use default HAL-recommended values)
5. Generate the project code
6. Replace the auto-generated files with those from this repository

##  Hardware Connections

**Testing UART only:** You can use the onboard ST-Link without any peripherals.

**Testing I2C and SPI:** Connect the following sensors:

### SHT35 (I2C)

| Pin | STM32 Pin |
|-----|-----------|
| SDA | PB7       |
| SCL | PB6       |
| VCC | 3.3V      |
| GND | GND       |

### BME280 (SPI)

| Pin | STM32 Pin |
|-----|-----------|
| VCC | 3.3V      |
| GND | GND       |
| CSB | PC13      |
| SDO | PA6       |
| SDA | PA7       |
| SCL | PA5       |

> **Note:** Sensor data is not processed or converted to physical values. The sensors are used only to verify data transmission.

## Testing

The `main.cpp` file contains basic test routines for sending and receiving data through all supported protocols. The `CommunicationLib.hpp` serves as a wrapper to centralize handler definitions.

## Project Info

- **University:** AGH University of Science and Technology  
- **Course:** Object-Oriented Programming Languages  
- **Field:** Electronics and Telecommunications, 3rd Year  
- **Author:** Michał Ciągała  
- **Instructor:** Jakub Zimnol  
- **Date:** 09.01.2025

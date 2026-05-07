# ESP32 connect STM32 with UART

## Project Structure
- Code_ESP32: ESP32 code using ESP-IDF framework
- Code_STM32: STM32 code using STM32CubeIDE

## Hardware Setup
- ESP32 Development Board
- STM32F411CEU6 Board
- UART Connection:
  - ESP32 TX (GPIO1) -> STM32 RX (PA10) 
  - ESP32 RX (GPIO3) -> STM32 TX (PA9)
  - Common Ground

## Software Requirements
- ESP-IDF (for ESP32 code)
- STM32CubeIDE (for STM32 code)

## Configuration
- UART Baudrate: 115200
- Data bits: 8
- Stop bits: 1
- Parity: None
- Flow Control: None
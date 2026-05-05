# STM32 Fundamentals

A personal collection of hands-on exercises and peripheral testing projects built on the **STM32F411CE** microcontroller. Each module focuses on a specific peripheral or concept, demonstrating practical understanding of embedded systems programming using the STM32 HAL library.

---

## Skills Demonstrated

- Configuring STM32 peripherals using **STM32CubeMX** and implementing firmware with the **HAL library**
- Working with **GPIO**, **UART**, **I2C**, **DMA**, and **NVIC interrupt** systems on STM32F4
- Interfacing external components (OLED display, I2C LCD, push buttons) with proper wiring and driver integration
- Flashing and debugging embedded firmware using **STM32CubeIDE** and **ST-Link V2**

---

## Projects

| Project | Description | Peripherals Used |
|---|---|---|
| **Blink_Led** | Basic GPIO output — blink an onboard LED | GPIO |
| **Nhapnhay_LED** | LED blink patterns with timing control | GPIO, SysTick |
| **ReadButton_State** | Read digital input from a push button | GPIO Input |
| **GPIO_EXTI** | Trigger actions via external interrupt pin | GPIO, EXTI |
| **Interrupts_Ngat_ngoai** | External interrupt handling practice | NVIC, EXTI |
| **System_exception** | Explore HardFault and system exception behavior | NVIC, CoreDebug |
| **MemorySTM32** | Understand flash/RAM memory layout and usage | Memory mapping |
| **I2C_STM32** | I2C communication basics | I2C, HAL |
| **Test_I2C_LCD** | Drive a character LCD over I2C | I2C, LCD |
| **Test_oled** | Display graphics on a 128x64 SSD1306 OLED | I2C, SSD1306 |
| **UART_Thuchanh** | UART send/receive practice | USART |
| **UART_Intterrupt** | UART communication via interrupt | USART, NVIC |
| **UART_Intterrupt_EX** | Extended UART interrupt handling | USART, NVIC |
| **UART_DMA** | UART data transfer using DMA | USART, DMA |

---

## Hardware

- **MCU**: STM32F411CEU6 (Black Pill board)
- **Clock**: Up to 100 MHz (Cortex-M4)
- **External components**: LEDs, push buttons, SSD1306 OLED, I2C LCD, USB-UART adapter

## Development Environment

| Tool | Purpose |
|---|---|
| STM32CubeIDE | IDE, compiler (GCC), debugger |
| STM32CubeMX | Peripheral configuration and code generation |
| STM32 HAL Library | Hardware abstraction layer |
| ST-Link V2 | Flashing and debugging |

---

> These projects were built individually to explore and validate understanding of each STM32 peripheral. They serve as a reference for embedded systems fundamentals.
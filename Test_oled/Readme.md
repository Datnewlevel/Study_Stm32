# STM32 OLED Display with SSD1306 Driver

A simple project demonstrating how to interface an OLED display with STM32F411CE microcontroller using I2C communication protocol and SSD1306 driver.

## 📋 Overview

This project shows how to connect and control a 128x64 OLED display using the SSD1306 driver. The display communicates with the STM32 microcontroller via I2C protocol, making it easy to display text, graphics, and animations.

## 🔧 Hardware Requirements

- **STM32F411CE** microcontroller (Black Pill board)
- **SSD1306 OLED Display** (128x64 pixels, I2C interface)
- **Connecting wires**
- **Breadboard** (optional)

## 📱 OLED Display Specifications

- **Resolution**: 128x64 pixels
- **Driver**: SSD1306
- **Interface**: I2C (4-pin)
- **Operating Voltage**: 3.3V - 5V
- **Display Color**: Monochrome (Blue/White/Yellow)

## 🔌 Pin Connections

| OLED Pin | STM32F411CE Pin | Description |
|----------|-----------------|-------------|
| **GND**  | GND            | Ground      |
| **VCC**  | 3.3V           | Power Supply|
| **SCL**  | PB6 (I2C1_SCL) | Clock Line  |
| **SDA**  | PB7 (I2C1_SDA) | Data Line   |

```
OLED Display          STM32F411CE
┌─────────────┐      ┌─────────────┐
│    ┌───┐    │      │             │
│    │   │    │      │         PB6 ├──── SCL
│    │ █ │    │      │         PB7 ├──── SDA
│    │   │    │      │         3V3 ├──── VCC
│    └───┘    │      │         GND ├──── GND
└─────────────┘      └─────────────┘
```

## 🚀 Features

- ✅ Display text in different fonts
- ✅ Draw basic shapes (lines, rectangles, circles)
- ✅ Display images/bitmaps
- ✅ Scroll text animations
- ✅ Multiple font sizes support
- ✅ Pixel-level control

## 📁 Project Structure

```
Test_oled/
├── Core/
│   ├── Inc/
│   │   ├── main.h
│   │   ├── ssd1306.h          # SSD1306 driver header
│   │   ├── ssd1306_conf.h     # Configuration file
│   │   ├── ssd1306_fonts.h    # Font definitions
│   │   └── ssd1306_tests.h    # Test functions
│   └── Src/
│       ├── main.c             # Main application
│       ├── ssd1306.c          # SSD1306 driver implementation
│       ├── ssd1306_fonts.c    # Font data
│       └── ssd1306_tests.c    # Test implementations
├── Drivers/                   # STM32 HAL drivers
└── README.md
```

## ⚙️ Setup Instructions

### 1. Hardware Setup
1. Connect the OLED display to STM32 according to the pin diagram above
2. Ensure proper power supply (3.3V recommended)
3. Double-check all connections

### 2. Software Setup
1. Open the project in **STM32CubeIDE**
2. Configure I2C1 peripheral in CubeMX:
   - **Mode**: I2C
   - **Speed**: Standard Mode (100 KHz)
   - **Pins**: PB6 (SCL), PB7 (SDA)
3. Build and flash the project

### 3. Code Configuration
```c
// In ssd1306_conf.h
#define SSD1306_I2C_PORT        hi2c1
#define SSD1306_I2C_ADDR        (0x3C << 1)  // Default I2C address
#define SSD1306_WIDTH           128
#define SSD1306_HEIGHT          64
```

## 💻 Basic Usage

### Initialize Display
```c
#include "ssd1306.h"

int main(void) {
    // HAL initialization
    HAL_Init();
    SystemClock_Config();
    MX_I2C1_Init();
    
    // Initialize OLED
    ssd1306_Init();
    
    // Clear screen
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();
    
    while(1) {
        // Your code here
    }
}
```

### Display Text
```c
// Set cursor position
ssd1306_SetCursor(2, 0);

// Write string
ssd1306_WriteString("Hello STM32!", Font_11x18, White);

// Update display
ssd1306_UpdateScreen();
```

### Draw Shapes
```c
// Draw rectangle
ssd1306_DrawRectangle(10, 10, 50, 30, White);

// Draw circle
ssd1306_DrawCircle(64, 32, 20, White);

// Draw line
ssd1306_Line(0, 0, 127, 63, White);

// Update display
ssd1306_UpdateScreen();
```

## 🎯 Example Output

The display will show:
- Welcome message
- Real-time counter
- Basic graphics demonstration
- Font size examples

## 🛠️ Troubleshooting

| Problem | Solution |
|---------|----------|
| Display not working | Check I2C connections and address |
| Garbled text | Verify font configuration |
| No display output | Check power supply and initialization |
| I2C communication error | Verify SCL/SDA pin assignment |

## 📚 API Reference

### Core Functions
- `ssd1306_Init()` - Initialize the display
- `ssd1306_UpdateScreen()` - Refresh display buffer
- `ssd1306_Fill(color)` - Fill entire screen
- `ssd1306_SetCursor(x, y)` - Set text cursor position

### Text Functions
- `ssd1306_WriteString(str, font, color)` - Write text
- `ssd1306_WriteChar(ch, font, color)` - Write single character

### Graphics Functions
- `ssd1306_DrawPixel(x, y, color)` - Draw pixel
- `ssd1306_DrawLine(x0, y0, x1, y1, color)` - Draw line
- `ssd1306_DrawRectangle(x, y, w, h, color)` - Draw rectangle
- `ssd1306_DrawCircle(x, y, r, color)` - Draw circle

## 🤝 Contributing

Feel free to submit issues and enhancement requests!

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

---

**Happy Coding! 🚀**

*Made with ❤️ for STM32 learning*
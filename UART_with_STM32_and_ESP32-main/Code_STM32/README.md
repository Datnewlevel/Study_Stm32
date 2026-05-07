# STM32F411CEU6 - UART LED Controller

## Chức năng
- Nhận lệnh chuỗi "ON" hoặc "OFF" qua UART.
- Bật/tắt LED nối chân PA5 tương ứng với lệnh nhận được.

## Sơ đồ kết nối
- LED nối với chân PA5 (có thể thay đổi tùy ý).
- UART kết nối với ESP32:
  - TX (ESP32) -> RX (STM32, thường là PA10)
  - RX (ESP32) -> TX (STM32, thường là PA9)
  - GND nối chung

## Lưu ý
- Tốc độ baud UART: 115200
- Lệnh nhận: "ON\n" hoặc "OFF\n"
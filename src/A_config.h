// #ifndef config_h
// #define config_h

// // ===== DISPLAY LIBRARY ===== //
// #include "SH1106Spi.h"
// #include "SH1106Wire.h"
// #include "SSD1306Spi.h"
// #include "SSD1306Wire.h"
// #include <SPI.h>
// #include <Wire.h>
// // =========================== //

// // #define OLED_096_I2C
// #define OLED_13_I2C
// // #define OLED_096_SPI
// // #define OLED_13_SPI

// // ===================== DISPLAY CONFIG ==================== //
// #define USE_DISPLAY true // default display setting

// #ifdef ESP32

// // BUTTON Define
// #define BUTTON_UP 34
// #define BUTTON_DOWN 36
// #define BUTTON_A 39
// #define BUTTON_LEFT 33
// #define BUTTON_RIGHT 32

// // BUTTON Define
// #define OUTPUT_DEFAULT 10
// #define INPUT_DEFAULT 11

// #define SOFTWARE_SERIAL_RX 12
// #define SOFTWARE_SERIAL_TX 13

// #define SDA_SENSOR_DEFAULT 22
// #define SCL_SENSOR_DEFAULT 21

// #define ANALOG_DEFAULT A0

// #ifdef OLED_096_I2C
// // for 0.96" OLED
// #define DEAUTHER_DISPLAY SSD1306Wire display = SSD1306Wire(0x3c, 21, 22);
// #endif

// #ifdef OLED_13_I2C
// // for 1.3" OLED
// #define DEAUTHER_DISPLAY SH1106Wire display = SH1106Wire(0x3c, 21, 22);
// #endif

// #ifdef OLED_096_SPI
// // for0.96" OLED with SPI
// #define DEAUTHER_DISPLAY SSD1306Spi display = SSD1306Spi(5, 4, 15);
// #endif

// #ifdef OLED_13_SPI
// // for 1.3" OLED with SPI
// #define DEAUTHER_DISPLAY SH1106Spi display = SH1106Spi(5, 4, 15);
// #endif

// #else
// #define BUTTON_UP 13
// #define BUTTON_DOWN 12
// #define BUTTON_A 14

// // SENSOR INPUT AND OUTPUT PIN
// #define OUTPUT_DEFAULT D0
// #define INPUT_DEFAULT D3

// #define SOFTWARE_SERIAL_RX D3
// #define SOFTWARE_SERIAL_TX D4

// #define SDA_SENSOR_DEFAULT D3
// #define SCL_SENSOR_DEFAULT D4

// #ifdef OLED_096_I2C
// // for 0.96" OLED
// #define DEAUTHER_DISPLAY SSD1306Wire display = SSD1306Wire(0x3c, 5, 4);
// #endif

// #ifdef OLED_13_I2C
// // for1.3 " OLED
// #define DEAUTHER_DISPLAY SH1106Wire display = SH1106Wire(0x3c, 5, 4);
// #endif

// #ifdef OLED_096_SPI
// // for0.96" OLED with SPI
// #define DEAUTHER_DISPLAY SSD1306Spi display = SSD1306Spi(5, 4, 15);
// #endif

// #ifdef OLED_13_SPI
// // for 1.3" OLED with SPI
// #define DEAUTHER_DISPLAY SH1106Spi display = SH1106Spi(5, 4, 15);
// #endif

// /*  RST = GPIO 5 (D1)
//     DC = GPIO 4 (D2)
//     CS = GPIO 15 (D8) or GND
//     SCK/SCL = GPIO 14 (D5)
//     SDA/MOSI = GPIO 13 (D7) */

// #endif

// #endif

# Arduino Nano Earthquake Early Warning System - Wiring Diagram

## Component Pinout Table

| Component | Pin | Arduino Nano Pin | Notes |
|---|---|---|---|
| **MPU6050 Accelerometer** | VCC | `5V` | Sensor Power |
| | GND | `GND` | Common Ground |
| | SCL | `A5` | I2C Clock |
| | SDA | `A4` | I2C Data |
| **0.96" SSD1306 OLED** | VCC | `5V` | Display Power |
| | GND | `GND` | Common Ground |
| | SCL | `A5` | I2C Clock (Shared) |
| | SDA | `A4` | I2C Data (Shared) |
| **Piezo Buzzer** | Positive (+) | `Digital Pin 8` | PWM Audio Alarm Signal |
| | Negative (-) | `GND` | Ground |
| **Red Hazard LED** | Anode (+) | `Digital Pin 7` | 220Ω Resistor to Pin 7 |
| | Cathode (-) | `GND` | Ground |
| **Green Safe LED** | Anode (+) | `Digital Pin 6` | 220Ω Resistor to Pin 6 |
| | Cathode (-) | `GND` | Ground |

---

## I2C Bus Connections

Both the **MPU6050** (`0x68`) and **SSD1306 OLED** (`0x3C`) connect in parallel to the Arduino Nano I2C bus:

```
                  +-----------------------+
                  |  Arduino Nano (A4/A5) |
                  +-----------------------+
                             | |
              +--------------+ +--------------+
              | (SDA)                     | (SCL)
              |                           |
       +--------------+            +--------------+
       |   MPU6050    |            | SSD1306 OLED |
       | (Addr: 0x68) |            | (Addr: 0x3C) |
       +--------------+            +--------------+
```

---

## Circuit Schematic Overview

```
                      +-------------------+
                      |   ARDUINO NANO    |
                      |                   |
   5V ---------------| VCC               |
  GND ---------------| GND               |
                     |                    |
   A4 (SDA) ---------| SDA  (MPU6050 &   |
   A5 (SCL) ---------| SCL   OLED Display)|
                     |                    |
   Pin 8 ------------| PWM -> Piezo Buzzer|---> GND
   Pin 7 ------------| [220Ω] -> Red LED |---> GND
   Pin 6 ------------| [220Ω] -> Green LED|--> GND
                      +-------------------+
```

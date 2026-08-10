# Arduino Nano Earthquake Early Warning System (U8g2 OLED Driver)

A 100% C++ **Embedded Earthquake Detection & Early Warning System** running on an **Arduino Nano (ATmega328P)** using an **MPU6050 6-DOF Accelerometer**, **0.96" SSD1306 OLED Display (U8g2 Library)**, **Piezo Buzzer Alarm**, and **Red/Green Hazard Status LEDs**.

---

## Component Hardware List & Pinout

| Component | Pin Name | Arduino Nano Connection | Notes |
|---|---|---|---|
| **Arduino Nano** | - | Microcontroller Board | 5V Operating Voltage |
| **MPU6050 Accelerometer** | VCC | `5V` | Sensor Power |
| | GND | `GND` | Ground |
| | SCL | `A5` | I2C Clock |
| | SDA | `A4` | I2C Data |
| **SSD1306 OLED (128x64)** | VCC | `5V` | Display Power |
| | GND | `GND` | Ground |
| | SCL | `A5` | Shared I2C Clock |
| | SDA | `A4` | Shared I2C Data |
| **Piezo Buzzer** | Positive (+) | `Digital Pin 8` | PWM Audio Alarm Signal |
| | Negative (-) | `GND` | Ground |
| **Red Hazard LED** | Anode (+) | `Digital Pin 7` | Series 220Ω Resistor to Pin 7 |
| | Cathode (-) | `GND` | Ground |
| **Green Safe LED** | Anode (+) | `Digital Pin 6` | Series 220Ω Resistor to Pin 6 |
| | Cathode (-) | `GND` | Ground |

---

## Circuit Schematic Overview

```
                      +-------------------+
                      |   ARDUINO NANO    |
                      |                   |
   5V ----------------| VCC               |
  GND ----------------| GND               |
                      |                   |
   A4 (SDA) ----------| SDA  (MPU6050 &   |
   A5 (SCL) ----------| SCL   OLED Display)|
                      |                   |
   Pin 8 -------------| PWM -> Piezo Buzzer|---> GND
   Pin 7 -------------| [220Ω] -> Red LED  |---> GND
   Pin 6 -------------| [220Ω] -> Green LED |---> GND
                      +-------------------+
```

---

## Required Arduino IDE Libraries

Install the following official library via Arduino IDE **Library Manager** (`Ctrl+Shift+I`):
- **U8g2** by Oliver Kraus (`U8g2lib.h`)

---

## System Operational States

- **NOMINAL SAFE STATE** ($\text{PGA} < 0.15g$):
  - Green LED: **ON**
  - Red LED & Buzzer: **OFF**
  - OLED Display: Displays `PGA: 0.000 g`, `Richter: M 0.0`, `STATUS: SAFE`.

- **WARNING STATE** ($0.15g \le \text{PGA} < 0.35g$):
  - Green LED & Red LED: **ON**
  - OLED Display: Displays `STATUS: SEISMIC ACTIVITY`.

- **EARTHQUAKE ALERT STATE** ($\text{PGA} \ge 0.35g$):
  - Green LED: **OFF**
  - Red LED: **HIGH**
  - Piezo Buzzer: **PULSING 2kHz HIGH-DECIBEL ALARM TONE**
  - OLED Display: Displays `STATUS: EARTHQUAKE ALERT!`.

---

## Project Directory

```
earthquake_monitoring_system/
├── arduino_earthquake_alarm/
│   └── arduino_earthquake_alarm.ino   # Arduino C++ Sketch with U8g2 Driver
├── WIRING_DIAGRAM.md                  # Hardware Pinout Schematic
└── README.md                          # Documentation
```

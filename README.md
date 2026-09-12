# 🌍 Real-Time Earthquake Monitoring & Seismic Early Warning System

[![GitHub Repository](https://img.shields.io/badge/GitHub-Repository-00f0ff?style=for-the-badge&logo=github&logoColor=white)](https://github.com/ALWINTR/earthquake-monitoring-system)
[![Developer](https://img.shields.io/badge/Developer-Alwin_T_R-0284c7?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/alwintr)
[![Platform](https://img.shields.io/badge/Platform-Arduino_Nano_%26_ADXL335-38bdf8?style=for-the-badge&logo=arduino&logoColor=white)](https://github.com/ALWINTR)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

A high-sensitivity real-time seismic vibration monitoring and early warning system powered by Arduino and an ADXL335 3-Axis Analog Accelerometer / MPU6050, featuring 10-bit ADC vector magnitude sampling, dynamic baseline calibration, low-pass digital noise filtering, OLED waveform rendering, and acoustic alarm sirens.

---

## 📌 Seismic Detection Theory & Vector Model

Seismic ground motion introduces acceleration vectors across three spatial orthogonal axes (\(X, Y, Z\)). The total instantaneous gravitational and inertial vector magnitude \( |A| \) is given by:

$$\|A\| = \sqrt{A_x^2 + A_y^2 + A_z^2}$$

In a stationary resting state, \( |A| = 1.0	ext{g} \) (gravitational constant). When seismic P-waves (primary compressive waves) or destructive S-waves (shear waves) arrive, the net dynamic acceleration delta \( \Delta A \) spikes:

$$\Delta A = | \|A\| - 1.0	ext{g} |$$

When \( \Delta A > 	ext{Threshold}_{	ext{Seismic}} \), the early warning alarm triggers instantaneously.

---

## ⚙️ Hardware Bill of Materials (BOM)

| Component | Technical Specification | Function |
| :--- | :--- | :--- |
| **Microcontroller** | Arduino Nano (ATmega328P, 16MHz) | High-speed ADC oversampling & alert FSM |
| **Accelerometer** | ADXL335 (±3g Tri-Axial Analog Sensor) | Dynamic seismic acceleration sensing |
| **Visual Display** | SSD1306 0.96" I2C OLED Display (128x64) | Real-time waveform & Richter magnitude display |
| **Acoustic Alarm** | 5V High-Decibel Active Piezo Siren | Immediate emergency audible warning |
| **Status Indicators** | Tri-Color RGB Status LED Array | Green (Normal), Yellow (Tremor), Red (Severe) |
| **Power Input** | 9V DC / USB 5V Regulated Rail | Low-noise analog power rail |

---

## 🔌 Circuit Pinout Table

| Sensor / Module Pin | Arduino Nano Pin | Signal Type | Description |
| :--- | :--- | :--- | :--- |
| **ADXL335 X_OUT** | Analog Pin A0 | 10-Bit ADC In | X-Axis horizontal acceleration |
| **ADXL335 Y_OUT** | Analog Pin A1 | 10-Bit ADC In | Y-Axis horizontal acceleration |
| **ADXL335 Z_OUT** | Analog Pin A2 | 10-Bit ADC In | Z-Axis vertical acceleration |
| **OLED SDA** | Analog Pin A4 | I2C Data Bus | SSD1306 graphics datastream |
| **OLED SCL** | Analog Pin A5 | I2C Clock Bus | SSD1306 serial clock |
| **Piezo Siren (+)** | Digital Pin D8 | Digital Output | Emergency siren alarm trigger |
| **LED Green (Normal)** | Digital Pin D11 | Digital Output | Ambient steady-state indicator |
| **LED Red (Alarm)** | Digital Pin D12 | Digital Output | Seismic alert warning indicator |

---

## 🧠 Firmware Architecture & Filter Algorithms

The Arduino firmware (`arduino_earthquake_alarm/arduino_earthquake_alarm.ino`) executes a 100Hz discrete sampling loop:
1. **Oversampling & ADC Averaging**: Samples 16 consecutive ADC readings per channel to suppress high-frequency electrical noise.
2. **Exponential Moving Average (EMA) Baseline**: Continuously updates the steady-state baseline reference to eliminate thermal drift:
   $$B_k = lpha \cdot A_k + (1 - lpha) \cdot B_{k-1} \quad (lpha = 0.05)$$
3. **Threshold Discrimination**:
   - Level 0 (\( \Delta A < 0.08	ext{g} \)): Ambient Background Noise (Safe).
   - Level 1 (\( 0.08	ext{g} \le \Delta A < 0.25	ext{g} \)): Minor Tremor / Micro-Seismic Activity.
   - Level 2 (\( \Delta A \ge 0.25	ext{g} \)): Major Earthquake Warning -> Continuous Siren.

---

## 🚀 Installation & Calibration Guide

1. Clone repository:
   ```bash
   git clone https://github.com/ALWINTR/earthquake-monitoring-system.git
   ```
2. Open in Arduino IDE.
3. Install the **U8g2** OLED graphics library:
   - In Arduino IDE -> Library Manager -> Search `U8g2` -> Install.
4. Mount the ADXL335 sensor rigidly to a flat horizontal surface to ensure accurate ground coupling.
5. Upload code to **Arduino Nano** at 115200 baud.

---

## 👨‍💻 Author

**Alwin T R** — Robotics & Automation Engineer  
- 💼 LinkedIn: [linkedin.com/in/alwintr](https://www.linkedin.com/in/alwintr)  
- 🌌 Portfolio: [alwintr.github.io](https://alwintr.github.io)  
- 💻 GitHub: [github.com/ALWINTR](https://github.com/ALWINTR)

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

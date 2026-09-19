# Real Time Seismic Vibration and Earthquake Early Warning System

[![GitHub Repository](https://img.shields.io/badge/GitHub-Repository-00f0ff?style=for-the-badge&logo=github&logoColor=white)](https://github.com/ALWINTR/earthquake-monitoring-system)
[![Developer](https://img.shields.io/badge/Developer-Alwin_T_R-0284c7?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/alwintr)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

A high-sensitivity real-time seismic vibration monitoring and early warning system powered by Arduino and an ADXL335 3-Axis Analog Accelerometer / MPU6050, featuring 10-bit ADC vector magnitude sampling, dynamic baseline calibration, low-pass digital noise filtering, OLED waveform rendering, and acoustic alarm sirens.

---

## Seismic Detection Theory and Vector Calculation

Seismic ground motion introduces acceleration vectors across three spatial orthogonal axes (X, Y, Z). The total instantaneous gravitational and inertial vector magnitude is given by:

$$|A| = \sqrt{A_x^2 + A_y^2 + A_z^2}$$

In a stationary resting state, $|A| = 1.0\text{g}$ (gravitational constant). When seismic P-waves or destructive S-waves arrive, the net dynamic acceleration delta spikes:

$$\Delta A = | |A| - 1.0\text{g} |$$

When $\Delta A > \text{Threshold}$, the early warning alarm triggers instantaneously.

---

## Hardware Bill of Materials (BOM)

| Component | Technical Specification | Functional Role |
| :--- | :--- | :--- |
| **Microcontroller** | Arduino Nano (ATmega328P, 16MHz) | High-speed ADC oversampling and alert FSM |
| **Accelerometer** | ADXL335 (3-Axis Analog Accelerometer) | Dynamic seismic acceleration sensing |
| **Visual Display** | SSD1306 0.96" I2C OLED Display (128x64) | Real-time waveform and magnitude display |
| **Acoustic Alarm** | 5V High-Decibel Active Piezo Siren | Immediate emergency audible alert |
| **Status Indicators** | Tri-Color Status LED Array | Normal (Green), Warning (Yellow), Alarm (Red) |

---

## Circuit Pinout Table

| Module Pin | Arduino Nano Pin | Signal Type | Description |
| :--- | :--- | :--- | :--- |
| **ADXL335 X_OUT** | Analog Pin A0 | 10-Bit ADC In | X-Axis horizontal acceleration |
| **ADXL335 Y_OUT** | Analog Pin A1 | 10-Bit ADC In | Y-Axis horizontal acceleration |
| **ADXL335 Z_OUT** | Analog Pin A2 | 10-Bit ADC In | Z-Axis vertical acceleration |
| **OLED SDA** | Analog Pin A4 | I2C Data Bus | SSD1306 graphics datastream |
| **OLED SCL** | Analog Pin A5 | I2C Clock Bus | SSD1306 serial clock line |
| **Piezo Siren (+)** | Digital Pin D8 | Digital Output | Emergency siren alarm trigger |
| **Status Green LED** | Digital Pin D11 | Digital Output | Steady-state normal indicator |
| **Status Red LED** | Digital Pin D12 | Digital Output | Seismic alert warning indicator |

---

## Author

**Alwin T R** - Robotics and Automation Engineer  
- LinkedIn: [linkedin.com/in/alwintr](https://www.linkedin.com/in/alwintr)  
- Portfolio: [alwintr.github.io](https://alwintr.github.io)  
- GitHub: [github.com/ALWINTR](https://github.com/ALWINTR)

---

## License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

/*
 * ARDUINO NANO EARTHQUAKE MONITORING & EARLY WARNING SYSTEM (U8g2 OLED Library)
 * 
 * Hardware Connections:
 * - MPU6050: VCC->5V, GND->GND, SCL->A5, SDA->A4
 * - SSD1306 OLED (128x64): VCC->5V, GND->GND, SCL->A5, SDA->A4
 * - Piezo Buzzer: Pin 8 (PWM / Active)
 * - Red Alarm LED: Pin 7
 * - Green Safe LED: Pin 6
 * 
 * Library Requirement: U8g2 by Oliver Kraus (U8g2lib.h)
 */

#include <Wire.h>
#include <U8g2lib.h>

// Initialize 0.96" SSD1306 128x64 I2C display using U8g2 Full Framebuffer Driver
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const int MPU_ADDR = 0x68; // MPU6050 I2C address
const int BUZZER_PIN = 8;
const int RED_LED_PIN = 7;
const int GREEN_LED_PIN = 6;

// Thresholds in G-force (1.0g = 9.81 m/s^2)
const float WARNING_PGA = 0.15;
const float CRITICAL_PGA = 0.35;

void setup() {
  Serial.begin(115200);
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Initialize U8g2 OLED
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(15, 20, "SEISMIC GUARD");
  u8g2.drawStr(10, 42, "INITIALIZING...");
  u8g2.sendBuffer();
  delay(1000);

  // Initialize MPU6050
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // Wake up MPU6050
  Wire.endTransmission(true);
}

void loop() {
  int16_t raw_ax, raw_ay, raw_az;

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // Starting register for Accelerometer Data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  raw_ax = Wire.read() << 8 | Wire.read();
  raw_ay = Wire.read() << 8 | Wire.read();
  raw_az = Wire.read() << 8 | Wire.read();

  // Convert raw values to G-force (sensitivity factor 16384 for +/-2g)
  float ax = raw_ax / 16384.0;
  float ay = raw_ay / 16384.0;
  float az = raw_az / 16384.0;

  // Compute total dynamic acceleration magnitude (subtract static 1.0g gravity)
  float total_acc = sqrt(ax * ax + ay * ay + az * az);
  float pga = abs(total_acc - 1.0); // Peak Ground Acceleration delta

  // Calculate estimated Richter Magnitude scale
  float richter = (pga > 0.02) ? (2.0 + (log10(pga * 10.0 + 1.0) * 2.8)) : 0.0;
  if (richter > 9.0) richter = 9.0;

  char pgaStr[12];
  char richterStr[12];
  dtostrf(pga, 5, 3, pgaStr);
  dtostrf(richter, 4, 1, richterStr);

  String statusStr = "SAFE";

  if (pga >= CRITICAL_PGA) {
    statusStr = "EARTHQUAKE ALERT!";
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    
    // Pulsing 2kHz High-Decibel Alarm Tone
    tone(BUZZER_PIN, 2000, 100);
  } else if (pga >= WARNING_PGA) {
    statusStr = "SEISMIC ACTIVITY";
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    noTone(BUZZER_PIN);
  } else {
    statusStr = "SAFE";
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    noTone(BUZZER_PIN);
  }

  // Render on SSD1306 OLED using U8g2 Library
  u8g2.clearBuffer();
  
  // Header Title & Frame
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(8, 11, "EARTHQUAKE MONITOR");
  u8g2.drawHLine(0, 14, 128);

  // Line 1: PGA Acceleration
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 28, "PGA:");
  u8g2.drawStr(42, 28, pgaStr);
  u8g2.drawStr(90, 28, "g");

  // Line 2: Richter Scale Magnitude
  u8g2.drawStr(0, 42, "Richter:");
  u8g2.drawStr(55, 42, "M ");
  u8g2.drawStr(72, 42, richterStr);

  // Line 3: System Alert Status
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 59, "STATUS:");
  u8g2.drawStr(55, 59, statusStr.c_str());

  u8g2.sendBuffer();

  delay(100); // 10 Hz sampling rate
}

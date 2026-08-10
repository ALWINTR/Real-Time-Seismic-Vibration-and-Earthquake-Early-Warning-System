/*
 * ARDUINO NANO EARTHQUAKE MONITORING & EARLY WARNING SYSTEM
 * 
 * Hardware Connections:
 * - MPU6050: VCC->5V, GND->GND, SCL->A5, SDA->A4
 * - SSD1306 OLED (128x64): VCC->5V, GND->GND, SCL->A5, SDA->A4
 * - Piezo Buzzer: Pin 8 (PWM / Active)
 * - Red Alarm LED: Pin 7
 * - Green Safe LED: Pin 6
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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

  // Initialize SSD1306 OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED Allocation Failed"));
  } else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 15);
    display.println(F("SEISMIC DETECTOR"));
    display.setCursor(25, 35);
    display.println(F("INITIALIZING..."));
    display.display();
    delay(1000);
  }

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

  String status = "SAFE";

  if (pga >= CRITICAL_PGA) {
    status = "EARTHQUAKE ALERT";
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    
    // Pulsing Alarm Tone
    tone(BUZZER_PIN, 2000, 100);
  } else if (pga >= WARNING_PGA) {
    status = "SEISMIC ACTIVITY";
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    noTone(BUZZER_PIN);
  } else {
    status = "SAFE";
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    noTone(BUZZER_PIN);
  }

  // Update OLED Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("EARTHQUAKE MONITOR"));
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

  display.setCursor(0, 16);
  display.print(F("PGA: "));
  display.print(pga, 3);
  display.println(F(" g"));

  display.setCursor(0, 28);
  display.print(F("Richter: M "));
  display.println(richter, 1);

  display.setCursor(0, 42);
  display.print(F("STATUS: "));
  display.println(status);
  display.display();

  // Stream JSON telemetry to Serial Port (115200 baud)
  Serial.print("{\"ax\":");
  Serial.print(ax, 3);
  Serial.print(",\"ay\":");
  Serial.print(ay, 3);
  Serial.print(",\"az\":");
  Serial.print(az, 3);
  Serial.print(",\"pga\":");
  Serial.print(pga, 3);
  Serial.print(",\"richter\":");
  Serial.print(richter, 1);
  Serial.print(",\"status\":\"");
  Serial.print(status);
  Serial.println("\"}");

  delay(100); // 10 Hz sampling rate
}

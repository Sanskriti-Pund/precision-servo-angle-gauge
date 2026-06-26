# precision-servo-angle-gauge
A smart embedded systems project using an Arduino Uno R4 to map potentiometer rotation to an SG90 Servo Motor with live angle tracking on an I2C 1602 LCD.
# Arduino Servo Angle Gauge (with LCD Display)

I built a simple interactive system that lets you control a servo motor's angle using a potentiometer knob, while showing the exact live angle and a visual progress bar on an I2C LCD screen. 

It is a great beginner project for understanding how to read analog inputs, control motors using PWM, and send data over an I2C bus.

---

## How it Works
1. **The Knob:** Turning the potentiometer changes the voltage going into the Arduino's analog pin (`A0`).
2. **The Brain:** The Arduino takes that voltage signal, converts it to a number between 0 and 1023, and then rescales it to a standard servo angle (0 to 180 degrees).
3. **The Output:** The Arduino moves the servo arm to that exact angle and updates the 1602 LCD screen using the I2C protocol so you can see what's happening in real-time.

---

## Parts Needed
* **Arduino Board** (Uno R3, Uno R4, or similar)
* **1602 LCD Display** (The version with the 4-pin I2C backpack on the back)
* **SG90 Micro Servo Motor**
* **10kΩ Potentiometer**
* Breadboard and jumper wires

---

## Wiring Guide

### LCD Screen (I2C)
* **VCC** -> Arduino **5V**
* **GND** -> Arduino **GND**
* **SDA** -> Arduino **A4**
* **SCL** -> Arduino **A5**

### Potentiometer
* Left Pin -> Arduino **GND**
* Middle Pin -> Arduino Analog **A0**
* Right Pin -> Arduino **5V**

### Servo Motor
* Brown Wire (Ground) -> Arduino **GND**
* Red Wire (Power) -> Arduino **5V**
* Orange Wire (Signal) -> Arduino Digital Pin **3**

---

## Code / Sketch

Make sure you have the `LiquidCrystal_I2C` and `Servo` libraries installed in your Arduino IDE before uploading this code.

```cpp
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Set up the LCD at I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

const int POT_PIN = A0;   
const int SERVO_PIN = 3; 

void setup() {
  lcd.init();
  lcd.backlight();
  
  myServo.attach(SERVO_PIN);
  
  // Quick startup message
  lcd.setCursor(0, 0);
  lcd.print("Servo Gauge");
  lcd.setCursor(0, 1);
  lcd.print("Loading...");
  delay(1500);
  lcd.clear();
}

void loop() {
  // Read the dial (0 to 1023)
  int potValue = analogRead(POT_PIN);
  
  // Convert it to degrees (0 to 180)
  int angle = map(potValue, 0, 1023, 0, 180);
  
  // Move the servo
  myServo.write(angle);
  
  // Display the text angle on the top row
  lcd.setCursor(0, 0);
  lcd.print("Angle: ");
  lcd.print(angle);
  lcd.print((char)223); // Degree symbol (°)
  lcd.print("   ");     // Cleans up leftover numbers
  
  // Draw the loading-bar gauge on the bottom row
  lcd.setCursor(0, 1);
  lcd.print("[");
  int bars = map(angle, 0, 180, 0, 12);
  for(int i = 0; i < 12; i++) {
    if(i < bars) {
      lcd.print("="); 
    } else {
      lcd.print(" "); 
    }
  }
  lcd.print("]");
  
  delay(30); // Small delay to keep the screen stable
}

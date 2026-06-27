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
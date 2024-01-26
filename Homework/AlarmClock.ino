#include <LiquidCrystal.h>

const int buzzerPin = 10;
const int buttonPin = 3;

// RGB led
const int led_RED = 2;
const int led_GREEN = 12;
const int led_BLUE = 13;

// Variables for LCD
const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
const int contrastPin = 11;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long setTime = 0; // Time when the alarm is set (in milliseconds)
unsigned long alarmDuration = 30000; // Alarm duration in milliseconds (30 seconds)

bool alarmActive = false;
bool buttonState = HIGH;  // Current state of the button
bool lastButtonState = HIGH;  // Previous state of the button
unsigned long lastDebounceTime = 0;  // Time of the last debounce check
unsigned long debounceDelay = 50;  // Debounce time in milliseconds

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(led_RED, OUTPUT);
  pinMode(led_BLUE, OUTPUT);
  pinMode(led_GREEN, OUTPUT);
  lcd.begin(16, 2);
  pinMode(contrastPin, OUTPUT);
  analogWrite(contrastPin, 90);
}

void loop() {
  // Display elapsed time on LCD
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - setTime;

  lcd.setCursor(0, 0);
  lcd.print(F("Elapsed Time:"));
  lcd.setCursor(0, 1);
  lcd.print(elapsedTime / 1000);

  // Check if the alarm should be activated
  if (elapsedTime >= alarmDuration && !alarmActive) {
    activateAlarm();
  }

  // Check if the button has been pressed to stop the alarm
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    analogWrite(contrastPin, 90);
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW && alarmActive) {
        deactivateAlarm();
      }

      if (buttonState == LOW && !alarmActive) {
        resetTime();
      }
    }
  }

  lastButtonState = reading;
}

void activateAlarm() {
  alarmActive = true;
  digitalWrite(led_RED, HIGH);
  digitalWrite(led_GREEN, HIGH);
  digitalWrite(led_BLUE, HIGH);
  tone(buzzerPin, 1000); // Sound frequency in hertz (in this example, 1000 Hz)
}

void deactivateAlarm() {
  alarmActive = false;
  digitalWrite(led_RED, LOW);
  digitalWrite(led_GREEN, LOW);
  digitalWrite(led_BLUE, LOW);
  noTone(buzzerPin); // Stop the sound
  setTime = millis(); // Reset the time
}

void resetTime() {
  digitalWrite(led_RED, HIGH);
  setTime = millis(); // Reset the time

  // Make sure the contrast is set correctly
  analogWrite(contrastPin, 90);

  lcd.clear(); // Clear the LCD screen
  delay(100);  // Wait for 100 milliseconds for the LED to turn off
  digitalWrite(led_RED, LOW);
}

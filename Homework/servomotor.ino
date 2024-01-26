#include <Servo.h>

// Variables for the sensor
const int trigPin = 8;
const int echoPin = 9;

// Variable for LED output
const int ledPin = 12;

// Variable for buzzer
const int constantPin = 7;

// Variables for motor control
int startPoint = 0;
int endPoint = 180;
int triggerLed = 10;

Servo servoMotor;  // Servo motor object

void setup() {
  // Sensor setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Motor setup
  servoMotor.attach(11);  // Attach servo to pin 11
  Serial.begin(9600);

  // LED and Buzzer setup
  pinMode(ledPin, OUTPUT);
  pinMode(constantPin, OUTPUT);
}

void loop() {
  moveMotor();
}

// Function to move the motor from left to right and right to left on a 180-degree angle
void moveMotor() {
  int i;
  for (i = startPoint; i <= endPoint; i++) {
    servoMotor.write(i);
    delay(15);
    calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }

  for (i = endPoint; i >= startPoint; i--) {
    servoMotor.write(i);
    delay(15);
    calculateDistance();
    Serial.print(i);
    Serial.println(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

// Function to calculate the distance if an object is in the range of the sensor
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  checkLed();
  return distance;
}

// Function to check if the LED can be turned on or not
// It turns ON if there is an object extremely close to the sensor
void checkLed() {
  if (distance < triggerLed) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(constantPin, LOW);
    Serial.println(F("Object detected"));
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(constantPin, HIGH);
  }
}

#include<Servo.h>
//variables for the sensor
const int trigPin = 8;
const int echoPin = 9;
//variable for led output
const int ledPin = 12;
//variable for static Led
const int constantPin = 7;
//variables 
long duration;
int distance ;

int startPoint = 0;
int endPoint = 180;
int triggerLed = 10;

Servo servoMotor;

void setup(){
  //sensor 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //motor
  servoMotor.attach(11);
  Serial.begin(9600);
  //led output
  pinMode(ledPin, OUTPUT);
  pinMode(constantPin, OUTPUT);
}

void loop(){
  moveMotor();
}

//function to move the motor  from left to right and right to left on a 180 angle
void moveMotor(){
 int i;
 for (i=startPoint; i<=endPoint; i++)
 {
  servoMotor.write(i);
  delay(15);
  calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
 }
 for(i=endPoint; i>=startPoint; i--)
 {
  servoMotor.write(i);
  delay(15);
  calculateDistance();
  Serial.print(i);
  Serial.println(",");
  Serial.print(distance);
  Serial.print(".");
 }
}
//function to calculate the distance if an objects is in the range of the sensor
int calculateDistance(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  checkLed();
  return distance;
}
//function to check if the led can be turned on or not
//it turns ON if there is an object extremely close to the sensor
void checkLed(){
  if (distance < triggerLed){
    digitalWrite(ledPin, HIGH);
    digitalWrite(constantPin, LOW);
    Serial.println(F("Object detected"));
  }
  else {
    digitalWrite(ledPin, LOW);
    digitalWrite(constantPin, HIGH);
  }
}

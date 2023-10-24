///declaram variabilele
const int pinGreen=A0;
const int pinRed=A1;
const int pinBlue=A2;

const int ledPinGreen=11;
const int ledPinRed=10;
const int ledPinBlue=9;

float potValueRed = 0;
float potValueGreen = 0;
float potValueBlue = 0;

float ledValueRed = 0;
float ledValueGreen = 0;
float ledValueBlue = 0;

int inputAnalogMin = 0;
int inputAnalogMax= 1023;

//digital
int ledPinMin=0;
int ledPinMax=255;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
}

void ReadAnalog()
{
  //valorile potentiometrelor 
  potValueRed = analogRead(pinRed);
  potValueGreen = analogRead(pinGreen);
  potValueBlue = analogRead(pinBlue);
}

void Mapare()
{
  ledValueRed = map(potValueRed, inputAnalogMin, inputAnalogMax, ledPinMin, ledPinMax);
  ledValueGreen = map(potValueGreen, inputAnalogMin, inputAnalogMax, ledPinMin, ledPinMax);
  ledValueBlue = map(potValueBlue, inputAnalogMin, inputAnalogMax, ledPinMin, ledPinMax);
}

void WriteAnalog()
{

  //potentiometru + led
  analogWrite(ledPinRed, ledValueRed);
  analogWrite(ledPinGreen, ledValueGreen);
  analogWrite(ledPinBlue, ledValueBlue); 
}

void loop() {
  // put your main code here, to run repeatedly:
  ReadAnalog();
  Mapare();
  WriteAnalog();
}

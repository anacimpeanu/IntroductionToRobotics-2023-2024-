// Declarare variabile
const int numberFloors = 3;
const int thisPin;
const int maximumIntensity=256;
byte reading;

const int buttonPinFloor[numberFloors] = {2,3,4}; 
const int ledPinFloor[numberFloors] = {9,10,12};
const int ledPinElevatorState = 5;

// Declarari pentru buzzer
const int buzzerPin = 11;
int buzzerTone = 500;
int currentTone = 0;

//Declarari debounce
const unsigned long debounceDelay = 50; //interval de debounce
unsigned long lastDebounceTime[numberFloors];

//variabile de timp
unsigned long lastActionTime = 0;
unsigned long waitingTime = 5000;  //Timpul de asteptare pentru a chema liftul la alt etaj
unsigned long interval = 1000;


//Declarari stari initiale 
byte buttonStateFloor[numberFloors];      //Starea initiala a butoanelor care este LOW
byte lastButtonStateFloor[numberFloors];  //Ultima stare a butoanelor

int currentFloor = 1;
int targetFloor = -1;
int direction = 0; //0->inactiv, 1->urcare ,-1->coborare

//declarari pentru sunet
unsigned long soundStartTime = 0;
int soundState = 1;

void setup(){

  pinMode(buttonPinFloor[0], INPUT_PULLUP);
  pinMode(buttonPinFloor[1], INPUT_PULLUP);
  pinMode(buttonPinFloor[2], INPUT_PULLUP);

  pinMode(ledPinFloor[0], OUTPUT);
  pinMode(ledPinFloor[1], OUTPUT);
  pinMode(ledPinFloor[2], OUTPUT);

  pinMode(ledPinElevatorState, OUTPUT);
  
  Serial.begin(9600);
}

void loop(){

  for (int thisPin = 0; thisPin < numberFloors ; thisPin++){

    //starea butonului corespunzator etajului

    reading = digitalRead(buttonPinFloor[thisPin]);
    if(reading != lastButtonStateFloor[thisPin]){
      
      // Retin ultima stare a butonului inregistrata

      lastDebounceTime[thisPin] = millis();
    }

    // Verificari daca starea etajului a fost schimbata

    if((millis() - lastDebounceTime[thisPin]) > debounceDelay){
      if(reading != buttonStateFloor[thisPin]){
        buttonStateFloor[thisPin] = reading;

        if(buttonStateFloor[thisPin] == LOW){
          targetFloor = thisPin + 1;
          if(targetFloor != currentFloor){
            if(targetFloor > currentFloor){
              direction = 1;
            }
            else{
              direction = -1;
            }

            // Actualizarea ultimei actiuni ale timpului

            lastActionTime = millis();
          }
        }
      }
    }
    lastButtonStateFloor[thisPin] = reading; // Ultima stare a butonului
  }
  
  if(soundState == 0){
      SoundMaker();
  }

  digitalWrite(ledPinFloor[currentFloor - 1], HIGH);
  
  // Verific daca am un etaj tinta

  if(targetFloor != -1 && targetFloor != currentFloor && soundState == 1){
    moveElevator(targetFloor,direction);
  }
}

void moveElevator(int floor , int dir){

  // floor -> etaj tinta , dir -> directia

  digitalWrite(ledPinElevatorState, LOW);
  pulseLED(ledPinElevatorState);
  
  // Verific daca liftul urca ( 1 ) sau coboara ( -1 )
  
  int step = (dir == 1) ? 1 : -1;

  if (currentFloor != floor) {
    currentFloor += step;
    updateFloorIndicators();
    pulseLED(ledPinElevatorState);
  }

  // Etajul curent cu valoarea etajului tinta 

  currentFloor = floor;
  if(currentFloor == floor){

    updateFloorIndicators();
    digitalWrite(ledPinElevatorState, HIGH);
    soundState = 0;
    tone(buzzerPin, buzzerTone, 1000);
    /*
    delay(waitingTime);
    tone(buzzerPin, 400, 1000);
    delay(waitingTime);
    tone(buzzerPin, 200, 1000);
    */
  }

  lastActionTime = millis();

  // Asteptarea etajului

  delay(waitingTime);
  digitalWrite(ledPinElevatorState, LOW);
}

void updateFloorIndicators() {
  digitalWrite(ledPinFloor[0], currentFloor == 1);
  digitalWrite(ledPinFloor[1], currentFloor == 2);
  digitalWrite(ledPinFloor[2], currentFloor == 3);
}

// Functia de pulsatie , folosind intensitatea maxima ( 256 ) sau minima ( 0 )
void pulseLED(int ledPin) {
  for (int thisLed= 0; thisLed < 256; thisLed++) {
    analogWrite(ledPin, thisLed);
    delay(1);
  }
  for (int thisLed = 255; thisLed >= 0; thisLed--) {
    analogWrite(ledPin, thisLed);
    delay(1);
  }
}

// Functia pentru sunete
void SoundMaker(){
  
  if(millis() - soundStartTime >= waitingTime){
    tone(buzzerPin, buzzerTone, 500);

    // Sunetul creste 
    buzzerTone +=500;  

    // Numarul de sunete generate ( maxim doua -> urcare , -> coborare)
    currentTone++;

    soundStartTime = millis();
  }
  if (currentTone == 2){
    currentTone = 0;  // Reset
    soundState = 1;   // Liftul poate cobori/urca
    buzzerTone = 1000; //Reset
  }
}

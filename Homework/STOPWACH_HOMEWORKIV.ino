// Define connections to the shift register
const int latchPin = 11; // Connects to STCP (latch pin) on the shift register
const int clockPin = 10; // Connects to SHCP (clock pin) on the shift register
const int dataPin = 12; // Connects to DS (data pin) on the shift register

// Define connections to the digit control pins for a 4-digit display
const int segD1 = 4;
const int segD2 = 5;
const int segD3 = 6;
const int segD4 = 7;

// Store the digits in an array for easy access
int displayDigits[] = {segD1, segD2, segD3, segD4};
const int displayCount = 4; // Number of digits in the display

// Define byte encodings for the hexadecimal characters 0-9
byte byteEncodings[] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
};

// Define a byte encoding for the decimal point (assuming it's controlled by a separate segment)
// made it separate, it didn't want to work when I put it in the byteEncodings[]
byte decimalPoint = B00000001; // Turn on the rightmost segment

// Declare variables for buttons 
const int buttonReset = 8;
const int buttonStart = 2;
const int buttonSave = 3;

// Declare things for the reset button which does NOT have interrupts
byte buttonResetState = HIGH;

// Declare led 

const int ledPin = 13;
byte ledState = LOW;

// Declare flags for states of buttons 
bool stateStart = false; // keeps track of timer, if timer is counting it becomes true, if not, like if it is paused, it stays false
bool statePause = false; //remembers if the timer is in pause or not, could have used just hasStarted as well
bool showDisplay = false; //might use it, still deciding
bool stateReset = false;

// Declare variables for time debounce and interrupts 

// Start button 
bool makeStartPause = false; //checks if the button was or not pressed, initially it isn't
unsigned long lastMakeStartPause = 0; //remembers the time the button was pressed last time
const int pauseInterval = 100; // debounce interval of button

// Save button
bool makeCycle = false; //checks if the button was or not pressed, initially it isn't
unsigned long lastMakeCycle = 0; // remembers the time the button was pressed last time
const int cycleInterval = 500; // debounce interval of button

// Another variable for time ( controlling the display update timing )
unsigned long lastIncrement = 0;
unsigned long delayCount = 100; // Delay between updates (milliseconds)
unsigned int number = 0; // The number being displayed


// Variables for button 3 , save laps and show the laps on the display
const int maximLaps = 4;
int saveLap[maximLaps] = {0};
int countLaps = 0;
int showSavedLap = 0;
int countLapPresses = 0;
bool inCycleMode = false;


unsigned long lastShowDisplay = 0;
unsigned int showInterval = 2000;


void setup() {
  // put your setup code here, to run once:
  // Initialize the pins connected to the shift register as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(buttonReset, INPUT_PULLUP);
  pinMode(buttonStart, INPUT_PULLUP);
  pinMode(buttonSave, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(buttonStart), handleInputStart, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonSave), handleInputSave, FALLING);

  // Initialize digit control pins and set them to LOW (off)
  for (int thisPin = 0; thisPin < displayCount; thisPin++) {
    pinMode(displayDigits[thisPin], OUTPUT);
    digitalWrite(displayDigits[thisPin], LOW);
  }

  // Begin serial communication for debugging purposes
  Serial.begin(9600);

  // Set the initial state
  setInitialState();

}

void setInitialState() {
  number = 0;
  writeNumber(number);
}

void showDecision() {
  if( millis() - lastShowDisplay >= showInterval){
    showOnDisplay();
    ledState=LOW;
    digitalWrite(ledPin, ledState);
    lastIncrement = millis();
    inCycleMode = true;
    }
  else{
    showOnDisplay();
  }
}

// Function if we decide that we are in counting number and write numbers or if we find out the status of saved laps
void incrementDecision() {
  if(stateStart){
    if (millis() - lastIncrement > delayCount) {

      // Increment the number and reset 'lastIncrement'
      number++;

      // Ensure that 'number' wraps around after reaching 9999 to start over from 0
      number %= 10000; // Wrap around after 9999
      lastIncrement = millis();
    }
  }
  if (showDisplay){
    showDecision();
  }
  else{
  // Display the incremented number on the 7-segment display using multiplexing
  writeNumber(number);}
}
void loop() {

  incrementDecision();
  canStart();
  canReset();
  canSave();

}

void writeReg(int digit) {
  // Prepare to shift data by setting the latch pin low
  digitalWrite(latchPin, LOW);
  // Shift out the byte representing the current digit to the shift register
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  // Latch the data onto the output pins by setting the latch pin high
  digitalWrite(latchPin, HIGH);
}

void activateDisplay(int displayNumber) {
  // Turn off all digit control pins to avoid ghosting
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  // Turn on the current digit control pin
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeNumber(int number) {
  // Initialize necessary variables for tracking the current number and digit position
  int currentNumber = number;
  int displayDigit = displayCount - 1; // Start with the most significant digit
  int lastDigit = 0;

  // Loop through each digit of the current number
  while (displayDigit >= 0) {
    // Extract the last digit of the current number
    lastDigit = currentNumber % 10;

    // Activate the current digit on the display
    activateDisplay(displayDigit);

    // Output the byte encoding for the last digit to the display
    if (displayDigit == 2) {
      // Check if it's the D3 digit
      writeReg(byteEncodings[lastDigit] | decimalPoint); // Turn on the decimal point
    } else {
      writeReg(byteEncodings[lastDigit]); // No decimal point
    }

    // Implement a delay for multiplexing visibility
    delay(1); // A small delay to visualize multiplexing

    // Move to the next digit
    displayDigit--;

    // Update 'currentNumber' by removing the last digit
    currentNumber /= 10;

    // Clear the display to prevent ghosting between digit activations
    writeReg(B00000000); // Clear the register to avoid ghosting
  }
}

// Called when the start button is pressed. It checks the debounce range ,
// making sure it doesn't react to short fluctuations in the button signal.

void handleInputStart(){
  if (millis() - lastMakeStartPause >= pauseInterval){
    makeStartPause = true;   
  }
  lastMakeStartPause = millis();   
}

// We declare a function to see the states of the buttons when we press the start button
void canStart() {
  // Check if the start button has been pressed 

  if (makeStartPause){
    stateStart = !stateStart; 
    
    // Reset the pause, reset, and display states
    if(stateStart == true){
      statePause = false;
      stateReset = false;
      showDisplay = false;
    }
    else{
      
      // Set the pause state to true
      statePause= true;

    }
  
  // Reset the signal indicating that the start button was pressed
  makeStartPause = false;
  }
}


// A function where we see what decisions are made in the code when we press the reset button
// The function is divided into two, it checks and resets in pause mode to be able to run laps
// and at the same time, if we are in the cycle of laps and the reset button is pressed again, it will help to reset the saved laps


void canReset() {
  buttonResetState = digitalRead(buttonReset);
  // Check if the reset button has been pressed (its state is LOW
  if (buttonResetState == LOW){

    // If the system is in a paused state
    if(statePause){
      stateReset = true;
      setInitialState();
      statePause = false;

      // Turn on the LED
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
    }

    // If the system is in cycle mode (inCycleMode)
    if(inCycleMode){
      
      stateReset = true;

      // Reset the saved lap values
      for(int i = 0; i < maximLaps; i++){
        saveLap[i] = 0;
      }
      // Restore the initial state of the system
      setInitialState();
      inCycleMode = false;
      showDisplay = false;
    }
  }
}

// Called when the save button is pressed. It checks the debounce range ,
// making sure it doesn't react to short fluctuations in the button signal.


void handleInputSave() {
  if (millis() - lastMakeCycle >= cycleInterval){
    makeCycle = true; 
    // These values ​​help me to save in lapuri, because I can retain a maximum of 4 values, and if I have more presses, my save vector is overwritten.
    // So it is quite logical that I will take regardless of the number of clicks on save % 4.
    countLapPresses ++;
    countLapPresses %=4;
  }
  lastMakeCycle= millis();
}

// Function for which decisions are made if I press the save button
void canSave() {
  // Check if the save button is pressed
  if (makeCycle){
    Serial.println("Save button");
    // Check if the timer (stateStart) is active

   if (stateStart == true){ // if the counter is going, just save the laps in the array
      // If the timer is counting, save the laps in the array
      saveLap[countLaps] = number;
      Serial.print("save lap number ");
      Serial.print(countLaps);
      Serial.print(":");
      Serial.println(saveLap[countLaps]);
      // Increment the lap counter and ensure it wraps around
      countLaps++;
      countLaps %= 4;
    }
    // Check if the LED is turned on
    if(ledState == HIGH){
       // Enable the display for laps
      showDisplay = true;
    }
    // Reset the button press state
    makeCycle = false;
  }
}

// Writing function of the saved laps
void showOnDisplay() {
  inCycleMode = true;
  showSavedLap = saveLap[countLapPresses];
  writeNumber(showSavedLap);
}
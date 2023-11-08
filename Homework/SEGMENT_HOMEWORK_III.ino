// Declare all the segments pins for the 7-segment display
const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

const int segSize = 8;

const int buzzerPin = 11;
int buzzerTone = 500;

// Declare a vector to hold the pin values
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

// Declare the position of the pin on the segment (to which segment it belongs)
const int indexPinA = 0;
const int indexPinB = 1;
const int indexPinC = 2;
const int indexPinD = 3;
const int indexPinE = 4;
const int indexPinF = 5;
const int indexPinG = 6;
const int indexPinDP = 7;


const int directionCount = 4; //up, down, left, right
// // Declare the position of the pin on the segment (to which segment it belongs)

// const int displayPinA = 0;
// const int displayPinB = 1;
// const int displayPinC = 2;
// const int displayPinD = 3;
// const int displayPinE = 4;
// const int displayPinF = 5;
// const int displayPinG = 6;
// const int displayPinDP = 7;


//Declare the table of states presented in the document, type a matrix, which will contain which possible pins can light up
//At the same time, I use the value "-1" to highlight the direction that cannot be accessed
const int movementMatrix[segSize][directionCount] = {
//   {      -1,       displayPinG,    displayPinF,  displayPinB },    // Stari pentru segmentul specific ' a '
//   { displayPinA,   displayPinG,    displayPinF,      -1      },    // Stari pentru segmentul specific ' b '
//   { displayPinG,   displayPinD,    displayPinE,  displayPinDP},    // Stari pentru segmentul specific ' c '
//   { displayPinG,       -1,         displayPinE,  displayPinC },    // Stari pentru segmentul specific ' d '
//   { displayPinG,   displayPinD,       -1,        displayPinC },    // Stari pentru segmentul specific ' e '
//   { displayPinA,   displayPinG,       -1,        displayPinB },    // Stari pentru segmentul specific ' f '
//   { displayPinA,   displayPinD,       -1,             -1     },     // Stari pentru segmentul specific ' g '
//   {      -1,           -1,         displayPinC,       -1     },     // Stari pentru segmentul specific ' dp '
// };
  {0, 6, 5, 1}, // a  (0)
  {0, 6, 5, 1}, // b  (1)
  {6, 3, 4, 7}, // c  (2)
  {6, 3, 4, 2}, // d  (3)
  {6, 3, 4, 2}, // e  (4)
  {0, 6, 5, 1}, // f  (5)
  {0, 3, 6, 6}, // g  (6)
  {7, 7, 2, 7}  // dp (7)
};

//declare the pins for the joystick
const int pinSW = 2; // digital pin connected to switch output
const int pinX = A0; // A0 = analog pin connected to X output
const int pinY = A1; // A1 = analog pin connected to Y output

byte ledState[segSize]; //0 pentru OFF, 1 pentru ON

// Declare time 
byte currentSegmentBlinking = 0;
// States of Button
bool lastButtonState = HIGH;
bool buttonState = HIGH;
bool buttonPressed = false;

// Variable time
unsigned long buttonPressStartTime = 0;
unsigned long lastJoystickTime = 0;
bool joyChangedState = true;
int currentPinIndex = 7; //we're starting on the dp 

//declare the time variables for debounce and blink

// Defines the interval (in milliseconds) for debouncing a button press.
const int debounceInterval = 100;

// Defines the interval (in milliseconds) for controlling LED blink timing.
const int blinkInterval = 500;

// Stores the timestamp (in milliseconds) of the last time the LED blinked.
unsigned long lastTimeItBlinked = 0;

// Stores the timestamp (in milliseconds) of the last time a button press was debounced.
unsigned long lastTimeItDebounced = 0;

// Specifies a time threshold (in milliseconds) for a joystick action.
const int joystickTime = 800;

// Specifies a time threshold (in milliseconds) for triggering a reset action.
const int resetTime = 2000;


//declare variables for axis 
const int extremeHigh = 900; /// when hold to extreme right or up, either x or y become ~1023
const int extremeLow = 100; ///when hold to extreme left of down, either x or y become ~ 0 (under 10)
const int holdPositionLess = 400;  //We check if the absolute difference between the axis values ​​is 600 (aprx |1000 - 400|). In this case, we will know that the joystick will move to the right or up
const int holdPositionMore = 600;   //We check if the absolute difference between the axis values ​​is 400 (). In this case, we will know that the joystick will move to the left or down

// For the last two cases, they apply to three scenarios: when both x and y start at approximately 514 and 508, and when they move to the right or up, resulting in either x or y reaching 510 or 515. Consequently, I chose to establish intervals based on these conditions.


// Setup 

void setup() {
  // put your setup code here, to run once:
  for( int thisSegment = 0; thisSegment < segSize; thisSegment++){
    pinMode(segments[thisSegment], OUTPUT);
  }

  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt(pinSW), handleInterrupt, FALLING);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);

  
  Serial.begin(9600);

  digitalWrite(segments[pinDP], HIGH); // Turn on the decimal point
}

void loop() {
  // Read the analog values from the X and Y pins.
  int xValue = analogRead(pinX);
  int yValue = analogRead(pinY);

  // Check if it's time to process joystick input based on a time threshold.
  if (millis() - lastJoystickTime >= joystickTime) {
      // Initialize a flag to track whether the joystick state has changed.
      joyChangedState = false;

      // Check if the joystick position corresponds to moving in one of four directions.
      // If the joystick is moved to a particular direction, it triggers an action.

      // Condition 1: Joystick moved to the right.
      if (xValue > extremeHigh && yValue > holdPositionLess && yValue < holdPositionMore) {
          moveLed(movementMatrix[currentPinIndex][0]); // Perform a specific action.
          lastJoystickTime = millis(); // Update the last joystick interaction time.
          joyChangedState = true; // Set the flag to indicate a state change.
      }
      // Condition 2: Joystick moved to the left.
      else if (xValue < extremeLow && yValue > holdPositionLess && yValue < holdPositionMore) {
          moveLed(movementMatrix[currentPinIndex][1]); // Perform a different action.
          lastJoystickTime = millis(); // Update the last joystick interaction time.
          joyChangedState = true; // Set the flag to indicate a state change.
      }
      // Condition 3: Joystick moved upward.
      else if (yValue < extremeLow && xValue > holdPositionLess && xValue < holdPositionMore) {
          moveLed(movementMatrix[currentPinIndex][2]); // Perform another action.
          lastJoystickTime = millis(); // Update the last joystick interaction time.
          joyChangedState = true; // Set the flag to indicate a state change.
      }
      // Condition 4: Joystick moved downward.
      else if (yValue > extremeHigh && xValue > holdPositionLess && xValue < holdPositionMore) {
          moveLed(movementMatrix[currentPinIndex][3]); // Perform a different action.
          lastJoystickTime = millis(); // Update the last joystick interaction time.
          joyChangedState = true; // Set the flag to indicate a state change.
    }
  }


// Check if a button press is detected.
  if (buttonPressed) {
      // Check if it's the first time the button was pressed.
      if (!buttonPressStartTime) {
          buttonPressStartTime = millis(); // Record the current time.
      }
      // Check if the time between the button press and now exceeds the reset time threshold.
      if (millis() - buttonPressStartTime >= resetTime) {
          // Long press detected, perform a reset operation.
          resetingFunc(); // Call the resetingFunc to reset the display.
          buttonPressed = false; // Reset the button press state.
      } 
      // Check for debouncing the button.
      else if ((millis() - lastTimeItDebounced) > debounceInterval) {
          lastTimeItDebounced = millis(); // Update the last time the button was debounced.
          buttonState = digitalRead(pinSW); // Read the current button state.

          // Check if the button state has changed.
          if (buttonState != lastButtonState) {
              // Toggle the LED state and the last button state to handle button press/release.
              ledState[currentPinIndex] = !ledState[currentPinIndex];
              lastButtonState = !lastButtonState;
              buttonPressed = false; // Reset the button press state.
          }
      }
  } 
  // If no button press is detected, reset the button press start time and button state.
  else {
    
      buttonPressStartTime = 0; // Reset the button press start time.
      buttonPressed = false; // Reset the button press state.
  }

  displayLeds();
  makeItBlink();
}


// This function is responsible for moving the LED segment to a new position.
void moveLed(int newSegment) {
  // Check if the new segment is different from the current one.
  if (newSegment != currentPinIndex) {
    // Update the LED state for the new segment.
    currentSegmentBlinking = ledState[newSegment];
    // Update the current LED segment index to the new one.
    currentPinIndex = newSegment;
  }
}


// Reset the display after you keep pressing for 5 sec
void resetingFunc() {
  for (int i = 0; i < segSize; i++) {
    ledState[i] = 0; // Turn off all segments
  }
  currentPinIndex = 7; // Start at the decimal point
  tone(buzzerPin, buzzerTone, 1000); 
}

// Display the state of the segments
void displayLeds() {
  for (int thisLed = 0; thisLed < segSize; thisLed++) {
    if(thisLed != currentPinIndex)
      digitalWrite(segments[thisLed], ledState[thisLed]);
  }
}

// This function is responsible for handling the blinking of the current LED segment.
void makeItBlink() {
  // Check if it's time to toggle the LED state based on the blink interval.
  if (millis() - lastTimeItBlinked >= blinkInterval) {
    // Update the last blinking time to the current time.
    lastTimeItBlinked = millis();
    // Toggle the state of the current LED segment.
    currentSegmentBlinking = !currentSegmentBlinking;
    // Set the LED to the new state (on or off) based on currentSegmentBlinking.
    digitalWrite(segments[currentPinIndex], currentSegmentBlinking);
  }
}


// Handle interrupt
void handleInterrupt() {
  buttonPressed = true;
}

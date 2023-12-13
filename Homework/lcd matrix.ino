#include <LedControl.h>
#include <EEPROM.h>
//Definirea adresei pentru salvarea valorii de luminozitate în EEPROM
#define BRIGHTNESS_EEPROM_ADDRESS 0
// variables for LCD 
#include <LiquidCrystal.h>
const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// Variables for controlling the LED matrix display
const int dinPin = 12;    // Data input pin for the LED matrix
const int clkPin = 11;    // Clock input pin for the LED matrix
const int csPin = 10;     // Chip select input pin for the LED matrix
LedControl lc = LedControl(dinPin, clkPin, csPin, 1);  // LED matrix control object

const int ledPin = A2;       // Pin for bomb LED
const int buzzerPin = 13;    // Pin for the buzzer

// Joystick control variables
const int joystickDeadzone = 50;   // Threshold for joystick movement
const int moveInterval = 300;      // Minimum time interval between player movements

// Timing variables
unsigned long lastMoveTime = 0;     // Timestamp of the last player movement
unsigned long bombLastPlacedTime = 0;  // Timestamp of the last bomb placement
unsigned long previousMillis = 0;      // Timestamp for various time-related tasks
const long interval = 200;             // Interval for certain periodic actions

// Game grid and player position variables
const int matrixSize = 8;   // Size of the game grid (matrixSize x matrixSize)
const int xPin = A0;         // Analog pin for the X-axis of the joystick
const int yPin = A1;         // Analog pin for the Y-axis of the joystick
const int buttonPin = 2;     // Digital pin for the joystick button
int playerX = matrixSize / 2;   // Initial X position of the player
int playerY = matrixSize / 2;   // Initial Y position of the player

// Game state variables
bool walls[matrixSize][matrixSize];   // Array representing the presence of walls in the game
bool wallsGenerated = false;           // Flag indicating whether walls have been generated
bool displayHiFlag = true;             // Flag for displaying HI message

// Bomb-related variables
bool bombPlaced = false;          // Flag indicating whether a bomb has been placed
bool detonateFlag = false;        // Flag indicating whether the bomb is set to detonate
int bombX, bombY;                 // Coordinates of the bomb on the game grid
bool flagBomb = false;             // Flag indicating the ability to place a bomb

unsigned long bombPreviousMillis = 0;  // Timestamp for bomb-related timing
const long bombInterval = 1000;         // Interval for bomb detonation
const long bombIntervalBlinking = 100;  // Blinking interval for the bomb LED
int score = 0;                         // Global game score
unsigned long gameStartTime;           // Timestamp of the start of the game
bool displayWelcome = true;
int livesPlayer = 3;
int bombRadius = 1;
unsigned long timerGame;
bool displayFlagMenu = false;
int menuState = 0; 
char selectedOption;
bool flagJoystickMenu = true;
bool flagJoystickGame = false;
unsigned long currentMessageStartTime = 0;
const unsigned long messageDuration = 3000;  
int currentMessageIndex = 0;
bool instructionsDisplayUp = true;
bool instructionsDisplayDown = false;
const int lcdBacklightPin = 3; 
int subMenuState = 0;  

int lcdBrightness = 128;  
bool flagMenu = true;
bool flagSubMenu = false; 
int matrixBrightness = 8;  
const int matrixIntensityAddress = 0; 
int matrixIntensity = 0;


void setLCDBrightness(int brightness) {

  brightness = constrain(brightness, 0, 255);

  analogWrite(lcdBacklightPin, brightness);

  EEPROM.write(BRIGHTNESS_EEPROM_ADDRESS, brightness);
}


void loadLCDBrightnessFromEEPROM() {
  lcdBrightness = EEPROM.read(BRIGHTNESS_EEPROM_ADDRESS);
  setLCDBrightness(lcdBrightness);
}
int backlightLevel = 128;  


void setup() {
  Serial.begin(9600);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  
  //displayWelcomeMessage();
  lcd.begin(16, 2);
  pinMode(3, OUTPUT); 
  analogWrite(3, 128); 
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  randomSeed(analogRead(A3));

  generateRandomWalls();
  gameStartTime = millis();   // Record the moment when the game starts
  score = 0;                  // Reset the game score to zero at the beginning of each new game
}


const char messages[][17] = {
  "WELCOME PLAYER",
  "ARE YOU READY ?",
  "FOR THIS GAME",
  "BOMBERMAN"
};
void displayMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(messages[currentMessageIndex]);
  lcd.autoscroll();
  delay(1500);
  lcd.noAutoscroll();
  if (currentMessageIndex < sizeof(messages) / sizeof(messages[0]) - 1) {
    currentMessageIndex++;
  } else {
    displayWelcome = false;
    displayFlagMenu = true;
    displayHiFlag = false;
  }
}


void displayMenu() {
  //lcd.clear();
  //flagSubMenu = false;
  switch (menuState) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("MAIN MENU");
      lcd.setCursor(0, 1);
      lcd.print("START GAME");
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("MAIN MENU");
      lcd.setCursor(0, 1);
      lcd.print("SETTINGS");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("MAIN MENU");
      lcd.setCursor(0, 1);
      lcd.print("ABOUT");
      break;
  }
}

void aboutMe() {
  lcd.setCursor(0, 0);
  //lcd.autoscroll();
  lcd.print("ANA CIMPEANU");
  lcd.setCursor(0, 1);
  lcd.print("GITHUB:anaacimpeanu");
  //lcd.noAutoscroll();
}
void displaySubMenu() {
  flagSubMenu = true;
  lcd.clear();
  switch (subMenuState) {

    case 0:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SETTINGS LIGHT");
      lcd.setCursor(0, 1);
      lcd.print("LCD CONTRAST");
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SETTINGS LIGHT");
      lcd.setCursor(0, 1);
      lcd.print("MATRIX CONTRAST");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SETTINGS LIGHT");
      lcd.setCursor(0, 1);
      lcd.print("RETURN TO MENU");
      break;
  }
}
void processMenuNavigation() {
  int joystickX = analogRead(xPin);
  int joystickY = analogRead(yPin);

  if (flagSubMenu) {
    processSubMenuNavigation(joystickY);
  } else {
    processMainMenuNavigation(joystickY);
  }
}

void processMainMenuNavigation(int joystickY) {
  if (joystickY < 100) {
    // Moving down
    menuState = (menuState + 1) % 3;
    displayMenu();
  } else if (joystickY > 900) {
    // Moving up
    menuState = (menuState - 1 + 3) % 3;
    displayMenu();
  }

  if (digitalRead(buttonPin) == LOW) {
    // Button pressed
    if (menuState == 0) {
      // "Start Game" selected
      displayFlagMenu = false;
      //timerGame = millis();
    } else if (menuState == 1) {
      // "Settings" selected
      displaySubMenu();
      //navigateSettings();
    } else if (menuState == 2) {
      // "About" selected
      aboutMe();
    }
  }
}

void processSubMenuNavigation(int joystickY) {
  
  Serial.println("Inside processSubMenuNavigation");
  if (joystickY < 100) {
    // Moving down
    subMenuState = (subMenuState + 1) % 3;
    displaySubMenu();
  } else if (joystickY > 900) {
    // Moving up
    subMenuState = (subMenuState - 1 + 3) % 3;
    displaySubMenu();
  }
  delay(300);
  if (digitalRead(buttonPin) == LOW) {
    // Button pressed
    if (subMenuState == 0) {
      // "Adjust Backlight" selected
      adjustBacklight();
    } else if (subMenuState == 1) {
      adjustMatrixBrightness();
    } else if (subMenuState == 2) {
      // "Return to Main Menu" selected
      flagSubMenu = false;
      displayMenu();
    }
    // Handle other submenu options if needed (subMenuState == 1, etc.)
  }
}

void adjustMatrixBrightness() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("> RETURN");
  lcd.setCursor(0, 1);
  lcd.print("USE UP OR DOWN");

  while (true) {
    int joystickX = analogRead(xPin);
    int joystickY = analogRead(yPin);

    if (joystickY < 100) {
      lcd.clear();
      matrixIntensity = min(15, matrixIntensity + 1);
      lc.setIntensity(0, matrixIntensity);
      lcd.setCursor(0, 0);
      lcd.print("DECREASED");
      lcd.setCursor(0, 1);
      lcd.print("Current Level: " + String(matrixIntensity));
    } else if (joystickY > 900) {
      lcd.clear();
      matrixIntensity =  max(0, matrixIntensity - 1);
      lcd.setCursor(0, 0);
      lcd.print("INCREASED");
      lcd.setCursor(0, 1);
      lcd.print("Current Level: " + String(matrixIntensity));
      lc.setIntensity(0, matrixIntensity);
      delay(1);
    }

    // lcd.setCursor(0, 0);
    //lcd.print("Current Level: " + String(matrixIntensity));

    // Save the matrix intensity to EEPROM and return to the previous menu
    if (joystickX < 100) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SAVED VALUE");
      lcd.setCursor(0, 1);
      lcd.print("UP FOR RETURN");
      EEPROM.write(matrixIntensityAddress, matrixIntensity);
      delay(1);  // Delay to display the saved value message
      
      break;
    }

    //delay(1);  // Adjust the delay if needed
  }
  flagSubMenu = true;
}

void adjustBacklight() {
  Serial.println("Inside adjustBacklight");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("> RETURN");
  lcd.setCursor(0, 1);
  lcd.print("USE UP OR DOWN ");
  while (true) {
    int joystickX = analogRead(xPin);
    int joystickY = analogRead(yPin);

    if (joystickY < 100) {
      lcd.clear();
      backlightLevel = min(255, backlightLevel + 5);
      lcd.setCursor(0, 0);
      lcd.print("DECREASED");
      lcd.setCursor(0, 1);
      lcd.print("Current Level: " + String(backlightLevel));
      delay(1);
    } else if (joystickY > 900) {
    
      lcd.clear();
      backlightLevel = max(0, backlightLevel - 5);
      lcd.setCursor(0, 0);
      lcd.print("INCREASED");
      lcd.setCursor(0, 1);
      lcd.print("Current Level: " + String(backlightLevel));
      delay(1);
    }

    if (joystickX < 100) {// Salvarea nivelului în EEPROM și revenirea la meniul anterior
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SAVED VALUE");
      lcd.setCursor(0, 1);
      lcd.print("UP FOR RETURN");
      EEPROM.write(0, backlightLevel);

      break;
    }

    analogWrite(lcdBacklightPin, backlightLevel);
    //delay(50);
  }
  flagSubMenu = true;
}
void handleButtonPress() {
  //lcd.clear();
  // Show to the display the countdown images and make decisions 
  if (digitalRead(buttonPin) == LOW && !wallsGenerated ) {
    for (int count = 3; count >= 0; count--) {
      displayCountdown(count);
    }
    wallsGenerated = true; 
    timerGame = millis(); // Mark that walls have been generated and the game has started
    //displayHiFlag = false;  // Turn off the hi display flag to switch to the game display
  }
}


void handleJoystickInput() {
    //lcd.clear();
    int xValue = analogRead(xPin);  // Read the analog value from the X-axis of the joystick
    int yValue = analogRead(yPin);  // Analog

    // Check if joystick movement is significant
    if (abs(xValue - 512) > joystickDeadzone || abs(yValue - 512) > joystickDeadzone) {
      if (millis() - lastMoveTime >= moveInterval || bombPlaced) {
        updatePlayerPosition(xValue, yValue);
        lastMoveTime = millis();
      }
    }
    
     // Check if the joystick button is pressed
    if (digitalRead(buttonPin) == LOW) {
      if (!bombPlaced && flagBomb) {  // Place a bomb if none is already placed and the flag is set
        placeBomb();
      }
    } else {
      // Check if a bomb is placed and the detonation flag is set
      if (bombPlaced && detonateFlag && millis() - bombLastPlacedTime > bombInterval) {
        detonateBomb(); // Detonate the bomb if conditions are met
      }
    }

    displayWalls(); // Display the walls on the LED matrix
    displayBlinkingPlayer();   // Display the player's blinking position on the LED matrix
    displayBlinkingBomb();     // Display the blinking bomb on the LED matrix
    checkGameWin();  // Check if the player has won the game
    displayGameDetails();
}

void displayGameDetails() {
  unsigned long elapsedTime = millis() - timerGame;
  int seconds = elapsedTime / 1000;
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(seconds);
  lcd.print("s");
  lcd.setCursor(0, 1);
  lcd.print("Lives: ");
  lcd.print(livesPlayer);
}

void checkGameWin() {
  if (allWallsEliminated()) {
    handleGameWin();
  }
}

// Check if all the walls have been removed
bool allWallsEliminated() {
  for (int row = 0; row < matrixSize; row++) {
    for (int column = 0; column < matrixSize; column++) {
      if (walls[row][column]) {
        return false;
      }
    }
  }
  return true;
}

void handleGameWin() {
  // Record the end time of the game
  unsigned long gameEndTime = millis();

  // Calculate the total game time
  unsigned long gameTime = gameEndTime - gameStartTime;

  // Calculate the bonus based on the number of broken walls
  int wallBreakBonus = countWallsBroken() * 10;
  // Update the global score with the wall break bonus and game time

  score += wallBreakBonus + gameTime;
  Serial.print("Score: ");
  Serial.println(abs(score));

   // Display the winning animation on the LED matrix
  displayWinAnimation();

  // Reset the game state to prepare for a new game
  resetGameState();
}

void resetGameState() {
  // Reset flags and variables to their initial state
  //lcd.clear();
  wallsGenerated = false;    // Reset the flag indicating whether walls have been generated
  displayHiFlag = true;  
  displayWelcome = true;    // Set the flag to display the "hi" message
  bombPlaced = false;        // Reset the flag indicating whether a bomb is placed
  detonateFlag = false;      // Reset the flag indicating whether to detonate a bomb
  generateRandomWalls();     // Generate a new random wall configuration
  gameStartTime = millis();   // Record the current time as the start time of the new game
}


void displayWinAnimation() {
  const uint64_t smileyImage = 0x3c42a581a599423c;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your score : ");
  lcd.setCursor(0,1);
  lcd.print(score);
  displayImage(smileyImage);
  playWinSound();
  delay(2000);
  lc.clearDisplay(0);
  lcd.clear();
}

// Count how many walls were broken for the score
int countWallsBroken() {
  int count = 0;
  for (int row = 0; row < matrixSize; row++) {
    for (int column = 0; column < matrixSize; column++) {
      if (!walls[row][column]) {
        count++;
      }
    }
  }
  return count;
}

// Function with which we make sure that no walls are generated above or next to the player, to allow movement at the beginning of the game

bool isPlayerSurrounded(int x, int y) {
  // Check if there are walls in the neighboring cells
  if ((x > 0 && walls[y][x - 1]) || (x < matrixSize - 1 && walls[y][x + 1]) ||
      (y > 0 && walls[y - 1][x]) || (y < matrixSize - 1 && walls[y + 1][x]) ||
      (x > 0 && y > 0 && walls[y - 1][x - 1]) || (x < matrixSize - 1 && y > 0 && walls[y - 1][x + 1]) ||
      (x > 0 && y < matrixSize - 1 && walls[y + 1][x - 1]) || (x < matrixSize - 1 && y < matrixSize - 1 && walls[y + 1][x + 1])) {
    return true;
  }
  return false;
}


void generateRandomWalls() {
  //timerGame = millis();
  generateRandomPosition();  // Generate a new random player position

  // Generate random walls in the matrix
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize; j++) {
      walls[i][j] = random(2) == 0; // Randomly set each cell as a wall or empty space
    }
  }

  // Ensure that the player is not surrounded by walls
  while (isPlayerSurrounded(playerX, playerY)) {
    // Regenerate walls until the player is not surrounded
    for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
        walls[i][j] = random(2) == 0;
      }
    }
  }
}

void generateRandomPosition() {
  // Generate a random X and Y coordinate for the player
  playerX = random(matrixSize);
  playerY = random(matrixSize);

  // Check if the generated position is valid
  while (walls[playerY][playerX] || isPlayerSurrounded(playerX, playerY)) {
    // If the position is not valid, generate new random coordinates
    playerX = random(matrixSize);
    playerY = random(matrixSize);
  }
}

// Function to display the walls on the display
void displayWalls() {

  for (int row = 0; row < matrixSize; row++) {
    for (int column = 0; column < matrixSize; column++) {
      if (walls[row][column]) {
        lc.setLed(0, row, column, true);
      }
    }
  }
}

void displayBlinkingPlayer() {
  unsigned long currentMillis = millis();
  static bool playerLEDState = false;

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    playerLEDState = !playerLEDState;

    lc.setLed(0, playerY, playerX, playerLEDState);
  }
}

void displayBlinkingBomb() {
  unsigned long currentMillis = millis();
  static bool bombLEDState = false;

  if (bombPlaced && detonateFlag) {
    if (currentMillis - bombPreviousMillis >= bombIntervalBlinking) {
      bombPreviousMillis = currentMillis;
      bombLEDState = !bombLEDState;

      lc.setLed(0, bombY, bombX, bombLEDState);
    }
  }
}

const int moveDelay = 200;

unsigned long lastMoveMillis = 0;

void updatePlayerPosition(int xValue, int yValue) {
  // Calculate the change in X and Y coordinates based on joystick input
  int deltaX = xValue - 512;
  int deltaY = yValue - 512;

  // Store the player's current position
  int previousX = playerX;
  int previousY = playerY;

  lc.setLed(0, previousY, previousX, false);

  unsigned long currentMillis = millis();

  if (currentMillis - lastMoveMillis >= moveDelay) {
    // Check joystick input for X-axis movement
    if (abs(deltaX) > joystickDeadzone) {
      if (deltaX > 0 && playerX < matrixSize - 1 && !walls[playerY][playerX + 1]) {
        playerX++;
      } else if (deltaX < 0 && playerX > 0 && !walls[playerY][playerX - 1]) {
        playerX--;
      }
    }

    // Check joystick input for Y-axis movement
    if (abs(deltaY) > joystickDeadzone) {
      if (deltaY > 0 && playerY < matrixSize - 1 && !walls[playerY + 1][playerX]) {
        playerY++;
      } else if (deltaY < 0 && playerY > 0 && !walls[playerY - 1][playerX]) {
        playerY--;
      }
    }

    // Check if the player's position has changed
    if (playerX != previousX || playerY != previousY) {

      // Turn on the LED at the new player position
      lc.setLed(0, playerY, playerX, true);

      // Set the flagBomb to true, indicating that the player can place a bomb
      flagBomb = true;
    }

    lastMoveMillis = currentMillis;
  }
}

void placeBomb() {
   // Check if a bomb is not already placed
  if (!bombPlaced) {
    // Set the bomb's position to the player's current position
    bombX = playerX;
    bombY = playerY;
    bombPlaced = true;
    detonateFlag = true;
    // Turn on the LED and buzzer to indicate the bomb placement
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    playBoomSound();
    bombLastPlacedTime = millis();
  }
}

void detonateBomb() {
  // Check if a bomb is currently placed
  if (bombPlaced) {
    // Eliminate walls in all four directions from the bomb
    eliminateFirstWallInDirection(bombX, bombY, 1, 0);
    eliminateFirstWallInDirection(bombX, bombY, -1, 0);
    eliminateFirstWallInDirection(bombX, bombY, 0, 1);
    eliminateFirstWallInDirection(bombX, bombY, 0, -1);

    // Check if the player is within the blast radius
    int deltaX = abs(playerX - bombX);
    int deltaY = abs(playerY - bombY);

    if (deltaX <= bombRadius && deltaY <= bombRadius) {
      // Player is within the blast radius, decrement lives
      livesPlayer--;

      if (livesPlayer <= 0) {
        // Player has no lives left, reset the game
        livesPlayer = 3;
        resetGameState();
      }
    }

    // Clear bomb on the matrix
    lc.setLed(0, bombY, bombX, false);

    // Turn off the LED and buzzer
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);

    // Mark the bomb as no longer placed and ready to detonate
    bombPlaced = false;
    detonateFlag = false;
  }
}


void eliminateFirstWallInDirection(int startX, int startY, int dirX, int dirY) {

  // Iterate in the specified direction until reaching the matrix boundaries

  for (int x = startX + dirX, y = startY + dirY;
       x >= 0 && x < matrixSize && y >= 0 && y < matrixSize;
       x += dirX, y += dirY) {
    if (walls[y][x]) {
      // Eliminate the wall at the current position
      walls[y][x] = false;
       // Turn off the LED at the corresponding position on the display
      lc.setLed(0, y, x, false);
      // Play a sound to indicate the elimination of the wall
      playCrashSound(); 
       // Exit the loop after eliminating the first wall in the specified direction
      break;
    }
  }
}

// Functions for displaying animations (helper code from the site whose name I forgot again (it turns on the LEDs on the matrix and generates the code for you)

void displayHi() {
  const uint64_t hiImage = 0x0052525e52125200;

  unsigned long currentMillis = millis();
  if (millis() - currentMillis < interval) {
    displayImage(hiImage);
    //lc.clearDisplay(0);
  }
  
}

void displayBomb() {
  const uint64_t bombImage =   0x9da5a59da5a59dff;

  unsigned long currentMillis = millis();
  if (millis() - currentMillis < interval) {
    displayImage(bombImage);
    //lc.clearDisplay(0);
  }
  
}

void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte rowData = (image >> (i * 8)) & 0xFF;
    lc.setRow(0, i, rowData);
  }
}
void displayCountdown(int count) {
  const uint64_t countdownImage[] = {
    0x0000000000000000,
    // Define binary representations for numbers 3, 2, 1
    0x0018181c1818187e, // 1
    0x003c6660300c067e, // 2
    0x003c66603860663c, // 3
  };

  if (count >= 0 && count <= 3) {
    displayImage(countdownImage[count]);
    playCountdownSound();
    delay(1000); // Adjust the delay as needed
    lc.clearDisplay(0);
  }
}

// Buzzer functions with relatively different sounds
void playBoomSound() {
  tone(buzzerPin, 400, 100);
  delay(500);
  noTone(buzzerPin);
}

void playCrashSound() {
  tone(buzzerPin, 300, 100); // Reglat frecvența și durata pentru sunetul "CRASH"
  delay(200); // O scurtă pauză între sunete
  noTone(buzzerPin);
}

void playCountdownSound() {
  tone(buzzerPin, 500, 200);
  delay(200);
  noTone(buzzerPin);
}

// A function that helps the buzzer sing Jingles Bells more specially
 void playWinSound() {
  int melody[] = {
    659, 659, 659, 659, 659, 659, 659, 784, 523, 587, 659,
    698, 698, 698, 698, 698, 659, 659, 659, 659, 587, 587,
    659, 587, 784
  };
   int noteDurations[] = {
     8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8
   };
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(buzzerPin, melody[i], noteDuration);
    delay(noteDuration * 1.30); 
    noTone(buzzerPin);
    delay(50);
  }
}
void swipeDecision() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Swipe UP or   ");
  lcd.setCursor(0, 1);
  lcd.print("DOWN to navigate");
}

void loop() {
  if(displayWelcome && displayHiFlag){
      displayHi();
      displayMessage();
      swipeDecision();
      //displayHiFlag = false;
   } else if (displayFlagMenu) {
    processMenuNavigation();
    displayBomb();
  } else {
    handleButtonPress();
    handleJoystickInput();
  }
}

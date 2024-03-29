# IntroductionToRobotics-2023-2024-

Robotics Introduction Course ( 3rd year )
-📍Faculty of Mathematics and Informatics of Bucharest
- 🤖 Documentation
- 🤖 Code
- 🤖 Homeworks

# Content
- 🚨[Homework 1](#homework-1)
- 🚨[Homework 2](#homework-2)
- 🚨[Homework 3](#homework-3)
- 🚨[Homework 4](#homework-4)
- 🚨[Homework 5](#homework-5)
- 🚨[Homework 6](#homework-6)
- 🚨[Homework 7](#homework-7)
- 🚨[Homework 8](#homework-8)
- 🚨[Homework 9](#homework-9)
- 🚨[Homework 10](#homework-10)

# Homework-1
<details>
<summary> <h2> RGB led control with 3 potentiometers 🎮 </h2> </summary>
<h3>Task</h3>
<details>
Utilize a separate potentiometer to independently control each color of the RGB LED (Red, Green, and Blue). This control should be achieved using digital electronics.
</details>

### 🖥 Code : [ The Code 🖥 ](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/blob/main/Homework/RGB_HOMEWORK_1.ino)

### 🕹 Electronic scheme: ![IR schema final](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/94e1bbc6-0383-4f4e-93e0-0ff483e604af)


### 📸 Electronic circuit in real life:
![ir 4](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/ea5f1460-1497-47f4-814b-68cbce823bef)


![ir 3](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/f2147743-0050-4abc-8c60-3fa82d5a2e7c)

### 📽 Video : [ RGB Video 🧨](https://youtu.be/yFtEyoPxVpA)

### 🔌 Important : 
- The red LED has too much internal resistance, and a 330 resistor further reduces the current reaching the LED
- So, for the red LED, I use a resistance of 10, so we allow a current with a higher intensity to reach the LED

</details> 

# Homework-2
<details>
<summary> <h2> Elevator 🛗 </h2> </summary>
  
This assignment involves simulating a 3-floor elevator control system using
LEDs, buttons, and a buzzer with Arduino.
You'll acquire expertise in utilizing button state transitions, applying debouncing methods, and orchestrating various components to simulate real-life situations.
## Tasks
### Design a control system that simulates a 3-floor elevator using the Arduino platform.
### LED Indicators: 
- Three LEDs, each symbolizing a different floor, with one lighting up to show the current floor. Another LED indicating the elevator's status, blinking during movement and 
staying steady when stationary.
### Buttons:
- Create 3 buttons for floor call requests. When pressed, the elevator should simulate movement towards the corresponding floor after a brief delay (2-3 seconds).
### Buzzer: The buzzer should produce brief sounds in the following situations:
              - When the elevator arrives at the requested floor (resembling a "ding").
              - During elevator door closing and movement (with distinct sounds for each action).
### State & Timers:
- If the elevator is already at the chosen floor, pressing the button for that floor does nothing. Otherwise, after a button press, the elevator should first wait for the doors to close and then move to the desired floor. If the elevator is already moving, it should either delay the action or queue it for after completing its current tasks.



### 🖥 Code : [ The Code 🖥 ](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/blob/main/Homework/ELEVATOR_HOMEWORK_II.ino)

### 🕹 Electronic scheme:![schema_ir_2](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/6a709726-ad35-45eb-980c-59fab8d0455c)

### 📸 Electronic circuit in real life:
![poza1_ir_2](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/6c3cefd1-6c12-4939-9919-63c0e31eb168)
![poza2_ir_2](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/8b36885d-4b3b-407d-9781-5d5c582b716d)

### 📽 Video : [ ELEVATOR VIDEO 🛗](https://youtube.com/shorts/OGeQ3VK3NGE?feature=share)

</details>

# Homework-3
<details>
<summary> <h2> 7- segment display drawing </h2> </summary>
To operate the segment and create drawings on the display, you will employ the joystick for precise control. The transition between segments must feel organic, ensuring that they move smoothly from their current location to adjacent positions, while avoiding passing through obstacles or "walls."

## Task 

- Begin at the starting point, which should be located at the decimal point (DP). The current position will consistently blink, regardless of whether the segment is active or not. Utilize the joystick to transition between neighboring positions, as indicated in the table for the appropriate movements. A brief press of the button will toggle the segment's state between ON and OFF, while a prolonged press of the button will reset the entire display by deactivating all segments and relocating the current position to the decimal point.
-  ### Components : 
                - 1 7-segment display
                - 1 joystick
                - resistors and wires (perlogic)
   
- ### Tabel with cases :
<img width="294" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/beaa7d3f-8ca8-4410-9803-9875ad7518bd">



### 🖥 Code : [ The Code 🖥 ](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/blob/main/Homework/SEGMENT_HOMEWORK_III.ino)

### 🕹 Electronic scheme: ![ir_3](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/7584b217-328a-480e-b98e-504ca061965c)


### 📸 Electronic circuit in real life:
![ir_p_3](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/77f75aaf-c00c-450b-887b-41b630c5b583)

![ir_p2_3](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/001baccc-71d5-4ff9-b7f3-60d259fb01bf)

### 📽 Video : [ 7-segment drawing](https://youtu.be/vHeJH_eb4iU)

### 🔌 Important : 
## The axes of the merging joystick will be taken into account (that difference is explained in the way and in the code)
## Something useful for me : [Something](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/files/13293533/Facultate.3.pdf)


</details> 

# Homework-4
<details>
<summary> <h2> Stopwach ⏲  </h2> </summary>
I have implemented a stopwatch timer that measures time in tenths of a second and includes a feature to save lap times.

### Task 
To implement a stopwatch.
Initial state : 000.0.
📍 Make sure you put the dot ”.”
## Components 
            - 7-segment display
            - 3 buttons
            - resistors and wires 
            - Bonus : I was thinking of using a led / buzzer to check the operation of the buttons
## The functionality of the buttons

            ⚙️ Button 1 - START / PAUSE 
            📍 Important to know : The display will indicate "000.0". Upon pressing the Start button, the timer will commence.
            📍 Counting mode :
                  - Button 2 doesn't work 
            📍 In pause mode :
                  - Button 2 can reset the display back at initial state ( if it is pressed ) 
                  - Button 3 doesn't work 
                  
            ⚙️ Button 2 - RESET
            📍 Important to know : Reset functionality is available when the timer is in pause mode. 
            📍 Button 2 and the timer is still couting othing happens .
            📍 If in lap viewing mode, resetting will also clear saved laps.

            ⚙️ Button 3 - Save the lap time when in counting mode and cycle through the last four saved laps.
            📍 Important to know : 
                - Counting mode -> every time you press the lap button ( button 3 )
                - This save the timers value up to 4 times when pressed the fifth time it overrides the one saved first.
              
### 🖥 Code : [ The Code 🖥 ](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/blob/main/Homework/STOPWACH_HOMEWORKIV.ino)


### 🕹 Electronic scheme:![ir_5](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/78b6ffd3-abde-4524-9f84-64fa78e4670b)


### 📸 Electronic circuit in real life: 


<img width="500" hight="500" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/88dac72a-e223-45ef-8bc4-714e24ed891a">

<img width="500" high="500" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/8458a06b-b6b6-4f53-8cd4-e5ddd05b7ac7">





### 📽 Video : [Stopwach ⏲ ](https://youtube.com/shorts/kbCsYBEE1Zw)



</details>

# Homework-5
<details>
<summary> <h2> Pseudo-Smart Environment Monitor and Logger 💻 </h2> </summary>
  
Create a "Smart Environment Monitor and Logger" with Arduino, employing diverse sensors to collect environmental data. The system will store this data in EEPROM, offer visual indications through an RGB LED, and enable user interaction via a Serial Menu.

### Task 
## Components 
            - Arduino Uno Board
            - Ultrasonic Sensor (HC-SR04)
            - LDR ( Light-Dependent Resistor )
            - RGB LED
            - Resistors
            - Breadboard and wires
## Menu Structure
            - 1. Sensor Settings
               📍- 1.1 Sensors Sampling Interval 
               📍- 1.2 Ultrasonic Alert Threshold 
               📍- 1.3 LDR Alert Threshold
               📍- 1.4 Back to the menu
            - 2. Reset Logger Data 
               📍- 2.1 Yes 
               📍- 2.2 No
            - 3. System Status 
               📍- 3.1 Current Sensor Readings
               📍- 3.2 Current Sensor Settings 
               📍- 3.3 Display Logged Data
               📍- 3.4 Back to the menu
            - 4. RGB LED Control
               📍- 4.1 Manual Color Control 
               📍- 4.2 LED : Toggle Automatic ON/OFF
## Important
### ⚙️ 1.1 
<details> Input a value between 1 and 10 seconds when prompted; this will serve as the sampling rate for the sensors. Choose whether to use a separate value for each sensor or the same value for both. </details>

### ⚙️ 1.2
<details> 
Set a threshold for the ultrasonic sensor, indicating proximity (min or max). Receive an alert if the sensor value exceeds the threshold, accompanied by a red LED indication in Automatic Mode (refer to section 4.2). </details>

### ⚙️ 1.3
<details> 
Request a threshold value for the LDR sensor, determining if it signifies the minimum or maximum value (e.g., indicating nightfall). When the sensor surpasses the threshold, generate an alert, possibly a message. If the LED operates in Automatic Mode, turning red signifies any sensor exceeding the specified range.
</details>

### ⚙️ Reset 
<details> 
ARE YOU SURE? 
  - <b>YES</b> -> i can reset one of this sensors or both -> main menu
  - <b>NO</b> -> back to Main Menu
</details>

### ⚙️ 3.1 
<details>
  
Continuously display sensor readings at the specified sampling rate from all sensors. Implement a method to exit this process, such as pressing a designated key, and inform the user of this exit method through a message.

</details>

### ⚙️ 3.2 
<details> 
Displays the sampling rate and threshold value for all sensors.
</details>

### ⚙️ 3.3
<details>
  Displays last 10 sensor readings for all.
sensors.
</details>

### Manual Color Control 
<details>
  Set RGB colors manually .
</details>

### ⚙️ ON/OFF
<details>
  - <b> ON </b> -> led color should be <color> GREEN </color>color> and <color> RED </color> if is it on ALERT mode .
  - <b> OFF </b> -> Led should use the last saved RGB values .
</details>

### 🖥 Code : [ The Code 🖥 ](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/blob/main/Homework/MENU_HOMEWORK_V.ino)
### 🕹 Electronic scheme:![WhatsApp Image 2023-11-20 at 10 35 11_edf0d5b3](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/4c8819ae-2183-4a0a-b3e2-54e1758eea06)


### 📸 Electronic circuit in real life: 
<img width="295" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/76b5f62b-2c66-4c53-8b0b-3888554f5980">
<img width="291" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/7c7c4830-df4b-4325-8973-34e16d8d3a2d">
<img width="296" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/52492d38-05a8-401c-9602-bf843d1a328a">

### 📽 Video : [ Menu ](https://youtu.be/zxJAoutdkxM)

</details>

# Homework-6
<details>
<summary> <h2> MATRIX MINI GAME - BOMBERMAN 💣 </h2> </summary>
  
### Tasks

Create a compact game utilizing an 8x8 matrix featuring three distinct elements: a player (slowly blinking), bombs/bullets (rapid blinking), and walls (non-blinking). This serves as an introductory exercise for your matrix project. The fundamental concept involves generating walls across the map (occupying 50% - 75% of the space) and navigating with the player to dismantle them.

## Components 
            • Arduino Uno Board ⌨️
            • Joystick 
            • 8x8 LED Matrix
            • MAX7219
            • Resistors and capacitors as needed
            • Breadboard and connecting wires
            • LED 🚨
            • Buzzer 🔊
## Details 
            🐱 Setup game 
                When the game starts, a "hi" message is displayed on the matrix, creating an inviting atmosphere. 
                Press the joystick button to initiate the game. 
                A countdown sequence (3, 2, 1) is displayed, signaling the start of the gameplay.
                
<img width="217" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/65a77ce4-0959-4af3-a3c2-989432745f6d">
<img width="217" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/6b946d37-d482-4849-8821-a40eb1a009bf">
<img width="217" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/82241178-b397-4908-aa76-6ff6198a3ba3">
<img width="217" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/09036ea9-441c-4bed-94a9-2e2aeb32cad9">

            🐱 Player Control
                Use the joystick to move the player LED within the matrix.
                The player LED blinks slowly, providing a visual indicator of its position.
                The player can move up, down, left, right without going through walls.
            
            🐱 Wall Destruction
                Navigate the player to break walls strategically.
                Walls cover 50% - 75% of the matrix initially.
                Breaking walls contributes to the player's score.
                Remember, when generating a new map, the player is strategically positioned in such a way that he can move.

            🐱 Bomb Placement
                Press the joystick button to place a bomb.
                The bomb blinks rapidly, indicating its presence.
                Bombs eliminate walls in all four directions upon detonation.

            🐱 Scoring
                Score is calculated based on the time taken to win and the number of walls broken.
                A bonus is awarded for each wall destroyed.
               

            🔔 Winning the Game
                The game is won when all walls are eliminated. 
                A winning animation, accompanied by a festive jingle, is displayed on the matrix. The total score, 
                including bonuses, is presented in the Serial Monitor.
                
            ♻️ Resetting the Game
                After winning or when starting a new game, the system resets. 
                Press the joystick button again to initiate a new game.

## Matrix 
<img width="400" hight="500" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/95e1beea-e6bb-4dc6-af20-dd0617830be4">

My matrix is ​​of type AS. I used this table to make the correct connections

### 🖥 Code : [ The Code 🖥 ](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/blob/main/Homework/matrix_mini_game.ino)

### 🕹 Electronic scheme: 
<img width="400" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/050bc037-00db-4902-9b37-8958375c7ca7">
 


### 📸 Electronic circuit in real life:
<img width="230" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/0622e265-0ba4-4b74-bac7-1cfb0ad5f0e8">
<img width="230" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/70ac8057-c796-4ed6-b34c-41ee8b78ba13">
<img width="230" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/5d40b922-4d6b-4b9f-84e4-c7c351ec7763">
<img width="230" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/b0b879ad-1ac1-45f8-ad04-a0f2289183ca">


### 📽 Video : [ Mini Matrix Bomberman Game 💣 ](https://youtu.be/sQofCCTeTTw)

### 🔌 Important : 
- The red LED has too much internal resistance, and a 330 resistor further reduces the current reaching the LED
- So, for the red LED, I use a resistance of 10, so we allow a current with a higher intensity to reach the LED
- The LedControl library is properly installed and configured for the game to function correctly.

</details> 

# Homework-7

<details>
<summary> <h2> LCD MATRIX 🌐 </h2> </summary>
  
### Tasks
FEATURES FOR THE GAME LCD
## Components 
            • Arduino Uno Board ⌨️
            • Joystick 
            • 8x8 LED Matrix
            • MAX7219
            • Resistors and capacitors as needed
            • Breadboard and connecting wires
            • LED 🚨
            • Buzzer 🔊
            • LCD
### INTRO MESSAGE LCD
      🐱 The project lights up, this message will display the message   
         "HI!" on the matrix, and the welcome messages will be played on 
          the LCD:
                                "WELCOME PLAYERS"
                                "ARE YOU READY?"
                                "FOR THIS GAME"
                                "BOMBERMAN"
                                
### RULES FOR NAVIGATE 

  🤓 After displaying the welcome message on the matrix screen, a representative picture for the menu will appear.
<img width="300" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/0b96c78d-9b7d-4e0e-b5d5-38dcce74c418">


  🤓 During this time, the instructions will appear on the LCD screen. You can navigate through the menu only Up or Down (obviously, using the joystick). 
    To enter the menu, it is only necessary to scroll down or up and the options will appear

  
  <img width="300" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/140144d0-44a0-4718-bc11-3b4ae2250e69">

### MENU
            🕹️ START GAME
                • If you click on this option, the game will start (see homework 6 for the game's functionalities)
            🕹️ SETTINGS
                • LCD CONTRAST
                • MATRIX CONTRAST
                • RETURN TO MENU
            🕹️ ABOUT
                • Shows the creator's name and github.

### SETTINGS FUNCTIONALITIES

        • LCD CONTRAST 
           The user sets the contrast he wants on the LCD, he will be       
           greeted when he chooses this sub-option of the SETTINGS option 
           of the navigation rule (up or down to increase or decrease the 
           contrast level, respectively), and pressing the left button will 
           take him to RETURN TO MENU
           
  <img width="300" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/9b93af15-a85b-4578-9898-148ed38895da">

          When the desired brightness has been decided, swiping to the right allows him 
          to see that the value has been saved,
          and if he clicks up he will be sent back to the options in SETTINGS.

  <img width="300" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/ffe0da2f-b15d-4c12-b808-a5c02dac1c5e">
  
          Moreover, during the increase/decrease slide, representative messages will 
          appear on the screen, as well as the brightness level
          
  <img width="300" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/a395b275-4c73-403e-9b82-813770ab70e2">

           • MATRIX CONTRAST 
           The user sets the contrast he wants on the MATRIX, he will be       
           greeted when he chooses this sub-option of the SETTINGS option 
           of the navigation rule (up or down to increase or decrease the 
           contrast level, respectively), and pressing the left button will 
           take him to RETURN TO MENU
           
  <img width="300" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/9b93af15-a85b-4578-9898-148ed38895da">
  
          When the desired brightness has been decided, swiping to the right allows him 
          to see that the value has been saved,
          and if he clicks up he will be sent back to the options in SETTINGS.

  <img width="300" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/ffe0da2f-b15d-4c12-b808-a5c02dac1c5e">
  
          Moreover, during the increase/decrease slide, representative messages 
          will appear on the screen, as well as the brightness level
          
  <img width="300" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/a395b275-4c73-403e-9b82-813770ab70e2">

### Bonus 
        During the game, the game time (in real time) and 
        the remaining lives will appear on the LCD.
        At the end of the game, the score will be displayed together with a sound 
        and smiley face ( Homework 6 ) and you will return to the main menu.
<img width="300" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/2c6cafe9-02b2-43a4-83b2-29a8dded2436">

### 🔌 Important 

        Lives decrease when the player is within the radius of the bomb at a distance of 1.
        Thus, the lives will decrease, and at the moment of 0 lives, the game ends and you return to the menu.

    
### 🖥 Code : [ The Code 🖥 ](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/blob/main/Homework/lcd%20matrix.ino)

### 🕹 Electronic scheme: 
- Laboratory source
<img width="400" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/8fc92705-f607-47a6-b0ee-b2798439c8e2">

### 📸 Electronic circuit in real life:
<img width="230" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/0b76c207-54f7-4afe-9f62-b7985685a231">
<img width="230" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/08825859-64f0-41b3-9f00-f306360592d5">
<img width="230" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/d8dc45d4-e6ed-47fa-990b-2b3782e590bc">
<img width="230" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/d09a24e5-1c29-4689-a03d-8d188f430039">



### 📽 Video : [ Mini Matrix Bomberman Game LCD 💣 ](https://youtu.be/dTc4CBEA8FU)

### 🔌 Important : 
- The red LED has too much internal resistance, and a 330 resistor further reduces the current reaching the LED
- So, for the red LED, I use a resistance of 10, so we allow a current with a higher intensity to reach the LED
- The LedControl library is properly installed and configured for the game to function correctly.

</details> 

# Homework-8
<details>
  
<summary> <h2> Arduino radar with ultrasonic sensor 🔆 </h2> </summary>
  
### Task
                At its core, the project features an ultrasonic sensor attached to a servo motor,
                providing a sweeping lateral motion covering a 180-degree span. 
                This sensor diligently scans its surroundings within an unspecified distance.(30 unites)
                The construction process initiates with establishing hardware connections to seamlessly 
                translate pin numbers into subsequent code.
                Initially, I interfaced the ultrasonic sensor with the Arduino Board:
                🔆 VCC to 5V
                🔆 GND to GND PIN
                🔆 TRIG to Pin 2
                🔆 ECHO to Pin 3
                
                Subsequently, the servo motor found its place in the scheme:

                🔆 RED wire to 5V
                🔆 BROWN wire to GND
                🔆 ORANGE wire to Pin 4

                To ensure a secure connection, resistors were used instead of glue to affix the ultrasonic sensor to the servo motor.

  ## Components 
            • Arduino Uno Board ⌨️
            • Ultrasonic sensor
            • Servo motor
            • Resistors 
            • Breadboard and connecting wires
            • 2 LED 🚨
## Result

Moving on to the coding phase, I meticulously crafted a function to gather data from the sensor. Within a loop, I implemented instructions for the servo motor to gracefully pivot from left to right, covering a 180-degree span. The yellow sensor light remains on when no obstacles are detected, while the red LED illuminates when an obstacle is within the sensor's range.

### 🖥 Code : [ The Code 🖥 ](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/blob/main/Homework/servomotor.ino)

### 📸 Electronic circuit in real life:
<img width="260" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/02d5719c-d483-41e0-9576-846939997d56">
<img width="260" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/6c38e8e6-77c4-4c35-abb9-a01954dd9cfe">
<img width="260" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/f5a37717-4a05-4a9b-9236-c4b179fd071d">
<div align="center"> 
<img width="458" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/1141d368-c1e8-4af0-9d11-fb06572b9d33">
</div>

### 📽 Video : [ Arduino radar with ultrasonic sensor 🔆](https://youtube.com/shorts/4hARGa3JwM8)

### 🔌 Important : 
- The red LED has too much internal resistance, and a 330 resistor further reduces the current reaching the LED
- So, for the red LED, I use a resistance of 10, so we allow a current with a higher intensity to reach the LED

</details> 

# Homework-9
<details>
  
<summary> <h2> Sequence memory game 🔆 </h2> </summary>
  
### Task
                  Welcome to the LED Memory Challenge, a Simon Says-inspired game that puts your memory 
                  skills to the test! Equipped with 4 LEDs (each with resistors), 
                  4 buttons, and 1 buzzer, this game promises a delightful mix of visual and auditory challenges. 
                  The goal? Replicate a randomly generated LED pattern within a reasonable 3-second timeframe.

  ## Components 
            • Arduino Uno Board ⌨️
            • Buzzer
            • 4 buttons
            • Resistors 
            • Breadboard and connecting wires   
            • 4 LEDs 🚨
## How it works

# Initialization:

🚨 As you power up the Arduino, a festive rendition of "Jingle Bells" sets the tone for the game.
With a maximum of 13 levels, the challenge awaits. Any mistakes prompt a reset, inviting you to try again.

# Gameplay:

🚨 Pressing any button starts a new game, unveiling a randomly generated LED pattern.
The pattern involves illuminating specific LEDs in sequence, testing your memory prowess.

# Player Input:

🚨 Your task is to reproduce the pattern within 3 seconds. Press the corresponding buttons in the correct order.

# Feedback:

🚨 Successfully replicating the pattern triggers a pleasant sound from the buzzer.
Any errors result in a different sound, signifying an incorrect move.

# Time Constraint:

🚨 There is a 3-second window between each button press. Failure to press within this timeframe restarts the game, maintaining a dynamic pace.

# Levels and Progression:

🚨 Conquering each level unlocks the next, escalating the complexity and length of the patterns.
Aim to reach the pinnacle of 13 levels for a triumphant experience.

# Challenge Restart:

🚨 Failing to press within 3 seconds or making an error initiates a quick restart, inviting you to take on the challenge anew.

### 🖥 Code : [ The Code 🖥 ](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/blob/main/Homework/MemoryGame.ino)

### 📸 Electronic circuit in real life: 
<img width="260" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/ec277fec-2e45-495e-9367-11e66fde687e">
<img width="260" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/4f21755c-b10c-4ebf-a022-99d81dc22882">
<img width="260" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/6ac4ee4b-4879-4432-9f62-bd96fff82b93">


### 📽 Video : [ Memory game🔆](https://youtu.be/dAf1eE8GmaE)

### 🔌 Important : 
- The red LED has too much internal resistance, and a 330 resistor further reduces the current reaching the LED
- So, for the red LED, I use a resistance of 10, so we allow a current with a higher intensity to reach the LED

</details> 

# Homework-10
<details>
  
<summary> <h2> Alarm Clock 🔆 </h2> </summary>
  
### Task

Alarm Clock with LCD, Buzzer, and RGB. Set to an absolute time (30 seconds). When it reaches that time, the alarm triggers (buzzer sounds, and RGB LED flashes). It can be stopped by pressing a button.

  ## Components 
            • Arduino Uno Board ⌨️
            • Buzzer
            • Button
            • Resistors 
            • Breadboard and connecting wires   
            • RGB🚨
            • LCD
## How it works

# Setting the Alarm Time:

🚨 Begin by configuring the alarm for an absolute time of 30 seconds.

# Alarm Activation:

🚨 Once the set time is reached, the alarm triggers. This involves the buzzer producing a sound, the RGB LED starting to flash, and the red LED turning on immediately when the user presses the designated button.

# User Interaction - Stopping the Alarm:

🚨 Users have the ability to stop the alarm manually by pressing a designated button. Upon button press, the red LED lights up, providing a visual confirmation that the alarm has been successfully stopped.

# Continuous Countdown Display:

🚨 As time progresses from 0 to 30 seconds, and every 30 seconds thereafter, a dynamic display on the LCD screen showcases the elapsed time. This provides users with a visual indication of the countdown.

# Engaging User Experience:

🚨 The combination of auditory (buzzer), visual (flashing RGB LED, LCD display), and tactile (button press activating the red LED) elements creates an engaging and interactive alarm experience. Users can easily perceive the passage of time, stop the alarm with a button press, and receive visual confirmation of the action through the red LED. The LCD display continuously updates to show the remaining time in the countdown.

### 🖥 Code : [ The Code 🖥 ](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/blob/main/Homework/AlarmClock.ino)

### 📸 Electronic circuit in real life: 
<img width="260" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/f4c6ca02-eb0b-4360-8187-98b72726f368">
<img width="260" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/b30f9e32-d378-4bcf-b3e6-ad0d96e73dec">
<img width="260" alt="image" src="https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/2b3cd7cf-c2ce-4322-8b74-2491a1b08d31">


### 📽 Video : [ Alarm clock 🚨 ](https://youtu.be/fQbxWyLY75M)


## Important
You can see in the last picture that the alarm sounds continuously if the button is not pressed, I could not film because it was late and my flatmate was sleeping. But in essence, it's exactly like the phone alarm that rings continuously if you don't deactivate it and you can cancel it at any time, as it rings anyway after 30 seconds
</details> 


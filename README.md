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
- 🚨to be continued.............
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
![rocket-3972_256](https://github.com/anacimpeanu/IntroductionToRobotics-2023-2024-/assets/115561036/f3795070-b819-4e07-bff8-05112beb6c84)

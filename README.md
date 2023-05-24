# MTRX2700 Major Project - Manshatronics
## Overview

## Modules
Simon Says- 
Module uses GPIO inputs, LEDs, and an LCD board
In the puzzle, the player must pass 4 levels of increasing difficulty wherein they must match the LED lit up by the game with the corresponding LED a consecutively for x number of times without error.
Failing to press the correspond button will result in the game restarting from the beginning. 
At the completion of each level, the LED wheel will display certain LEDs of different colours which will be key to solving the next puzzle.

## Group Contributions
Neel – High five (main), (assist) CAT-Scan and LiDar lock (back-up puzzle) 

Jestin – Simon says (main), RemotePuzzle (main), (assist) servo movement function in high five 

Josh - Connect the wires  

Mansh – Magnetic Detector (main), RemotePuzzle (assist)  

Zach – CAT Scan (main) 

## Git Layout
## System Level Overview

### High Five


### CAT Scan
In this puzzle, the user must employ critical problem solving skills to overcome this puzzle. The puzzle starts by first displaying a clue via PuTTY. "All problems can be solved with a CAT scan. They begin with a simple: 10". The puzzle is acompanied with a cardboard cutout with 5 empty slots that the user can either fill in or leave empty. The solution to this puzzle is to input in binary the ASCII values of the letters of CAT, meaning '00011', '00001', '10100'.

### LiDar lock
This puzzle uses the PTUs LiDAR functions to create an interactive and futuristic puzzle. This puzzle involves the player "high fiving" the LiDAR, which starts the game, and sets the LiDAR lock puzzle into motion. The PTU will rotate into a random position, at which point the player will need to place an object in the line of sight of the LiDAR. The object must also be placed at a specific distance away from the LiDAR, and when this distance is achieved, the an LED on the discovery board will light up. Once this distance is reached, the user must hold the object at that position for 3 seconds, after which the LiDAR will move into its next position. There is a total of 3 different  positions that the user must complete with various distances to finish the puzzle. In addition to this, the user has a countdown timer of 10 seconds that only pauses when the player is in the correct position for that specific lock. If this countdown timer runs out, the game resets back to the first lock, and the player must try again.

The program for this puzzle was a backup code initially, so there are a few minor flaws within the code. In specific, the timer counts occasionally skip counts when during the puzzle. Intially, we suspected this occured due to the program running heavy tasks following the timers and to minimise these we ensured that the time-sensitive tasks were prioritised. However, this didn't solve the issue. In addition, we attempted to use an interupt based approach as opposed to polling. In which case, there were issues occuring with the interupt not raising a flag for when a given event occurs and we were not able to execute this in time. Ultimately, the timer issue in this case would most likely the result of using polling and is something to be focused on more next time.

**Files Overview**
- `main.c`
  - This file calls the movement function and HAL  initialisation functions, whilst also managing the LEDs that appear when the user places the object at the correct distance
- `last_period.c`
  - This function reads the values from the PTU LiDAR unit, determining how long a beam of light takes to reflect back to the PTU
  - The code checks the state of GPIO pin GPIOA_PIN_8 using HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8). It assumes that this pin is connected to the same light signal being captured by TIM1 channel 1.
  - If the pin is set to high (1), it means that the input signal has experienced a rising edge. In this case, the rise_time variable is updated with the value of IC_Val1. On the other hand, if the pin is not set to high (0), it means that the input signal has experienced a falling edge. In this case, the last_period variable is updated with the difference between IC_Val1 (current captured value) and rise_time (value captured during the previous rising edge).
- `movement.c`
  - This functions uses the speed of light calculations as well parameters regarding the desired yaw and pitch of the PTU to rotate the PTU to a specific location, in order to set new lock positions.
- `Lock.c`
  - This function contains the code for the 3 different LiDAR positions and distances at which the object will need to be placed
  - It uses the last period calculations as well as a timer function to count how long the user has held up the object at the correct location, as well as how long the user has not held up the object at the correction, such that the countdown timer can be decremented.



### Simon Says
Module uses GPIO inputs, LEDs, and an LCD board
In the puzzle, the player must pass 4 levels of increasing difficulty wherein they must match the LED lit up by the game with the corresponding LED a consecutively for x number of times without error.
Failing to press the correspond button will result in the game restarting from the beginning. 
At the completion of each level, the LED wheel will display certain LEDs of different colours which will be key to solving the next puzzle.
**Files Overview**
- `main.c`
  - This file contains code that allows for the calibration of the game. The calibration process involves the user pressing each button, with the corresponding LED on the
    board lighting up, allowing the user to see what button each light corresponds to.
  - A timer is also set to ensure the user does not take too long to press the button, and if the user does, the program will reset to the start
  - In addition, an LCD screen acts as the UI, providing simple instructions and showing the timer countdown
  - It also controls the activation and movement between the various levels of the game
 
- `level1 - level4.c`
  - Essentially controls the progression of each level of the game
  - Each level will follow the same method:
     - It will display one light at a time, and the user is required to press the corresponding button on the breadboard
     - If the user gets a light wrong, the puzzle resets to level 1
     - The difficulty of each level increases by giving the user less time to press the buttons, and by increasing the number of buttons they need to press correctly to get 
       past the level
     - Once the final level is reached, the LCD announces that the game is finished, and by pressing the button on the breadboard, the user can cycle through all the              patterns, which is then used in the wiring puzzle
- `lcd.c`
  - This file contains all functions necessary to operate the LCD screen, including but not limited to:
    - LCD_init : Initialises a 16 column by 2 row LCD screen without the curson
    - LCD_int  : Printing an int on the LCD
    - LCD_string : Printing a string on the LCD
    - LCD_cursor : Creates the cursor to indicate where on the LCD data is to be written
    - LCD_clear : Clears the LCD string
 

### **Power Communications**
This puzzle involves using a previously obtained pattern of LEDs, realizing it represents a pattern of LED connections, and connecting the LEDs with the correct wires. Once the wires are connected correctly, *power is successfully supplied to the LCD display*. There are also 3 knobs (potentiometers) which must each be tuned to the sum of the $x$ and $y$ coordinate values in the magnetometer game. Each coloured wire has a known resistor soldered in its center. The two LEDs each wire must be connected between also have the same resistor, creating a 1:2 ratio voltage divider. The ADC1 channels 5, 6, 7 and 8 are used in regular scan conversion mode to measure the voltages at each LED. If all wires are in the correct position, then the measured voltage should be approximately equal to $\frac{2}{3}V_{REF}$. ADC1 channels 2,3 and 4 are used to measure the voltage at each of the potentiometers. A 10-bit resolution is used (i.e. the measured values are from 0 to 1023), so we can divide by 64 to discreteize the voltage measurements into 16 steps (for each char on the LCD)

##### Files Overview for Power Communications


### **Combination Lock \ Magnetic Detector** 
The combination lock is a puzzle designed to act like an ordinary combination lock, but using the magnetometer of the discovery board instead of an actual physical mechanism. The combination lock would use the magnetometer to find the relative heading of the discovery board, from 0 to 360. In a typical combination lock, different numbers are placed at different angles, and so the discovery board could be placed in a mold so that it can only rotate in place, with the mold having numbers around the edge just as a typical combination lock would. Each number will correspond to a different angle, which can be implemented in the code. The player of the escape room would then need to discover the combination for the lock through the other puzzles, and then input those by spinning the discovery board in a specific way.
**Files Overview for combination lock**
- main.c
  - This file consists of HAL functions to extract raw data from the magnetometer, with all the appropriate register address and the correct startup sequence.
- heading.c (proposed)
  - This file would contain functions that would allow for the raw magnetometer data to be converted to heading data.
  - This would be done by first finding the magnitude of all the magnetic field, by using sqrt(x^2+y^2+z^2). Then, the x,y and z values will be normalised by dividing them 
    by the magnitude. Finally, the true heading can be found by the finding the inverse tan of x/y.
- combination.c (proposed)
  - This file contains code necessary for checking the current angle of the discovery board, and deciphering what number that angle corresponds to.
  - If the user rotates the discovery board the correct amount, the board will flash green. If the user does this incorrectly, the board will flash red, and the user will       need to restart the combination lock from the beginning
  - The user will need to turn to a range of different values acquired throughout the rest of the game, which will be indicated by the numbers on the mold
  - A timer will also be implemented, giving the user a short time period to rotate the board to each value, and if this timeframe is exceeded, the challenge will restart
  
However, due to limitations of the magnetometer sensor module itself, including noise and low sensitivity, this was not a viable idea, and so, the Magnetic Detector game   was created instead;
This game involves a magnetic pad being placed underneath a piece of grid paper. The magnetic pad will have magnets dotted around the area, and by using the discovery board as a sensor, the location of the magnets can be found. The grid location coordinates of the magnetic locations will be a code that once put together, allows the       RemotePuzzle game to be activated. To help the player find where the magnets are, 4 LEDs light up when the player is close, and all LEDs light up when the player has the   discovery board on top of the magnet itself.

**Files Overview for Magnetic Detector**
  - main.c
    - main function: This function calls all the initialiser functions, and also converts the raw x,y and z magnetometer data into an angle describing the direction of the       strongest magnetic field, with it reaching 90 if it is directly below the the discovery board, and around 45 if it is at 45 degrees to the strongest magnetic field.
    - configuring_magnetometer: This functions configures the settings for the magnetometer, firstly by resetting it by sending a 0x00 to the CFG_REG_A_M register. Then,         the magnetometer is set to continuous measurement mode, by sending 0x01 value to the CFG_REG_C_M register.
    - read_magnetometer: This functions read the MSB and LSB of all the raw x,y and z magnetometer values, and then uses the MSB and LSB to convert to exact x,y and z             magnetic data.
    - detecting_magnets: This function uses the angle of maximum field strength to create various thresholds to display how close the player is to finding the magnets. If         the angle is above 40 degrees, 4 LEDs will light up, and if the angle is greater than 70, all the LEDs light up, as the player will be above the magnet, with a small       margin for error.

## Remote Puzzle
This puzzle acts as a bridge to progress between the magnetic detector puzzle and the connect wires puzzle. This involves the user inputting the code acquired during the magnetic detector puzzle into a wireless remote, which will lead to the activation of the connect wires puzzle. As the user inputs the coordinates into the remote, the program checks whether the coordinate inputed is one of the desired ones, and if so, the LEDs on the board flashes, and the user can input the next coordinates, with 3 coordinates necessary in total. If the player types in an incorrect code, the program does not reset to the beginning, but rather allows the user unlimited opportunities to keep typing codes until the goal is achieved.
**Files Overview for Remote Puzzle**
- main.c
  - This file initialises the LCD in parallel with the connect wires code, such that once the player types in the correct code, the function of the LCD changes to the functionality necessary for connect wires, instead of having to manually detach the LCD and attach to the other discovery board  
  - This code also initialises the wireless connection between the discovery board and the remote, by connecting the spare pins of the board to the remote's receiver
- lcd.c
  - This file contains all functions necessary to operate the LCD screen, including but not limited to:
    - LCD_init : Initialises a 16 column by 2 row LCD screen without the curson
    - LCD_int  : Printing an int on the LCD
    - LCD_string : Printing a string on the LCD
    - LCD_cursor : Creates the cursor to indicate where on the LCD data is to be written
    - LCD_clear : Clears the LCD string

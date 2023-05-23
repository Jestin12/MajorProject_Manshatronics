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

Jestin – Simon says (main), RemoteServo (main), (assist) servo movement function in high five 

Josh - Connect the wires  

Mansh – Combination lock (main), RemoteServo (assist)  

Zach – CAT Scan (main) 

## Git Layout
## System Level Overview

### High Five


### CAT Scan


### LiDar lock



### Simon Says
Module uses GPIO inputs, LEDs, and an LCD board
In the puzzle, the player must pass 4 levels of increasing difficulty wherein they must match the LED lit up by the game with the corresponding LED a consecutively for x number of times without error.
Failing to press the correspond button will result in the game restarting from the beginning. 
At the completion of each level, the LED wheel will display certain LEDs of different colours which will be key to solving the next puzzle.
**Files Overview**
- main.c
  - This file contains code that allows for the calibration of the game. The calibration process involves the user pressing each button, with the corresponding LED on the
    board lighting up, allowing the user to see what button each light corresponds to.
  - A timer is also set to ensure the user does not take too long to press the button, and if the user does, the program will reset to the start
  - In addition, an LCD screen acts as the UI, providing simple instructions and showing the timer countdown
  - It also controls the activation and movement between the various levels of the game
 
- level1 - level4.c
  - Essentially controls the progression of each level of the game
  - Each level will follow the same method:
     - It will display one light at a time, and the user is required to press the corresponding button on the breadboard
     - If the user gets a light wrong, the puzzle resets to level 1
     - The difficulty of each level increases by giving the user less time to press the buttons, and by increasing the number of buttons they need to press correctly to get 
       past the level
     - Once the final level is reached, the LCD announces that the game is finished, and by pressing the button on the breadboard, the user can cycle through all the              patterns, which is then used in the wiring puzzle
- lcd.c
  - This file contains all functions necessary to operate the LCD screen, including but not limited to:
    - LCD_init : Initialises a 16 column by 2 row LCD screen without the curson
    - LCD_int  : Printing an int on the LCD
    - LCD_string : Printing a string on the LCD
    - LCD_cursor : Creates the cursor to indicate where on the LCD data is to be written
    - LCD_clear : Clears the LCD string
 

### Connect the wires



### **Combination Lock** 
The combination lock is a puzzle designed to act like an ordinary combination lock, but using the magnetometer of the discovery board instead of an actual physical mechanism. The combination lock would use the magnetometer to find the relative heading of the discovery board, from 0 to 360. In a typical combination lock, different numbers are placed at different angles, and so the discovery board could be placed in a mold so that it can only rotate in place, with the mold having numbers around the edge just as a typical combination lock would. Each number will correspond to a different angle, which can be implemented in the code. The player of the escape room would then need to discover the combination for the lock through the other puzzles, and then input those by spinning the discovery board in a specific way.
**Files Overview**
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

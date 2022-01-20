# brakeless
## Requirements
 - Your OS has to be Windows because of "windows.h" lib.
 - You must have installed a g++ compiler like [MinGW](https://www.mingw-w64.org/).

## Configuration
After installing a g++ compiler, follow these steps:
 1. Copy the **glut.h** file to directory: ***C:\<your_compiler>\include\GL***;
 2. Copy the **glut32.dll** file to ***C:/Windows/System32*** and ***C:\Windows\SysWOW64***;
 3. Link these libraries to your IDE to use them to compile the project: **glut32.lib, libglu32.a, libglut32.a, libopengl32.a**.
 
## The Project
A simple car game like those in old video games. The basic idea is to avoid others cars while the game increase the difficulty;

## How it Works
The game have basically two screens.
  1. A Start screen with basic instructions;
  2. The actual game, with two camera settings.

In the first place the camera is positioned behind the player's car, but it can be changed to top.

The game have two light settings as well, the first one represents the day, and the second one represents the night.

###### The enemies

The game have basically three enemy cars, that are positioned on a array, the array represents the lanes, and it are randomly placed on a position;
The game loop calculates the positions of the enemy decreasing by dificulty value (It defines how much fast the enemies are);
The player can switch between the lanes, but looses if an enemy car crash on its car.

## Screens

![image](https://github.com/isaacguibson/brakeless/blob/master/images/tela_inicial.png)
![image](https://github.com/isaacguibson/brakeless/blob/master/images/dia_camera_tras.png)
![image](https://github.com/isaacguibson/brakeless/blob/master/images/noite_camera_tras.png)
![image](https://github.com/isaacguibson/brakeless/blob/master/images/menu.png)
![image](https://github.com/isaacguibson/brakeless/blob/master/images/dia_camera_cima.png)
![image](https://github.com/isaacguibson/brakeless/blob/master/images/noite_camera_cima.png)

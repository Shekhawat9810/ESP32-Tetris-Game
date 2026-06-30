# ESP32-Tetris-Game
ESP32 Tetris Console is a compact, embedded game system that brings the iconic Tetris experience to life using an ESP32 microcontroller and a 0.96" SSD1306 OLED display. Designed as an exercise in embedded systems architecture, this project bridges the gap between low-level hardware signals and high-level game logic.

#Project Overview
This project transforms a blank hardware setup into a fully functional game console. It features a 16x8 matrix engine, real-time collision detection, and a scoring system. Designed as an exercise in embedded systems architecture, it bridges the gap between low-level electronic signals and high-level game logic.

#Hardware Components

* Microcontroller: ESP32 DevKit V1

* Display: 0.96" SSD1306 I2C OLED

* Input: 2-Axis Analog Joystick (with integrated push-button)

| Component | Part Pin | ESP32 Board Label |
| :--- | :--- | :--- |
| OLED Display | GND | GND |
| OLED Display | VDD (VCC) | 3V3 |
| OLED Display | SCK (SCL) | D22 |
| OLED Display | SDA | D21 |
| Joystick | GND | GND |
| Joystick | +5V (VCC) | 3V3 |
| Joystick | VRX | D34 |
| Joystick | VRY | D35 |
| Joystick | SW | D13 |

#Software Features
*Custom Game Engine: Uses a 16x8 grid-based array to manage the playfield and piece states.

*Collision Logic: Implements boundary-box testing to ensure game integrity.

*Rotation Algorithm: Uses a matrix transposition-and-reverse algorithm for smooth piece rotation.

*Non-Blocking Gravity: Uses millis() for timer-based game progression, ensuring the game remains responsive to input.

*Game State Management: Handles transitions between active play and "Game Over" states.


#Getting Started
*Prerequisites: Install the Arduino IDE.

*Libraries: Install the following through the Library Manager:

*Adafruit SSD1306

*Adafruit GFX Library

*Setup: Connect your ESP32 and ensure the correct board and port are selected in the IDE.

*Upload: Copy the Tetris.ino code into your IDE, compile, and upload to the ESP32.

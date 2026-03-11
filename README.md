# ESP32 BLE Gamepad Controller

This project implements a **Bluetooth Low Energy (BLE) gamepad using an ESP32**.  
The ESP32 acts as a wireless controller and sends joystick and button inputs to a computer using the **BLE HID gamepad profile**.

The device uses an analog joystick and four push buttons to emulate a controller.  
On the PC side, **x360ce (Xbox 360 Controller Emulator)** is used to map and calibrate the controller for compatibility with games that expect an Xbox controller.

---

## Features

- Bluetooth Low Energy HID gamepad using ESP32
- Analog joystick support (X and Y axes)
- Four digital buttons (Triangle, Circle, Cross, Square)
- Automatic joystick center calibration on startup
- Deadzone filtering for stable joystick control
- Compatible with Windows games using **x360ce**

---

## Hardware Requirements

- ESP32 development board
- Analog joystick module
- 4 push buttons
- Connecting wires

---

## Pin Configuration

| Component | ESP32 Pin |
|----------|-----------|
| Joystick X | GPIO 34 |
| Joystick Y | GPIO 35 |
| Triangle Button | GPIO 26 |
| Circle Button | GPIO 33 |
| Cross Button | GPIO 32 |
| Square Button | GPIO 25 |

Buttons use **INPUT_PULLUP**, so pressing the button pulls the pin **LOW**.

---

## Software Requirements

- Arduino IDE
- ESP32 board support package
- BLE Gamepad library

BLE Gamepad library:  
https://github.com/lemmingDev/ESP32-BLE-Gamepad

Install it using the Arduino Library Manager or manually from the repository.

---

## How It Works

1. When the ESP32 starts, it initializes Bluetooth as a **BLE HID Gamepad**.
2. The joystick center position is automatically calibrated.
3. The joystick movement is mapped to the full HID range.
4. Button presses are detected and sent as gamepad button events.
5. The ESP32 continuously sends HID reports to the connected device.

The joystick includes a **deadzone** to prevent unwanted movement when near the center.

---

## Connecting to a PC

1. Upload the firmware to the ESP32.
2. Power the ESP32.
3. Open **Bluetooth settings on your computer**.
4. Search for devices.
5. Connect to the device named:

ESP32 Gamepad

Once connected, the device will appear as a **Bluetooth game controller**.

---

## Using x360ce for Game Compatibility

Some games only support **Xbox controllers**.  
x360ce allows the BLE gamepad to emulate an Xbox 360 controller.

### Download x360ce

Official website:

https://www.x360ce.com/

Direct download page:

https://www.x360ce.com/#Download

Download the latest **x360ce release** and extract it.

---

## x360ce Setup Instructions

1. Download and extract **x360ce**.
2. Run `x360ce.exe`.
3. The software will detect connected controllers.
4. Your ESP32 BLE Gamepad should appear as a generic controller.
5. Click **Add Controller** if it is not automatically detected.
6. Open the **Controller Mapping** section.
7. Move the joystick and press buttons to map them.
8. Assign axes and buttons to the corresponding Xbox controls.
9. Save the configuration.

Once configured, games will detect the controller as an **Xbox 360 controller**.

---

## Controls

| Input | Function |
|------|----------|
| Joystick | Left analog stick |
| Triangle | Button 1 |
| Circle | Button 2 |
| Cross | Button 3 |
| Square | Button 4 |

---

## Calibration

When the ESP32 starts:

- The joystick center position is automatically recorded.
- Movement is calculated relative to this center point.
- A **deadzone** prevents small analog noise from causing movement.

---

## Notes

- Ensure Bluetooth is enabled on your PC.
- Some games require x360ce or Steam controller support.
- The joystick deadzone value can be adjusted in the code for better sensitivity.

---

## Technologies Used

- ESP32
- Bluetooth Low Energy (BLE HID)
- Arduino Framework
- ESP32 BLE Gamepad Library
- x360ce Xbox Controller Emulator

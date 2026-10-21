# ESP32 BLE Personal Macro Pad

A DIY Bluetooth Low Energy (BLE) macro pad built with an ESP32. This project turns physical buttons into keyboard shortcuts, allowing you to control your computer wirelessly without a traditional keyboard.

The macro pad uses the `ESP32-BLE-Keyboard` library to emulate a Bluetooth keyboard and send shortcut combinations to a connected device.

## Features

- **Copy:** `Ctrl + C`
- **Paste:** `Ctrl + V`
- **Select All:** `Ctrl + A`
- Wireless keyboard input over Bluetooth Low Energy
- Physical buttons connected to ESP32 GPIO pins
- Extendable with additional shortcuts and custom macros

## Hardware Requirements

- ESP32 development board with BLE support
- 3 push buttons
- Jumper wires
- Breadboard or custom PCB
- USB cable for programming and power

## Pin Configuration

| Function                | ESP32 GPIO |
| ----------------------- | ---------: |
| Copy (`Ctrl + C`)       |    GPIO 23 |
| Paste (`Ctrl + V`)      |    GPIO 13 |
| Select All (`Ctrl + A`) |    GPIO 19 |

## Software Requirements

- Arduino IDE
- ESP32 board support package
- ESP32 BLE Keyboard library by T-vK

Library: [ESP32-BLE-Keyboard on GitHub](https://github.com/T-vK/ESP32-BLE-Keyboard)

## How It Works

1. The ESP32 initializes the serial monitor and starts its BLE keyboard service.
2. Pair the ESP32 with your computer or another compatible Bluetooth host.
3. Press a physical button connected to a configured GPIO pin.
4. The ESP32 sends the associated keyboard shortcut over Bluetooth.
5. The firmware releases all pressed keys after sending the shortcut.

## Firmware Setup

Include the required libraries:

```cpp
#include <BleKeyboard.h>
#include <Arduino.h>
```

Create a BLE keyboard instance:

```cpp
BleKeyboard bleKeyboard;
```

Start the BLE keyboard service inside `setup()`:

```cpp
Serial.begin(115200);
Serial.println("Starting BLE Macropad");
bleKeyboard.begin();
```

Before sending keyboard input, check that the host is connected:

```cpp
if (bleKeyboard.isConnected()) {
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press('c');
    bleKeyboard.releaseAll();
}
```

## Troubleshooting: `BleKeyboard.cpp` Compilation Error

### Error location

You may encounter a compiler error similar to:

```text
ESP32_BLE_Keyboard/BleKeyboard.cpp:
In member function 'void BleKeyboard::begin()':
```

This line identifies where compilation failed, but the actual diagnostic usually appears in the following lines.

A common cause is an incompatibility between the `ESP32-BLE-Keyboard` library and newer versions of the Arduino ESP32 board core, particularly version 3.x.

### Fix 1: Check the full error message

1. Open Arduino IDE.
2. Enable verbose output during compilation under **File → Preferences → Show verbose output during compilation**.
3. Compile the sketch again.
4. Find the first actual `error:` message beneath the `BleKeyboard.cpp` heading.

If it mentions `std::string`, `setValue`, or a mismatch involving `String`, use the compatibility fix below.

### Fix 2: Update the library's string conversions

Back up the library file before editing it:

```text
Documents/Arduino/libraries/ESP32_BLE_Keyboard/BleKeyboard.cpp
```

Inside `BleKeyboard::begin()`, look for code that passes a `std::string` directly to an ESP32 BLE API.

For example, if the error identifies this line:

```cpp
hid->manufacturer()->setValue(deviceManufacturer);
```

try changing it to:

```cpp
hid->manufacturer()->setValue(
    String(deviceManufacturer.c_str())
);
```

If the compiler specifically flags the device-name initialization line:

```cpp
BLEDevice::init(deviceName);
```

and reports that the API expects an Arduino `String`, try:

```cpp
BLEDevice::init(String(deviceName.c_str()));
```

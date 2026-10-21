# Bluetooth Projects — ESP32

A collection of hands-on Bluetooth Classic and Bluetooth Low Energy (BLE) projects built around the ESP32 microcontroller.

This repository explores wireless communication, audio streaming, sensor monitoring, and Human Interface Devices (HID) through practical embedded systems projects.

The goal is to learn how Bluetooth works at the application level while building useful hardware projects with C/C++, Arduino, sensors, and peripheral interfaces.

## Projects

### 1. Bluetooth Speaker

**Directory:** [`Bluetooth_Speaker/`](./Bluetooth_Speaker/)

An ESP32-based Bluetooth audio project that explores wireless audio reception and audio output through external amplification hardware.

**Key concepts**
- Bluetooth Classic audio streaming using A2DP
- Digital-to-analog audio output
- External audio amplifiers and speakers
- Audio signal routing and hardware integration

**Learning objectives**
- Understand the Bluetooth A2DP audio sink role.
- Explore the audio path from wireless reception to speaker output.
- Integrate microcontrollers with external audio hardware.

### 2. ESP32 BLE Environmental Monitor

**Directory:** [`ESP32_BLE_Environmental_Monitor/`](./ESP32_BLE_Environmental_Monitor/)

An environmental monitoring project exploring how sensor measurements can be collected by an ESP32 and made available through Bluetooth Low Energy.

**Key concepts**
- Bluetooth Low Energy communication
- Sensor interfacing and data acquisition
- I²C and peripheral communication, where supported by the selected sensors
- Wireless environmental data monitoring

**Learning objectives**
- Acquire environmental measurements from sensors.
- Understand BLE communication between an embedded device and a compatible client.
- Explore how sensor data can be organized and transmitted wirelessly.

### 3. Wireless Macro Pad

**Directory:** [`Wireless_Macro-pad/`](./Wireless_Macro-pad/)

A personal wireless macro pad that uses the ESP32 to emulate a Bluetooth keyboard and trigger keyboard shortcuts from physical buttons.

**Key features**
- Copy — `Ctrl + C`
- Paste — `Ctrl + V`
- Select All — `Ctrl + A`

**Key concepts**
- Bluetooth Low Energy HID
- GPIO input handling
- Keyboard shortcut generation
- Button debouncing and input reliability

**Learning objectives**
- Understand how an ESP32 can act as a Bluetooth HID peripheral.
- Map physical inputs to keyboard events.
- Build a wireless productivity device using embedded firmware.

## Technologies and Concepts

| Area | Technologies / Concepts |
|---|---|
| Microcontroller | ESP32 |
| Programming | C/C++, Arduino framework |
| Wireless communication | Bluetooth Classic, Bluetooth Low Energy |
| Audio | A2DP, DAC/audio output, external amplification |
| Sensors | Sensor interfacing and data acquisition |
| HID | BLE keyboard emulation and shortcut generation |
| Hardware | GPIO, peripheral interfaces, prototyping |

The exact libraries and hardware requirements depend on the individual project. Refer to each project's source code and documentation for implementation details.

## Repository Structure

```text
Bluetooth-Projects/
├── Bluetooth_Speaker/
├── ESP32_BLE_Environmental_Monitor/
├── Wireless_Macro-pad/
├── ESP32-DEV-CP2102-C-003.jpg
└── README.md
```

## Getting Started

### Requirements

- An ESP32 development board compatible with the selected project
- Arduino IDE or another supported development environment
- Appropriate USB cable and programming drivers
- Project-specific sensors, buttons, audio components, and wiring
- Bluetooth-enabled host device where required

### Setup

1. Clone this repository:

   ```bash
   git clone https://github.com/Emele-Winner2/Bluetooth-Projects.git
   ```

2. Open the repository directory:

   ```bash
   cd Bluetooth-Projects
   ```

3. Choose a project folder.
4. Read the project-specific instructions and inspect its source code.
5. Install the required libraries and select the correct ESP32 board in your development environment.
6. Connect the required hardware, compile the firmware, and upload it to the board.
7. Test the project using its intended Bluetooth host or peripheral.

**Note:** Bluetooth Classic and BLE have different capabilities and library requirements. Check the specific ESP32 variant and software dependencies before building.

## Learning Goals

This collection is intended to develop practical experience with:

- Bluetooth Classic versus Bluetooth Low Energy
- Wireless communication between embedded devices and host systems
- ESP32 peripheral programming
- Sensor acquisition and data handling
- Bluetooth audio applications
- HID devices and keyboard emulation
- Hardware-software integration and debugging

## Contributing

Suggestions, improvements, and technical feedback are welcome. If you find a bug or want to propose an enhancement, open an issue or submit a pull request.
---

**Built as part of my journey into computer engineering, embedded systems, and wireless hardware development.**

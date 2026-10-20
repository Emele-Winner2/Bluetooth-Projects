# ESP32 BLE Environmental Monitor

A Bluetooth Low Energy (BLE) environmental monitoring project built with an **ESP32** and a **BMP280 pressure and temperature sensor**. The device reads temperature, atmospheric pressure, and estimated altitude, then transmits the measurements wirelessly to a smartphone using BLE notifications.

The project explores sensor interfacing, embedded C/C++ programming, BLE GATT services and characteristics, and real-time sensor data transmission.

## Features

- **Temperature monitoring** — reads temperature in degrees Celsius.
- **Atmospheric pressure monitoring** — reads pressure in pascals (Pa).
- **Altitude estimation** — estimates altitude using atmospheric pressure and a reference sea-level pressure.
- **BLE connectivity** — exposes sensor data through a custom BLE service.
- **Notifications** — sends sensor measurements to subscribed BLE clients.
- **Serial debugging** — prints sensor readings to the Serial Monitor for testing.

## Hardware Requirements

| Component | Purpose |
|---|---|
| ESP32 development board | Main microcontroller and BLE server |
| BMP280 sensor module | Temperature and atmospheric pressure measurements |
| Jumper wires | Hardware connections |
| USB cable | Programming and serial communication |
| Smartphone | BLE scanning and monitoring with nRF Connect |

## Software Requirements

- Arduino IDE
- ESP32 Arduino Core
- Adafruit BMP280 Library
- Adafruit Unified Sensor Library, if required by your installed library version
- ESP32 BLE Arduino library
- nRF Connect for Mobile

## Hardware Connections

The BMP280 communicates with the ESP32 over I²C.

| BMP280 | ESP32 |
|---|---|
| VIN/VCC | Compatible supply voltage for your module |
| GND | GND |
| SDA | Default ESP32 I²C SDA pin |
| SCL | Default ESP32 I²C SCL pin |

**Note:** The default ESP32 I²C pins are commonly GPIO 21 (SDA) and GPIO 22 (SCL), but they can vary by board and software configuration. The sketch currently uses the library's default I²C configuration.

## How It Works

1. The ESP32 initializes the BMP280 sensor over I²C.
2. The sensor is configured for normal operating mode, with temperature and pressure oversampling and filtering.
3. The ESP32 initializes its BLE stack and creates a BLE server.
4. A custom BLE service and a readable, notifiable characteristic are created.
5. The ESP32 advertises the service so a smartphone can discover and connect to it.
6. The main loop reads temperature, pressure, and estimated altitude.
7. Each reading is formatted into a string and assigned to the BLE characteristic.
8. The ESP32 calls `notify()` to transmit the updated value to subscribed clients.

## BLE Configuration

| Parameter | Value |
|---|---|
| Device name | `BLE Environmental Monitor` |
| Service UUID | `4fafc201-1fb5-459e-8fcc-c5c9c331914b` |
| Characteristic UUID | `beb5483e-36e1-4688-b7f5-ea07361b26a8` |
| Characteristic properties | Read and Notify |
| Notification descriptor | CCCD (`BLE2902`) |

The characteristic supports both on-demand reads and notifications. To receive automatic updates, a client must connect and subscribe to notifications.

## Running the Project

1. Install the required libraries in the Arduino IDE.
2. Connect the BMP280 to the ESP32 using I²C.
3. Select the appropriate ESP32 board and port.
4. Upload the sketch.
5. Open the Serial Monitor at **9600 baud**.
6. Install and open nRF Connect on your smartphone.
7. Scan for `BLE Server Example` and connect.
8. Expand the custom service and locate the characteristic using the UUID above.
9. Enable notifications using the characteristic's notification control.
10. Observe the incoming sensor measurements.

## Example Output

The Serial Monitor displays readings in a format similar to:

```text
Temperature = 28.45 C
Pressure = 100850.25 Pa
Approx altitude = 13.65 m
```

Actual values depend on the environment and the sensor's calibration and operating conditions.

## Important Implementation Details

### Characteristic updates

The project uses one BLE characteristic for all three measurements. Each call to `setValue()` replaces the previous characteristic value, so the temperature, pressure, and altitude are sent as **separate notifications**, rather than as one combined message.

The current loop includes a 500 ms delay after sending all three readings. This means the device attempts to send three notifications per loop iteration, approximately every half-second, subject to execution time and BLE connection conditions.

### Altitude estimation

The BMP280 does not measure altitude directly. The `readAltitude(1013.25)` function estimates altitude using the assumed sea-level pressure of 1013.25 hPa. For more accurate results, use an appropriate local sea-level pressure value.

### Pressure units

The Adafruit BMP280 library returns pressure in pascals (Pa). The displayed pressure value is therefore labelled in Pa.

## License

This project is available for educational and personal experimentation.

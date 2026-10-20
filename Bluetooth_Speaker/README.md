# ESP32 Bluetooth A2DP Audio Receiver

A Bluetooth audio receiver built using an ESP32, the **ESP32-A2DP** library, and **Arduino Audio Tools**. The project receives wireless stereo audio from a smartphone or computer using Bluetooth Advanced Audio Distribution Profile (A2DP) and routes the audio to an analog output for an external amplifier and speaker system.

The goal is to explore Bluetooth audio streaming, digital-to-analog conversion (DAC), audio signal paths, and hardware integration while building a foundation for a custom Bluetooth speaker (Although Arduino IDE abstracts lots of stuff 😭😭)

## Features

- **Bluetooth audio streaming** — receives stereo audio from compatible Bluetooth source devices.
- **A2DP Sink** — configures the ESP32 as a Bluetooth audio receiver.
- **Analog audio output** — routes decoded audio through the configured audio output interface.
- **External amplifier support** — allows the analog output to feed a suitable audio amplifier.
- **Speaker integration** — supports an external speaker system through the amplifier.
- **Embedded audio development** — explores audio streams, Bluetooth profiles, and signal routing.

## Hardware Requirements

| Component                          | Purpose                                          |
| ---------------------------------- | ------------------------------------------------ |
| Compatible ESP32 development board | Bluetooth audio receiver and audio processing    |
| External audio amplifier           | Amplifies the analog audio signal                |
| Speaker or speakers                | Converts amplified electrical signals into sound |
| Suitable power supply              | Powers the ESP32 and amplifier                   |
| Jumper wires and audio connections | Connects the audio output to the amplifier       |
| Smartphone or computer             | Bluetooth audio source                           |

**Important:** The exact output hardware depends on your ESP32 variant. Some ESP32 chips support an internal DAC, while others require an external DAC or an audio codec. Verify the capabilities of your board before wiring the amplifier.

## Software Requirements

- Arduino IDE
- ESP32 Arduino Core
- [ESP32-A2DP](https://github.com/pschatzmann/ESP32-A2DP)
- [Arduino Audio Tools](https://github.com/pschatzmann/arduino-audio-tools)

Install the required libraries using the Arduino Library Manager or their official GitHub installation instructions.

## How It Works

The project uses Bluetooth A2DP to receive music from a paired source device.

1. The ESP32 initializes the Bluetooth audio sink.
2. The sink advertises the Bluetooth device name `InternalDAC`.
3. A smartphone or computer connects and streams audio over Bluetooth A2DP.
4. The A2DP library receives and decodes the audio stream.
5. Arduino Audio Tools routes the audio data to the configured `AnalogAudioStream` output.
6. The output signal feeds a suitable external amplifier.
7. The amplifier drives the connected speakers.

## Audio Signal Path

```text
Smartphone / Computer
          |
          | Bluetooth A2DP
          v
    ESP32 Bluetooth
      Audio Sink
          |
          v
    Audio Processing
          |
          v
  Analog Audio Output
          |
          v
  External Amplifier
          |
          v
       Speakers
```

## Current Implementation

The current sketch initializes the audio output stream and starts the Bluetooth A2DP sink.

```cpp
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

AnalogAudioStream out;
BluetoothA2DPSink a2dp_sink(out);

void setup() {
    Serial.begin(115200);
    a2dp_sink.start("InternalDAC");
}

void loop() {
}
```

### Code Overview

- `AudioTools.h` provides audio stream and processing abstractions.
- `BluetoothA2DPSink.h` provides the Bluetooth A2DP sink implementation.
- `AnalogAudioStream out` defines the selected analog audio output stream.
- `BluetoothA2DPSink a2dp_sink(out)` connects the A2DP receiver to that output stream.
- `a2dp_sink.start("InternalDAC")` starts the sink using `InternalDAC` as its Bluetooth device name.

The `loop()` function is empty because the audio library manages the Bluetooth and audio streaming tasks.

**Hardware note:** `AnalogAudioStream` does not guarantee that every ESP32 board will produce audio on an internal DAC automatically. Confirm the supported output backend, GPIO configuration, and DAC capabilities for your selected board and installed library version.

## Getting Started

1. Install the ESP32 board support package in the Arduino IDE.
2. Install ESP32-A2DP and Arduino Audio Tools.
3. Open the project sketch.
4. Select your ESP32 board and serial port.
5. Compile and upload the code.
6. Power the ESP32 and open Serial Monitor at **115200 baud**.
7. Open Bluetooth settings on your phone or computer.
8. Find and connect to `InternalDAC`.
9. Play audio from your source device.
10. Connect the configured analog audio output to a compatible external amplifier and speaker system.

## Amplifier and Speaker Integration

The ESP32's audio output is intended to provide an audio signal, not enough power to drive most passive speakers directly.

- Use a suitable amplifier between the audio output and passive speakers.
- Confirm the amplifier's input voltage range and signal type.
- Ensure the ESP32 audio output and amplifier input share a suitable signal ground when required by the interface.
- Power the amplifier from a supply appropriate for its voltage and current requirements.
- Avoid connecting a speaker directly to a DAC output.
- Keep analog audio wiring short and away from noisy switching power circuitry where practical.

NOTE: Your ESP32 board will require an internal DAC for this project to work.

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

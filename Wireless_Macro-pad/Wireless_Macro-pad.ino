//My own Personal macro pad with functions like CTRL+A CTRL+C CTRL+V u can add more if u want..
#include <BleKeyboard.h>
#include <Arduino.h>
#define COPY 23
#define PASTE 13
#define SELECT_ALL 19


BleKeyboard bleKeyboard;
void setup() {
  // put your setup code here, to run once:
  pinMode(COPY, INPUT);
  pinMode(PASTE, INPUT);
  pinMode(SELECT_ALL, INPUT);
  Serial.begin(115200);
  Serial.println("Starting BLE Macropad");
  bleKeyboard.begin();
}

void loop() {
  if (bleKeyboard.isConnected() && digitalRead(COPY)) {
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press('c');
    bleKeyboard.releaseAll();
  }

  if (bleKeyboard.isConnected() && digitalRead(SELECT_ALL)) {
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press('a');
    bleKeyboard.releaseAll();
  }

  if (bleKeyboard.isConnected() && digitalRead(PASTE)) {
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press('v');
    bleKeyboard.releaseAll();
  }
  delay(100);
}

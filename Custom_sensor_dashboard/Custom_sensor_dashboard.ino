#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <BLE2902.h>
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define BMP_SCK (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS (10)

Adafruit_BMP280 bmp;  // I2C
BLECharacteristic *pCharacteristic;
void setup() {
  Serial.begin(9600);
  while (!Serial) delay(100);  // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */


  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    Serial.print("SensorID was: 0x");
    Serial.println(bmp.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
  Serial.println("Starting BLE work!");

  if (!BLEDevice::init("BLE Environmental Monitor")) {
    Serial.println("BLE initialization failed!");
    return;
  }

  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pServer->advertiseOnDisconnect(true);
  pCharacteristic =
    pService->createCharacteristic(CHARACTERISTIC_UUID,  BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMaxPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}


void loop() {

  char message[64];
  snprintf(message, sizeof(message),
           "Temperature = %.2f C",
           bmp.readTemperature());
  Serial.println(message); 
  pCharacteristic->setValue(message);
  pCharacteristic->notify();

  snprintf(message, sizeof(message),
           "Pressure = %.2f Pa",
           bmp.readPressure());
  Serial.println(message); 
  pCharacteristic->setValue(message);
  pCharacteristic->notify();

  snprintf(message, sizeof(message),
           "Approx altitude =  %.2f m",
           bmp.readAltitude(1013.25));
  Serial.println(message); 
  pCharacteristic->setValue(message);
  pCharacteristic->notify();
  Serial.println();

  delay(500);
}

/*
 * Minimal-Beispiel zum Empfang von I2C-Daten mit dem Arduino Nano vom ESP32.
 * Robotic Tutorials, Niko Rosberg, 25.12.2021
 */

#include <Wire.h>         // I2C-Library
#define I2C_ADDRESS 0x04  // I2C-Adresse des ESP32
#define LED LED_BUILTIN   // Pin-Nummer für interne LED des Arduino
// I2C pins
#define SDA A4
#define SCL A5

volatile uint8_t msg = 0x00;  // Variable für I2C-Nachricht


void setup() {
  Wire.begin(I2C_ADDRESS);      // Initialisierung der I2C-Schnittstelle
  Wire.onReceive(readI2Cinput); // Aktivierung der I2C-Interrupt-Funktion

  pinMode(LED, OUTPUT);
}

void loop() {

  controlLED(msg, 200);
  delay(1000);
  
}

void readI2Cinput(int howMany) {
  while(Wire.available() > 0) {
    msg = Wire.read();
  }
}

void controlLED(uint8_t number, int interval) {
  for(int i=0; i<number; i++) {
    digitalWrite(LED, HIGH);
    delay(interval);
    digitalWrite(LED, LOW);
    delay(interval);
  }
  msg = 0;
}

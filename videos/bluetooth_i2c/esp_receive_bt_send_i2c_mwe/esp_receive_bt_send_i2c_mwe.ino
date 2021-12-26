/*
 * Minimal-Beispiel für ESP32
 * Empfang von Daten über Bluetooth von Android Smartphone
 * Weiterschicken der Daten über I2C
 * Robotic Tutorials, Niko Rosberg, 25.12.2021
 * 
 */

#include <Wire.h>             // library für I2C
#include "BluetoothSerial.h"  // library für bluetooth

#define I2C_FREQ 100000 // 100kHz I2C speed
#define SDA_0 21        // SDA pin
#define SCL_0 22        // SCL pin
#define NANO 0x04       // slave I2C Adresse (muss gleich sein wie im Arduino-Sketch)

uint8_t bt_message = 0;     // für Bluetooth Empfang
uint8_t i2c_message = 0;    // für I2C Nachricht
#define LED 2               // internal LED pin

TwoWire I2C_0 = TwoWire(0); // Initialisierung des I2C bus
BluetoothSerial SerialBT;   // Erstellen eines Objekts für die Bluetooth-Übertragung

void setup() {
  I2C_0.begin(SDA_0, SCL_0, I2C_FREQ); // begin I2C bus
  SerialBT.begin("RoboticTutorials");
  
  pinMode(LED, OUTPUT);
}

void loop() {
  // erhalte bluetooth Nachricht
  if(SerialBT.available()) {
    digitalWrite(LED, HIGH);
    
    bt_message = SerialBT.read();

    i2c_message = bt_message;
    
    // sende i2c_message zum Arduino
    I2C_0.beginTransmission(NANO);
    I2C_0.write(i2c_message);
    I2C_0.endTransmission();
    
    digitalWrite(LED, LOW);
  }
  delay(10);
}

---
layout: post
title: "Arduino Code for Tutorial #20: Bluetooth-I2C-Datenübertragung"
categories:
excerpt-separator: <!--endofexcerpt-->
---

Das ist der Arduino-Code und ESP32-Code aus Tutorial 20: "Bluetooth-I2C-Datenübertragung".

<!--endofexcerpt-->

##### Hier kommt ihr zum Video mit einer ausführlichen Erklärung des Codes:

[<img src="../../../../../robotic-tutorials/assets/media/Youtube_Link_images/yt_link_flash_memory.jpg" alt="Link-Image">](https://www.youtube.com/watch?v=jDxaIuXRgvo)

## Programm für den ESP32:

```c

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

```

## Hier ist das Programm für den Arduino Nano:

```c

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

```

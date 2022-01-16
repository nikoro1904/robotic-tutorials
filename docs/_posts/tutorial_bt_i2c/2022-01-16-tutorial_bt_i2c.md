---
layout: post
title: "Bluetooth-I2C-Datenübertragung (Tutorial #21)"
categories:
excerpt-separator: <!--endofexcerpt-->
---

Wie kann ein ESP32 als Bluetooth-Adapter für den Arduino verwendet werden?
Oder wie funktioniert Bluetooth mit dem ESP32 an sich?

<!--endofexcerpt-->

# Bluetooth-I2C-Datenübertragung

## Motivation

Ein großes Manko bei der Arbeit mit dem günstigen Arduino Nano ist die fehlende Möglichkeit zur kabellosen Datenübertragung, also per Wifi oder Bluetooth. Um das zu beheben, gibt es mehrere Möglichkeiten:

- einen anderen Arduino kaufen (z.B. *den Arduino Nano 33 BLE* oder den ganz neuen *Arduino Nano RP2040 Connect*),
- ein Bluetooth-Adapter-Modul kaufen (z.B. das HC-05 oder HC-06),
- oder man verwendet einen ESP32 mit integriertem Bluetooth als Adapter.
    
Die dritte Variante wollen wir uns etwas genauer anschauen, denn tatsächlich kann es die günstigste Variante sein. Einfache Arduino Nano-Klone (aus China) bekommt man für wenige Euro im Internet, die etwas krasseren Varianten (wie z.B. der neue Arduino Nano RP2040 Connect) sind jedoch ungleich teurer. Bluetooth-Adapter findet man recht günstig, jedoch nicht bei den klassischen Elektronik-Online-Shops, hier zahlt man für diese in der Regel zweistellige Preise.

Ein ESP32-Board kann da eine billigere Alternative sein. Und es bietet viiiiiiiiiiel mehr Möglichkeiten als die anderen Varianten. Man kann den Arduino gleich damit ersetzen, in meinem Fall war der aber schon in eine Schaltung integriert, sodass ich den ESP als Bluetooth-I2C-Adapter verwendet habe.

## Hardware (Schaltung)

Wir wollen Arduino (Nano) und ESP32 über die I2C-Schnittstelle verbinden. Das ist ganz einfach, es gibt nur zwei Leitungen. Wir verbinden einfach die beiden SCL- und die beiden SDA-Pins miteinander. SCL ist die "Serial Clock" und SDA ist "Serial Data". Beim Arduino Nano sind das die Pins A5 für SCL und A4 für SDA. Beim ESP32 kommt es darauf an, welches Board ihr verwendet. Ich habe ein NodeMCU-32s Board, das hat den SCL-0 Pin an GPIO 22 und den SDA-0 Pin an GPIO 21. Dann müssen wir nur noch die beiden Grounds der Mikrocontroller zusammenschließen.

![Hardware-Verbindungen ESP32 und Arduino Nano](../../../../robotic-tutorials/assets/media/tutorial_bt_i2c/hardware_connections.png)

## Software

Ihr findet den kompletten Code (zum Copy-Paste) auf [dieser Seite](https://nikoro1904.github.io/robotic-tutorials/2021/12/26/tutorial_bt_i2c.html) oder in unserem [Github-Repo](https://github.com/nikoro1904/robotic-tutorials/tree/master/videos/bluetooth_i2c).

### ESP32

Um den ESP32 mit der Arduino-IDE programmieren zu können, müssen wir die ESP-Boards erst hinzufügen. Dafür fügt ihr in den Einstellungen die folgende Adresse als "zusätzliche Boardverwalter-URL" ein: `https://dl.espressif.com/dl/package_esp32_index.json`. Dann muss man den Boardverwalter öffnen, nach "esp32" suchen und das entsprechende Paket installieren. Evtl. muss man die Arduino-IDE zwischendurch neustarten.

Wir verwenden für den ESP32 die [BluetoothSerial-Library](https://github.com/espressif/arduino-esp32/tree/master/libraries/BluetoothSerial). Diese ist sehr einfach zu bedienen und zu verstehen und verwendet *Bluetooth Classic*, also nicht *Bluetooth Low Energy (BLE)*. Im Prinzip kann man die Library fast genauso verwenden wie die *normale* Serial Library, für die serielle (USB-) Schnittstelle zwischen Arduino und PC.

#### Präprozessor-Direktive

Als erstes inkludieren wir die Wire-Library (für I2C) und die BluetoothSerial-Library und definieren ein paar Konstanten. die I2C-Frequenz muss die gleiche sein, wie die am Arduino (stellen wir später ein) und auch die I2C-Adresse des Arduino Nano muss übereinstimmen. Wir können die Adresse aber frei wählen als beliebige Zahl zwischen 0 und 255.

```c++
#include <Wire.h>             // library für I2C
#include "BluetoothSerial.h"  // library für bluetooth

#define I2C_FREQ 100000 // 100kHz I2C speed
#define SDA_0 21        // SDA pin
#define SCL_0 22        // SCL pin
#define NANO 0x04       // slave I2C Adresse (muss gleich sein wie im Arduino-Sketch)
```

#### Definition globaler Variablen und Objekte

Anschließend definieren wir ein paar Variablen. Für die Nachrichten, die wir hin- und herschicken, verwenden wir unsigned ints mit 8 Bit Länge. Das ist das Standard-Format (für ein Byte), das sowohl von der Wire- als auch der Bluetooth-Library verwendet wird. Dann initialisieren wir den I2C-Bus. Wir verwenden hier den I2C-Bus 0 (der ESP hat auch noch einen zweiten I2C-Bus mit anderen Pins für SCL und SDA). Schließlich erstellen wir auch noch ein Objekt für die Bluetooth-Verbindung.

```c++
uint8_t bt_message = 0;     // für Bluetooth Empfang
uint8_t i2c_message = 0;    // für I2C Nachricht
#define LED 2               // internal LED pin

TwoWire I2C_0 = TwoWire(0); // Initialisierung des I2C bus
BluetoothSerial SerialBT;   // Erstellen eines Objekts für die Bluetooth-Übertragung
```

#### Setup-Funktion

Wir starten den I2C-Bus mit der Angabe der Pins und der Frequenz und beginnen auch die Bluetooth-Übertragung. Hier geben wir unserem ESP einen Bluetooth-Namen, den wir später sehen können, wenn wir mit unserem Smartphone nach neuen Bluetooth-Devices suchen.

```c++
void setup() {
  I2C_0.begin(SDA_0, SCL_0, I2C_FREQ); // begin I2C bus
  SerialBT.begin("RoboticTutorials");
  
  pinMode(LED, OUTPUT);
}
```

#### Loop-Funktion

In der Loop-Funktion fragen wir mit einem *if* und `SerialBT.available()`, ob es neue Bluetooth-Daten gibt. Ist das der Fall, lesen wir sie mit `SerialBT.read()` ein. Jetzt könnte man die Nachricht noch modifizieren, falls gewünscht, oder auch direkt auf dem ESP verarbeiten (wenn man keinen Arduino angeschlossen hat). Wir schicken sie aber per I2C weiter: Zunächst starten wir die I2C-Übertragung mit `I2C_0.beginTransmission(NANO);`. `NANO` ist hier die Konstante für die I2C-Adresse des Arduino. Dann senden wir die Nachricht mit `I2C_0.write()` und beenden die Übertragung wieder. In unserem Code lassen wir die interne LED des ESP noch kurz aufblinken während diesem Vorgang, sodass wir sehen können, wenn etwas gesendet wird.

Mit diesem Programm lesen wir immer nur eine Bluetooth-Nachricht (also eine 8-bit Variable) aus. Für längere Nachrichten lässt sich das ganze auch effektiver Programmieren, z.B. wenn man Arrays verwendet.

```c++
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

### Arduino Nano

Für den Arduino haben wir ein Beispiel-Programm geschrieben, das die I2C-Nachricht empfängt und weiterverarbeitet. Hier blinkt die interne LED so oft wie die Zahl, die wir erhalten. 

#### Präprozessor-Direktive und Variablen

Vor dem eigentlichen Programm inkludieren wir die I2C-Library, definieren die I2C-Adresse des Arduino und definieren Konstanten/Variablen für die I2C-Pins und die Nachricht, die wir erhalten. Für die Nachricht verwenden wir zusätzlich zum Typbezeichner `uint8_t` das Keyword `volatile`. Dieses Keyword ermöglicht es uns, die Variable `msg` innerhalb mehrerer Funktionen zu verwenden.

```c++
#include <Wire.h>         // I2C-Library
#define I2C_ADDRESS 0x04  // I2C-Adresse des ESP32
#define LED LED_BUILTIN   // Pin-Nummer für interne LED des Arduino
// I2C pins
#define SDA A4
#define SCL A5

volatile uint8_t msg = 0x00;  // Variable für I2C-Nachricht
```

#### Funktionen

Wir verwenden zwei eigene Funktionen in diesem Programm. Die eine (`readI2CInput()`) müssen wir verwenden, die andere (`controlLED()`) ist optional, erhöht aber in einem komplexeren Programm die Übersicht deutlich.

Die Funktion `readI2CInput()` wird später in den Interrupt integriert, also immer dann ausgeführt, wenn eine I2C-Nachricht ankommt und ein Interrupt ausgelöst wird. Sie sollte daher sehr kurz sein.

```c++
void readI2Cinput(int howMany) {
  while(Wire.available() > 0) {
    msg = Wire.read();
  }
}
```

Fortsetzung folgt...




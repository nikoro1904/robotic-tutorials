---
layout: post
title: "Beispielprogramme zu Tutorial #14 - Schieberegister"
categories:

---

Das sind die Beispielprogramme, die im Youtube-Video verwendet wurden. 

<iframe width="728" height="410" src="https://www.youtube.com/embed/xMDiBpyuriU" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

### 1. In das Schieberegister schreiben

```c
/* Robotic Tutorials Beispielcode Tutorial 14: Schieberegister 
 *  26.12.2019
 * 
 * Beispielcode, den ich verwendet habe, um zwei "8 Segment-Anzeigen" mit
 * zwei Power Logic Shift Registern TPIC 6B595 anzusteuern. Die zwei Schieberegister sind
 * mit ihren SER IN und SER OUT Pins in Reihe geschalten, die Steuer Pins (SRCLR, G, SRCK, RCK)
 * sind jeweils parallel geschalten. Die 8 Segmente einer Anzeige sind kurze LED-Streifen, sie
 * erhalten jeweils 12V von extern und sind wie folgt angeordnet:
 * 
 *   -    ----0----
 *   |    |       |
 *   |    5       1
 *   |    |       |
 *   7    ----6----
 *   |    |       | 
 *   |    4       2
 *   |    |       |
 *   -    ----3----
 * 
 * Die Zahlen der Segmente passen sowohl zu den Zahlen der DRAIN-Anschlüsse als auch zu
 * den entsprechenden Positionen der Bits in den 8-Bit char Variablen. 
 * 
 */

// Definition von Variablen
char shadow = 0x00; // für Zwischenspeicher
char zero  = 0x3f;  // 0  0b0011 1111
char one   = 0x06;  // 1
char two   = 0x5b;  // 2
char three = 0x4f;  // 3
char four  = 0x66;  // 4
char five  = 0x6d;  // 5
char six   = 0x7d;  // 6
char seven = 0x07;  // 7
char eight = 0x7f;  // 8
char nine  = 0x6f;  // 9
char ten     = 0x80 | zero;  // 10 (| ist ein bitwise OR)
char eleven  = 0x80 | one;  // 11
char twelve  = 0x80 | two;  // 12
char thirt   = 0x80 | three;  // 13
char fourt   = 0x80 | four;  // 14
char fift    = 0x80 | five;  // 15
char sixt    = 0x80 | six;  // 16
char sevent   = 0x80 | seven;  // 17
char eightt   = 0x80 | eight;  // 18
char ninet    = 0x80 | nine;  // 19
char a = 0x77;  // A
char empty = 0x00;  // "alle LEDs aus"
char symbol[22] = {zero, one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve,
                   thirt, fourt, fift, sixt, sevent, eightt, ninet, a, empty
                  }; // Array aller verfügbaren Zeichen

// Definition der Variablen für die Pins am Arduino
#define data 6 // SERIAL IN Pin des Schieberegister ist an DP6 des Arduino
#define srclr 2 // SRCLR Pin des Schieberegister ist an DP2 des Arduino
#define g 3 // ...
#define rclk 4
#define srclk 5

void setup() {
  // Definition der Pins als Output
  for (int j=2; j<=6; j++) {
    pinMode(j, OUTPUT);
  }
  // Pins G und SRCLR des Schieberegisters werden nur einmal beschrieben
  digitalWrite(g, LOW);
  digitalWrite(srclr, HIGH);
}

void loop() {
  // Diese for-Schleife geht durch alle Zeichen im Array symbol[] durch, zählt also immer von 0 bis 19 und A
  for (int i = 0; i < 22; i++) {
    digitalWrite(rclk, LOW); // setze den Storage Register Clock Pin auf 0
    //shiftOut(data, srclk, LSBFIRST, symbol[i]); // sende die ersten 8 Bit (Schieberegister 2)
    shiftOut(data, srclk, MSBFIRST, symbol[i]); // sende die zweiten 8 Bit (Schieberegister 1)
    digitalWrite(rclk, HIGH); // setze den Storage Register Clock Pin auf 1 (steigende Flanke)
    delay(700);
  }

// Mit diesem Code ohne for-Schleife kann man die einzelnen Symbole testen.
//    digitalWrite(rclk, LOW);
//    shiftOut(data, srclk, MSBFIRST, symbol[18]);
//    shiftOut(data, srclk, MSBFIRST, symbol[18]);
//    digitalWrite(rclk, HIGH);
//    delay(1000);

}
```

### 2. Aus dem Schieberegister lesen

```c
/* Robotic Tutorials Beispielcode Tutorial 14: Schieberegister 
 * 26.12.2019   
 */

char sent = 0b11110110;
byte received = 0x00;

// Definition der Variablen für die Pins am Arduino
#define serial_in 6 // SERIAL IN Pin des Schieberegister ist an DP6 des Arduino
#define srclr 2 // SRCLR Pin des Schieberegister ist an DP2 des Arduino
#define g 3 // ...
#define rclk 4
#define srclk 5
#define serial_out 7

void setup() {
  // Definition der Pins als Output
  for (int j=2; j<=6; j++) {
    pinMode(j, OUTPUT);
  }
  // Pins G und SRCLR des Schieberegisters werden nur einmal beschrieben
  digitalWrite(g, LOW);
  digitalWrite(srclr, HIGH);
  Serial.begin(9600);
  delay(50);
}

void loop() {

// Mit diesem Code ohne for-Schleife kann man die einzelnen Symbole testen.
    digitalWrite(rclk, LOW);
    shiftOut(serial_in, srclk, MSBFIRST, sent);
    digitalWrite(rclk, HIGH);
    delay(100);
    digitalWrite(srclk, LOW);
    received = shiftIn(serial_out, srclk, MSBFIRST);
    Serial.println(received, BIN);
    delay(1000);

}
```

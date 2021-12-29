---

layout: post
title: "Beispielprogramme zu Tutorial #15 - Schrittmotor"
categories:
excerpt_separator: <!--endofexcerpt-->

---

Das sind die Beispielprogramme, die im YouTube-Video verwendet wurden. 

<!--endofexcerpt-->

[<img src="../../../../../robotic-tutorials/assets/media/Youtube_Link_images/yt_link_schrittmotor.jpg" alt="Link-Image">](https://www.youtube.com/watch?v=dYo7K8SLafk)

**Ihr findet sie auch in unserem [Github-Repo](https://github.com/nikoro1904/robotic-tutorials/tree/master/videos/stepper_motor)**

##Ansteuerung mit Stepper.h library

```c
// Robotic Tutorials Schrittmotor Tutorial
// Test der Stepper library
// 17.2.2020

// laden der Library "Stepper.h"
#include <Stepper.h>

// initialisieren des angeschlossenen Motors
// "motor_1" ist der Name des Motors, so können wir ihn später ansprechen
// Wir können also auch mehrere Stepper in einem Programm bedienen.
// Die erste Zahl in der Klammer ist die Anzahl der Schritte, die der Motor braucht,
// um sich um 360 Grad zu drehen. Diese Angabe ist im Datenblatt des Motors zu finden.
// Wenn ihr hier eine falsche Zahl eingebt, ist einfach die Geschwindigkeit des Motors
// nachher anders.
// Die 4 Zahlen danach sind die Nummern der Pins, an die der Arduino angeschlossen ist.
// Die Reihenfolge ist wichtig. Richtig ist A, A', B, B'.
Stepper motor_1 = Stepper(200,2,3,4,5);

void setup() {
  // so stellen wir die Geschwindigkeit des Motors in Umdrehungen pro Minute ein.
  // Das lässt sich auch jederzeit im Code wieder ändern.
  motor_1.setSpeed(100);
}

void loop() {

 // In die step-Funktion schreiben wir, wieviele Schritte der Motor machen soll.
 // Wenn wir eine negative Zahl angeben, dreht er sich andersherum
 motor_1.step(200);
}
```

##Manuelle Ansteuerung im Vollschritt-, Halbschritt- oder Wavedrivebetrieb

```c
/* Beispielcode für Schrittmotor-Tutorial (Vollschritt-, Halbschritt-, Wavedrive-Betrieb)
   Robotic Tutorials, 15.02.2020

   Dieses Arduino-Programm ist zur Ansteuerung eines bipolaren Hybrid-Schrittmotors.
   In diesem Beispiel dreht sich der Motor einfach immer weiter.

   Die Art der Ansteuerung ist der Vollschritt-, Halbschritt-, Wavedrive-Betrieb.

   Der Schrittmotor hat zwei Spulen, A und B. Die Spulen haben die Anschlüsse A, A', B und B'
   Für eine übersichtliche Darstellung der Arrays wurde die Reihenfolge der Arduino-Pins im Array pin[] festgelegt.
   - Arduino DP 2 ist verbunden mit Input 1 des L293B, dieser ist verbunden mit Anschluss A des Motors (Schwarz)
   - Arduino DP 3  -> L293B Input 2 -> Motor A' (Grün)
   - Arduino DP 4  -> L293B Input 3 -> Motor B  (Rot)
   - Arduino DP 5 -> L293B Input 4 -> Motor B' (Blau)

*/
//             A, B, A',B'
int pin[4] = { 2, 4, 3, 5 };
//             S, R, G, B

// Für den Vollschrittbetrieb:
//  Pin p:            p =  2    4    3    5        // Schritt s:
int fullstep[4][4] = {   {HIGH, HIGH, LOW, LOW },  // s = 0
                         {LOW, HIGH, HIGH, LOW },  // s = 1
                         {LOW, LOW, HIGH, HIGH },  // s = 2
                         {HIGH, LOW, LOW, HIGH} }; // s = 3
// Für den Wavedrive-Betrieb:                         
//  Pin p:            p =  2    4    3    5        // Schritt s:
int wavedrive[4][4] = {   {HIGH, LOW, LOW, LOW },  // s = 0
                          {LOW, HIGH, LOW, LOW },  // s = 1
                          {LOW, LOW, HIGH, LOW},   // s = 2
                          {LOW, LOW, LOW, HIGH} }; // s = 3
// Für den Halbschrittbetrieb:
//  Pin p:            p =  2    4    3    5        // Schritt s:
int halfstep[8][4] = {   {HIGH, LOW, LOW, LOW },   // s = 0
                         {HIGH, HIGH, LOW, LOW },  // s = 1
                         {LOW, HIGH, LOW, LOW },   // s = 2
                         {LOW, HIGH, HIGH, LOW },  // s = 3
                         {LOW, LOW, HIGH, LOW},    // s = 4
                         {LOW, LOW, HIGH, HIGH},   // s = 5
                         {LOW, LOW, LOW, HIGH},    // s = 6
                         {HIGH, LOW, LOW, HIGH} }; // s = 7                          

int waitTime = 2000;  // Der kleinstmögliche Wert, damit sich der Motor noch dreht, ist ca. 400 Mikrosekunden

void setup() {
  // Definition der Pins als Outputs:
  for (int p = 2; p <= 5; p++)  {
    pinMode(p, OUTPUT);
  }
}

void loop() {
  // Doppelte for-Schleife zur Ansteuerung des Motors:
  for (int s = 0; s < 4; s++) {
    for (int p = 0; p < 4; p++) {
      digitalWrite(pin[p], fullstep[s][p]);
    }
    delayMicroseconds(waitTime);
  }
}
```

##Manuelle Ansteuerung im Mikroschritt-Betrieb

```c
/* Beispielcode für Schrittmotor-Tutorial (Mikroschritt-Betrieb)
   Robotic Tutorials, 15.02.2020

   Dieses Arduino-Programm ist zur Ansteuerung eines bipolaren Hybrid-Schrittmotors.
   In diesem Beispiel dreht sich der Motor einfach immer weiter.

   Die Art der Ansteuerung ist der Mikroschrittbetrieb

   Der Schrittmotor hat zwei Spulen, A und B. Die Spulen haben die Anschlüsse A, A', B und B'
   Für eine übersichtliche Darstellung der Arrays wurde die Reihenfolge der Arduino-Pins im Array pin[] festgelegt.
   - Arduino DP 3 ist verbunden mit Input 1 des L293B, dieser ist verbunden mit Anschluss A des Motors (Schwarz)
   - Arduino DP 5  -> L293B Input 2 -> Motor A' (Grün)
   - Arduino DP 6  -> L293B Input 3 -> Motor B  (Rot)
   - Arduino DP 10 -> L293B Input 4 -> Motor B' (Blau)

*/
//             A, B, A',B'
int pin[4] = { 3, 6, 5, 10 };
//             S, R, G, B

// A_value und B_value sind für Zwischenergebnisse, die anderen Variablen sind für direkte Ansteuerung der Motor-Pins.
int A_value = 0;
int A_plus_val = 0;
int A_minus_val = 0;
int B_value = 0;
int B_plus_val = 0;
int B_minus_val = 0;
const int max_pwm_value = 255; // 256 ist die maximale Anzahl verschiedener PWM-Spannungen (zw. 0 und 5 Volt)
const int sinus_frequency = 10;
int waitTime = 1000;  // Der kleinstmögliche Wert, damit sich der Motor noch dreht, ist ca. 400 Mikrosekunden

void setup() {
  // Definition der Pins als Outputs:
  for (int p = 0; p < 4; p++)  {
    pinMode(pin[p], OUTPUT);
  }
}

void loop() {
  // for-Schleife für die Anzahl der Schritte des Motors. 3140 entspricht einer 360°-Umdrehung.
  for (int t=0; t<3140; t++)  {
    // Wir berechnen zunächst die pseudo-analogen Spannungswerte der Spulen A und B:
    A_value = max_pwm_value*sin(t/sinus_frequency);
    B_value = max_pwm_value*cos(t/sinus_frequency);
    // In den folgenden beiden if-Funktionen werden negative Sinus-Werte umgerechnet in positive 
    if (A_value > 0) {
      A_plus_val = A_value;
      A_minus_val = 0;
    }
    else {
      A_plus_val = 0;
      A_minus_val = abs(A_value);
    }
    if (B_value > 0) {
      B_plus_val = B_value;
      B_minus_val = 0;
    }
    else {
      B_plus_val = 0;
      B_minus_val = abs(B_value);
    }      
    // hier werden die Sinus-Werte auf die Pins des Motors (bzw. des L293B) geschrieben
    analogWrite(pin[0], A_plus_val);
    analogWrite(pin[1], B_plus_val);
    analogWrite(pin[2], A_minus_val);
    analogWrite(pin[3], B_minus_val);
    // ein kleines Delay ist nötig, weil der Arduino schneller rechnet, als der Motor sich drehen kann
    delayMicroseconds(waitTime);
  }
}
```

Eine Erklärung dieser Programme wird in [diesem Post](https://nikoro1904.github.io/robotic-tutorials/2020/03/29/tutorial-schrittmotor.html) und in diesem YouTube-Video gegeben.

<iframe width="728" height="410" src="https://www.youtube.com/embed/dYo7K8SLafk" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

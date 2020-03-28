---
layout: post
title: "Tutorial #15: Schrittmotoren mit dem Arduino ansteuern"
categories:
---

In diesem Artikel wird erklärt, wie man einen (Hybrid-)Schrittmotor mit dem Arduino ansteuern kann. Wir verwenden einen bipolaren Motor, also einen mit zwei Spulen und vier Anschlüssen.

Wir haben zu diesem Motor auch ein Video auf YouTube veröffentlicht. Die Arduino-Programme dazu findet ihr in [diesem Artikel](https://nikoro1904.github.io/robotic-tutorials/2020/03/28/code-tutorial-schrittmotor.html).

<iframe width="728" height="410" src="https://www.youtube.com/embed/dYo7K8SLafk" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Wozu brauche ich Schrittmotoren?

Ein Schrittmotor ist ein Gleichstrommotor, bei dem man den Schrittwinkel sehr genau einstellen kann. Die Winkelauflösung hängt dabei vom Typ ab, manche einfachen Motoren benötigen nur sechs Schritte pro Umdrehung. Das ist ziemlich unpraktisch, daher werden in der Regel Hybridschrittmotoren verwendet, die von der amerikanischen [NEMA](https://www.nema.org/pages/default.aspx) genormt sind. Diese Motoren haben alle 200 Schritte für 360°. Das erlaubt z.B. den Einsatz in Robotiksystemen und 3D-Druckern. Daher ist es sinnvoll, einen solchen Schrittmotor für sein Projekt zu verwenden.

![auseinandergebauter Schrittmotor](../../../assets/media/tutorial_schieberegister/stepper_motor_stock_1.jpg "Ein auseinandergebauter Schrittmotor. Image by https://pixabay.com/users/martinjurekcz-8203231/ from https://pixabay.com/")

## Welchen Schrittmotor brauche ich?

Wir empfehlen, einen von der NEMA genormten Hybrid-Schrittmotor zu verwenden. Diese werden häufig eingesetzt, daher gibt es dazu auch viel Dokumentation und Infomaterial, wie z. B. diesen Artikel. Je nach euren Anforderungen müsst ihr dann noch die passende Größe wählen. Leider werden häufig rückständige (amerikanische) Maßeinheiten angegeben (z.B. in-oz, das sind inch ounces, 1 in-oz sind 16 in-pd (inch pounds) und das sind **ca.** 11,3 Ncm). **WTF?!** Ounces und Pounds können sowohl Kräfte (in N) als auch Massen (in kg) sein?!  
Am besten sucht man einfach bei europäischen Verkäufern nach Motoren und schaut sich die Datenblätter an.

Unser Schrittmotor ist ein [Hybridschrittmotor](https://www.youtube.com/watch?v=v7zIZeE5dbo) vom Typ NEMA 14 (PSM35BYG104) mit 10,8V Betriebsspannung. Die 14 bedeutet, dass sein Gehäuse eine Breite von 1,4 inch (ca. 35,6 mm) hat. Grundsätzlich funktionieren aber bipolare Hybrid-Schrittmotoren (z.B. vom Typ NEMA 17 oder NEMA 23) alle gleich. Bipolar bedeutet, dass der Motor vier Anschlüsse hat. Im Gegensatz dazu haben unipolare Schrittmotoren sechs Anschlüsse.

Der Motor hat zwei Spulen (man spricht auch von Phasen, daher: zweiphasiger Schrittmotor). Diese Spulen haben die Anschlüsse A, A', B und B'. Zu welchen Kabeln diese gehören, sehen wir im Datenblatt nach. Sonst kann man das auch mit dem Multimeter messen (Spulen haben für Gleichstrom keinen ohmschen Widerstand) und einfach ausprobieren.

![Ausschnitt aus dem Datenblatt des Motors](../../../assets/media/tutorial_schieberegister/Screenshot_Datenblatt_Motor.png "Ausschnitt aus dem Datenblatt des Motors")

## Wie funktioniert die Ansteuerung des Schrittmotors?

Die Ansteuerung eines Schrittmotors ist nicht ganz einfach. Im Datenblatt sehen wir, dass für die benötigte Spannung und den Strom der Arduino nicht ausreicht. Wir verwenden deshalb eine [H-Brücke](https://en.wikipedia.org/wiki/H_bridge), den Chip L293B.

![Ausschnitt aus dem Datenblatt des L293B](../../../assets/media/tutorial_schieberegister/L293B_Datasheet.jpg "Ausschnitt aus dem Datenblatt des L293B")

Der L293B funktioniert im Prinzip ein bisschen wie mehrere Relais. Wir können ihm digitale TTL-Signale aus dem Arduino senden, der Chip schaltet dementsprechend eine externe Spannungsquelle und gibt die höheren Spannungen und Ströme an den Motor weiter. 

Wir schließen Arduino, L293B, den Motor und die externe Quelle wie folgt zusammen:

* Die INPUT-Pins (2, 7, 10, 15) vom L293B an die Digital Pins 2, 3, 4, 5 vom Arduino.
* Die OUTPUT-Pins (3, 6, 11, 14) vom L293B an die Anschlüsse A, B, A', B' vom Motor.
* Die CHIP ENABLE-Pins (1, 9) vom L293B an +5V am Arduino (oder an Digital Pins). Sind die CE-Pins auf Ground-Potential, werden die internen H-Brücken deaktiviert.
* Der Vss-Pin (16) vom L293B wird an +5V vom Arduino angeschlossen. Er versorgt den L293B mit interner Logikspannung.
* Der Vs-Pin (8) geht zur externen Spannungsquelle. Er versorgt dann indirekt den Motor) mit Strom.
* Die Ground-Pins (4, 5, 12, 13) des L293B verbindet man mit dem GND des Arduino und der externen Spannungsquelle. Für den Testbetrieb reicht es aus, wenn nur ein Pin des Chips verwendet wird.

![Schaltplan Schrittmotor und L293B](../../../assets/media/tutorial_schieberegister/Schaltplan_Schrittmotor.jpg "Schaltplan Schrittmotor und L293B")

Um den Schrittmotor zu bewegen, müssen wir jetzt die Anschlüsse immer abwechselnd in unterschiedlichen Richtungen mit Strom versorgen. Hierfür gibt es verschiedene Möglichkeiten. 

* Variante 1: Man verwendet eine Library, z.B. Stepper.h, siehe [hier](https://www.arduino.cc/en/Reference/Stepper).
* Variante 2: Für mehr Kontrolle, aber auch mehr Aufwand, kann man den Motor auch "manuell" ansteuern. 

Für die manuelle Ansteuerung kann man zwischen verschiedenen Modi wählen, unter anderem gibt es:

+ Vollschrittbetrieb (full step mode)
+ Wavedrive-Betrieb (wavedrive)
+ Halbschrittbetrieb (half step mode)
+ Mikroschrittbetrieb (micro step mode)

### Vollschrittbetrieb
Im Vollschrittbetrieb haben wir das höchste Drehmoment. Es werden immer beide Spulen bestromt, die Reihenfolge ist dabei: AB, BA', A'B', B'A' und wieder von vorne. Bei jedem Umschalten bewegt sich der Motor einen Schritt (also 1,8°) weiter. Für Schritte in die umgekehrte Richtung dreht man die Reihenfolge einfach um. 

Im Arduino-Code machen wir das so: Wir definieren ein zweidimensionales Array für die vier Kombinationen und mit einer doppelten for-Schleife (einer übergeordneten für die Schritte und einer untergeordneten für die vier Pins) setzen wir die Pins auf HIGH oder LOW. Weil der Arduino schneller taktet, als sich der Motor bewegen kann, müssen wir nach jedem Schritt noch ein kleines Delay von mind. 0,4 ms einbauen.  
Wenn wir eine Zählvariable einbauen und das ganze in eine while-Schleife packen, können wir die Anzahl der Schritte einstellen, die der Motor machen soll.

```c++
//             A, B, A',B'
int pin[4] = { 2, 4, 3, 5 };
//             S, R, G, B

// Für den Vollschrittbetrieb:
//  Pin p:            p =  2    4    3    5        // Schritt s:
int fullstep[4][4] = {   {HIGH, HIGH, LOW, LOW },  // s = 0
                         {LOW, HIGH, HIGH, LOW },  // s = 1
                         {LOW, LOW, HIGH, HIGH },  // s = 2
                         {HIGH, LOW, LOW, HIGH} }; // s = 3

int waitTime = 2000;  // Der kleinstmögliche Wert, damit sich der Motor noch dreht, ist ca. 400 Mikrosekunden

void setup() {
  // Definition der Pins als Outputs:
  for (int p = 2; p <= 5; p++)  {
    pinMode(p, OUTPUT);
  }
}

void loop() {
  // Doppelte for-Schleife zur Ansteuerung des Motors:
  for (int s = 0; s < 8; s++) {
    for (int p = 0; p < 4; p++) {
      digitalWrite(pin[p], halfstep[s][p]);
    }
    delayMicroseconds(waitTime);
  }
}
```

### Wavedrive-Betrieb
Der Wavedrive-Betrieb ist die einfachste Art der manuellen Ansteuerung. Es ist immer nur eine Spule bestromt, die Reihenfolge ist A, B, A', B'. Wir haben deshalb auch nur halb so viel Drehmoment wie beim Vollschrittbetrieb, dafür aber auch nur halb so viel Stromverbrauch.  
Für den Arduino-Code ändert sich nur das Array, der Rest der Ansteuerung ist identisch wie beim Vollschrittbetrieb.

```c
// Für den Wavedrive-Betrieb:                         
//  Pin p:            p =  2    4    3    5        // Schritt s:
int wavedrive[4][4] = {   {HIGH, LOW, LOW, LOW },  // s = 0
                          {LOW, HIGH, LOW, LOW },  // s = 1
                          {LOW, LOW, HIGH, LOW},   // s = 2
                          {LOW, LOW, LOW, HIGH} }; // s = 3
```

### Halbschrittbetrieb
Im Halbschrittbetrieb machen wir nur halb so große Schritte (0,9° pro Schritt) und brauchen daher acht Kombinationen der Beschaltung der Spulen. Da immer abwechselnd eine und dann beide Spulen bestromt werden, ist das Drehmoment nicht konstant. Die Reihenfolge der Schaltung ist: A, AB, B, BA', A', A'B', B', B'A. Deshalb muss man in der Ansteuerung noch die äußere for-Schleife von vier auf acht Durchläufe ändern.

```cpp
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
```

### Mikroschrittbetrieb
Im Mikroschrittbetrieb kann man den Motor in deutlich kleineren Schritten bewegen. Dazu legt man eine sinusförmige Spannung an Spule A und eine cosinusförmige an Spule B. Nun kann man mit dem Arduino keine echten analogen Spannungen erzeugen, sondern nur zeitdiskrete PWM-Signale. Das ermöglicht uns, die Anzahl der Schritte pro Periode (des Sinus) fast beliebig einzustellen. Bei nur vier Schritten pro Periode ist der Mikroschrittbetrieb identisch zum Wavedrivebetrieb. Man kann aber auch nicht beliebig viele Schritte einstellen, da der Arduino das PWM-Signal nur in 8 Bit auflöst, das heißt es gibt max. 256 verschiedene "pseudo-analoge" Spannungswerte.

Wir stellen deshalb die Amplitude unseres berechneten Sinus auf 255 ein. Positive Werte für Spule A geben wir direkt an Pin A weiter. Negative Werte für Spule A wandeln wir in positive Werte um und geben sie an Pin A' weiter, da der Arduino ja auch keine negativen Spannungen ausgeben kann. 

Die bereits erwähnte Anzahl der Mikroschritte pro Periode können wir über die Frequenz des Sinus einstellen. Denkt immer daran, dass eine Periode 4 "Vollschritten" entspricht. Wenn wir jetzt also eine Frequenz von 10 wählen, macht das 

2&pi; * 10 = 62,8 Mikroschritte pro Periode. 

Auf 360° sind das dann 

200*62,8/4=3140 Mikroschritte. 

Ob der Motor wirklich so kleine Schritte machen kann, sei dahingestellt. Schon im Datenblatt finden wir ja die Angabe 1,8° pro Vollschritt mit einer Ungenauigkeit von 5%. 5% von 1,8° sind 0,09°, der eben errechnete Schrittwinkel bei 3140 Mikroschritten für eine vollständige Umdrehung beträgt 

360°/3140=0,115°. 

Unsere Ungenauigkeit pro Schritt ist also fast so hoch wie der Mikroschrittwinkel selbst.

```c
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

Die vollständigen Arduino-Codes findet ihr auch [hier](https://nikoro1904.github.io/robotic-tutorials/2020/03/28/code-tutorial-schrittmotor.html).
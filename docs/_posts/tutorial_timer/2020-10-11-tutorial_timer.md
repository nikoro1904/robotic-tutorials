---
layout: post
title: "Timer- und PWM-Funktionen am Arduino einstellen."
categories:
excerpt_separator: <!--endofexcerpt-->

---

[![Titelbild](../../../../robotic-tutorials/assets/media/tutorial_timer/preview_timer_white.png)](https://nikoro1904.github.io/robotic-tutorials/2020/10/11/tutorial_timer.html)

<!--endofexcerpt-->

Was bedeutet PWM? Wie stelle ich Duty-Cycle und Frequenz eines PWM-Signals ein?

## Was sind PWM-Signale?

PWM steht für Pulse-Width-Modulation oder auf deutsch: Pulsweitenmodulation. Das steht für eine Funktion vom Arduino, bzw. allgemein von Mikrocontrollern. 

An den sogenannten PWM-Pins, die auf dem Board oft mit einer Tilde (~) gekennzeichnet werden, kann der Arduino PWM-Signale ausgeben. PWM-Signale sind Wechselspannungen mit einem Offset (also im Prinzip Mischspannungen), wobei sie nur zwei verschiedene Werte annehmen können. Diese zwei Werte sind HIGH und LOW, also ca. 5 und 0 Volt. Die HIGH- und LOW-Werte wechseln sich in einer bestimmten Frequenz ab und bilden so ein Rechteck-Signal (englisch: square signal).

Die Frequenz dieses PWM-Signals ist konstant und wird vom Timer des Arduinos vorgegeben. Die Voreinstellung für den Arduino UNO ist z.B. 490 Hz für die Pins  3, 9, 10 und 11 bzw. 980 Hz für die Pins 5 und 6. Man kann diese Frequenz auch ändern, aber dazu später mehr.

Der zweite Parameter einer solchen binären Wechselspannung ist der Duty-Cycle. Der Duty-Cycle beschreibt, wie lange das PWM-Signal auf HIGH und wie lange es auf LOW ist. Er wird in Prozent angegeben. Dabei entspricht ein Duty-Cycle von 100% einem HIGH-Anteil von 100% (also im Prinzip eine Gleichspannung von ca. 5 V) und ein Duty-Cycle von 70% dementsprechend einem HIGH-Anteil von 70% und einem LOW-Anteil von 30%.

<iframe width="728" height="410" src="https://www.youtube.com/embed/lj4yvjqSDcM" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Man kann z.B. eine LED mit einem PWM-Signal anstatt einer Gleichspannung ansteuern. Bei einem Duty-Cycle von z.B. 50% würde sie dann mit einer hohen Frequenz blinken. Da diese Frequenz aber so hoch ist, dass unsere Augen da nicht mitkommen, sehen wir keine blinkende LED sondern eine um 50% schwächer leuchtende LED. Über die Variation des Duty-Cycles lässt sich also die Helligkeit einer LED einstellen, ohne eine analoge Spannung verwenden zu müssen. Das ist ein großer Vorteil, denn so brauchen wir dafür keinen Digital-Analog-Converter, wie er ja auf dem Arduino UNO nicht enthalten ist. Ähnlich wie die Helligkeit einer LED lässt sich mit PWM auch die Drehzahl eines Gleichstrommotors einstellen.

**Man könnte also sagen, ein PWM-Signal ist eine "virtuelle analoge Spannung".**

## Wie generiere ich ein PWM-Signal mit dem Arduino?

Ein PWM-Signal zu generieren, ist dank den Arduino-Funktionen sehr einfach. Zunächst muss man aber schauen, dass man auch den richtigen I/O-Pin verwendet, sonst ist die Fehlersuche nachher sehr frustrierend. Folgende Tabelle zeigt die PWM-Pins verschiedener Arduino-Modelle:

| BOARD                     | PWM PINS                       | PWM FREQUENZ                               |
|:-------------------------:|:------------------------------:|:------------------------------------------:|
| Uno, Nano, Mini           | 3, 5, 6, 9, 10, 11             | 490 Hz (Pins 5 und 6: 980 Hz)              |
| Mega                      | 2 - 13, 44 - 46                | 490 Hz (Pins 4 und 13: 980 Hz)             |
| Leonardo, Micro, Yún      | 3, 5, 6, 9, 10, 11, 13         | 490 Hz (Pins 3 und 11: 980 Hz)             |
| Uno WiFi Rev2, Nano Every | 3, 5, 6, 9, 10                 | 976 Hz                                     |
| MKR Boards *              | 0 - 8, 10, A3, A4              | 732 Hz                                     |
| MKR1000 WiFi *            | 0 - 8, 10, 11, A3, A4          | 732 Hz                                     |
| Zero *                    | 3 - 13, A0, A1                 | 732 Hz                                     |
| Nano 33 IoT *             | 2, 3, 5, 6, 9 - 12, A2, A3, A5 | 732 Hz                                     |
| Nano 33 BLE/BLE Sense     | 1 - 13, A0 - A7                | 500 Hz                                     |
| Due **                    | 2-13                           | 1000 Hz                                    |
| 101                       | 3, 5, 6, 9                     | Pins 3 und 9: 490 Hz, Pins 5 und 6: 980 Hz |

\* Zusätzlich zu PWM-Signalen können die Boards MKR, Nano 33 IoT und Zero am A0-Pin echte analoge Signale ausgeben
\*\* Das Board Due kann and den Pins DAC0 und DAC1 ebenfalls echte analoge Spannungen ausgeben.
Quelle der Tabelle: [arduino.cc](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/) 

Im Code muss die Funktion analogWrite() verwendet werden. Sie erhält zwei Parameter: Der erste ist eine Integer, die für die Nummer des I/O-Pins steht, der zweite steht für den Duty-Cycle als Integer-Zahl zwischen 0 und 255. Will man den Duty-Cycle in % angeben, muss man ihn vorher umrechnen (siehe unten).

```c++
int ledPin = 5;
int dutyCycle = 127; // entspricht 50%
analogWrite(ledPin, dutyCycle);
```

Man kann ein PWM-Signal natürlich auch manuell erzeugen, indem man den Pin auf HIGH setzt (mit digitalWrite), dann z.B. mit der delay()-Funktion wartet, den Pin wieder auf LOW setzt, dann wieder wartet und so weiter. Das ist viel komplizierter, dafür kann man aber recht einfach die Frequenz variieren.

### Einstellung des Duty-Cycles

Wie bereits erwähnt, funktioniert die Einstellung des Duty-Cycles über den zweiten Parameter der analogWrite()-Funktion. Dieser muss eine Integer zwischen 0 und 255 sein. Zur Umrechnung von Prozentwerten kann man z.B. [map()-Funktion](https://www.arduino.cc/reference/en/language/functions/math/map/)  verwenden. Sie funktioniert so:

```c++
neuerWert = map(alterWert, untereGrenzeAlt, obereGrenzeAlt, untereGrenzeNeu, obereGrenzeNeu, alterWert);
achtBitWert = map(prozentWert,0,100,0,255);
```

### Einstellung der Frequenz

coming soon...

<iframe width="728" height="410" src="https://www.youtube.com/embed/HfIPJ1FykdQ" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

---
layout: post
title: "Tutorial #14: Schieberegister mit Arduino ansteuern"
categories:
---

#### Schieberegister sind eine tolle Möglichkeit, Pins am Arduino einzusparen und die synchrone Ansteuerung von Pins stark zu vereinfachen. In diesem Text wird erklärt, wie das funktioniert.

-----------------------------------------------


##### Zu diesem Text haben wir ein Video auf unserem YouTube-Kanal hochgeladen:
<iframe width="728" height="410" src="https://www.youtube.com/embed/0AR1Knf9hLM" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
##### Die Beispiel-Arduino-Programme findet ihr [hier](https://nikoro1904.github.io/robotic-tutorials/2019/12/27/code-tutorial-schieberegister.html)
-----------------------------------------------


Wenn man im Internet nach "Arduino Shift Register" (Shift Register ist der englische Ausdruck für Schieberegister) sucht, findet man fast hauptsächlich Tutorials und Anleitungen zu **74HC...** Schieberegistern, z.B. 74HC164 oder 74HC595. Deshalb soll es hier NICHT um diese Schieberegister gehen. In diesem Text wird ein **TPIC 6B595 POWER LOGIC 8-BIT SHIFT REGISTER** behandelt. 

#### Gliederung:
1. Schieberegister allgemein
2. Das TPIC 6B595 Power Logic Shift Register
3. Arduino-Ansteuerung von Schieberegistern


## Schieberegister allgemein
Ein Schieberegister besteht im Prinzip aus aneinander gehängten [D-Flip-Flops](https://de.wikipedia.org/wiki/Flipflop). Ein D-Flip-Flop ist eine Speichereinheit für 1 Bit (also 1 oder 0). Es hat einen Eingang (Daten-Pin, D), einen Clock-Pin (C oder CLK), einen Ausgang (Q) und manchmal einen invertierten Ausgang (Q&#x305;). Es funktioniert so: Wenn der Clock-Pin C eine aufsteigende Flanke erhält, speichert er den aktuellen Zustand des Daten-Pins D und gibt ihn am Ausgang Q aus, bzw. gibt den invertierten Zustand von D an Q&#x305; aus.  
Wenn man jetzt die Clock-Pins mehrerer D-Flip-Flops verbindet, synchronisiert man die Flip-Flops. Dann kann man Q1 von Flip-Flop 1 mit D2 von Flip-Flop 2 verbinden, Q2 mit D3, Q3 mit D4 und so weiter. So kann man mit jedem Takt die Bits weiterschieben.

![Schaltplan eines 4-Bit Schieberegisters.](../../../assets/media/tutorial_schieberegister/4_bit_simple.jpeg "Schaltplan eines 4-Bit-Schieberegisters.")

Solche Schieberegister werden in vielen elektronischen Bauteilen verwendet, auch im Arduino. Wirklich praktisch werden sie aber erst in Kombination mit einem parallelen Register. Dabei wird jeder Ausgang Q der Flip-Flops mit dem Eingang D eines zusätzlichen D-Flip-Flops verbunden. Diese zusätzlichen Flip-Flops sind nicht in Reihe geschalten, haben aber eine gemeinsame Clock. Ihre Ausgänge Q sind z.B. die Pins außen an einem Chip.  

![Schaltplan eines 4-Bit Schieberegisters mit parallelen Ausgängen.](../../../assets/media/tutorial_schieberegister/4_bit_with_parallel_out.jpeg  "Schaltplan eines 4-Bit Schieberegisters mit parallelen Ausgängen.")

Die 4 parallelen Ausgänge können jetzt z.B. Pins von einem Chip sein. So hat man 4 parallele Ausgänge, aber nur drei Eingänge (der serielle Dateneingang plus die zwei Clocks). So richtig lohnt sich das also noch nicht, wir haben nur einen Pin vom Arduino gespart. Man kann das ganze aber natürlich zu einem 8-Bit oder 16-Bit Schieberegister vergrößern und braucht immer noch nur 3 EIngänge.

## Das TPIC 6B595 Power Logic Shift Register
Die bisher gezeigten, klassischen Schieberegister eignen sich hervorragend zur Datenverarbeitung. Auch einzelne LEDs kann man vielleicht gerade noch so ansteuern. Für höhere Leistungen sind sie jedoch nicht mehr geeignet, das SN74HC595 z.B. hat eine maximale Stromaufnahme von +/- 70 mA und das für alle 8 Bit zusammen.

Möchte man aber z.B. Motoren mit deutlich höherer Stromaufnahme schalten, bietet sich ein POWER LOGIC SHIFT REGISTER wie das TPIC 
B595 an. Das funktioniert im Prinzip wie jedes Schieberegister, also auch mit einer internen Low-Power Logik mit 5 V. An jedem parallelen Ausgang ist aber ein [Feldeffekt-Transistor (FET)](https://de.wikipedia.org/wiki/Feldeffekttransistor) angeschlossen. Die Logik ist mit den Gates (G) der Transistoren verbunden. Das heißt, wenn eine logische 1 anliegt, öffnet sich das Gate und der physische Ausgang (Drain, D) wird mit der Source (S) des Transistors verbunden. Die Sources aller Ausgänge sind direkt an den Ground-Pin (GND) des Chips angeschlossen. So erhält man im Prinzip seriell steuerbare Schalter.

![Schaltplan eines 4-Bit Schieberegisters mit parallelen Ausgängen mit FETs.](../../../assets/media/tutorial_schieberegister/4_bit_with_FETs.jpeg  "Schaltplan eines 4-Bit Schieberegisters mit parallelen Ausgängen mit FETs.")

Das TPIC 6B595 ist ein 8-Bit Schieberegister. Jeder Output-Pin (also jedes Drain) kann maximal 50 V und 150 mA steuern. Insgesamt kann der Chip aber nur 500 mA, d.h. es können nicht alle 8 Pins gleichzeitig 150 mA leiten. Den genauen Schaltplan mit allen technischen Daten findet man im [Datenblatt](https://www.ti.com/lit/ds/symlink/tpic6b595.pdf) von Texas Instruments.

Insgesamt hat der Chip des TPIC 6B595 20 Pins, im folgenden werden diese hier kurz beschrieben:

* **1, 20) NC (not connected).** Diese Pins sind intern im Chip nicht verbunden.
* **2) Vcc**, Logik-Versorgungsspannung. Hier muss eine Spannungsquelle mit 4,5 V bis 5,5 V angeschlossen werden, z.B. der 5V-Pin vom Arduino.
* **3) SER IN**, serieller Eingang des Schieberegisters.
* **4), 5), 6), 7) DRAIN0 bis DRAIN3**
* **8) <span style="text-decoration:overline">SRCLR</span>**, Shift Register Clear. Muss auf HIGH (+5V) gesetzt werden, damit Daten im Schieberegister gespeichert werden können. Wenn SRCLR' auf LOW (0V) gesetzt wird, werden alle Daten im Schieberegister gelöscht.
* **9) G&#x305;**, Output Enable. Muss auf LOW gesetzt werden, damit die Daten vom parallelen Register an die FETs weitergegeben werden kann. Man kann hiermit also das Schieberegister vorübergehend an- und ausschalten.
* **10, 11, 19) GND** 
* **12) RCK**, Register Clock. Bei einer steigenden Flanke werden Daten vom Schieberegister ins parallele Register übernommen. Wenn dann noch der Output Enable Pin aof LOW ist, werden die Drain-Anschlüsse entsprechend geschalten.
* **13) SRCK**, Shift Register Clock. Für jede steigende Flanke werden die Daten im Schieberegister eine Stelle weitergeschoben.
* **14), 15), 16), 17)** DRAIN4 bis DRAIN7
* **18) SER OUT**, serieller Ausgang des Schieberegisters. Kann direkt an den seriellen Eingang eines zweiten Chips angeschlossen werden, um das Schieberegister auf 16 Bit zu verlängern.

Die prinzipielle interne Verschaltung kann man im [Datenblatt](https://www.ti.com/lit/ds/symlink/tpic6b595.pdf) finden. Hier ein Ausschnitt daraus: 
![Internes Logikdiagramm des TPIC 6B595](../../../assets/media/tutorial_schieberegister/Logic_Diagram.jpeg  "Internes Logikdiagramm des TPIC 6B595")

## Arduino-Ansteuerung von Schieberegistern
Wenn man verstanden hat, was die einzelnen Pins am Schieberegister (SRCK, G&#x305;, SER IN, usw.) jeweils für eine Funktion haben, ist die Ansteuerung sehr einfach. 

Für eine einfache Funktion kann man die Pins G&#x305; und <span style="text-decoration:overline">SRCLR</span> dauerhaft auf LOW, bzw. HIGH schalten. Man kann sie direkt mit dem GND bzw. Vcc Pin verbinden oder jeweils an einen Digital Pin am Arduino anschließen. Dann kann man sie mit folgendem Code in der Setup-Funktion schalten:
```c++
#define srclr 4
#define g 6

void setup() {
	pinMode(g, OUTPUT);
	pinMode(srclr, OUTPUT);
	digitalWrite(g, LOW);
	digitalWrite(srclr, HIGH);
	}
 ```
 
Als nächstes kümmern wir uns um die anderen Pins. Wir schließen also RCK, SRCK und SER IN an weitere Digital Pins vom Arduino. Vcc kommt an den 5V-Pin und die GND-Pins an den GND-Pin vom Arduino. Wir passen unsere Setup Funktion dafür an:

```c++
#define ser_in 2
#define srck 3
#define srclr 4
#define rck 5
#define g 6

void setup() {
	for(j=2; j<=6; j++) {
		pinMode(j, OUTPUT);
		}
	digitalWrite(g, LOW);
	digitalWrite(srclr, HIGH);
	}
```

An die Ausgänge können wir zum Beispiel LEDs mit Vorwiderständen schalten. Das sieht dann z.B. so aus:

![Beispielschaltplan](../../../assets/media/tutorial_schieberegister/circuit.jpeg  "Beispielschaltplan")

In der Loop Funktion können wir jetzt die LEDs über das Schieberegister einzeln ein- und ausschalten, also z.B. ein Lauflicht oder andere Lichteffekte programmieren. Hierfür schreiben wir 8-Bit Variablen in das Register. Das sind in C++ Variablen vom Datentyp ```char```. Wenn wir jetzt die LEDs alle einschalten wollen, schicken wir z.B. diese Variable  
```char all_leds_on = 0b11111111;```  
oder als Hexadezimalzahl:  
```char all_leds_on = 0xff;```  
Wenn wir einzelne LEDs ausschalten wollen, ersetzen wir die entsprechenden 1 Bits mit 0. Zum Beispiel wenn jede zweite LED an sein soll:  
```char every_second_led = 0b01010101;```  
bzw.  
```char every_second_led = 0x55;```

### Das Schieberegister beschreiben
Diese Variablen können dann mit der [shiftOut()-Funktion](https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/) in das Schieberegister geschoben werden. Das setzen der steigenden Flanke vom SRCK-Pin für jedes einzelne Bit übernimmt die Funktion. Es muss zusätzlich aber noch die steigende Flanke für den RCK-Pin gesetzt werden. So wird markiert, wann die Daten im Schieberegister an die Drain-Anschlüsse weitergegeben werden sollen. Das ganze sieht z.B. so aus:

```c++
#define ser_in 2
#define srck 3
#define srclr 4
#define rck 5
#define g 6

char every_second_led = 0x55;

void setup() {
	for(j=2; j<=6; j++) {
		pinMode(j, OUTPUT);
		}
	digitalWrite(g, LOW);
	digitalWrite(srclr, HIGH);
	}
void loop() {
	digitalWrite(rck, LOW);
	shiftOut(ser_in, srck, MSBFIRST, every_second_led);
	digitalWrite(rck, HIGH);
	delay(500);
	
	digitalWrite(rck, LOW);
	shiftOut(ser_in, srck, LSBFIRST, every_second_led);
	digitalWrite(rck, HIGH);
	delay(500);
	}
```

Mit diesem Code werden zuerst die LEDs 0, 2, 4, 6 angeschalten, nach 500 ms Pausen werden die LEDs 1, 3, 5, 7 angeschalten. Das wiederholt sich dann immer wieder.  
In die shiftOut()-Funktion müssen wir folgende Informationen mitreinschreiben: 
1. Den Pin, der an den Dateneingang des Schieberegisters angeschlossen ist.
2. Den Pin, der an die Clock des Schieberegisters angeschlossen ist.
3. MSBFIRST oder LSBFIRST. MSB ist das **M**ost **S**ignificant **B**it, LSB das **L**east **S**ignificant **B**it. Das MSB ist also das Bit ganz links, LSB das ganz rechts. Mit diesem Parameter können wir also festlegen, in welcher Richtung die Variable in das Schieberegister geschoben werden soll.
4. Die 8-Bit Variable, die wir in das Schieberegister schreiben wollen.

### Das Schieberegister auslesen
Am SERIAL OUT Pin des Schieberegisters könnten wir auslesen, welche Bits aus dem Schieberegister rausgeschoben werden, also quasi der Überlauf. Wir können auch das Schieberegister auslesen, indem wir z.B. 0x00 hereinschieben und den Ausgang auslesen. Solange wir keine aufsteigende Flanke an den RCK-Pin schicken, werden die Zustände der Transistoren (bzw. der Drain-Pins oder der Ausgänge) nicht übernommen. Zum Auslesen des Registers verwendet man die [shiftIn()-Funktion](https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftin/).

### Mehrere Schieberegister kaskadieren / aneinanderhängen
Wenn wir nicht nur 8, sondern z.B. 16 oder 24 LEDs so schalten wollen, können wir 2 bzw. 3 Schieberegister aneinanderhängen, d.h. wir verbinden den SERIAL OUT Pin des 1. Registers mit dem SERIAL IN PIn des 2. Registers und so weiter. Die Steuerpins RCK, SRCK u.s.w. können zwischen den Schieberegistern verbunden werden. Dann können wir entweder eine 16-Bit Variable an den ersten SERIAL IN Pin schicken (das wäre eine Variable vom Typ ```int```), oder wir schicken einfach zwei oder drei 8-Bit Variablen (vom Typ ```char```) direkt nacheinander. Die aufsteigende Flanke für den RCK-Pin dürfen wir dann aber erst nach dem letzten shiftOut() schicken.

------------------------------------------------------------------

Veröffentlicht am 24.12.2019  
Bei Fragen bitte eine Email schicken (siehe unten) oder einen Kommentar unter das zugehörige Youtube-Video (kommt bald) schreiben.


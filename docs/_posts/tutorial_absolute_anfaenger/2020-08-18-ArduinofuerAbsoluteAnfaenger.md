---
layout: post
title: "Arduino-Grundlagen für absolute Anfänger (#1)"
categories:
excerpt_separator: <!--endofexcerpt-->

---

[![Titelbild](../../../../robotic-tutorials/assets/media/tutorial_absolute_anfaenger/preview_anfaenger.png)](https://nikoro1904.github.io/robotic-tutorials/2020/08/18/ArduinofuerAbsoluteAnfaenger.html)

Was ist eigentlich ein Arduino und was brauche ich, um damit zu arbeiten?

<!--endofexcerpt-->

## Was ist ein Arduino?

Ein Arduino ist ein Mikrocontroller (wird manchmal mit µC abgekürzt) auf einer kleinen Platine, zusammen mit ein paar zusätzlichen elektronischen Bauteilen, sodass man ihn ganz einfach verwenden kann. Der eigentliche Mikrocontroller ist nur ein kleiner Chip auf der Platine, z.B. ein ATmega328P von der Firma Atmel. Die Firma “Arduino” hat die Schaltpläne für die Platinen frei verfügbar veröffentlicht, sodass man Arduino-Boards nicht nur von der offiziellen Marke kaufen kann, sondern es gibt auch viele sogenannte “Klone”, die in der Regel billiger sind und genauso gut funktionieren. 

[<img src="../../../../robotic-tutorials/assets/media/Youtube_Link_images/yt_link_absolute_anfaenger.jpg" alt="Link-Image">](https://www.youtube.com/watch?v=b-VcfwqDJLU)

Unabhängig von der Firma, die die Arduinos herstellt, gibt es verschiedene Typen, die sich vor allem durch den Mikrocontroller-Chip unterscheiden. Der kleinste Arduino-Typ, der “Arduino Nano”, hat z.B. einen ATmega328, der mittelgroße und bekannteste “Arduino Uno” hat einen ATmega328P und der größere Arduino Mega hat einen ATmega2560. Der Chip wirkt sich auf verschiedene Eigenschaften aus, die offensichtlichste ist die Anzahl der I/O-Pins. I/O-Pins sind Input/Output-Pins, das sind die Anschlüsse, mit denen der Mikrocontroller mit der Außenwelt kommunizieren kann. Verwendet man sie als Output, kann man z.B. eine LED ein- und ausschalten. Verwendet man sie als Input, kann man z.B. den Wert eines Temperatursensors lesen.

Zur eben beschriebenen Hardware benötigt man auch eine Software, um dem Arduino zu sagen was er machen soll, um ihn also zu programmieren. Auch diese Software ist frei verfügbar, man kann sie gratis auf der Website arduino.cc herunterladen. Die Arduino Entwicklungsumgebung (kurz: Arduino IDE) verwendet die Programmiersprache C++. Allerdings benötigt man für die Arduino-Programmierung nur einen sehr kleinen Teil von C++, der auch so vereinfacht ist, dass es wirklich jeder verstehen kann.

![Screenshot von der Download-Seite der Arduino IDE](../../../assets/media/tutorial_absolute_anfaenger/download_screenshot.jpg "Screenshot von der Download-Seite der Arduino IDE")

## Was benötige ich, um einen Arduino zu programmieren?

### Minimal-Setup

Grundsätzlich braucht man zur Arduino-Programmierung nur 3 Dinge:

- einen Computer (Linux, Mac, Windows, …)
- einen Arduino
- ein passendes USB-Kabel

Mit dem Computer lädt man die Arduino IDE herunter (hier) und installiert sie. Dann schließt man mit dem USB-Kabel den Arduino an und schon kann man beginnen. Um zu überprüfen, ob man alles richtig gemacht hat, kann man in der IDE unter Datei-Beispiele-01.Basics-Blink ein Beispielprogramm laden. Dann wählt man unter Werkzeuge noch das passende Board und den Port aus. Jetzt drückt man auf “Überprüfen” und anschließend auf “Hochladen”. Wenn man alles richtig gemacht hat, kann man jetzt auf dem Board eine LED im Sekundentakt blinken sehen. Eine genauere Anleitung kommt etwas später in diesem Dokument.

![Ein Original-Arduino vom Modell UNO](../../../assets/media/tutorial_absolute_anfaenger/arduino-stock.jpg "Ein Original-Arduino vom Modell UNO")

### Was sollte ich noch dazu kaufen?

Mit dem Minimal-Setup kann man nicht wirklich etwas anfangen. Was man dazu kaufen sollte, hängt natürlich davon ab, was man mit dem Arduino anfangen will. Auf jeden Fall sinnvoll ist folgendes:

- ein Steckbrett (Breadboard)
- ein paar Jumper-Kabel 

[Bild von Breadboard und Jumpers]

Alles andere ist wieder von der spezifischen Anwendung abhängig. Wenn man einfach nur etwas basteln und ausprobieren möchte, um den Arduino kennen zu lernen, empfiehlt sich folgendes:

- ein kleines Sortiment von Widerständen
- ein paar LEDs
- einen oder zwei Buttons (Druckknöpfe)
- ein Potentiometer
  …

[Bilder der genannten Gegenstände]

Damit kann man schon einiges ausprobieren. Wem das zu wenig ist, der kann sich mal die Projekt-Ideen und -Beispiele anschauen. Es gibt viele Möglichkeiten, für wenig Geld ein paar kleine Dinge zu basteln.

![Arduino Community Logo](../../../assets/media/tutorial_absolute_anfaenger/ArduinoCommunityLogo.png "Arduino Community Logo")

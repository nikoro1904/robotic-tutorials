# Video Differential-Antrieb
Niko, 26. Mai 2021

## Abstract

Dieses Video zeigt, wie man einen Roboter mit Differential-Antrieb programmieren kann. Als Beispiel wird der Code zur Berechnung der Motordrehzahlen und Drehrichtungen mittels linearer Abbildung von x- und y-Koordinate eines Joysticks auf den zweidimensionalen Vektorraum der (gerichteten)Drehzahlen der Motoren gegebn. Details zur Elektronik werden mit Ausnahme des Schaltplans nicht gezeigt. Zum Schluss werden noch ein paar praktische Tipps gegeben.

### Weiterführende Informationen zu Differential-Drive-Kinematik
http://www.cs.columbia.edu/~allen/F15/NOTES/icckinematics.pdf

## Struktur:
	- Einleitung
		- Was ist ein Differentialantrieb?
		- Wo braucht man einen Differential?
	- Methoden
		- Wie programmiert man das?
		- Wie wird die Elektronik aufgebaut?
	- Ergebnisse
		- Die Realität
	- Fazit

## Text

### Was ist ein Differentialantrieb?

Ein Differentrialantrieb, oder kurz einfach "Differential", auf englisch "differential drive", ist ein Antrieb aus zwei unabhängigen Motoren einer Achse. D.h. das rechte und das linke Rad haben jeweils einen eigenen Motor. Räder der anderen Achsen benötigen dann keinen Antrieb. Drehen beide Motoren vorwärts, fährt der Roboter nach vorne. Drehen beide rückwärts, fährt er nach hinten. Dreht dabei aber z.B. der linke Motor schneller wie der rechte, macht der Roboter eine Rechtskurve, weil die linke Seite schneller fährt und die rechte Seite quasi "überholt". Der Name "Differential" kommt daher, dass die Richtung des Roboters über die Differenz, also den Unterschied der Drehzahlen der Räder eingestellt wird.

### Wo braucht man einen Differential?

Ein Differential wird gern für kleine mobile Roboter wie z.B. Staubsaugerroboter oder Rasenmäherroboter verwendet. Auch Rollstühle funktionieren nach diesem Prinzip, nur sind die Antriebe hier die Muskeln des Patienten. Man kann sie so in alle Richtungen in der Ebene lenken und auch auf der Stelle rotieren lassen, wenn beide Räder gleich schnell aber in unterschiedliche Richtungen drehen. So ist es einfach, z.B. aus Ecken oder engen Orten herauszumanövrieren.x

### Wie programmiert man das?

Die Programmierung ist der etwas komplizierte Teil bei dem ganzen. Üblicherweise hat man die Informationen Geschwindigkeit und Richtung und möchte diese überführen in z.B. PWM-Werte für die Drehzahl der Motoren.

Man muss also eine 2D-Information (Geschwindigkeit, Richtung) in eine andere 2D-Information (Drehzahl Rechts, Drehzahl Links) umrechnen.

Oder man beginnt mit einem Joystick und möchte dessen x- und y-Position in die Motordrehzahlen umrechnen. Auch dann konvertiert man eine 2D-Information in eine andere 2D-Information. Diese Variante wollen wir uns in diesem Video anschauen, es ist aber nicht schwierig, den Richtungswinkel in einen solchen y-Wert umzurechnen. Schaut dazu auf unseren Website-Eintrag zu diesem Video, Link ist in der Beschreibung. Dort findet ihr auch den Arduino-Code zum Video.

Für die Umrechnung von Joystick-Position zu Motor-Drehzahlen gibt es jetzt theoretisch unendlich viele verschiedene Möglichkeiten. Wir wählen hier eine einfache und relativ sinnvolle Lösung, eine lineare Abbildung. Wenn ihr das folgende mathematische nicht versteht oder nicht verstehen wollt, könnt ihr auch einfach die Lösung übernehmen und für euch anpassen. Ich versuche aber, die Erklärung möglichst einfach und wenig fachsprachlich zu geben.

Als erstes skalieren wir alle unsere Werte auf einen Wert zwischen -1 und 1. Das macht die Theorie einfacher und universal für verschiedene Hardware. Später rechnen wir das dann wieder auf Werte zwischen 0 und 1023 oder 0 und 255 um, um die realen Bauteile anzusteuern.

Eine lineare Abbildung von 2D zu 2D funktioniert über eine Matrix-Multiplikation. Wir verwenden eine 2x2 Matrix mit 2 Zeilen und 2 Spalten, also den vier Parametern a, b, c und d. Diese repräsentieren einfach beliebige Zahlen. Multiplizieren wir die Matrix mit dem Eingangsvektor (z.B. x- und y-Wert des Joysticks), erhalten wir den Ergebnisvektor (z.B. Drehzahl Rechts und Drehzahl Links). Das ganze können wir aber auch als zwei separate Rechnungen darstellen, dann brauchen wir die Matrix-Schreibweise nicht mehr.

Jetzt müssen wir die vier Parameter a, b, c und d bestimmen. Um die Parameter festzulegen, suchen wir uns Kombinationen aus Eingangsvektoren und Ergebnisvektoren, die bekannt sind, bzw. die wir jetzt festlegen.

Z.B. wollen wir für den Eingangsvektor (0,0), dass sich beide Motoren nicht bewegen. Wenn wir das in die Gleichungen eintragen, müssen sie aufgehen, d.h. es darf keinen Widerspruch geben. Das ist auch nicht der Fall, war aber auch nicht zu erwarten bei einer solchen linearen Abbildung.

Wir brauchen noch mehr solche Kombinationen. Ist unser Joystick z.B. gerade und maximal nach vorne gerichtet, dann ist unser Eingangsvektor = (0, 1). Unser Ausgangsvektor soll in diesem Fall (1, 1) sein, also beide Motoren sollen mit 100% Geschwindigkeit nach vorne drehen.

Alle folgenden Kombinationen müssen "linear unabhängig" von den vorherigen sein. Das heißt, sie dürfen sich nicht durch einfache Skalierung oder das zusammensetzen vorheriger Kombinationen ergeben. In diesem Fall wäre jetzt eine neue Kombination mit (-1, -1) nicht möglich. Sie ist einfach die vorherige Kombination mit -1 multipliziert und liefert keine neue Information, wie man sieht.

Eine weitere Kombination wäre (1, 0) und (-1, 1). Das bedeutet übersetzt: Bewegen wir den Joystick nur nach rechts, soll der Roboter sich auch nur nach rechts drehen, ohne dabei nach vorne und hinten zu fahren. Dafür muss der linke Motor nach vorne drehen (+1) und der rechte gleichzeitig nach hinten (-1).

Eine weitere nötige und mögliche Kombination seht ihr hier in blau. Durch das Einsetzen in die Gleichungen können wir die Parameter der Matrix bestimmen. Wir erhalten z.B. folgende Matrix.

(a, b; c, d) = (-1, 1; 1, 1)

Die Rechnung, die wir im Arduino Programm ausführen müssen, sieht dann so aus:

1. Einlesen der Joystick-Werte mit analogRead() -> gibt Werte zwischen 0 und 1023.
2. Skalieren dieser Werte auf den Bereich -1 bis 1.
3. Berechnung der Ergebniswerte mit den Gleichungen der linearen Abbildung.
4. Skalieren auf die Ausgangswerte, hier PWM-Werte mit einem Bereich von 0 bis 255. Achtung! Der Betrag dieser Zahl bestimmt die Drehzahl, das Vorzeichen die Drehrichtung. Wir benötigen beide Informationen, aber separat.
5. Im nächsten Schritt berechnen wir also den Betrag
6. Und anschließend legen wir die Richtung anhand des Vorzeichens fest, die Funktion dazu haben wir hier oben definiiert. Was die INPUT-Pins sind, sehen wir gleich.
7. Im 7. und letzten Schritt, bevor wieder alles von vorne beginnt, schreiben wir die Beträge, also die Absolutwerte von eben an die ENABLE-PINS.

Wie wir diese Informationen verarbeiten, seht ihr jetzt:

### Wie wird die Elektronik aufgebaut?

Für dieses Beispiel verwenden wir zwei einfach DC-Motoren, die wir mit einer L293B-H-Brücke ansteuern. Wie das geht, könnt ihr in unserem Video Nr. 12 anschauen, es ist auch in der Beschreibung verlinkt. Wir schließen die Motoren so an wie hier auf dem Schaltplan, dass wir beide Motoren in beide Richtungen drehen können.

Die Richtungsinformation schreiben wir als digitale Werte auf die INPUT-Pins des L293. So wird festgelegt, in welcher Richtung der Strom durch die H-Brücken fließen kann. Die Stromrichtung bestimmt dann eben die Drehrichtung der Motoren. Die Drehzahlwerte schreiben wir als PWM-Werte auf die Enable-Pins. Sie stellen ein, wieviel Strom durch die H-Brücken fließen und bestimmen eben somit die Drehzahl.

Damit die Motoren am Ende auch so drehen wie gewünscht, ist entscheidend, dass sie richtig rum mit dem L293 verbunden sind. Das findet man aber am besten durch ausprobieren heraus.

### Die Realität

Bisher war alles hier Theorie. In der Praxis funktioniert das ganze dann leider nicht so schön, auch wenn das Prinzip richtig ist. Z.B. schwanken die Positionen des Joysticks immer ein bisschen, sodass die Motoren immer etwas unruhig sind. Auch ist die Steuerung sehr hart und empfindlich, schon kleine Bewegungen am Joystick lösen starke Bewegungen des Roboters aus.

Möglichkeiten zur Lösung dieser Probleme sind z.B. die Diskretisierung der Eingangs- oder Ausgangswerte. Wir haben z.B. die Ausgangswerte von 0 bis 255 nochmal in 5 Abschnitte aufgeteilt, sodass z.B. für Werte von 0 bis 50 eine 0 ausgegeben wird, für Werte zwischen 51 bis 102 eine 51 und so weiter. Das macht den Roboter weniger wackelig. Wem die Lenkung zu extrem ist, der muss die Parameter der Matrix anpassen, z.B. so: 

(-1/2, 1; 1/2, 1)

Hier haben wir für die Eingangskombination (1, 0) (Rechtskurve) den Ausgang (-0.5, 0.5) gewählt. Das macht die Kurven weniger scharf.

Am Ende muss man natürlich selber schauen, was einem am besten passt für die eigene Anwendung. Schreibt gerne eure eigenen Tipps oder auch offene Fragen in die Kommentare.

### Fazit:

Wir hoffen, ihr konntet aus dem Video etwas mitnehmen. Links zum Arduino-Code und Schaltplan sind in der Beschreibung. Bis zum nächsten Mal, ciao!

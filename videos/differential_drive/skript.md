# Video Differential-Antrieb
Niko, 26. Mai 2021

## Übersicht
- Abstract
	- weiterführende Informationen
- Struktur des Videos
- Text des Videos
- Text des Videos (englisch)

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

Durch das Einsetzen in die Gleichungen können wir die Parameter der Matrix bestimmen. Wir erhalten z.B. folgende Matrix.

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


## Text (english mainly by deepl)

A differential drive, or simply "differential" for short, is a drive consisting of two independent motors on one axle. This means that the right and left wheels each have their own motor. Wheels of the other axles then do not need a drive. If both motors turn forward, the robot moves forward. If both motors turn backwards, the robot moves backwards. If, however, the left motor turns faster than the right motor, for example, the robot makes a right turn because the left side moves faster and "overtakes" the right side. The name "differential" comes from the fact that the direction of the robot is set via the difference, i.e. the difference in the speeds of the wheels.

### Where do you need a differential?

A differential is popular for small mobile robots such as vacuum cleaner robots or lawn mower robots. Wheelchairs also work on this principle, only here the drives are the patient's muscles. This allows them to be steered in all directions on the plane and also to rotate on the spot if both wheels turn at the same speed but in different directions. This makes it easy to maneuver out of corners or tight places.

### How do you program it?

The programming is the somewhat complicated part of it all. Usually you have the speed and direction information and you want to convert that into, for example, PWM values for the speed of the motors.

So you have to convert one 2D information (speed, direction) into another 2D information (speed of right wheel, speed of left wheel).

Or you start with a joystick and want to convert its x and y position into the motor speeds. Then you also have to convert one 2D information into another 2D information. We will look at this variant in this video, but it is not difficult to convert the direction angle into such a y-value. Have a look at our github repo, link is in the description. There you will also find the Arduino code to the video.

Now, for converting joystick position to motor speeds, there are theoretically an infinite number of different possibilities. We chose a simple and relatively reasonable solution, a linear mapping. If you don't understand or don't want to understand the following mathematical, you can just take the solution and adapt it for your needs. But I will try to give the explanation as simple and as less technical as possible.

First we scale all our values to a value between -1 and 1. This makes the theory easier and universal for different hardware. Later, we scale that back to values between 0 and 1023 or 0 and 255 to drive the real components.

A linear mapping from 2D to 2D works via matrix multiplication. We use a 2x2 matrix with 2 rows and 2 columns, i.e. the matrix has four parameters a, b, c and d. These simply represent arbitrary numbers. If we multiply the matrix with the input vector (e.g. x- and y-value of the joystick), we get the result vector (e.g. speed right and speed left). But we can also represent the whole thing as two separate calculations, then we don't need the matrix notation.

Now we have to determine the four parameters a, b, c and d. To determine the parameters, we look for combinations of input vectors and result vectors, which are known, or which we will determine right now.

For example, for the input vector (0,0), we want both motors to not move. If we enter this into the equations, they must tally, i.e. there must be no contradiction. This is not the case, but was also not to be expected with such a linear mapping.

We need more such combinations. For example, if our joystick is straight and maximally forward, then our input vector = (0, 1). Our output vector in this case should be (1, 1), so both motors should turn forward with 100% speed.

All following combinations must be "linearly independent" from the previous ones. That is, they must not result from simple scaling or putting together previous combinations. In this case, a new combination with (-1, -1) would not be possible. It is simply the previous combination multiplied by -1 and doesn't provide any new information, as you can see.

Another combination would be (1, 0) and (-1, 1). This means: If we move the joystick only to the right, the robot should also turn only to the right, without moving forward and backwards. For this, the left motor must rotate forward (+1) and the right motor must rotate backwards at the same time (-1).

By inserting the vectors into the equations we can determine the parameters of the matrix. For example, we get the following matrix.

(a, b; c, d) = (-1, 1; 1, 1)

The calculations we have to do in the Arduino program then look like so:

1. reading the joystick values with analogRead() -> gives values between 0 and 1023.
2. scaling these values to the range -1 to 1.
3. calculation of the result values with the equations of the linear mapping.
4. scaling to the output values, here PWM values with a range from 0 to 255. Attention! The magnitude of this number determines the speed, the sign determines the direction of rotation. We need both information, but separately.
5. so in the next step we calculate the magnitude
6. and then we define the direction based on the sign, we defined the function for this up here. We will see what the INPUT pins are in a moment.
In the 7th and last step, before everything starts again from the beginning, we write the absolute values to the ENABLE-PINS.

You will now see how we process this information:

### How is the electronics set up?

For this example we use two simple DC motors, which we control with a L293B-H bridge. You can see how this is done in our video #12, it is also linked in the description. We connect the motors as shown here on the schematic, so we can turn both motors in both directions.

We write the direction information as digital values to the INPUT pins of the L293. This determines in which direction the current can go through the H-bridges. The direction of the current then determines the direction of rotation of the motors. We write the speed values as PWM values to the enable pins. They set how much current flows through the H-bridges and thus determine the speed.

For the motors to turn as desired in the end, it is crucial that they are connected to the L293 correctly. The best way to find out is by trial and error.

### Reality

So far, everything here has been theory. In practice, unfortunately, the whole thing doesn't work so well, even if the principle is correct. For example, the joystick positions always fluctuate a bit, so the motors are always a bit unsteady. Furthermore, the control is very hard and sensitive, even small movements on the joystick trigger strong movements of the robot.

Ways to solve these problems include discretizing the input or output values. For example, we have divided the output values from 0 to 255 again into 5 sections, so that e.g. for values from 0 to 50 the output is 0, for values between 51 to 102 it is 51 and so on. This makes the robot less wobbly. If the steering is too extreme for you, you have to adjust the parameters of the matrix, e.g. like this: 

(a, b; c, d) = (-1/2, 1; 1/2, 1)

Here we have chosen the output (-0.5, 0.5) for the input combination (1, 0) (right curve). This makes the curves less sharp.

In the end, of course, you have to see for yourself what suits you best for your own application. Feel free to post your own tips or open questions in the comments.

### Conclusion:

We hope you were able learn something from the video. Links to the Arduino code and schematics are in the description. See you next time, ciao!

Translated with www.DeepL.com/Translator (free version)


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
Stepper motor_1 = Stepper(200,5,4,3,2);

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

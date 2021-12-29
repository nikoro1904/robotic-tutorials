/* Beispielcode für Schrittmotor-Tutorial
   Robotic Tutorials, 15.02.2020

   Dieses Arduino-Programm ist zur Ansteuerung eines bipolaren Hybrid-Schrittmotors.
   In diesem Beispiel dreht sich der Motor einfach immer weiter.
   Die Art der Ansteuerung kann durch Verwendung der Arrays wavedrive, fullstep und halfstep geändert werden.
   Die Drehgeschwindigkeit kann durch Änderung der Variable waitTime eingestellt werden.

   Der Schrittmotor hat zwei Spulen, A und B. Die Spulen haben die Anschlüsse A, A', B und B'
   Für eine übersichtliche Darstellung der Arrays wurde die Reihenfolge der Arduino-Pins im Array pin[] festgelegt.
   - Arduino DP 2 ist verbunden mit Input 1 des L293B, dieser ist verbunden mit Anschluss A des Motors (Schwarz)
   - Arduino DP 3 -> L293B Input 2 -> Motor A' (Grün)
   - Arduino DP 4 -> L293B Input 3 -> Motor B  (Rot)
   - Arduino DP 5 -> L293B Input 4 -> Motor B' (Blau)

*/

// Definition der Variablen:

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
  
  for (int s = 0; s < 8; s++) {
    for (int p = 0; p < 4; p++) {
      digitalWrite(pin[p], halfstep[s][p]);
    }
    delayMicroseconds(waitTime);
  }
}

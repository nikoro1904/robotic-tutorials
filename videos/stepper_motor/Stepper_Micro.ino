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

// Definition der Variablen:

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
  
  delay(500);
}

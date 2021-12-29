/*
***ROBOTIC TUTORIALS  - 27.März 2017***

  BEISPIEL 1 : 7-Segment-Anzeige

  Das ist der Code für die 7-Segment-Anzeige, der ohne den Decoder funktioniert.
  Die COM-Pins der Anzeige werden über Vorwiderstände an eine Spannungsquelle (Common Cathode)
  oder Ground (Common Anode) angeschlossen. Alle anderen Pins werden direkt an Digital Pins
  des Arduino angeschlossen. Sie werden mit digitalWrite() angesteuert, entweder leuchten die Segmente
  der Anzeige bei HIGH (Common Anode) oder LOW (Common Cathode).

  In diesem Programm zählt die 7-Segment-Anzeige jede Sekunde 1 nach oben, nach 9 fängt sie wieder
  bei 0 an. Der Digital Point wird nicht verwendet. Wenn eure Anzeige keine richtigen Zahlen anzeigt,
  kann es sein, dass eure Pins in einer anderen Reihenfolge sind. Dann entweder die Kabel am Arduino
  umstecken oder die Nummern der PIns in den digitalWrite()-Befehlen ändern.

  Viel Spaß!

  DIESES PROGRAMM FUNKTIONIERT FÜR COMMON ANODE
*/


void setup() {

  for (int i = 1; i < 8; i++)
  {
    pinMode( i , OUTPUT);   //Digital Pins 1-8 werden als OUTPUTs gesetzt
  }

}

void loop() {

  //NULL
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);

delay(500);

  //EINS
  digitalWrite(1, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

delay(500);

//ZWEI
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);

  delay(500);

//DREI
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);

   delay(500);

//VIER
  digitalWrite(1, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  delay(500);

  //FÜNF
  digitalWrite(1, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  delay(500);
  
  //SECHS
  digitalWrite(1, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  delay(500);

   //SIEBEN
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

  delay(500);

     //ACHT
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  delay(500);

       //NEUN
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

delay(500);
  
  


}


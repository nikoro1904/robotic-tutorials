int led = 9;
int Helligkeit = 0;
int aenderung = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(led, Helligkeit);
  Helligkeit = Helligkeit + aenderung;
  if (Helligkeit >= 255 || Helligkeit <= 0) { 
    // Beachte, dass ">" mit ">=" und "<" mit "<=" ausgetauscht wurde, das war auch ein Fehler im Code
    //Helligkeit = -Helligkeit; // Diese Zeile war FALSCH!
    aenderung = -aenderung;     // Diese Zeile ist dafür richtig.
  }
  delay(50); // das Delay von 50 Millisekunden verzögert alles etwas, sodass die LED langsamer dimmt
}

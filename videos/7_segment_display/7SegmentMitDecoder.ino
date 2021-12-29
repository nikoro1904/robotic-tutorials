// Testprogramm für einen automatischen Sekunden-Zähler bei einer 7-Segment-Anzeige
//
//
// Robotic Tutorials
// 27.03.2017
//
//******************************************************************************
//
/* Hardware-Aufbau
Eine 7-Segment-Anzeige mit gemeinsamer Anode (Kingbright SA56-11EWA)
Die Anoden sind über einen Vorwiderstand an 5V am Arduino Leonardo angeschlossen.
Die restlichen Pins der 7SA sind an die passenden Pins des Decoder (Texas Instruments SN74LS247)
(a,b,c,d,e,f,g) angeschlossen. Der Decoder hat keinen Pin für den Digit Point DP, dieser müsste 
bei Bedarf extra angesteuert werden. Die Pins LT, BI/RBO und RBI am Decoder sind mit 3,3V am Arduino verbunden.
Der Vcc am Decoder erhält 5V vom Arduino, Ground ist ebenfalls an Ground am Arduino angeschlossen.

Die Pins A,B,C,D am Decoder sind an die Digital Pins 2-5 am Arduino angeschlossen.
Diese Pins werden vom Arduino nacheinander angesteuert, um von 0-9 hochzuzählen.

Die 7SA zählt jetzt ständig durchlaufend von 0 bis 9, wobei der DP so geschalten wird, dassdie LED eigentlich von 0-19 zählt.
*/

// Die Variablen werden deklariert, A,B,C,D sind die Variablen für die Pins am LS247
const int pA=2, pB=3, pC=04, pD=5, pP=6;

void setup() {
  
  
  // In der for-Schleife werden die Pins 2-6 als OUTPUTs festgelegt.
 for(int i=2; i<7; i++)  {
   pinMode(i, OUTPUT);
   digitalWrite(i, LOW);
 }//ende for
 
 digitalWrite(pP, HIGH);
 delay(1000);
 
 
}//ende setup

void loop() {
  
  // Diese state-Variablen werden bei Beginn jedes Durchlaufs
  // der Loop-Funktion neu beschrieben, und zwar mit dem aktuellen
  // Status ihres Output-Pins (0 oder 1)
  int sA = bitRead(PORTD,1);
  int sB = bitRead(PORTD,0);
  int sC = bitRead(PORTD,4);
  int sD = bitRead(PORTC,6);
  int sP = bitRead(PORTD,7);

//A
  if(sA == 0) { digitalWrite(pA, HIGH); } 
    else { digitalWrite(pA, LOW);  } 

//B
  if( (!sB && sA) || ( sB && !sA && !sD ) )
    { digitalWrite(pB,HIGH); }
      else { digitalWrite(pB, LOW); }    

//C
  if( (sA && sB && !sC) || (sC && !(sA && sB) ) ) 
    { digitalWrite(pC, HIGH); }
      else { digitalWrite(pC, LOW); }

//D
  if( (sA && sB && sC) || sD ) {digitalWrite(pD, HIGH); }
    else { digitalWrite(pD, LOW); }

//Digital Point (direkt)
  if( sA && sD) { 
    for(int i = 2; i < 6; i++) {
      digitalWrite(i, LOW); }
        if( sP ) {digitalWrite(pP, LOW);}
          else { digitalWrite(pP,HIGH); }
     }
      
      delay(500);
  
    
  
}// ende loop

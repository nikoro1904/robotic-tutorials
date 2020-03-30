---
layout: post
title: "Arduino Code for Tutorial #17: Ultrasonic Robot"
categories:
---

This is the Arduino Code we used in the tutorial.

<iframe width="560" height="315" src="https://www.youtube.com/embed/hcRbmlVoC-8" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

```c
/*
 * By : Robotic Tutorials
 * Date : 31/04/2020
 * 
 * Description : In this program the configuration of the ultrasound sensor as well as the servomotor will be carried out.
 * 
 *
 * In this program the HC-SR04 sensor is configured (which is an ultrasonic sensor).
 * The connection of the pins is as follows:
 * 
 * In this link you can find the sensor data sheet:  http://www.micropik.com/PDF/HCSR04.pdf
 * 
 *  ------------------------------------
 *      HC-SR04   -   Arduino Pins
 *  ------------------------------------
 *      Vcc      -        Vcc      
 *      Trig     -        8     
 *      Echo     -        9       
 *      GND      -        GND
 * -------------------------------------
 * 
 * The data read by the sensor will be sent by the LCD-Display to verify that the 
 * correct data is obtained.
 */

// Include the Servo Library
#include <Servo.h>

// Create a servo object to control a servo
Servo myServo;

// Definition of gloval variables
#define trigPin   ((uint8_t)8)
#define echoPin   ((uint8_t)9)
#define pinServo  ((uint8_t)10) // This Pins must be a PWM pin (~Pin)

// Definition of the variables for the calculation of the distance
int Pause = 5;
int i = 90;
long duration = 0;
int distanceCenter = 0;
int distanceLeft = 0;
int distanceRight = 0;

// Definition of Functions
int distanceCalculateLeft(int _trigPin, int _echoPin);
int distanceCalculateCenter(int _trigPin, int _echoPin);
int distanceCalculateRight(int _trigPin, int _echoPin);

void setup() {

  // Initialization of pins as inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // attaches the servo on pin 9 to the servo object
  myServo.attach(10);
}

void loop() {

  distanceCenter = distanceCalculateCenter(trigPin, echoPin);

  if(distanceCenter <= 15){
    // Motor STOP FUNCTION
    delay(200);
    
    // The resvomotor turns to the right
    for(int i = 90; i >= 5; i--){
      myServo.write(i);      // Here we will set the position of the servo according to the value in i
      delay(Pause);
    }
    distanceRight = distanceCalculateRight(trigPin, echoPin);
    delay(20);
    
    // The resvomotor turns to the left
    for(int i = 5; i <= 175; i++){
      myServo.write(i);      // Here we will set the position of the servo according to the value in i
      delay(Pause);
    }
    distanceLeft = distanceCalculateLeft(trigPin, echoPin);
    delay(20);

    // Servomotor returns to the initial position
    for(int i = 175; i >= 90; i--){
      myServo.write(i);
      delay(Pause);
    }
  }

}


/**************************************  Functions **********************************/ 


/*
 * @ Description : This function returns the value of the calculated distance when there is an object in front.
 * 
 */
int distanceCalculateCenter(int _trigPin, int _echoPin){

  int _distanceCenter;
  
  // Here we clear the trigPin
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 us
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Here we will measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(_echoPin, HIGH);

  // Calculate the distance. Use 343m/s as speed of sound
  //distance = (duration/2)/29.1;
  _distanceCenter = (duration*0.0343)/2;

  return _distanceCenter;
}

/*
 * @ Description : This function returns the value of the calculated distance when there is an object to the left.
 * 
 */
int distanceCalculateLeft(int _trigPin, int _echoPin){

  int _distanceLeft;
  
  // Here we clear the trigPin
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 us
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Here we will measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(_echoPin, HIGH);

  // Calculate the distance. Use 343m/s as speed of sound
  //distance = (duration/2)/29.1;
  _distanceLeft = (duration*0.0343)/2;

  return _distanceLeft;
}

/*
 * @ Description : This function returns the value of the calculated distance when there is an object to the right.
 * 
 */
int distanceCalculateRight(int _trigPin, int _echoPin){

  int _distanceRight;
  
  // Here we clear the trigPin
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 us
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Here we will measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(_echoPin, HIGH);

  // Calculate the distance. Use 343m/s as speed of sound
  //distance = (duration/2)/29.1;
  _distanceRight = (duration*0.0343)/2;

  return _distanceRight;
}
```

```c

/*
 * By : Robotic Tutorials
 * Date : 31/04/2020
 * 
 * In this program the integration of the two programs previously explained is carried out.
 * In this way you can optimize the operation of the robot, according to the results obtained.
 * 
 * 
 * L293D: http://www.ti.com/lit/ds/symlink/l293.pdf
 * In this link you can find the sensor data sheet:  http://www.micropik.com/PDF/HCSR04.pdf
 */


/* ---------------------------
 * Pin       -   Pin         -
 * ARDUINO   -   L293D       -
 * ---------------------------
 * PIN2      -    7  (2A)    -
 * PIN3      -    10 (3A)    -
 * PIN4      -    15 (4A)    -
 * PIN5      -    9  (3,4EN) -
 * PIN6      -    1  (1,2EN) -
 * PIN7      -    2  (1A)    -
 * ---------------------------
 * 
 * 
 *  *  ------------------------------------
 *      HC-SR04   -   Arduino Pins
 *  ------------------------------------
 *      Vcc      -        Vcc      
 *      Trig     -        8     
 *      Echo     -        9       
 *      GND      -        GND
 * -------------------------------------
 * 
 * 
 */


// Include the Servo Library
#include <Servo.h>

// Create a servo object to control a servo
Servo myServo;

/* Define for the Control - Motor DC */
#define MotorLeft_1A    ((uint8_t)7)
#define MotorLeft_2A    ((uint8_t)2)
#define MotorRight_3A   ((uint8_t)3)
#define MotorRight_4A   ((uint8_t)4)
#define PinSpeed_A      ((uint8_t)6)   // ~PWM Pin
#define PinSpeed_B      ((uint8_t)5)   // ~PWM Pin

// Definition of gloval variables
#define trigPin   ((uint8_t)8)
#define echoPin   ((uint8_t)9) 
#define pinServo  ((uint8_t)10) // This Pins must be a PWM pin (~Pin)

// Definition of the variables for the calculation of the distance
int Pause = 5;
int i = 90;
long duration = 0;
float distanceCenter = 0.0;
float distanceLeft = 0.0;
float distanceRight = 0.0;

// Definition of Functions
float distanceCalculateCenter(int _trigPin, int _echoPin);
float distanceCalculateLeft(int _trigPin, int _echoPin);
float distanceCalculateRight(int _trigPin, int _echoPin);
void GoForward(uint8_t u8SpeedMotor1, uint8_t u8SpeedMotor2, uint8_t u8Pin1, uint8_t u8Pin2, uint8_t u8Pin3, uint8_t u8Pin4);
void GoBack(uint8_t u8SpeedMotor1, uint8_t u8SpeedMotor2, uint8_t u8Pin1, uint8_t u8Pin2, uint8_t u8Pin3, uint8_t u8Pin4);
void TurnRight(uint8_t u8SpeedMotor1, uint8_t u8SpeedMotor2, uint8_t u8Pin1, uint8_t u8Pin2, uint8_t u8Pin3, uint8_t u8Pin4);
void TurnLeft(uint8_t u8SpeedMotor1, uint8_t u8SpeedMotor2, uint8_t u8Pin1, uint8_t u8Pin2, uint8_t u8Pin3, uint8_t u8Pin4);
void Stop(uint8_t u8SpeedMotor1, uint8_t u8SpeedMotor2, uint8_t u8Pin1, uint8_t u8Pin2, uint8_t u8Pin3, uint8_t u8Pin4);


void setup() {

  pinMode(MotorLeft_1A, OUTPUT);
  pinMode(MotorLeft_2A, OUTPUT);
  pinMode(MotorRight_3A, OUTPUT);
  pinMode(MotorRight_4A, OUTPUT);  
  pinMode(PinSpeed_A, OUTPUT);
  pinMode(PinSpeed_B, OUTPUT);

  // Initialization of pins as inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // attaches the servo on pin 9 to the servo object
  myServo.attach(pinServo);

}

void loop() {

  distanceCenter = distanceCalculateCenter(trigPin, echoPin);
  
  if(distanceCenter <= 25.0 && distanceCenter >= 10.0){
    Stop(PinSpeed_A, PinSpeed_B, MotorLeft_1A, MotorLeft_2A, MotorRight_3A, MotorRight_4A); 
    delay(200);
    
    // The resvomotor turns to the right
    for(int i = 90; i >= 5; i--){
      myServo.write(i);      // Here we will set the position of the servo according to the value in i
      delay(Pause);
    }
    distanceRight = distanceCalculateRight(trigPin, echoPin);
    delay(50);
    
    // The resvomotor turns to the left
    for(int i = 5; i <= 175; i++){
      myServo.write(i);      // Here we will set the position of the servo according to the value in i
      delay(Pause);
    }
    distanceLeft = distanceCalculateLeft(trigPin, echoPin);
    delay(50);

    // Servomotor returns to the initial position
    for(int i = 175; i >= 90; i--){
      myServo.write(i);
      delay(Pause);
    }
    /* */
    if(distanceRight < distanceLeft){
      GoBack(PinSpeed_A, PinSpeed_B, MotorLeft_1A, MotorLeft_2A, MotorRight_3A, MotorRight_4A);
      delay(400);
      TurnLeft(PinSpeed_A, PinSpeed_B, MotorLeft_1A, MotorLeft_2A, MotorRight_3A, MotorRight_4A);
      delay(700);
      Stop(PinSpeed_A, PinSpeed_B, MotorLeft_1A, MotorLeft_2A, MotorRight_3A, MotorRight_4A);
      delay(50);
      
    }
    else{
      GoBack(PinSpeed_A, PinSpeed_B, MotorLeft_1A, MotorLeft_2A, MotorRight_3A, MotorRight_4A);
      delay(400);
      TurnRight(PinSpeed_A, PinSpeed_B, MotorLeft_1A, MotorLeft_2A, MotorRight_3A, MotorRight_4A);
      delay(700);
      Stop(PinSpeed_A, PinSpeed_B, MotorLeft_1A, MotorLeft_2A, MotorRight_3A, MotorRight_4A);
      delay(50);
    }
  }
  
  else{
      GoForward(PinSpeed_A, PinSpeed_B, MotorLeft_1A, MotorLeft_2A, MotorRight_3A, MotorRight_4A); 
    }
  
}


/**************************************  Functions **********************************/ 


/*
 * @ Description : 
 * 
 */
void GoForward(uint8_t u8SpeedMotor1, uint8_t u8SpeedMotor2, uint8_t u8Pin1, uint8_t u8Pin2, uint8_t u8Pin3, uint8_t u8Pin4){

 // Motor Right
  digitalWrite(u8Pin1, HIGH);
  digitalWrite(u8Pin2, LOW);
  analogWrite(u8SpeedMotor1, 255);

 // Motor Left
  digitalWrite(u8Pin3, HIGH);
  digitalWrite(u8Pin4, LOW);
  analogWrite(u8SpeedMotor2, 255);
}

void GoBack(uint8_t u8SpeedMotor1, uint8_t u8SpeedMotor2, uint8_t u8Pin1, uint8_t u8Pin2, uint8_t u8Pin3, uint8_t u8Pin4){

  // Motor Right
  digitalWrite(u8Pin1, LOW);
  digitalWrite(u8Pin2, HIGH);
  analogWrite(u8SpeedMotor1, 255);

  // Motor Left
  digitalWrite(u8Pin3, LOW);
  digitalWrite(u8Pin4, HIGH);
  analogWrite(u8SpeedMotor2, 255);

}

void TurnRight(uint8_t u8SpeedMotor1, uint8_t u8SpeedMotor2, uint8_t u8Pin1, uint8_t u8Pin2, uint8_t u8Pin3, uint8_t u8Pin4){

  // Motor Right
  digitalWrite(u8Pin1, HIGH);
  digitalWrite(u8Pin2, LOW);
  analogWrite(u8SpeedMotor1, 120);

  // Motor Left
  digitalWrite(u8Pin3, LOW);
  digitalWrite(u8Pin4, HIGH);
  analogWrite(u8SpeedMotor2, 60);

}

void TurnLeft(uint8_t u8SpeedMotor1, uint8_t u8SpeedMotor2, uint8_t u8Pin1, uint8_t u8Pin2, uint8_t u8Pin3, uint8_t u8Pin4){

  // Motor Right
  digitalWrite(u8Pin1, LOW);
  digitalWrite(u8Pin2, HIGH);
  analogWrite(u8SpeedMotor1, 60);

  // Motor Left
  digitalWrite(u8Pin3, HIGH);
  digitalWrite(u8Pin4, LOW);
  analogWrite(u8SpeedMotor2, 120);

}

void Stop(uint8_t u8SpeedMotor1, uint8_t u8SpeedMotor2, uint8_t u8Pin1, uint8_t u8Pin2, uint8_t u8Pin3, uint8_t u8Pin4){

  // Motor Right
  digitalWrite(u8Pin1, LOW);
  digitalWrite(u8Pin2, LOW);
  analogWrite(u8SpeedMotor1, 0);

  // Motor Left
  digitalWrite(u8Pin3, LOW);
  digitalWrite(u8Pin4, LOW);
  analogWrite(u8SpeedMotor2, 0);

}



/**************************************  Functions **********************************/ 


/*
 * @ Description : This function returns the value of the calculated distance when there is an object in front.
 * 
 */
float distanceCalculateCenter(int _trigPin, int _echoPin){

  float _distanceCenter;
  
  // Here we clear the trigPin
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 us
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Here we will measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(_echoPin, HIGH);

  // Calculate the distance. Use 343m/s as speed of sound
  //distance = (duration/2)/29.1;
  _distanceCenter = (duration*0.0343)/2;

  return _distanceCenter;
}

/*
 * @ Description : This function returns the value of the calculated distance when there is an object to the left.
 * 
 */
float distanceCalculateLeft(int _trigPin, int _echoPin){

  float _distanceLeft;
  
  // Here we clear the trigPin
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 us
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Here we will measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(_echoPin, HIGH);

  // Calculate the distance. Use 343m/s as speed of sound
  //distance = (duration/2)/29.1;
  _distanceLeft = (duration*0.0343)/2;

  return _distanceLeft;
}

/*
 * @ Description : This function returns the value of the calculated distance when there is an object to the right.
 * 
 */
float distanceCalculateRight(int _trigPin, int _echoPin){

  float _distanceRight;
  
  // Here we clear the trigPin
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 us
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Here we will measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(_echoPin, HIGH);

  // Calculate the distance. Use 343m/s as speed of sound
  //distance = (duration/2)/29.1;
  _distanceRight = (duration*0.0343)/2;

  return _distanceRight;
}
```
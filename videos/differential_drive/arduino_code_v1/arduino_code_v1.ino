
#define JOYSTICK_X A0
#define JOYSTICK_Y A1

#define A 1.0   // alternative: -0.5
#define B 1.0   // alternative: 1
#define C -1.0  // alternative: 0.5
#define D 1.0   // alternative: 1

#define INPUT1 2
#define INPUT2 3
#define INPUT3 4
#define INPUT4 5

#define ENABLE1 10
#define ENABLE2 11

void setInputPins(int n_scaled, int inA, int inB) {
  if (n_scaled <= 0) {
    digitalWrite(inA, HIGH);
    digitalWrite(inB, LOW);
  }
  else {
    digitalWrite(inA, LOW);
    digitalWrite(inB, HIGH);
  }
}

int discretizePWMValue(int pwmValue, int intervals) {
  int maxPWMValue = 255;
  int threshold = maxPWMValue/intervals; // integer division!
  for(int i=0; i<intervals; i++) {
    if(pwmValue < threshold*(i+1)) {
      return i*threshold;
    }
  } 
  if(pwmValue >= intervals*threshold) {
    return maxPWMValue;
  }
}

void setup() {
  // define I/O-pin directions
  int pins[6] = {2,3,4,5,10,11};
  for(int i=0; i<6; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  // 1. read in the analog joystick values
  int x_joystick = analogRead(JOYSTICK_X);
  int y_joystick = analogRead(JOYSTICK_Y);
  
  // 2. scale them to [-1, 1]
  float x_scaled = 2.0*(static_cast<float>(x_joystick)/1023.0)-1.0;
  float y_scaled = 2.0*(static_cast<float>(y_joystick)/1023.0)-1.0;
  
  // 3. n_R = Ax + By, n_L = Cx + Dy
  float n_R = A*x_scaled + B*y_scaled;
  float n_L = C*x_scaled + D*y_scaled;
  
  // 4. scale n_R and n_L for PWM values
  // static_cast<int>(z) makes an integer out of the float z, e.g. 2.7 -> 2.0  
  // round(z) rounds a float z to the float nearest to an integer, e.g. 2.7 -> 3.0 
  int n_R_scaled = static_cast<int>(round(n_R*255));
  int n_L_scaled = static_cast<int>(round(n_L*255));
  
  // 5. get absolute value of the PWM values
  int n_R_abs = abs(n_R_scaled);
  int n_L_abs = abs(n_L_scaled);
  
  // 6. get sign of the PWM values set the input pins of the L293
  setInputPins(n_R_scaled, INPUT1, INPUT2);
  setInputPins(n_L_scaled, INPUT3, INPUT4);

  // 6a. discretization of the PWM values (gives a bit more stability):
  // n_R_abs = discretizePWMValue(n_R_abs, 5);
  // n_L_abs = discretizePWMValue(n_L_abs, 5);
  
  // 7. Write PWM values to enable pins
  analogWrite(ENABLE1, n_R_abs);
  analogWrite(ENABLE2, n_L_abs); 
}

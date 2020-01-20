#include <PID_v1.h>

int speedLeftPin = 5;
int speedRightPin = 6;

int motorLeftAPin = 10;
int motorLeftBPin = 11;
int motorRightAPin = 12;
int motorRightBPin = 13;

int photoIntLeft = 2;
int photoIntRight = 4;

float ticSpeadMeasure = 0;
float tocSpeadMeasure = 0;
float elapsedSpeadMeasure = 0;
float timeSlot = 1000.0;

int prevEncoderStatusLeft = 0;
int currentEncoderStatusLeft = 0;
float countLeft = 0.0;

int prevEncoderStatusRight = 0;
int currentEncoderStatusRight = 0;
float countRight = 0.0;

double desiredSpeedLeft = 100;
double desiredSpeedRight = 100;
double measuredSpeedLeft = 0;
double measuredSpeedRight = 0;
double outputSpeedLeft;
double outputSpeedRight;

float pi = 3.14159265359;
float theta = pi/2;
float L = 0.15;
float R = 0.0654/2;
float v = (2*pi/60)*R*desiredSpeedLeft;
float dt = ((L*theta)/(2*v))*1000;
bool doneRotating = false;
float ticRotation = 0;
float tocRotation = 0;
float elapsedRotation = 0;

//Estoy editando este
PID PIDLeft(&measuredSpeedLeft, &outputSpeedLeft, &desiredSpeedLeft, 1.5, 5, 0.75, DIRECT);
//Estoy editando este

PID PIDRight(&measuredSpeedRight, &outputSpeedRight, &desiredSpeedRight, 1.5, 5, 0.75, DIRECT);

void setup() {
  pinMode(speedLeftPin, OUTPUT); 
  pinMode(speedRightPin, OUTPUT); 
  
  pinMode(motorLeftAPin, OUTPUT); 
  pinMode(motorLeftBPin, OUTPUT); 
  pinMode(motorRightAPin, OUTPUT); 
  pinMode(motorRightBPin, OUTPUT); 
  
  pinMode(photoIntLeft, INPUT);
  pinMode(photoIntRight, INPUT);

  PIDLeft.SetMode(AUTOMATIC);
  PIDRight.SetMode(AUTOMATIC);

  setSpeedDirection("forward", 127, "left");
  setSpeedDirection("backward", 127, "right");
  
  Serial.begin(9600);
}
void loop() {

  if(elapsedSpeadMeasure == 0) {
    ticSpeadMeasure = millis();
  }

  updateEncoderStatus();
  updateMeasuredSpeedValues();
  
  ticRotation = millis();
  while(elapsedRotation < dt && !doneRotating) {
    Serial.println(String(dt));
    PIDLeft.Compute();
    analogWrite(speedLeftPin,outputSpeedLeft);
    PIDRight.Compute();
    analogWrite(speedRightPin,outputSpeedRight);
    tocRotation = millis();
    elapsedRotation = tocRotation - ticRotation;
  }
  doneRotating = true;
  elapsedRotation = 0;
  analogWrite(speedLeftPin,0);
  analogWrite(speedRightPin,0);
  
}

void setSpeedDirection(String dirStr, int speedValue, String motor) {
  setDirection(dirStr, motor);
  setSpeedValue(speedValue, motor);
}

void setDirection(String dirStr, String motor) {
  int pinA;
  int pinB;
  int pinAValue;
  int pinBValue;

  if(motor == "left") {
    pinA = motorLeftAPin;
    pinB = motorLeftBPin;
  }
  else {
    pinA = motorRightAPin;
    pinB = motorRightBPin;
  }

  if(dirStr == "backward") {
    pinAValue = HIGH;
    pinBValue = LOW;
  }
  else {
    pinAValue = LOW;
    pinBValue = HIGH;
  }
  digitalWrite(pinA, pinAValue);
  digitalWrite(pinB, pinBValue);
}

void setSpeedValue(int speedValue, String motor) {
  int pin;
  if(motor == "left") {
    pin = speedLeftPin; 
  }
  else {
    pin = speedRightPin; 
  }
  analogWrite(pin, speedValue); 
}

void updateEncoderStatus() {
    prevEncoderStatusLeft = currentEncoderStatusLeft;
    currentEncoderStatusLeft = digitalRead(photoIntLeft);
    
    prevEncoderStatusRight = currentEncoderStatusRight;
    currentEncoderStatusRight = digitalRead(photoIntRight);
    
    if(prevEncoderStatusLeft == 1 && currentEncoderStatusLeft == 0) {
      countLeft = countLeft + 1;
    }

    if(prevEncoderStatusRight == 1 && currentEncoderStatusRight == 0) {
      countRight = countRight + 1;
    }
}

void updateMeasuredSpeedValues() {   
  tocSpeadMeasure = millis();
  elapsedSpeadMeasure = tocSpeadMeasure - ticSpeadMeasure;

  if(elapsedSpeadMeasure > timeSlot) {
    measuredSpeedLeft = getMeasuredSpeed("left");
    measuredSpeedRight = getMeasuredSpeed("right");
    
    Serial.println("LEFT{Output: " + String(outputSpeedLeft) + ", Measured: " + String(measuredSpeedLeft) + "}");
    Serial.println("RIGHT{Output: " + String(outputSpeedRight) + ", Measured: " + String(measuredSpeedRight) + "}\n");
    countLeft = 0;
    countRight = 0;
    elapsedSpeadMeasure = 0;
  }
}

float getMeasuredSpeed(String motor) {
  float count;
  if(motor == "left") {
    count = countLeft;
  }
  else {
    count = countRight;
  }
  return (count/20.0)*(60000.0/timeSlot);
}

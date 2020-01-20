//MEDIR VELOCIDAD
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

int speedPWMLeft = 130;
int speedPWMRight = 130;

float desiredSpeedLeft = 400;
float desiredSpeedRight = 400;
float measuredSpeedLeft = 0;
float measuredSpeedRight = 0;

float ticPID = 0;
float tocPID = 0;
float elapsedPID = 0;

float kPLeft;
float kILeft;
float kDLeft;

float errorLeft;
float errorIntegralLeft;

float kPRight;
float kIRight;
float kDRight;

float errorRight;
float errorIntegralRight;

void setup() {
  pinMode(speedLeftPin, OUTPUT); 
  pinMode(speedRightPin, OUTPUT); 
  
  pinMode(motorLeftAPin, OUTPUT); 
  pinMode(motorLeftBPin, OUTPUT); 
  pinMode(motorRightAPin, OUTPUT); 
  pinMode(motorRightBPin, OUTPUT); 
  
  pinMode(photoIntLeft, INPUT);
  pinMode(photoIntRight, INPUT);
  
  Serial.begin(9600);
}
void loop() {

  if(elapsedSpeadMeasure == 0) {
    ticSpeadMeasure = millis();
  }

  setSpeedDirection("forward", speedPWMLeft, "left");
  setSpeedDirection("forward", speedPWMRight, "right");

  updateEncoderStatus();

  updateMeasuredSpeedValues();

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

  if(dirStr == "forward") {
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
    
    Serial.println("LEFT{PWM: " + String(speedPWMLeft) + ", RPM: " + String(measuredSpeedLeft) + "}");
    Serial.println("RIGHT{PWM: " + String(speedPWMRight) + ", RPM: " + String(measuredSpeedRight) + "}\n");
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

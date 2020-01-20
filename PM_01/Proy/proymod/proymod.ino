#include <math.h> 
#include <PID_v1.h>

int vLPin = 5;
int vRPin = 6;

int motorLeftAPin = 10;
int motorLeftBPin = 11;
int motorRightAPin = 12;
int motorRightBPin = 13;

int photoIntLeft = 2;
int photoIntRight = 4;

double ticRPM = 0;
double tocRPM = 0;
double elapsedRPM = 0;
double timeSlot = 1000.0;

int prevEncoderStatusLeft = 0;
int currentEncoderStatusLeft = 0;
double countLeft = 0.0;

int prevEncoderStatusRight = 0;
int currentEncoderStatusRight = 0;
double countRight = 0.0;

double vL = 0;
double vR = 0;
double vLMeasured = 0;
double vRMeasured = 0;
double vLPWM;
double vRPWM;

double pi = 3.14159265359;
double L = 0.15;
double r = 0.0654/2;

double tic = 0;
double toc = 0;
double elapsed = 0;

double x = 0.3;
double y = 0.3;
double theta = 0;

double xEstimated = 0;
double yEstimated = 0;
double thetaEstimated = 0;

PID PIDLeft(&vLMeasured, &vLPWM, &vL, 1.5, 5, 0.75, DIRECT);
PID PIDRight(&vRMeasured, &vRPWM, &vR, 1.5, 5, 0.75, DIRECT);

void setup() {
  pinMode(vLPin, OUTPUT); 
  pinMode(vRPin, OUTPUT); 
  
  pinMode(motorLeftAPin, OUTPUT); 
  pinMode(motorLeftBPin, OUTPUT); 
  pinMode(motorRightAPin, OUTPUT); 
  pinMode(motorRightBPin, OUTPUT); 
  
  pinMode(photoIntLeft, INPUT);
  pinMode(photoIntRight, INPUT);

  PIDLeft.SetMode(AUTOMATIC);
  PIDRight.SetMode(AUTOMATIC);

  setVelocityDirection("forward", 127, "left");
  setVelocityDirection("forward", 127, "right");
  
  Serial.begin(9600);

  //delay(3000);
  //Serial.println("ahí va");
}
void loop() {

  

  if(elapsedRPM == 0) {
    ticRPM = millis();
  }
  
  //Serial.println("yamamo");
  //Serial.println("vLPWM = " + String(vLPWM) + " y vRPWM = " + String(vRPWM));
  updateEncoderStatus();
  updateMeasuredVelocityValues();

  updateEstimatedPosition();
  
  updateRequiredVelocityValues();

  PIDLeft.Compute();
  analogWrite(vLPin,vLPWM);
  PIDRight.Compute();
  analogWrite(vRPin,vRPWM);
  if(elapsed == 0) {
    tic = millis();
  }
  
}

void setVelocityDirection(String dirStr, int speedValue, String motor) {
  setDirection(dirStr, motor);
  setVelocity(speedValue, motor);
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

void setVelocity(int speedValue, String motor) {
  int pin;
  if(motor == "left") {
    pin = vLPin; 
  }
  else {
    pin = vRPin; 
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

void updateMeasuredVelocityValues() {   
  tocRPM = millis();
  elapsedRPM = tocRPM - ticRPM;

  if(elapsedRPM > timeSlot) {
    vLMeasured = getMeasuredVelocity("left");
    vRMeasured = getMeasuredVelocity("right");
    
    //Serial.println("LEFT{Output: " + String(vLPWM) + ", Measured: " + String(vLMeasured) + "}");
    //Serial.println("RIGHT{Output: " + String(vRPWM) + ", Measured: " + String(vRMeasured) + "}\n");
    countLeft = 0;
    countRight = 0;
    elapsedRPM = 0;
  }
}

double getMeasuredVelocity(String motor) {
  double count;
  if(motor == "left") {
    count = countLeft;
  }
  else {
    count = countRight;
  }
  return (count/20.0)*(60000.0/timeSlot);
}

double rpm2mps(double vrpm) {
  return (2*pi/60)*r*vrpm;
}

void updateEstimatedPosition() {
  toc = millis();
  elapsed = (toc - tic);

  if(elapsed > 0.01*timeSlot) {
    elapsed = elapsed/1000;
    double vLmps = rpm2mps(vLMeasured);
    double vRmps = rpm2mps(vRMeasured);
    double R;
    if(vLmps == 0 && vRmps == 0) {
      R = 0;
    }
    else {
      R = (L/2)*((vLmps + vRmps)/(vRmps - vLmps));
    }
    //Serial.println("vLmps = " + String(vLmps) + " vRmps = " + String(vRmps));
    double omega = (vRmps - vLmps)/L;
    //Serial.println("omega = "+ String(omega) + ", dt = " + String(elapsed) + " -> omegadt = " + String(omega*elapsed));
    //Serial.println("x = " + String(xEstimated) + " y = " + String(yEstimated) + " theta = " + String(thetaEstimated));
    //Serial.println("el sin = " + String(sin(thetaEstimated)) + " el cos = " + String(cos(thetaEstimated)) + " y la R " + String(R));
    double ICCx = xEstimated - R*sin(thetaEstimated);
    double ICCy = yEstimated + R*cos(thetaEstimated);
  
    //Serial.println("omegadt = " + String(omega*elapsed) + " ICCx = " + String(ICCx) + " ICCy = " + String(ICCy) + "\n");
  
    xEstimated = cos(omega*elapsed)*(xEstimated - ICCx) - sin(omega*elapsed)*(yEstimated - ICCy) + ICCx;
    yEstimated = sin(omega*elapsed)*(xEstimated - ICCx) + cos(omega*elapsed)*(yEstimated - ICCy) + ICCy;
    thetaEstimated = thetaEstimated + omega*elapsed;
    if(!isnan(xEstimated)) {
      Serial.println("omega = "+ String(omega) + ", dt = " + String(elapsed) + " -> omegadt = " + String(omega*elapsed));
      Serial.println("x = " + String(xEstimated) + " y = " + String(yEstimated) + " theta = " + String(thetaEstimated) + "\n");
    }
    elapsed = 0;
  }
}

double getDistance(double x, double y, double xEstimated, double yEstimated) {
  return sqrt(pow(x - xEstimated, 2) + pow(y - yEstimated, 2));
}

void updateRequiredVelocityValues() {
  double Krho = 1.5;
  double Kalpha = 4;
  
  //Derivación propia
  double rho = getDistance(x, y, xEstimated, yEstimated);
  double alpha = (atan2 (y - yEstimated, x - xEstimated) - thetaEstimated);
  
  //Serial.println("rho = " + String(rho) + " y alpha = " + String(alpha);
  double v = Krho*rho*cos(alpha);
  double omega = Krho*sin(alpha)*cos(alpha) + Kalpha*alpha;
  vL = 1/r*(v - (L/2)*omega);
  vR = 1/r*(v + (L/2)*omega);
  //Serial.println("vL = " + String(vL) + " y vR = " + String(vR) + "\n");
  /*
  double a = 1.5;
  double b = 4;
  double v = a*getDistance(x, y, xEstimated, yEstimated);
  //double w = b*(atan2 (y - yEstimated, x - xEstimated) - thetaEstimated);
  double w = b*(theta - thetaEstimated);
  //Serial.println("r = " + String(sqrt(pow(x - xEstimated, 2) + pow(y - yEstimated, 2))) + " y theta = " + String((atan2 (y - yEstimated, x - xEstimated) - thetaEstimated)));
  //Serial.println("v = " + String(v) + " y w = " + String(w));
  vL = 1/r*(v - (L/2)*w);
  vR = 1/r*(v + (L/2)*w);
  //Serial.println("vL = " + String(vL) + " y vR = " + String(vR) + "\n");
  */
}

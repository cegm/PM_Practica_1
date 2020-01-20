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
double timeSlot = 600.0;

int prevEncoderStatusLeft = 0;
int currentEncoderStatusLeft = 0;
int countLeft = 0;
int prevCountLeft = 0;

int prevEncoderStatusRight = 0;
int currentEncoderStatusRight = 0;
int countRight = 0;
int prevCountRight = 0;

double vL = 100;
double vR = 100;
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

double x = 0.5;
double y = 0;
double theta = 0;

double xEstimated = 0;
double yEstimated = 0;
double thetaEstimated = 0;

PID PIDLeft(&vLMeasured, &vLPWM, &vL, 1.5, 5, 0.75, DIRECT);
PID PIDRight(&vRMeasured, &vRPWM, &vR, 1.5, 5, 0.75, DIRECT);

bool done = false;

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
  delay(50);
  
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
  
  if(!done) {
    updateRequiredVelocityValues();
  }
  else {
    setVelocityDirection("forward", 0, "left");
    setVelocityDirection("forward", 0, "right");
  }
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
    //Serial.println("vLMeasured = " + String(vLMeasured) + " vRMeasured = " + String(vRMeasured) + "\n");
    
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
  //return rpm2mps((count/20.0)*(60000.0/timeSlot));
  return (count/20.0)*(60000.0/timeSlot);
}

double rpm2rads(double vrpm) {
  return (2*pi/60)*vrpm;
}

double rpm2mps(double vrpm) {
  return r*rpm2rads(vrpm);
}

void updateEstimatedPosition() {
  /*
  double deltaCountLeft = countLeft - prevCountLeft;
  double deltaCountRight = countRight - prevCountRight;

  double deltaS = (r/2)*(deltaCountLeft + deltaCountRight);
  double deltaTheta = (r/L)*(deltaCountRight - deltaCountLeft);
  
  xEstimated = xEstimated + cos(thetaEstimated)*deltaS;
  yEstimated = yEstimated + sin(thetaEstimated)*deltaS;
  thetaEstimated = thetaEstimated + deltaTheta;

  prevCountLeft = countLeft;
  prevCountRight = countRight;
  Serial.println("x = " + String(xEstimated) + " y = " + String(yEstimated) + " theta = " + String(thetaEstimated) + "\n");
  */
  
  toc = millis();
  elapsed = toc - tic;

  if(elapsed > (0.1/2)*timeSlot) {

    elapsed = elapsed/1000;
    //Serial.println(String(elapsed));
  
    double omegaL = rpm2rads(vLMeasured);
    double omegaR = rpm2rads(vRMeasured);
  
    double v = (r/2)*(omegaL + omegaR);
    double omega = (r/L)*(omegaR - omegaL);
  
    double vx = v * cos(thetaEstimated);
    double vy = v * sin(thetaEstimated);
    double thetadot = omega;
  
    xEstimated = xEstimated + vx*elapsed;
    yEstimated = yEstimated + vy*elapsed; // by the way, the last term is delta_y from the equations in your comment
    thetaEstimated = thetaEstimated + thetadot*elapsed;

    elapsed = 0;
    
    Serial.println("x = " + String(xEstimated) + " y = " + String(yEstimated) + " theta = " + String(thetaEstimated) + "\n");
  }
}

double getDistance(double x, double y, double xEstimated, double yEstimated) {
  return sqrt(pow(x - xEstimated, 2) + pow(y - yEstimated, 2));
}

void updateRequiredVelocityValues() {
  double tol = 0.05;
  
  double a = 1.55;
  double b = 3.6;
  
  double rho = getDistance(x, y, xEstimated, yEstimated);
  //double alpha = abs((atan2 (y - yEstimated, x - xEstimated) - thetaEstimated));
  double alpha = (atan2 (y - yEstimated, x - xEstimated) - thetaEstimated);

  // || (alpha > 10*tol && thetaEstimated < 2*pi*tol)
  if(rho > tol) {
    
    double v = a*rho;
    double omega = b*alpha;
    
    //double v = a*rho*cos(alpha);
    //double omega = a*sin(alpha)*cos(alpha) + b*alpha;
    
    vL = 1/r*(v - (L/2)*omega);
    vR = 1/r*(v + (L/2)*omega);
  }
  else {
    vL = 0;
    vR = 0;
    setVelocityDirection("forward", 0, "left");
    setVelocityDirection("forward", 0, "right");
    delay(1000);
    Serial.println("estoy en tol \n");
    done = true;
  }
  /*
  double tol = 0.02;
  
  double a = 1.5;
  double b = 3;
  
  double rho = getDistance(x, y, xEstimated, yEstimated);
  double alpha = abs((atan2 (y - yEstimated, x - xEstimated) - thetaEstimated));
  
  if(alpha > 10*tol) {
    if(rho > tol) {
      
      double v = a*rho;
      double omega = b*alpha;
      
      //double v = a*rho*cos(alpha);
      //double omega = a*sin(alpha)*cos(alpha) + b*alpha;
      
      vL = 1/r*(v - (L/2)*omega);
      vR = 1/r*(v + (L/2)*omega);
    }
    else {
      stopp();
      Serial.println("estoy en tol \n");
    }  
  }
  */
}

void stopp() {
  vL = 0;
  vR = 0;
  setVelocityDirection("forward", 0, "left");
  setVelocityDirection("forward", 0, "right");
  delay(1000);
  done = true;
}

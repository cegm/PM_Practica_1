#include <Wire.h>
const int xInput = A0;

void setup() 
{
  Wire.begin(); // Iniciar I2C
  pinMode(xInput, INPUT);
  Serial.begin(9600);

}

void loop() 
{
  int xValue = analogRead(xInput);
  Serial.println(xValue);
  transmission(xValue);
  
  

  delay(200);
}

void transmission(byte frame) {
  Wire.beginTransmission(8);
  Wire.write(frame);
  Wire.endTransmission();
}

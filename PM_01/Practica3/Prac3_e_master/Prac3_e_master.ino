#include <Wire.h>

int button_1 = 8;
int button_2 = 9;

void setup() {
  Wire.begin(); // Iniciar I2C
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
}

void loop() {
  int var1 = digitalRead(button_1);
  int var2 = digitalRead(button_2);
  
  if(var1 == LOW && var2 == LOW) {
    transmission("00");
  }
  if(var1 == LOW && var2 == HIGH) {
    transmission("01");
  }
  if(var1 == HIGH && var2 == LOW) {
    transmission("10");
  }
  if(var1 == HIGH && var2 == HIGH) {
    transmission("11");
  }
  
  delay(50);
  
}

void transmission(String frame) {
  Wire.beginTransmission(8);
  Wire.write(frame.c_str());
  Wire.endTransmission();
}

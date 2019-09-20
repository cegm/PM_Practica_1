int LED1 = 8;
int LED2 = 9;
int LED3 = 10;
int LED4 = 11;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  delay(250);
}

void loop() {

 for (int i = 1; i < 9; i++) {
    toogleBits(LED1);
    if(i==2 | i==6){
      toogleBits(LED2);
    }
    if(i=4){
      toogleBits(LED3);
      toogleBits(LED2);
    }
    if(i=8){
      toogleBits(LED2);
      toogleBits(LED3);
      toogleBits(LED4);
    }
    delay(250);
  }
}

void toogleBits(byte PIN) {
  digitalWrite(PIN, !digitalRead(PIN));
}

int pinIn = A0;
int pinOut = 8;
int pinThreshold = A1;

void setup() {
  Serial.begin(9600);
  pinMode(pinIn, INPUT);
  pinMode(pinOut, OUTPUT);
  pinMode(pinThreshold, INPUT);
}

void loop() {
  float a_input = analogRead(pinIn);
  float voltage = a_input * (100.0 / 1023.0); //Convert the analogic read into a voltage value.

  Serial.print("Darkness: ");
  Serial.print(voltage);
  Serial.println(" %");

  float a_threshold = analogRead(pinThreshold);
  float threshold = a_threshold * (100.0 / 1023.0);
  
  Serial.print("Threshold: ");
  Serial.print(threshold);
  Serial.println(" %");
  Serial.println(" ");
  
  if(voltage > threshold) {
    digitalWrite(pinOut, HIGH);
  } 
  else {
    digitalWrite(pinOut, LOW);
  }

  delay(1000);
  
}

//PROPORCIONAL
int speedPin = 3;
int motor1APin = 6;
int motor2APin = 7;
int speed_value_motor1;

int photoInt = 14;
int prev_val = 0;
int current_val = 0;
int count = 0;

float tic = 0;
float toc = 0;
float elapsed = 0;

float rpm = 505;
float rpm_measured = 0;
float error = rpm - rpm_measured;

void setup() {
  // H-bridge enable pin for speed control // H-bridge leg 1
  // H-bridge leg 2
  // status LED
  // value for motor speed
  // set digital i/o pins as outputs: 
  pinMode(speedPin, OUTPUT); 
  pinMode(motor1APin, OUTPUT); 
  pinMode(motor2APin, OUTPUT);
  
  pinMode(photoInt, INPUT);
  
  Serial.begin(9600);
}
void loop() {

  error = rpm - rpm_measured;
  if(elapsed == 0) {
    tic = millis();
  }
  
  // put motor in forward motion
  digitalWrite(motor1APin, LOW); // set leg 1 of the H-bridge low 
  digitalWrite(motor2APin, HIGH);// set leg 2 of the H-bridge high
  
  // just invert the above values for reverse motion, // i.e. motor1APin = HIGH and motor2APin = LOW
  
  // control the speed 0- 255
  speed_value_motor1 = min((0.51)*error, 255); // P
  analogWrite(speedPin, speed_value_motor1); // output speed as

  prev_val = current_val;
  current_val = digitalRead(photoInt); // read the value from the sensor
  //Serial.println(current_val);
  if(prev_val == 1 && current_val == 0) {
    count = count + 1;
  }

  toc = millis();
  elapsed = toc - tic;
  //Serial.println(elapsed);
  if(elapsed > 50) {
    rpm_measured = (count/20.0)*1200.0;
    //Serial.print("La velocidad es: ");
    //Serial.print(rpm_measured);
    //Serial.println(" rpm");
    Serial.println("PWM: " + String(speed_value_motor1) + " RPM: " + String(rpm_measured));
    count = 0;
    elapsed = 0;
  }

}

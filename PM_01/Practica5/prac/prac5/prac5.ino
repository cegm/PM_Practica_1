const int xInput = A0;
const int yInput = A1;
const int zInput = A2;

// initialize minimum and maximum Raw Ranges for each axis
int RawMin = 266;
int RawMax = 400;

void setup() 
{
  pinMode(xInput, INPUT);
  pinMode(yInput, INPUT);
  pinMode(zInput, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  //Read raw values
  int xRaw = ReadAxis(xInput);
  int yRaw = ReadAxis(yInput);
  int zRaw = ReadAxis(zInput);

  // Scale raw values"
  long xScaled = map(xRaw, RawMin, RawMax, 180, -180);
  long yScaled = map(yRaw, RawMin, RawMax, 255, -255);
  long zScaled = map(zRaw, RawMin, RawMax, -255, 255);

  Serial.println("x: " + String(xScaled) + ", y: " + String(yScaled) + ", z: " + String(zScaled));
  delay(500);
}

int ReadAxis(int axisPin)
{
  float reading = analogRead(axisPin);
  return reading;
}

#include <ros.h>
#include <std_msgs/Int32.h>

const int xInput = A0;
const int yInput = A1;

ros::NodeHandle n;

std_msgs::Int32 lin_speed;
ros::Publisher lin_speed_pub("/lin_speed", &lin_speed);

std_msgs::Int32 ang_speed;
ros::Publisher ang_speed_pub("/ang_speed", &ang_speed);

// initialize minimum and maximum Raw Ranges for each axis
int RawMin = 266;
int RawMax = 400;

void setup() 
{
  pinMode(xInput, INPUT);
  pinMode(yInput, INPUT);

  n.initNode();
  n.advertise(lin_speed_pub);
  n.advertise(ang_speed_pub);
}

void loop() 
{
  //Read raw values
  int xRaw = ReadAxis(xInput);
  int yRaw = ReadAxis(yInput);

  // Scale raw values"
  int xScaled = map(xRaw, RawMin, RawMax, 8, -8);
  int yScaled = map(yRaw, RawMin, RawMax, 8, -8);

  lin_speed.data = xScaled;
  lin_speed_pub.publish(&lin_speed);
  ang_speed.data = yScaled;
  ang_speed_pub.publish(&ang_speed);
  n.spinOnce();
}

int ReadAxis(int axisPin)
{
  float reading = analogRead(axisPin);
  return reading;
}

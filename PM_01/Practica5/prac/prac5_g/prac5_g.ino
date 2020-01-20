#include <ros.h>
#include <std_msgs/Int32.h>

int ledPin = LED_BUILTIN;
float requestedTime;

ros::NodeHandle n;

void ledCallback(const std_msgs::Int32 &msg) {
  requestedTime = msg.data;
  digitalWrite(ledPin, HIGH);
  delay(requestedTime);
  digitalWrite(ledPin, LOW);
}

ros::Subscriber<std_msgs::Int32> led_sub("led", &ledCallback);

void setup() {
  pinMode(ledPin, OUTPUT);
  n.initNode();
  n.subscribe(led_sub);
}

void loop() {
  n.spinOnce();
}

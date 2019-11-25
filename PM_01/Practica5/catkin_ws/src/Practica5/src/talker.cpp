#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

//This callback function gets called whenever a new message arrives on the ack topic
void ackCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  
  //Publisher on the chatter topic
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  
  //Subscriber on the ack topic
  ros::Subscriber sub = n.subscribe("ack", 1000, ackCallback);

  ros::Rate loop_rate(1);
  
  int count = 0;
  while (ros::ok())
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  
  ros::spin();

  return 0;
}

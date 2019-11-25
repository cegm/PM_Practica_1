#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

//This callback function gets called whenever a new message arrives on the ack topic
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
  
  ros::NodeHandle n;

  //Publisher on the ack topic
  ros::Publisher ack_pub = n.advertise<std_msgs::String>("ack", 1000);
  
  ros::Rate loop_rate(1);
  
  while (ros::ok())
  {
    std_msgs::String ack;
    std::stringstream ss;
    ss << "ACK: [" << msg->data.c_str() << "]";
    ack.data = ss.str();
    ROS_INFO("%s", ack.data.c_str());
    ack_pub.publish(ack);
    ros::spin();
    loop_rate.sleep();
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  
  //Subscriber on the chatter topic
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  
  ros::spin();

  return 0;
}

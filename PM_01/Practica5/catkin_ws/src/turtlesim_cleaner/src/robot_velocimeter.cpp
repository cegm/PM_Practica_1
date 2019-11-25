#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <std_msgs/Int32.h>
#include "turtlesim/Pose.h"

ros::Publisher velocity_publisher;

ros::Subscriber linear_sub;
ros::Subscriber angular_sub;

turtlesim::Pose turtlesim_pose;

turtlesim::Pose goal_pose;

using namespace std;

//method to move the robot straight

void moveCallback(const std_msgs::Int32& msg);
void rotateCallback (const std_msgs::Int32& msg);


int main(int argc, char **argv)
{
  ros::init(argc, argv, "robot_velocimeter");
  ros::NodeHandle n;
  
  linear_sub = n.subscribe("/lin_speed",1000, moveCallback);
  angular_sub = n.subscribe("/ang_speed",1000, rotateCallback);
  
  velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1000);
  
  
  ros::Rate loop_rate(0.5);
  
  ros::spin();
  
  return 0;

}

void moveCallback (const std_msgs::Int32& msg){
  geometry_msgs::Twist vel_msg;

	vel_msg.linear.x = msg.data;
  vel_msg.linear.y = 0;
  vel_msg.linear.z = 0;

  vel_msg.angular.x = 0;
  vel_msg.angular.y = 0;
  vel_msg.angular.z = 0;
  
  velocity_publisher.publish(vel_msg);
}

void rotateCallback (const std_msgs::Int32& msg){
  geometry_msgs::Twist vel_msg;

	vel_msg.linear.x = 0;
  vel_msg.linear.y = 0;
  vel_msg.linear.z = 0;

  vel_msg.angular.x = 0;
  vel_msg.angular.y = 0;
  vel_msg.angular.z = msg.data;
  
  if(abs(msg.data)>2){
  velocity_publisher.publish(vel_msg);
  }
  

}



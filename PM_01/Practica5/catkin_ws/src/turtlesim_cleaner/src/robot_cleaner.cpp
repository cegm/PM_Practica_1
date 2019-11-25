#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

ros::Publisher velocity_publisher;
ros::Subscriber pose_subscriber;
turtlesim::Pose turtlesim_pose;

turtlesim::Pose goal_pose;

using namespace std;

const double x_min = 0.0;
const double y_min = 0.0;
const double x_max = 11.0;
const double y_max = 11.0;

//method to move the robot straight
void move (double speed, double distance, bool isForward);
void rotate (double angular_speed, double angle, bool clockwise);
double degrees2radians (double angle_in_degrees);
double setDesiredOrientation (double desired_angle_radians);
void poseCallback(const turtlesim::Pose::ConstPtr & pose_message);
void moveGoal(const turtlesim::Pose goal_poase, double distance_tolerance);
double getDistance(double x1, double y1, double x2, double y2);

const double PI = 3.14159265359;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "robot_cleaner");
  ros::NodeHandle n;
  
  double speed, angular_speed;
  double distance, angle;
  bool isForward, clockwise;
  
  
  velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
  pose_subscriber = n.subscribe("/turtle1/pose",10, poseCallback);
  
  speed=4;
  distance = 5;
  isForward=1;
  
  ros::Rate loop_rate(0.5);
  
  
  goal_pose.x=3;
  goal_pose.y=3;
  goal_pose.theta=0;
  moveGoal(goal_pose, 0.01);
  loop_rate.sleep();
  
  
  setDesiredOrientation(degrees2radians(0));
  loop_rate.sleep();
  move(speed, distance, isForward);
  loop_rate.sleep();
  setDesiredOrientation(degrees2radians(90));
  loop_rate.sleep();
  move(speed, distance, isForward);
  loop_rate.sleep();
  setDesiredOrientation(degrees2radians(180));
  loop_rate.sleep();
  move(speed, distance, isForward);
  loop_rate.sleep();
  setDesiredOrientation(degrees2radians(-90));
  loop_rate.sleep();
  move(speed, distance, isForward);
  loop_rate.sleep();
  setDesiredOrientation(degrees2radians(0));
  
  
  ros::spin();
  
  return 0;

}

void move (double speed, double distance, bool isForward){
  geometry_msgs::Twist vel_msg;

  if(isForward){
	vel_msg.linear.x = abs(speed);
  }
  else{
	vel_msg.linear.x = -abs(speed);
  }
  vel_msg.linear.y = 0;
  vel_msg.linear.z = 0;

  vel_msg.angular.x = 0;
  vel_msg.angular.y = 0;
  vel_msg.angular.z = 0;
  
  //t0:current time
  double t0 = ros::Time::now().toSec();
  double current_distance = 0;
  ros::Rate loop_rate(10);
  
  do{
	  velocity_publisher.publish(vel_msg);
	  double t1 = ros::Time::now().toSec();
	  current_distance = speed * (t1-t0);
	  ros::spinOnce();
	  loop_rate.sleep();
  }while(current_distance < distance);
  
  vel_msg.linear.x = 0;
  velocity_publisher.publish(vel_msg);
}
void rotate (double angular_speed, double angle, bool clockwise){
  geometry_msgs::Twist vel_msg;

	vel_msg.linear.x = 0;
  vel_msg.linear.y = 0;
  vel_msg.linear.z = 0;

  vel_msg.angular.x = 0;
  vel_msg.angular.y = 0;
  
  if(clockwise){
	vel_msg.angular.z = -abs(angular_speed);
  }
  else{
	vel_msg.angular.z = abs(angular_speed);
  }
  
  double current_angle = 0.0;
  double t0 = ros::Time::now().toSec();
  ros::Rate loop_rate(10);
  do{
	  velocity_publisher.publish(vel_msg);
	  double t1 = ros::Time::now().toSec();
	  current_angle= angular_speed * (t1-t0);
	  ros::spinOnce();
	  loop_rate.sleep();
  }while(current_angle < angle);
  
  vel_msg.angular.z = 0;
  velocity_publisher.publish(vel_msg);
  
}

double degrees2radians(double angle_in_degrees){
  return angle_in_degrees*PI /180.0;
}

double setDesiredOrientation (double desired_angle_radians){
  double relative_angle_radians = desired_angle_radians - turtlesim_pose.theta;
  bool clockwise = ((relative_angle_radians<0)?true:false);
  //cout<< desired_angle_radians <<","<<turtlesim_pose.theta<<","<<relative_angle
  rotate (abs(relative_angle_radians)/4, abs(relative_angle_radians), clockwise);
}

void poseCallback(const turtlesim::Pose::ConstPtr & pose_message){
  turtlesim_pose.x = pose_message->x;
  turtlesim_pose.y = pose_message->y;
  turtlesim_pose.theta = pose_message->theta;
}

double getDistance(double x1, double y1, double x2, double y2){
  return sqrt(pow((x1-x2),2)+pow((y1-y2),2));
}

void moveGoal(const turtlesim::Pose goal_poase, double distance_tolerance){
  geometry_msgs::Twist vel_msg;
  
  ros::Rate loop_rate(10);
  do{
      vel_msg.linear.x = 1.5*getDistance(turtlesim_pose.x, turtlesim_pose.y, goal_pose.x, goal_pose.y);
      vel_msg.linear.y = 0;
      vel_msg.linear.z = 0;
      
      vel_msg.angular.x = 0;
      vel_msg.angular.y = 0;
      vel_msg.angular.z = 4*(atan2(goal_pose.y-turtlesim_pose.y, goal_pose.x-turtlesim_pose.x)-turtlesim_pose.theta);
      
      velocity_publisher.publish(vel_msg);
      ros::spinOnce();
	    loop_rate.sleep();
  }
  while(getDistance(turtlesim_pose.x, turtlesim_pose.y, goal_pose.x, goal_pose.y)>distance_tolerance);
  cout<<"end move goal"<<endl;
  vel_msg.linear.x = 0;
  vel_msg.angular.z = 0;
  velocity_publisher.publish(vel_msg);
}







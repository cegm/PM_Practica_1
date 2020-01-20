#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Int32.h>

using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc,argv,"prac5_g");
	ros::NodeHandle n;
	ROS_INFO_STREAM("prac5_g initialized");																																							
	ROS_INFO_STREAM(ros::this_node::getName());

	ros::Publisher led_pub = n.advertise<std_msgs::Int32> ("led", 1000);

	std_msgs::Int32 msg;
	int num; 
		
	while (ros::ok())
	{
		cout << "Requested time: " << endl;
		cin >> num;

		msg.data = num;
		led_pub.publish(msg);
	}

    return 0;
}
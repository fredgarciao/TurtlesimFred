#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

// Global variables
double x_pose;
double y_pose;
double x_actual;
double y_actual;
double theta_actual;
	
// Error variable -> Pose that you want - Actual Pose
double error = 0.1;
// Callback function to get the turtle pose
void callBack(const turtlesim::Pose& msg2){
	ROS_INFO("Pose x = %f", msg2.x);
	ROS_INFO("Pose y = %f", msg2.y);
	ROS_INFO("theta = %f", msg2.theta);
	
    // Assigning pose variables
	x_actual = msg2.x;
	y_actual = msg2.y;
	theta_actual = msg2.theta;
}

int main(int argc, char**argv){
    //Asking the pose
    std::cout << "Tell x and y to the turtle go:  \n " ;

    // Getting pose from terminal
	std::cin >> x_pose;
	std::cin >> y_pose;
	
	ros::init(argc, argv, "gotogoal"); // Connecting with ROS

	ros::NodeHandle n; // Object from ROS   
	 // Publiser in turtle1/cmdvel
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    // Subscriber of turtle pose
	ros::Subscriber sub = n.subscribe("turtle1/pose", 1000, callBack);
	
	ros::Rate loop_rate(50); // loop
	// Counts
	int count = 0; 
	// pose msg (object)
	turtlesim::Pose msg2;
	
	while(ros::ok()){
		// Vel msg (object)
		geometry_msgs::Twist msg1; 
		
		//X, Y and theta command
		// error in x
		double x_error = x_pose - x_actual;
		// error in y
		double y_error = y_pose - y_actual;
		// theta error
		double theta_error = atan2 ( ( y_error ) , ( x_error ) ) - theta_actual;
		// Linear_error
		double linear_error = sqrt(pow(x_error, 2.0) + pow(y_error, 2.0));
		// Euclidian distance		   
		if( linear_error >= error ){
			double Vx= linear_error * cos(theta_error) * 0.2;
			// Linear velocity
			double w = theta_error * 0.5;
			// theta velocity
			msg1.linear.x = Vx;

			msg1.angular.z = w;
		}
		else{
			msg1.linear.x =0.;
			msg1.angular.z = 0.;
		}
	
		pub.publish(msg1);
		
		ros::spinOnce();
		
		loop_rate.sleep();
		++count;
	}
	ros::spin();
	
	return 0;

}
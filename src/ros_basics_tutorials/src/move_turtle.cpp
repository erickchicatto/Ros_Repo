#include "ros/ros.h" // Must include for all ROS C++
#include "geometry_msgs/Twist.h" // To control linear and angular velocity of turtle
#include "turtlesim/Pose.h" // To obtain coodinates and orientation of turtle
#include <sstream>

//https://github.com/kheng-yu/TurtleSim_CPP/blob/main/src/runner.cpp

//Turtle class
class Turtle
{
private:

  double x;
  double y;
  double angle;
  double linvel;
  double angvel;
  const double KP_DIST = 5;
  const double KP_ANGLE = 5;
  
  ros::NodeHandle n; // Create its specific node handler
  ros::Publisher velocityPublisher;
  ros::Subscriber poseSubscriber;  

public:
   //constructor
   Turtle()
   {
    this->velocityPublisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    this->poseSubscriber = n.subscribe("/turtle1/pose", 10, &Turtle::updatePose, this);
   }
  
  //turtle class functions 
  double getX(){
      return x;
  }

  double getY(){
      return y;
  }

  double getAngle(){
      return angle;
  }

  double getLinVel(){
      return linvel;
  }

  double getAngVel(){
      return angvel;
  }







// Update turtle object's pose when receive /turtlesim/Pose/ msgs
    // topic: turtle1/pose
    // msg type: turtlesim/Pose
    // args: [double] x y theta linear_velocity angular_velocity
    void updatePose(const turtlesim::Pose::ConstPtr& msg)
    {
        this->x = msg->x;
        this->y = msg->y;
        this->angle = msg->theta; // in rads
        this->linvel = msg->linear_velocity; // in m/s
        this->angvel = msg->angular_velocity; // in rads

        // std::cout << "Updating pose, "<< "\n" << "x: " << msg->x << "\n";
        // std::cout << "y: " << msg->y << "\n";
        // std::cout << "Current angle: " << this->angle << "\n";
        // // std::cout << "linvel: " << msg->linear_velocity << "\n";
        // // std::cout << "angvel: " << msg->angular_velocity << "\n";
    }


};



int main(int argc, char **argv)
{
   return 0;    
}
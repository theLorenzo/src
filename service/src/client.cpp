#include "ros/ros.h"
#include "service/ResetZero.h"
#include "service/GivenPose.h"

char input;

std::string coordinate;
int main(int argc, char **argv)
{

  ros::init(argc, argv, "client");
  ros::NodeHandle n;

  ros::ServiceClient client = n.serviceClient<service::ResetZero>("reset_zero");
  ros::ServiceClient client1 = n.serviceClient<service::GivenPose>("given_pose");
  service::ResetZero srv1;
  service::GivenPose srv2;
  std::cout << "Ready to change the odometry, press enter to reset to origin or x,y,theta to set coordinates..";
  std::cin >> input;
  if(input == '\n'){
      srv1.request.x = 0;
      srv1.request.y = 0;
      srv1.request.theta = 0;
      ROS_INFO("CAMBIATO ALL'ORIGINE");
  }
  else{
      std::cout << "Ready to take the desider coordinates: ";
      srv2.request.x = coordinate[0];
      srv2.request.y = coordinate[2];
      srv2.request.theta = coordinate[4];
      ROS_INFO("CAMBIATO ALLA POSIZIONE DESIDERATA");

  }

  ros::spinOnce();

}

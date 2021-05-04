#include "ros/ros.h"
#include "service/ResetZero.h"
#include "service/GivenPose.h"

char input;

std::string coordinate;
float coordinata_x;
float coordinata_y;
float coordinata_theta;

int main(int argc, char **argv)
{

  ros::init(argc, argv, "client");
  ros::NodeHandle n;

  ros::ServiceClient client = n.serviceClient<service::ResetZero>("reset_zero");
  ros::ServiceClient client1 = n.serviceClient<service::GivenPose>("given_pose");
  service::ResetZero srv1;
  service::GivenPose srv2;
  std::cout << "Ready to change the odometry, write '1' to reset to origin or '2' to set coordinates..";
  std::cin >> input;
  if(input == '1'){
      if (client.call(srv1)) {
          srv1.request.x = 0;
          srv1.request.y = 0;
          srv1.request.theta = 0;
          ROS_INFO("CAMBIATO ALL'ORIGINE");
      }
  }
  else if (input == '2'){
      //std::cout << "Ready to take the desider coordinates: ";
      if (client.call(srv2)) {
          std::cout << "x coordinate: ";
          std::cin >> coordinata_x;
          std::cout << "y coordinate: ";
          std::cin >> coordinata_y;
          std::cout << "theta coordinate: ";
          std::cin >> coordinata_theta;

          srv2.request.x = coordinata_x;
          srv2.request.y = coordinata_y;
          srv2.request.theta = coordinata_theta;
          ROS_INFO("CAMBIATO ALLA POSIZIONE DESIDERATA");
      }

  }

  ros::spinOnce();

}

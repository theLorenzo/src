#include "ros/ros.h"
#include "service/ResetZero.h"

bool ResetZero(service::ResetZero::Request  &req,
         service::ResetZero::Response &res)
{
  res.set_a = req.a;
  res.set_a = 0;
  res.set_b = req.b;
  res.set_b = 0;
  res.set_c = req.c;
  res.set_c = 0;
  ROS_INFO("request: x=%f, y=%f, theta=%f", (float)req.a, (float)req.b, (float)req.c);
  ROS_INFO("sending back response: [%f], [%f], [%f]", (float)res.set_a, (float)res.set_b, (float)res.set_c);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "reset_zero_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("reset_zero", ResetZero);
  ROS_INFO("Ready to reset the odometry.");
  ros::spin();

  return 0;
}

#include "ros/ros.h"
#include "service/ResetZero.h"
#include "nav_msgs/Odometry.h"

class reset_zero
{

    
private:
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<service::ResetZero>("reset_zero");
    service::ResetZero srv;
    ros::Subscriber sub;
    nav_msgs::Odometry msg;
    ros::Publisher pub;

public:
     reset_zero(){
     sub = n.subscribe("/integrazione_odom", 200, &reset_zero::callback, this);
     pub = n.advertise<nav_msgs::Odometry>("integrazione_odom", 10);
     }


void callback(const nav_msgs::Odometry::ConstPtr &msg){

        srv.request.a = msg->pose.pose.position.x;
        srv.request.b = msg->pose.pose.position.y;
        srv.request.c = msg->pose.pose.position.z;
        if (client.call(srv))
        {
           ROS_INFO("reset x: %f", (float)srv.response.set_a);
           ROS_INFO("reset y: %f", (float)srv.response.set_b);
           ROS_INFO("reset theta: %f", (float)srv.response.set_c);
           pub.publish(msg);
        }
        else
        {
        ROS_ERROR("Failed to call service reset_zero");
        //return 1;
        }

  //return 0;

}


};

int main(int argc, char **argv)
{
 ros::init(argc, argv, "reset_zero");
 reset_zero my_reset_zero;
 ros::spin();
 return 0;
}




/*ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<service::ResetZero>("reset_zero");
  service::ResetZero srv;
  ros::Subscriber sub;

void odomCallback(const nav_msgs::Odometry::ConstPtr &msg){
   srv.request.a = msg->pose.pose.position.x;
   srv.request.b = msg->pose.pose.position.y;
   srv.request.c = msg->pose.pose.position.z;
}





int main(int argc, char **argv)
{
  /*ros::init(argc, argv, "add_two_ints_client");
  if (argc != 3)
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<service::ResetZero>("reset_zero");
  service::ResetZero srv;
  ros::Subscriber sub;
  sub = n.subscriber("/integrazione_odom", 200, &odomCallback);
  
  if (client.call(srv))
  {
    ROS_INFO("reset x: %f", (float)srv.response.set_a);
    ROS_INFO("reset y: %f", (float)srv.response.set_b);
    ROS_INFO("reset theta: %f", (float)srv.response.set_c);
  }
  else
  {
    ROS_ERROR("Failed to call service reset_zero");
    return 1;
  }

  return 0;
}*/

#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Header.h"
#include "nav_msgs/Odometry.h"
#include<geometry_msgs/TwistStamped.h>
#include <boost/bind.hpp>
#define _USE_MATH_DEFINES
#include<math.h>
#include <tf2/LinearMath/Quaternion.h>


class rviz_publisher
{

    nav_msgs::Odometry messaggio;
private:
    ros::NodeHandle n;
    tf::TransformBroadcaster br;
    tf::Transform transform;
    //tf::TransformBroadcaster br2;
    //tf::Transform transform2;
    ros::Subscriber sub;
    //ros::Subscriber sub2;

public:
     rviz_publisher(){

  	sub = n.subscribe("/integrazione_odom", 200, &rviz_publisher::callback, this);
  	//sub2 = n.subscribe("/scot_odom", 200, &rviz_publisher::callback2, this);


         while (ros::ok()){
             ros::spin();
         }

}


void callback(const nav_msgs::Odometry::ConstPtr &msg){

        transform.setOrigin( tf::Vector3(msg->pose.pose.position.x, msg->pose.pose.position.y, 0) );
        tf::Quaternion q;
        q[0] = msg->pose.pose.orientation.x;
        q[1] = msg->pose.pose.orientation.y;
        q[2] = msg->pose.pose.orientation.z;
        q[3] = msg->pose.pose.orientation.w;
        transform.setRotation(q);
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "integrazione_odom"));

}


};

int main(int argc, char **argv)
{
 ros::init(argc, argv, "rviz_publisher");
 rviz_publisher my_rviz_publisher;
 ros::spin();
 return 0;
}


#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Header.h"
#include "nav_msgs/Odometry.h"
#include <geometry_msgs/TwistStamped.h>
#include <boost/bind.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <tf2/LinearMath/Quaternion.h>


class rviz_publisher
{

    nav_msgs::Odometry messaggio;
private:
    ros::NodeHandle n;
    tf::TransformBroadcaster br;
    tf::Transform transform;
    tf::Transform transform2;
    tf::Transform transform3;
    ros::Subscriber sub;
    
public:
     rviz_publisher(){

  	sub = n.subscribe("/integrazione_odom", 200, &rviz_publisher::callback, this);
  	
         while (ros::ok()){
             ros::spin();
         }

}


void callback(const nav_msgs::Odometry::ConstPtr &msg){

        // definition of the tf between world and map
        transform2.setOrigin(tf::Vector3(0,0,0));
        tf::Quaternion q2;
        q2[0] = 0;
        q2[1] = 0;
        q2[2] = 0;
        q2[3] = 1;
        transform2.setRotation(q2);
        br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "world", "map"));

        // definition of the tf between map and integrazione_odom
        transform3.setOrigin(tf::Vector3(0,0,0));
        tf::Quaternion q3;
        q3[0] = 0;
        q3[1] = 0;
        q3[2] = 0;
        q3[3] = 1;
        transform3.setRotation(q3);
        br.sendTransform(tf::StampedTransform(transform3, ros::Time::now(), "map", "integrazione_odom"));


         // definition of the tf between integrazione_odom and base_link_integrazione
        transform.setOrigin( tf::Vector3(msg->pose.pose.position.x, msg->pose.pose.position.y, 0) );
        tf::Quaternion q;
        q[0] = msg->pose.pose.orientation.x;
        q[1] = msg->pose.pose.orientation.y;
        q[2] = msg->pose.pose.orientation.z;
        q[3] = msg->pose.pose.orientation.w;
        transform.setRotation(q);
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "integrazione_odom", "base_link_integrazione"));



}


};

int main(int argc, char **argv)
{
 ros::init(argc, argv, "rviz_publisher");
 rviz_publisher my_rviz_publisher;
 ros::spin();
 return 0;
}


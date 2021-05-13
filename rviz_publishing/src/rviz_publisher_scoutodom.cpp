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


class rviz_publisher_scoutodom
{

    nav_msgs::Odometry messaggio;
private:
    ros::NodeHandle n;
    tf::TransformBroadcaster br;
    tf::Transform transform;
    tf::Transform transform2;
    ros::Subscriber sub;
    ros::Publisher pub;

public:
    rviz_publisher_scoutodom(){

  	    sub = n.subscribe("/scout_odom", 200, &rviz_publisher_scoutodom::callback, this);
  	    pub = n.advertise<nav_msgs::Odometry>("/scout_odom_tf", 200);
        
        while (ros::ok()){
        ros::spin();
        }

    }


    void callback(const nav_msgs::Odometry::ConstPtr &msg){

        messaggio.header.stamp = ros::Time::now();
        messaggio.header.frame_id = "world";
        messaggio.child_frame_id = "odom";
        messaggio.pose.pose.position.x = msg->pose.pose.position.x;
        messaggio.pose.pose.position.y = msg->pose.pose.position.y;
        messaggio.pose.pose.position.z= msg->pose.pose.position.z;
        messaggio.pose.pose.orientation.x = msg->pose.pose.orientation.x;
        messaggio.pose.pose.orientation.y = msg->pose.pose.orientation.y;
        messaggio.pose.pose.orientation.z = msg->pose.pose.orientation.z;
        messaggio.pose.pose.orientation.w = msg->pose.pose.orientation.w;

        messaggio.twist.twist.linear.x = msg->twist.twist.linear.x;
        messaggio.twist.twist.linear.y = msg->twist.twist.linear.y;
        messaggio.twist.twist.linear.z = msg->twist.twist.linear.z;

        messaggio.twist.twist.angular.x = msg->twist.twist.angular.x;
        messaggio.twist.twist.angular.y = msg->twist.twist.angular.y;
        messaggio.twist.twist.angular.z = msg->twist.twist.angular.z;



        // definition of the tf between map and scout_odom
        transform2.setOrigin(tf::Vector3(0,0,0));
        tf::Quaternion q2;
        q2[0] = 0;
        q2[1] = 0;
        q2[2] = 0;
        q2[3] = 1;
        transform2.setRotation(q2);
        br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "map", "scout_odom"));


        transform.setOrigin( tf::Vector3(msg->pose.pose.position.x, msg->pose.pose.position.y, 0) );
        tf::Quaternion q;
        q[0] = msg->pose.pose.orientation.x;
        q[1] = msg->pose.pose.orientation.y;
        q[2] = msg->pose.pose.orientation.z;
        q[3] = msg->pose.pose.orientation.w;
        transform.setRotation(q);
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "scout_odom", "base_link_scoutodom"));


        pub.publish(messaggio);

    }


};

int main(int argc, char **argv)
{
 ros::init(argc, argv, "rviz_publisher_scoutodom");
 rviz_publisher_scoutodom my_rviz_publisher;
 ros::spin();
 return 0;
}


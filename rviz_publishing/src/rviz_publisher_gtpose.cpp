#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Header.h"
#include "nav_msgs/Odometry.h"
#include<geometry_msgs/TwistStamped.h>
#include<geometry_msgs/PoseStamped.h>
#include <boost/bind.hpp>
#define _USE_MATH_DEFINES
#include<math.h>
#include <tf2/LinearMath/Quaternion.h>


class rviz_publisher_gtpose
{

    geometry_msgs::PoseStamped messaggio;
private:
    ros::NodeHandle n;
    tf::TransformBroadcaster br;
    tf::Transform transform;
    ros::Subscriber sub;
    ros::Publisher pub;

public:
     rviz_publisher_gtpose(){

  	sub = n.subscribe("/gt_pose", 200, &rviz_publisher_gtpose::callback, this);
  	pub = n.advertise<geometry_msgs::PoseStamped>("/gt_pose_tf", 200);
  	         while (ros::ok()){
             ros::spin();
         }

}


void callback(const geometry_msgs::PoseStamped::ConstPtr &msg){


    messaggio.header.stamp = ros::Time::now();
    messaggio.header.frame_id = "map";
    //messaggio.header.child_frame_id = "gtpose";

    messaggio.pose.position.x = msg->pose.position.x;
    messaggio.pose.position.y = msg->pose.position.y;
    messaggio.pose.position.z= 0;
    messaggio.pose.orientation.x = msg->pose.orientation.x;
    messaggio.pose.orientation.y = msg->pose.orientation.y;
    messaggio.pose.orientation.z = msg->pose.orientation.z;
    messaggio.pose.orientation.w = msg->pose.orientation.w;

    /*messaggio.twist.twist.linear.x = msg->twist.twist.linear.x;
    messaggio.twist.twist.linear.y = msg->twist.twist.linear.y;
    messaggio.twist.twist.linear.z = msg->twist.twist.linear.z;

    messaggio.twist.twist.angular.x = msg->twist.twist.angular.x;
    messaggio.twist.twist.angular.y = msg->twist.twist.angular.y;
    messaggio.twist.twist.angular.z = msg->twist.twist.angular.z;*/


    transform.setOrigin( tf::Vector3(msg->pose.position.x, msg->pose.position.y, 0) );
        tf::Quaternion q;
        q[0] = msg->pose.orientation.x;
        q[1] = msg->pose.orientation.y;
        q[2] = msg->pose.orientation.z;
        q[3] = msg->pose.orientation.w;
        transform.setRotation(q);
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "gtpose"));

        pub.publish(messaggio);

}


};

int main(int argc, char **argv)
{
 ros::init(argc, argv, "rviz_publisher_gtpose");
 rviz_publisher_gtpose my_rviz_publisher;
 ros::spin();
 return 0;
}


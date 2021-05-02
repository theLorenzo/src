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
#include <tf/LinearMath/Quaternion.h>


class rviz_publisher_gtpose
{

    geometry_msgs::PoseStamped messaggio;
    float initial_x = 0.832142114639;
    float initial_y = 0.426361680031;
    double roll;
    double pitch;
    double yaw;
    double roll_init;
    double pitch_init;
    double yaw_init;
    tf::Quaternion new_quaternion;
    int flag = 0;

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

    tf::Quaternion q_rpy(
            msg->pose.orientation.x,
            msg->pose.orientation.y,
            msg->pose.orientation.z,
            msg->pose.orientation.w);
    tf::Matrix3x3 m(q_rpy);
    m.getRPY(roll, pitch, yaw);
    if (flag == 0){
        roll_init = roll;
        pitch_init = pitch;
        yaw_init = yaw;
    }
    new_quaternion.setRPY(roll-roll_init, pitch-pitch_init, yaw-yaw_init);
    flag = 1;

    messaggio.pose.position.x = msg->pose.position.x+initial_x;
    messaggio.pose.position.y = msg->pose.position.y-initial_y;
    messaggio.pose.position.z= 0;
    messaggio.pose.orientation.x = new_quaternion[0];
    messaggio.pose.orientation.y = new_quaternion[1];
    messaggio.pose.orientation.z = new_quaternion[2];
    messaggio.pose.orientation.w = new_quaternion[3];



    /*messaggio.twist.twist.linear.x = msg->twist.twist.linear.x;
    messaggio.twist.twist.linear.y = msg->twist.twist.linear.y;
    messaggio.twist.twist.linear.z = msg->twist.twist.linear.z;

    messaggio.twist.twist.angular.x = msg->twist.twist.angular.x;
    messaggio.twist.twist.angular.y = msg->twist.twist.angular.y;
    messaggio.twist.twist.angular.z = msg->twist.twist.angular.z;*/


    transform.setOrigin( tf::Vector3(msg->pose.position.x+initial_x, msg->pose.position.y-initial_y, 0) );
        tf::Quaternion q;

        q[0] = new_quaternion[0];
        q[1] = new_quaternion[1];
        q[2] = new_quaternion[2];
        q[3] = new_quaternion[3];
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


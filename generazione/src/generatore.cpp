#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Header.h"
#include "nav_msgs/Odometry.h"
#include<robotics_hw1/WheelSpeeds.h>
#include<robotics_hw1/BaselineMsg.h>
#include<geometry_msgs/TwistStamped.h>

class generatore_twist {
    float vl;
    float vr;
    float baseline = 1.012144;

    geometry_msgs::TwistStamped messaggio_twist;

private:
    ros::NodeHandle n;
    ros::Subscriber sub1;
    ros::Subscriber sub2;
    ros::Subscriber sub3;
    ros::Publisher pub;

public:
    generatore_twist(){

        sub1 = n.subscribe("/scout_odom", 200, &generatore_twist::callback, this);
        sub2 = n.subscribe("/vettore_motori", 200, &generatore_twist::callback2, this);
        sub3 = n.subscribe("/baseline_topic", 200, &generatore_twist::callback3, this);
        pub = n.advertise<geometry_msgs::TwistStamped>("twist_stamped", 10);

        while (ros::ok()){
            ros::spin();
        }
    }
    void callback(const nav_msgs::Odometry::ConstPtr& msg){
        //ROS_INFO("SONO ENTRATO NELLA CALLBACK 1");
        messaggio_twist.header.stamp = msg->header.stamp;
    }
    void callback2(const robotics_hw1::WheelSpeeds::ConstPtr& msg_wheel){
        //ROS_INFO("SONO ENTRATO NELLA CALLBACK 2");
        vl = (msg_wheel->speed1 * 0.10472 * 0.1575 * 0.026 + msg_wheel->speed3 * 0.10472 * 0.1575 * 0.026) / 2;
        vr = (msg_wheel->speed2 * 0.10472 * 0.1575 * 0.026 + msg_wheel->speed4 * 0.10472 * 0.1575 * 0.026) / 2;
        messaggio_twist.twist.linear.x = (vr-vl)/2;
        messaggio_twist.twist.linear.y = 0;
        messaggio_twist.twist.linear.z = 0;
        messaggio_twist.twist.angular.x = 0;
        messaggio_twist.twist.angular.y = 0;
        messaggio_twist.twist.angular.z = (vr+vl)/(baseline);
        pub.publish(messaggio_twist);
        //ROS_INFO("HO PUBBLICATO");

    }
    void callback3(const robotics_hw1::BaselineMsg::ConstPtr& msg1){
        //ROS_INFO("SONO ENTRATO NELLA CALLBACK 3");
    }
};
int main(int argc, char **argv){

    ros::init(argc, argv, "generatore_twist");
    generatore_twist my_generatore_twist;
    return 0;
}
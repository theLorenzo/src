#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Header.h"
#include "nav_msgs/Odometry.h"
#include<robotics_hw1/WheelSpeeds.h>
#include<geometry_msgs/TwistStamped.h>


class generatore_twist {
    float vl;
    float vr;
    float baseline = 1.030663; //appareant baseline computed in gen_baseline node
    float gear_ratio = 1/38.218040;

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
        pub = n.advertise<geometry_msgs::TwistStamped>("twist_stamped", 10);

        while (ros::ok()){
            ros::spin();
        }
    }

    void callback(const nav_msgs::Odometry::ConstPtr& msg){
        messaggio_twist.header.stamp = msg->header.stamp;
    }

    void callback2(const robotics_hw1::WheelSpeeds::ConstPtr& msg_wheel){
        vl = (msg_wheel->speed1 * 0.10472 * 0.1575 * gear_ratio + msg_wheel->speed3 * 0.10472 * 0.1575 * gear_ratio) / 2;
        vr = (msg_wheel->speed2 * 0.10472 * 0.1575 * gear_ratio + msg_wheel->speed4 * 0.10472 * 0.1575 * gear_ratio) / 2;
        messaggio_twist.twist.linear.x = (vr-vl)/2;
        messaggio_twist.twist.linear.y = 0;
        messaggio_twist.twist.linear.z = 0;
        messaggio_twist.twist.angular.x = 0;
        messaggio_twist.twist.angular.y = 0;
        messaggio_twist.twist.angular.z = (vr+vl)/(baseline);
        pub.publish(messaggio_twist);
    }

};

int main(int argc, char **argv){

    ros::init(argc, argv, "generatore_twist");
    generatore_twist my_generatore_twist;
    return 0;
}
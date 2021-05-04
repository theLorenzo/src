#include "ros/ros.h"
#include "robotics_hw1/MotorSpeed.h"
#include "robotics_hw1/WheelSpeeds.h"
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <std_msgs/Float64.h>
#include "std_msgs/Header.h"
#include <boost/bind.hpp>

class pub_sub
{

    robotics_hw1::WheelSpeeds message;


private:
    ros::NodeHandle n;
    message_filters::Subscriber<robotics_hw1::MotorSpeed> sub1;
    message_filters::Subscriber<robotics_hw1::MotorSpeed> sub2;
    message_filters::Subscriber<robotics_hw1::MotorSpeed> sub3;
    message_filters::Subscriber<robotics_hw1::MotorSpeed> sub4;
    ros::Publisher pub;
    typedef message_filters::sync_policies::ExactTime<robotics_hw1::MotorSpeed, robotics_hw1::MotorSpeed, robotics_hw1::MotorSpeed, robotics_hw1::MotorSpeed> MySyncPolicy;


public:
    pub_sub(){
        while (ros::ok()){

        sub1.subscribe(n, "/motor_speed_fl", 20);
        sub2.subscribe(n, "/motor_speed_fr", 20);
        sub3.subscribe(n, "/motor_speed_rl", 20);
        sub4.subscribe(n, "/motor_speed_rr", 20);
        pub = n.advertise<robotics_hw1::WheelSpeeds>("vettore_motori", 10);



        message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(100), sub1, sub2, sub3, sub4);
        sync.registerCallback(boost::bind(&pub_sub::callback, this, _1, _2, _3, _4));

        ros::spin();

    }
    }


void callback(const robotics_hw1::MotorSpeed::ConstPtr &msg1,
              const robotics_hw1::MotorSpeed::ConstPtr &msg2,
              const robotics_hw1::MotorSpeed::ConstPtr &msg3,
              const robotics_hw1::MotorSpeed::ConstPtr &msg4) {


    // ROS_INFO ("Quattro speeds: fl: %f, fr: %f, rl: %f, rr: %f",
    //          msg1->rpm, msg2->rpm, msg3->rpm, msg4->rpm);

    ROS_INFO("----------------------");
    message.header.stamp = msg1->header.stamp;
    message.speed1 = msg1->rpm;
    message.speed2 = msg2->rpm;
    message.speed3 = msg3->rpm;
    message.speed4 = msg4->rpm;
    pub.publish(message);
}

};


int main(int argc, char **argv){

    ros::init(argc, argv, "sincronizzatore");

    pub_sub my_pub_sub;
    ros::spin();
    return 0;
}

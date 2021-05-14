#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Header.h"
#include "nav_msgs/Odometry.h"
#include <robotics_hw1/WheelSpeeds.h>
#include <robotics_hw1/BaselineMsg.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <boost/bind.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf/transform_broadcaster.h>
#include "tf/transform_datatypes.h"
#include "tf/LinearMath/Matrix3x3.h"



class generatore_baseline
{

    float baseline=0;
    int flag_vettore_baseline = 0;
    int counter_b = 0;
    float baseline_temp = 0;
    int flag_time = 0;
    int flag_wait = 0;

    double old_time;
    double current_time;
    float theta_old;
    float theta_now;
    float media_now;
    float num = 0;


private:
    ros::NodeHandle n;
    message_filters::Subscriber<geometry_msgs::PoseStamped> sub1;
    message_filters::Subscriber<robotics_hw1::WheelSpeeds> sub2;
    ros::Publisher pub;

    typedef message_filters::sync_policies::ApproximateTime<geometry_msgs::PoseStamped, robotics_hw1::WheelSpeeds> MySyncPolicy;

public:
    generatore_baseline(){
        sub1.subscribe(n, "/gt_pose", 20);
        sub2.subscribe(n, "/vettore_motori", 20);
        pub = n.advertise<robotics_hw1::BaselineMsg>("baseline_topic", 1000);

        while (ros::ok()){
            ROS_INFO("SONO ENTRATO NEL WHILE");
            message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(100), sub1, sub2);
            sync.registerCallback(boost::bind(&generatore_baseline::callback1, this, _1, _2));
           ros::spin();
        }
    }
    void callback1(const geometry_msgs::PoseStamped::ConstPtr& msg_odom,
                  const robotics_hw1::WheelSpeeds::ConstPtr& msg_wheel) {
        

        if (flag_time == 0) {

                old_time = msg_odom->header.stamp.toSec();    
                float qx = msg_odom->pose.orientation.x;
                float qy = msg_odom->pose.orientation.y;
                float qz = msg_odom->pose.orientation.z;
                float qw = msg_odom->pose.orientation.w;

                double roll, pitch, yaw;
                tf::Quaternion q;
                q[0] = qx;
                q[1] = qy;
                q[2] = qz;
                q[3] = qw;

                tf::Matrix3x3(q).getRPY(roll, pitch, yaw);

                theta_old = yaw;
                flag_time = 1;
            } 
            else  if (flag_wait == 3){
                flag_wait = 0;
                current_time = msg_odom->header.stamp.toSec();
                float qx = msg_odom->pose.orientation.x;
                float qy = msg_odom->pose.orientation.y;
                float qz = msg_odom->pose.orientation.z;
                float qw = msg_odom->pose.orientation.w;


                double roll, pitch, yaw;
                tf::Quaternion q;
                q[0] = qx;
                q[1] = qy;
                q[2] = qz;
                q[3] = qw;

                tf::Matrix3x3(q).getRPY(roll, pitch, yaw);  // calcola yaw dal quaternione di gt_pose

                
                theta_now = yaw;


                float vl_1 = (msg_wheel->speed1 * 0.10472 * 0.1575 * 0.026 + msg_wheel->speed3 * 0.10472 * 0.1575 * 0.026) /2;
                float vr_1 = (msg_wheel->speed2 * 0.10472 * 0.1575 * 0.026 + msg_wheel->speed4 * 0.10472 * 0.1575 * 0.026) /2;
                float omega_z = (theta_now - theta_old) / (current_time - old_time);     //computes omega_z 
                float baseline = (vr_1+vl_1)/omega_z;
               


                if (((omega_z > 0.1 && omega_z < 0.8) || (omega_z > -0.8 && omega_z < -0.1)) && theta_now != theta_old) {
                    counter_b++;
                    num = num + ((vr_1 + vl_1) / omega_z);
                    media_now = num / counter_b;
                    ROS_INFO("media baseline: %f", media_now);     //printa la media ad ogni ciclo
                }
            }
            else flag_wait++;
            old_time = current_time;
            theta_old = theta_now;

        }



    float media(float vettore[]) // computes the mean of a vector of 1000 terms
    {
        float somma;
        for (int i = 0; i < 1001; ++i) {
            somma = somma + vettore[i];
        }
        float media_fatta = somma/1000;
        return media_fatta;
    }
};

int main(int argc, char **argv){
    ros::init(argc, argv, "generatore_baseline_gtpose");
    generatore_baseline my_generatore_baseline;
    return 0;
}



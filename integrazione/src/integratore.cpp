#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Header.h"
#include "nav_msgs/Odometry.h"
#include<robotics_hw1/WheelSpeeds.h>
#include<robotics_hw1/BaselineMsg.h>
#include<robotics_hw1/FinalMsg.h>
#include<geometry_msgs/TwistStamped.h>
#include <boost/bind.hpp>
#include <sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include <tf/LinearMath/Quaternion.h>
#include <dynamic_reconfigure/server.h>
#include <integrazione/metodiConfig.h>
#include <service/GivenPose.h>
#include <service/ResetZero.h>


class integratore
{

float x;
float y;
float theta;
float x_old = 0;
float y_old = 0;
float theta_old = 0;
float x_rk;
float y_rk;
float theta_rk;
float x_old_rk = 0;
float y_old_rk = 0;
float theta_old_rk = 0;

double current_time;
double old_time;
float integration_time = 0;

float vk;
float omegak;

float vx;
float omega_z;

int flag = 0;      //flag value used for the dynamic reconfigure request
int flag_time = 0;


private:
    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Subscriber sub2;
    ros::Publisher pub;
    ros::Publisher pub2;
    ros::Publisher pub3;
    nav_msgs::Odometry message;
    nav_msgs::Odometry message_rk;

    robotics_hw1::FinalMsg messaggio_finale;

    dynamic_reconfigure::Server<integrazione::metodiConfig> server;
    dynamic_reconfigure::Server<integrazione::metodiConfig>::CallbackType f;
    ros::ServiceServer service1;
    ros::ServiceServer service2;

public:
    integratore(){
        f = boost::bind(&integratore::callback_dyn, this, _1, _2);
        server.setCallback(f);
        sub = n.subscribe<geometry_msgs::TwistStamped>("/twist_stamped", 200, &integratore::callback, this);
        pub = n.advertise<nav_msgs::Odometry>("integrazione_odom", 10);
        pub3 = n.advertise<robotics_hw1::FinalMsg>("odom_and_method",10);
        service1 = n.advertiseService("reset_zero", &integratore::reset_zero_f,this);
        service2 = n.advertiseService("given_pose", &integratore::given_pose_f,this);


        n.getParam("starting_x", x_old);
        n.getParam("starting_y", y_old);
        n.getParam("starting_omega", theta_old);

        while (ros::ok()){
           ros::spinOnce();
        }
    }
    void callback(const geometry_msgs::TwistStamped::ConstPtr &msg_twist){

     if (flag_time == 0){

      old_time = msg_twist->header.stamp.toSec();       //at the first cycle, it takes as old_time the value of the bag.
      flag_time = 1;
     }
    
     current_time = msg_twist->header.stamp.toSec();  // la funzione toSec(); ?? top perch?? prende lo stamp
     vk = msg_twist->twist.linear.x;                  // e lo rende salvabile in una variabile di tipo double
     omegak = msg_twist->twist.angular.z;

     vx = msg_twist->twist.linear.x;
     omega_z = msg_twist->twist.angular.z;

    
     integration_time = current_time - old_time;
     //INTEGRAZIONE EULERO E PUBBLICAZIONE
     if(flag == 0) {
      x = x_old + vk*integration_time*cosf(theta_old);
      y = y_old + vk*integration_time*sinf(theta_old);
      theta = theta_old + omegak*integration_time;
      theta_old = theta;
      theta_old_rk = theta;
      x_old = x;
      x_old_rk = x;
      y_old = y;
      y_old_rk = y;
      old_time = current_time;
      message.header.stamp = ros::Time::now();
      message.header.frame_id = "odom";
      message.child_frame_id = "base_link_integrazione";
      tf::Quaternion myQuaternion;
      myQuaternion.setRPY(0, 0, theta);
      message.pose.pose.position.x = x;
      message.pose.pose.position.y = y;
      message.pose.pose.position.z = 0;

      message.twist.twist.linear.x = vx;
      message.twist.twist.angular.z = omega_z;

      message.pose.pose.orientation.x = myQuaternion[0];
      message.pose.pose.orientation.y = myQuaternion[1];
      message.pose.pose.orientation.z = myQuaternion[2];
      message.pose.pose.orientation.w = myQuaternion[3];
      pub.publish(message);

      messaggio_finale.odom = message;
      messaggio_finale.method.data = "Eulero";
      pub3.publish(messaggio_finale);

     }

    //INTEGRAZIONE RK E PUBBLICAZIONE

     else if (flag == 1) {
      x_rk = x_old_rk + vk*integration_time*cosf(theta_old_rk +(omegak*integration_time)/2);
      y_rk = y_old_rk + vk*integration_time*sinf(theta_old_rk +(omegak*integration_time)/2);
      theta_rk = theta_old_rk + omegak*integration_time;
      theta_old_rk = theta_rk;
      theta_old = theta_rk;
      x_old_rk = x_rk;
      x_old = x_rk;
      y_old_rk = y_rk;
      y_old = y_rk;

      message_rk.header.stamp = ros::Time::now();
      message_rk.header.frame_id = "odom";
      message_rk.child_frame_id = "base_link_integrazione";
      tf::Quaternion myQuaternion_rk;
      myQuaternion_rk.setRPY(0, 0, theta_rk);
      message_rk.pose.pose.position.x = x_rk;
      message_rk.pose.pose.position.y = y_rk;
      message_rk.pose.pose.position.z = 0;

      message_rk.twist.twist.linear.x = vx;
      message_rk.twist.twist.angular.z = omega_z;

      message_rk.pose.pose.orientation.x = myQuaternion_rk[0];
      message_rk.pose.pose.orientation.y = myQuaternion_rk[1];
      message_rk.pose.pose.orientation.z = myQuaternion_rk[2];
      message_rk.pose.pose.orientation.w = myQuaternion_rk[3];
      pub.publish(message_rk);

      messaggio_finale.odom = message_rk;
      messaggio_finale.method.data = "Rk";
      pub3.publish(messaggio_finale);
      old_time = current_time;
     }
        
    }


    void callback_dyn(integrazione::metodiConfig &config, uint32_t level) { 
      flag = config.metodo;  // flag takes the value corresponding to the chosen method, according to the enum definition in metodi.cfg
    }

    bool reset_zero_f(service::ResetZeroRequest &req, service::ResetZeroResponse &res){

      x = 0;
      y = 0;
      x_old = 0;
      y_old = 0;
      x_old_rk = 0;
      y_old_rk = 0;
      ROS_INFO("Odometry setted to the origin");

      return true;

    }

    bool given_pose_f(service::ResetZeroRequest &req, service::ResetZeroResponse &res){

      x = req.x;
      y = req.y;
      x_old = req.x;
      y_old = req.y;
      x_old_rk = req.x;
      y_old_rk = req.y;
      theta = req.theta;
      theta_old = req.theta;
      theta_rk = req.theta;
      theta_old_rk = req.theta;
      ROS_INFO("Odometry setted to the given pose %f,%f,%f", x, y, theta);
    
      return true;
    }

};

int main(int argc, char **argv){
    ros::init(argc, argv, "integratore");
    integratore my_integratore;
    return 0;
}



#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Header.h"
#include "nav_msgs/Odometry.h"
#include<robotics_hw1/WheelSpeeds.h>
#include<robotics_hw1/BaselineMsg.h>
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
double old_time = 1619342819.251675288;
float integration_time = 0;

float vk;
float omegak;

float vx;
float omega_z;

int flag = 0;

private:
    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Subscriber sub2;
    ros::Publisher pub;
    ros::Publisher pub2;
    nav_msgs::Odometry message;
    nav_msgs::Odometry message_rk;
    dynamic_reconfigure::Server<integrazione::metodiConfig> server;
    dynamic_reconfigure::Server<integrazione::metodiConfig>::CallbackType f;
    ros::ServiceServer service1;
    ros::ServiceServer service2;

public:
    integratore(){
        f = boost::bind(&integratore::callback_dyn, this, _1, _2);
        server.setCallback(f);
        sub = n.subscribe<geometry_msgs::TwistStamped>("/twist_stamped", 200, &integratore::callback, this);
        //sub2 = n.subscribe<geometry_msgs::TwistStamped>("/scout_odom", 200, &integratore::callback2, this);
        pub = n.advertise<nav_msgs::Odometry>("integrazione_odom", 10);
        //pub2 = n.advertise<nav_msgs::Odometry>("/scout_osom_tf", 10);
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
    current_time = msg_twist->header.stamp.toSec();  // la funzione toSec(); è top perchè prende lo stamp
    vk = msg_twist->twist.linear.x;                  // e lo rende salvabile in una variabile di tipo double
    omegak = msg_twist->twist.angular.z;

    vx = msg_twist->twist.linear.x;
    omega_z = msg_twist->twist.angular.z;

    //ROS_INFO("L'integrazione e' avvenuta a %f", current_time);

    integration_time = current_time - old_time;
    //INTEGRAZIONE EULERO E PUBBLICAZIONE
    if(flag == 0) {
    ROS_INFO("Eulero");
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
    //message.header = msg_twist->header;
    message.header.stamp = ros::Time::now();
    message.header.frame_id = "map";
    message.child_frame_id = "integrazione_odom";
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

    }

    //INTEGRAZIONE RK E PUBBLICAZIONE
    else if (flag == 1) {
    ROS_INFO("Rk");
    x_rk = x_old_rk + vk*integration_time*cosf(theta_old_rk +(omegak*integration_time)/2);
    y_rk = y_old_rk + vk*integration_time*sinf(theta_old_rk +(omegak*integration_time)/2);
    theta_rk = theta_old_rk + omegak*integration_time;
    theta_old_rk = theta_rk;
    theta_old = theta_rk;
    x_old_rk = x_rk;
    x_old = x_rk;
    y_old_rk = y_rk;
    y_old = y_rk;

    //message.header = msg_twist->header;
    message_rk.header.stamp = ros::Time::now();
    message_rk.header.frame_id = "map";
    message_rk.child_frame_id = "integrazione_odom";
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
    //message_rk.header.frame_id = "map";
    pub.publish(message_rk);
    old_time = current_time;
    }
    else 
    {
        ROS_INFO("HO SKIPPATO GLI IF e flag e': %u", flag); 
    }
    
   }


  void callback_dyn(integrazione::metodiConfig &config, uint32_t level) {
  
  ROS_INFO("Entrato nella callback_dyn");
  //ROS_INFO("Reconfigure Request: %d", 
   //         config.metodo);
  flag = config.metodo;
  ROS_INFO ("%d",flag);
}
bool reset_zero_f(service::ResetZeroRequest &req, service::ResetZeroResponse &res){

     x = 0;
     y = 0;
     x_old = 0;
     y_old = 0;
     x_old_rk = 0;
     y_old_rk = 0;
     ROS_INFO("Odometry traslata all'origine");

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
    ROS_INFO("Odometry traslata a %f,%f,%f", x, y, theta);
    return true;
    }

};

int main(int argc, char **argv){
    ros::init(argc, argv, "integratore");
    integratore my_integratore;
    return 0;
}



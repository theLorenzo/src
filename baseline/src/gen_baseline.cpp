#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Header.h"
#include "nav_msgs/Odometry.h"
#include<robotics_hw1/WheelSpeeds.h>
#include<robotics_hw1/BaselineMsg.h>
#include<geometry_msgs/TwistStamped.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <boost/bind.hpp>



class generatore_baseline
{


    float gear_ratio=0;
    float vettore_gr[100];
    int flag_vettore_gr = 0;
    int counter_v = 0;

    float baseline=0;
    float vettore_baseline[10000];
    int flag_vettore_baseline = 0;
    int counter_b = 0;

    float baseline_temp = 0;



private:
    ros::NodeHandle n;
    message_filters::Subscriber<nav_msgs::Odometry> sub1;
    message_filters::Subscriber<robotics_hw1::WheelSpeeds> sub2;
    ros::Publisher pub;

    typedef message_filters::sync_policies::ExactTime<nav_msgs::Odometry, robotics_hw1::WheelSpeeds> MySyncPolicy;

public:
    generatore_baseline(){
        sub1.subscribe(n, "/scout_odom", 20);
        sub2.subscribe(n, "/vettore_motori", 20);
        pub = n.advertise<robotics_hw1::BaselineMsg>("baseline_topic", 1000);

        while (ros::ok()){
            //ROS_INFO("SONO ENTRATO NEL WHILE");
            message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(100), sub1, sub2);
            sync.registerCallback(boost::bind(&generatore_baseline::callback1, this, _1, _2));
           ros::spin();
        }
    }
    void callback1(const nav_msgs::Odometry::ConstPtr& msg_odom,
                  const robotics_hw1::WheelSpeeds::ConstPtr& msg_wheel) {
        //ROS_INFO("SONO ENTRATO NELLA CALLBACK");

/*
        //si calcola il gear ratio:
    if (flag_vettore_gr == 0){                 //se il flag è 0 il vettore di valori gr non è ancora pieno
        ROS_INFO("Sto calcolando il gear ratio...");

        float vl = (msg_wheel->speed1*0.10472 + msg_wheel->speed3*0.10472) / 2; //prendo i valori
        float vr = (msg_wheel->speed2*0.10472 + msg_wheel->speed4*0.10472) / 2;
        float vx = msg_odom->twist.twist.linear.x;

        if (vr != vl && (vx>0.1 || vx<-0.1)){          // controllo che il denominatore non si annulli
            vettore_gr[counter_v] = 2 * vx / (0.1575 * (vl - vr)); //calcolo il gear ratio corrente e lo metto nel vettore
            counter_v++;
            if(counter_v == 100){ // se il vettore è pieno il flag scatta
                flag_vettore_gr = 1;
            }
        }
    }
    else {  // se il flag scatta a 1 si entra qui, dove si fa la media del vettore e si printa
        float media_vettore_gr = media(vettore_gr);
        gear_ratio = -1/(media_vettore_gr);
        ROS_INFO("Il gear ratio e' 1:%f", gear_ratio);
    }*/
        /*
           if (flag_vettore_baseline == 0){
                   ROS_INFO("Sto calcolando la baseline...");

                   float vl_1 = (msg_wheel->speed1*0.10472*0.1575*0.026 + msg_wheel->speed3*0.10472*0.1575*0.026) / 2;
                   float vr_1 = (msg_wheel->speed2*0.10472*0.1575*0.026 + msg_wheel->speed4*0.10472*0.1575*0.026) / 2;
                   float omega_z = msg_odom->twist.twist.angular.z;

                   if (omega_z != 0){
                       vettore_baseline[counter_b] = (vr_1+vl_1)/(omega_z);
                       counter_b++;
                       if(counter_b == 10000){
                           flag_vettore_baseline = 1;
                       }
                   }
               }
           else {
                   float media_vettore_baseline = media(vettore_baseline);
                   ROS_INFO("La baseline e' %f",media_vettore_baseline);
               }
           }*/
        /*
            //DEBUGGING: printa la baseline corrente
            float vl = (msg_wheel->speed1 * 0.10472 * 0.1575 * 0.026 + msg_wheel->speed3 * 0.10472 * 0.1575 * 0.026) / 2;
            float vr = (msg_wheel->speed2 * 0.10472 * 0.1575 * 0.026 + msg_wheel->speed4 * 0.10472 * 0.1575 * 0.026) / 2;
            float omega_z = msg_odom->twist.twist.angular.z; //conversione da rpm a rad/s è moltiplicare per quella costante
            //ROS_INFO("vl: %f, vr: %f, omega_z: %f", vl, vr, omega_z);

            if (omega_z != 0) {
                baseline_temp = 2*((vr - vl) / (2 * omega_z));
                ROS_INFO("Baseline: %f", baseline_temp);
                robotics_hw1::BaselineMsg messaggio;
                messaggio.header.stamp = msg_wheel->header.stamp;
                messaggio.data = baseline_temp;
                pub.publish(messaggio);
            }*/
    }

    float media(float vettore[]) // semplice funzione che calcola la media di un vettore di 100 valori
    {
        float somma;
        for (int i = 0; i < 10001; ++i) {
            somma = somma + vettore[i];
        }
        float media_fatta = somma/10000;
        return media_fatta;
    }
};

int main(int argc, char **argv){
    ros::init(argc, argv, "generatore_baseline");
    generatore_baseline my_generatore_baseline;
    return 0;
}



#ifndef __LASER_CONTROL_H__
#define __LASER_CONTROL_H__

#include <iostream>
#include <string>
#include <ros/ros.h>
#include "dynamixel.h"
#include "dynamixel_control/wheel_laser.h"
using namespace std;

class Laser
{
    public:
        void runposition();
        void endposition();
        void init();
        Laser(ros::NodeHandle &nh);
        ~Laser();
    private:
        ros::NodeHandle nh_;
        ros::Subscriber laser_sub;
        void laser_callback(const dynamixel_control::wheel_laser &msg);
        Motor motor13;
        Motor motor14;
        int position13;
        int position14;
        string port;
};

#endif

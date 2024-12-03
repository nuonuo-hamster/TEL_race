#ifndef __CAMERA_CONTROL_H__
#define __CAMERA_CONTROL_H__

#include <iostream>
#include <string>
#include <ros/ros.h>
#include "dynamixel.h"
#include "dynamixel_control/camera_angle.h"
using namespace std;

class Camera
{
    public:
        void init();
        Camera(ros::NodeHandle &nh);
        ~Camera();
    private:
        ros::NodeHandle nh_;
        ros::Subscriber camera_angle_sub;
        void camera_callback(const dynamixel_control::camera_angle &msg);
        Motor motor15;
        int position15;
        string port;
};

#endif

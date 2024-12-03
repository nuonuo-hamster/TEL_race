#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <iostream>
#include <string>
#include <ros/ros.h>
#include "dynamixel.h"
#include "arm/arm.h"
#include "trunk/trunk.h"
#include "camera_control/camera_control.h"
#include "laser_control/laser_control.h"

using namespace std;

class Control
{
    public:

        Control(ros::NodeHandle &nh);
        ~Control();
        

    private:
        ros::NodeHandle nh_;

};

#endif

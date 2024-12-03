#include "control/control.h"


Control::Control(ros::NodeHandle &nh)
    : nh_(nh)
{
    ROS_INFO("\n CONTROL CLASS CONSTRUCTED\n");
}
Control::~Control()
{
    ROS_INFO("\n CONTROL CLASS DECONSTRUCTED\n");
}



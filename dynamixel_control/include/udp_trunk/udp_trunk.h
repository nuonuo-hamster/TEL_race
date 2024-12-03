#ifndef __trunk_H__
#define __trunk_H__

#include <iostream>
#include <string>
#include <ros/ros.h>
#include "arm/arm.h"
#include "dynamixel.h"
#include "dynamixel_control/arm_trunk.h"

class Storage
{
public:
    void oriposition();
    void init();
    void startposition();
    void setposition();
    void backrise();
    void backdown();
    void pileposition();
    Storage(ros::NodeHandle &nh);
    ~Storage();

private:
    ros::NodeHandle nh_;
    ros::Subscriber arm_trunk_sub;
    void trunk_callback(const dynamixel_control::arm_trunk &msg);
    Move m_move;
    Motor motor1;
    Motor motor2;
    Motor motor3;
    Motor motor4;
    Motor motor5;
    Motor motor6;
    int position1;
    int position2;
    int position3;
    int position4;
    int position5;
    int position6;
    std::string port;
};

#endif

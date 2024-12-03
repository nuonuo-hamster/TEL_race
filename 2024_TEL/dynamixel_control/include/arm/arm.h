#ifndef __ARM_H__
#define __ARM_H__

#include <iostream>
#include <string>
#include <ros/ros.h>
#include "dynamixel.h"

class Move
{
public:
    void setposition();
    void gripposition();
    void gripping();
    void only_gripping_pos();
    void type2_gripping_pos();
    void only_grip();
    void grip_relex();
    void only_grip_min();
    void backtoposition();
    void fir_subposition();
    void fir_addposition();
    void sec_subposition();
    void sec_addposition();
    void thir_subposition();
    void thir_addposition();
    void fir_sec_subposition();
    void fir_sec_addposition();
    Move();
    Move(ros::NodeHandle &nh);
    ~Move();

private:
    ros::NodeHandle nh_;
    Motor motor1;
    Motor motor2;
    Motor motor3;
    Motor motor4;
    Motor motor5;
    Motor motor6;
    Motor motor7;
    int position1;
    int position2;
    int position3;
    int position4;
    int position5;
    int position6;
    int position7;
    std::string port;
};

#endif

#include "camera_control/camera_control.h"

Camera::Camera(ros::NodeHandle &nh)
    : motor15(1, 15, "/dev/arm"), nh_(nh)
{
    ROS_INFO("\n CAMERA_CONTROL CLASS CONSTRUCTED\n");
}

Camera::~Camera()
{
    ROS_INFO("\n CAMERA_CONTROL CLASS DECONSTRUCTED\n");
}

void Camera::init()
{
    position15 = 120;
    motor15.setServoState(ON);
    motor15.setSpeed(10);
    motor15.setPosition(position15);
    camera_angle_sub = nh_.subscribe("/dynamixel/camera_angle", 1, &Camera::camera_callback, this);
}

void Camera::camera_callback(const dynamixel_control::camera_angle &msg)
{
    // position15 = 120;
    motor15.setServoState(ON);
    motor15.setSpeed(10);
    if (msg.angle == 0)
    {
        position15 = 100;
    }
    if (msg.angle == 1)
    {
        position15 = 110;
    }
    if (msg.angle == 2)
    {
        position15 = 120;
    }
    if (msg.angle == 3)
    {
        position15 = 130;
    }
    if (msg.angle == 4)
    {
        position15 = 140;
    }
    if (msg.angle == 5)
    {
        position15 = 150;
    }
    if (msg.angle == 6)
    {
        position15 = 160;
    }
    if (msg.angle == 7)
    {
        ROS_INFO("camera angle:%d", position15);
        // cout << "motor15 angle:" << position15 << endl;
    }

    motor15.setPosition(position15);
    //    cout << "motor15 angle:" << position15 << endl;
    // motor15.setServoState(OFF);
}

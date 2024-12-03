#include "camera_control/camera_control.h"

int main(int argc,char** argv)
{
    ros::init(argc,argv,"camera_control");
    ros::NodeHandle nh;
    Camera camera(nh);
    camera.init();
    while(ros::ok())
    {
        ros::Rate loop_rate(10);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}


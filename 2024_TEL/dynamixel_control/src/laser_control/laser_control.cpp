#include "laser_control/laser_control.h"

int main(int argc,char** argv)
{
    ros::init(argc,argv,"laser_control");
    ros::NodeHandle nh;
    Laser laser(nh);
    laser.init();
    while(ros::ok())
    {
        ros::Rate loop_rate(10);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}


#include "control/control.h"

int main(int argc,char** argv)
{
    ros::init(argc,argv,"control_part");
    ros::NodeHandle nh;

    Control control(nh);
    Storage storage(nh);
    Laser laser(nh);
    Move move(nh);
    Camera camera(nh);

    storage.init();
    laser.init();
    camera.init();

    while(ros::ok())
    {
        ros::Rate loop_rate(10);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}


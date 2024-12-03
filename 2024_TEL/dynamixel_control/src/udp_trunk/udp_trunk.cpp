#include "udp_trunk/udp_trunk.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "udp_trunk");
    ros::NodeHandle nh;
    Storage storage(nh);
    storage.init();
    while (ros::ok())
    {
        ros::Rate loop_rate(10);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

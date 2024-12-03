#include "udp_trunk/udp_trunk.h"

Storage::Storage(ros::NodeHandle &nh)
    : nh_(nh), m_move(nh), motor1(1, 0, "/dev/trunk"), motor2(1, 1, "/dev/trunk"), motor3(1, 2, "/dev/trunk"), motor4(1, 3, "/dev/trunk"), motor5(2, 4, "/dev/trunk"), motor6(2, 5, "/dev/trunk")
{
    ROS_INFO("\n Storage CLASS CONSTRUCTED\n");
}

Storage::~Storage()
{
    ROS_INFO("\n Storage CLASS DECONSTRUCTED\n");
}

void Storage::init()
{
    arm_trunk_sub = nh_.subscribe("/dynamixel/arm_storage", 1, &Storage::trunk_callback, this, ros::TransportHints().unreliable().maxDatagramSize(10));

    oriposition();
    ros::Duration(1).sleep();
    m_move.setposition();
}

void Storage::trunk_callback(const dynamixel_control::arm_trunk &msg)
{
    motor1.setServoState(ON);
    motor2.setServoState(ON);
    motor3.setServoState(ON);
    motor4.setServoState(ON);
    motor5.setServoState(ON);
    motor6.setServoState(ON);
    if (msg.control == 1)
    {
        setposition(); //木板傾斜
    }
    if (msg.control == 2)
    {
        m_move.gripping(); //夾取動作
    }
    if (msg.control == 3)
    {
        m_move.backtoposition(); //積木放木板
    }
    if (msg.control == 4)
    {
        m_move.gripposition(); //夾爪放下
    }
    if (msg.control == 5)
    {
        pileposition(); //木板積木放置堆疊
    }
    if (msg.control == 6)
    {
        oriposition(); //擋板回初始位置
        ros::Duration(1).sleep();
        m_move.setposition(); //夾爪回初始位置
    }
    if (msg.control == 7) //就準備位置
    {
        double starttime = ros::Time::now().toSec();
        m_move.only_gripping_pos();
        ros::Duration(1).sleep();
        setposition();
        double endtime = ros::Time::now().toSec();
        ROS_INFO("time:%lf",endtime-starttime);
    }
    if (msg.control == 8) //單純夾取動作
    {
        m_move.only_grip();
    }
    if (msg.control == 9) //單純小物件夾取動作
    {
        m_move.only_grip_min();
    }
    if (msg.control == 10) //單純放鬆動作
    {
        m_move.grip_relex();
    }
    if (msg.control == 11) //背面擋板伸起動作
    {
        backrise();
    }
    if (msg.control == 12) //背面擋板降下動作
    {
        backdown();
    }
}

void Storage::startposition()
{
    motor1.setServoState(ON);
    motor2.setServoState(ON);
    motor3.setServoState(ON);
    motor4.setServoState(ON);

    position3 = 160;
    motor3.setServoState(ON);
    motor3.setSpeed(10);
    motor3.setPosition(position3);
    // cout << "motor3 angle:" << position3 << endl;
    motor3.waitForIdle();
}

void Storage::setposition() //木板傾斜
{
    motor1.setServoState(ON);
    motor2.setServoState(ON);
    motor3.setServoState(ON);
    motor4.setServoState(ON);
    motor5.setServoState(ON);
    motor6.setServoState(ON);

    position1 = 133;
    motor1.setServoState(ON);
    motor1.setSpeed(30);
    motor1.setPosition(position1);
    // cout << "motor1 angle:" << position1 << endl;

    position6 = 155;
    motor6.setServoState(ON);
    motor6.setSpeed(30);
    motor6.setPosition(position6);
    // cout << "motor6 angle:" << position6 << endl;

    position2 = 116;
    motor2.setServoState(ON);
    motor2.setSpeed(30);
    motor2.setPosition(position2);
    // cout << "motor2 angle:" << position2 << endl;

    position5 = 333;
    motor5.setServoState(ON);
    motor5.setSpeed(30);
    motor5.setPosition(position5);
    // cout << "motor5 angle:" << position5 << endl;

    position3 = 140;
    motor3.setServoState(ON);
    motor3.setSpeed(30);
    motor3.setPosition(position3);
    // cout << "motor3 angle:" << position3 << endl;

    position4 = 149;
    motor4.setServoState(ON);
    motor4.setSpeed(30);
    motor4.setPosition(position4);
    // cout << "motor4 angle:" << position4 << endl;

    /*  motor1.setServoState(OFF);
        motor2.setServoState(OFF);
        motor3.setServoState(OFF);
        motor4.setServoState(OFF);
        */
}

void Storage::oriposition()
{
    motor1.setServoState(ON);
    motor2.setServoState(ON);
    motor3.setServoState(ON);
    motor4.setServoState(ON);
    motor5.setServoState(ON);
    motor6.setServoState(ON);

    position4 = 159;
    motor4.setSpeed(10);
    motor4.setPosition(position4);
    //  cout << "motor4 angle:" << position4 << endl;
    motor4.waitForIdle();

    position3 = 250;
    motor3.setSpeed(10);
    motor3.setPosition(position3);
    //  cout << "motor3 angle:" << position3 << endl;
    motor3.waitForIdle();

    position2 = 92;
    motor2.setSpeed(50);
    motor2.setPosition(position2);
    //  cout << "motor2 angle:" << position2 << endl;
    // motor2.waitForIdle();

    position5 = 306;
    motor5.setSpeed(50);
    motor5.setPosition(position5);
    // cout << "motor5 angle:" << position5 << endl;
    motor5.waitForIdle();

    position6 = 145;
    motor6.setSpeed(50);
    motor6.setPosition(position6);
    // cout << "motor6 angle:" << position6 << endl;
    // motor6.waitForIdle();

    position1 = 120;
    motor1.setSpeed(50);
    motor1.setPosition(position1);
    //   cout << "motor1 angle:" << position1 << endl;
    motor1.waitForIdle();
}

void Storage::pileposition() //木板積木放置堆疊
{
    motor1.setServoState(ON);
    motor2.setServoState(ON);
    motor3.setServoState(ON);
    motor4.setServoState(ON);
    motor5.setServoState(ON);
    motor6.setServoState(ON);

    position3 = 240;
    motor3.setSpeed(10);
    motor3.setPosition(position3);
    // cout << "motor3 angle:" << position3 << endl;
    motor3.waitForIdle();

    position1 = 239;
    motor1.setSpeed(20);
    motor1.setPosition(position1);
    // cout << "motor1 angle:" << position1 << endl;

    position6 = 251;
    motor6.setSpeed(20);
    motor6.setPosition(position6);
    // cout << "motor6 angle:" << position6 << endl;

    position5 = 276;
    motor5.setSpeed(20);
    motor5.setPosition(position5);
    //  cout << "motor5 angle:" << position5 << endl;

    position2 = 60;
    motor2.setSpeed(20);
    motor2.setPosition(position2);
    // cout << "motor2 angle:" << position2 << endl;


    ros::Duration(3).sleep();
    position4 = 59;
    motor4.setSpeed(40);
    motor4.setPosition(position4);
    // cout << "motor4 angle:" << position4 << endl;
    motor4.waitForIdle();

    ros::Duration(1).sleep();
    position3 = 160;
    motor3.setSpeed(10);
    motor3.setPosition(position3);
    // cout << "motor3 angle:" << position3 << endl;

    /*   motor1.setServoState(OFF);
         motor2.setServoState(OFF);
         motor3.setServoState(OFF);
         motor4.setServoState(OFF);
         */
}

void Storage::backrise() //背面擋板伸起
{
    motor4.setServoState(ON);
    position4 = 59;
    motor4.setSpeed(40);
    motor4.setPosition(position4);
    // cout << "motor4 angle:" << position4 << endl;
    motor4.waitForIdle();
}

void Storage::backdown() //被面擋板降下
{
    motor4.setServoState(ON);
    position4 = 149;
    motor4.setSpeed(40);
    motor4.setPosition(position4);
    // cout << "motor4 angle:" << position4 << endl;
    motor4.waitForIdle();
}
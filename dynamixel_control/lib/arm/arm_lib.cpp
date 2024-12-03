#include "arm/arm.h"

Move::Move()
  : motor1(1, 6, "/dev/arm"), motor2(1, 7, "/dev/arm"), motor3(1, 8, "/dev/arm"), motor4(1, 9, "/dev/arm"), motor5(1, 10, "/dev/arm"), motor6(2, 11, "/dev/arm"), motor7(2, 12, "/dev/arm")
{
  ROS_INFO("Move default");
}

Move::Move(ros::NodeHandle &nh)
    : nh_(nh), motor1(1, 6, "/dev/arm"), motor2(1, 7, "/dev/arm"), motor3(1, 8, "/dev/arm"), motor4(1, 9, "/dev/arm"), motor5(1, 10, "/dev/arm"), motor6(2, 11, "/dev/arm"), motor7(2, 12, "/dev/arm")
{
  ROS_INFO("\n MOVE CLASS CONSTRUCTED\n");
}

Move::~Move()
{
  ROS_INFO("\n MOVE CLASS DECONSTRUCTED\n");
}

void Move::setposition() //初始位置
{
  position5 = 170;
  motor5.setServoState(ON);
  motor5.setSpeed(10);
  motor5.setPosition(position5);
  // cout << "motor5 angle:" << position5 << endl;
  // motor1.setServoState(OFF);

  motor5.waitForIdle();

  position4 = 156;
  motor4.setServoState(ON);
  motor4.setSpeed(10);
  motor4.setPosition(position4);
  // motor4.waitForIdle();
  // cout << "motor4 angle:" << position4 << endl;
  // motor2.setServoState(OFF);

  position3 = 133;
  motor3.setServoState(ON);
  motor3.setSpeed(10);
  motor3.setPosition(position3);
  motor3.waitForIdle();
  // cout << "motor3 angle:" << position3 << endl;
  // motor3.setServoState(OFF);

  position2 = 138;
  motor2.setServoState(ON);
  motor2.setSpeed(10);
  motor2.setPosition(position2);
  // motor2.waitForIdle();
  // cout << "motor2 angle:" << position2 << endl;
  motor4.setServoState(OFF);

  position1 = 156;
  motor1.setServoState(ON);
  motor1.setSpeed(10);
  motor1.setPosition(position1);
  motor1.waitForIdle();
  // cout << "motor1 angle:" << position1 << endl;
  // motor5.setServoState(OFF);

  position6 = 187;
  motor6.setServoState(ON);
  motor6.setSpeed(50);
  motor6.setPosition(position6);
  // cout << "motor6 angle:" << position6 << endl;
  motor6.setServoState(OFF);

  position7 = 132;
  motor7.setServoState(ON);
  motor7.setSpeed(50);
  motor7.setPosition(position7);
  // cout << "motor7 angle:" << position7 << endl;
  motor7.waitForIdle();
  motor7.setServoState(OFF);

  position5 = 200;
  motor5.setServoState(ON);
  motor5.setSpeed(5);
  motor5.setPosition(position5);
}

void Move::gripposition() //夾取位置
{
  position6 = 222;
  motor6.setServoState(ON);
  motor6.setSpeed(70);
  motor6.setPosition(position6);
  // cout << "motor6 angle:" << position6 << endl;
  motor6.setServoState(OFF);

  // position7 = 107;
  position7 = 92;
  motor7.setServoState(ON);
  motor7.setPosition(position7);
  motor7.waitForIdle();
  // cout << "motor7 angle:" << position7 << endl;
  motor7.setServoState(OFF);

  // position1 = 70;
  position1 = 136;
  motor1.setServoState(ON);
  motor1.setSpeed(20);
  motor1.setPosition(position1);
  // cout << "motor1 angle:" << position1 << endl;
  // motor1.setServoState(OFF);

  // position2 = 230;
  position2 = 169;
  motor2.setServoState(ON);
  motor2.setSpeed(20);
  motor2.setPosition(position2);
  // motor2.waitForIdle();
  // cout << "motor2 angle:" << position2 << endl;
  // motor2.setServoState(OFF);

  // position5 = 240;
  position5 = 120;
  motor5.setServoState(ON);
  motor5.setSpeed(10);
  motor5.setPosition(position5);
  motor5.waitForIdle();
  // cout << "motor5 angle:" << position5 << endl;
  // motor5.setServoState(OFF);

  // position3 = 220;
  position3 = 173;
  motor3.setServoState(ON);
  motor3.setSpeed(10);
  motor3.setPosition(position3);
  // cout << "motor3 angle:" << position3 << endl;
  //  motor3.setServoState(OFF);

  // position4 = 80;
  position4 = 128;
  motor4.setServoState(ON);
  motor4.setSpeed(10);
  motor4.setPosition(position4);
  motor4.waitForIdle();
  // cout << "motor4 angle:" << position4 << endl;
  // motor4.setServoState(OFF);

  // position6 = 27;
}

void Move::gripping() //夾取動作
{
  // position1 = 70;
  position1 = 100;
  motor1.setServoState(ON);
  motor1.setSpeed(20);
  motor1.setPosition(position1);
  // cout << "motor1 angle:" << position1 << endl;
  // motor1.setServoState(OFF);

  // position2 = 230;
  position2 = 197;
  motor2.setServoState(ON);
  motor2.setSpeed(20);
  motor2.setPosition(position2);
  // motor2.waitForIdle();
  // cout << "motor2 angle:" << position2 << endl;
  // motor2.setServoState(OFF);

  // position5 = 240;

  // cout << "motor5 angle:" << position5 << endl;
  // motor5.setServoState(OFF);

  // position3 = 220;
  position3 = 189;
  motor3.setServoState(ON);
  motor3.setSpeed(10);
  motor3.setPosition(position3);
  // cout << "motor3 angle:" << position3 << endl;
  //  motor3.setServoState(OFF);

  // position4 = 80;
  position4 = 105;
  motor4.setServoState(ON);
  motor4.setSpeed(10);
  motor4.setPosition(position4);
  motor4.waitForIdle();
  // cout << "motor4 angle:" << position4 << endl;
  // motor4.setServoState(OFF);

  position5 = 120;
  motor5.setServoState(ON);
  motor5.setSpeed(10);
  motor5.setPosition(position5);
  motor5.waitForIdle();
  /*position5 = 90;
  motor5.setServoState(ON);
  motor5.setSpeed(10);
  motor5.setPosition(position5);
  motor5.waitForIdle();
*/
  position6 = 180;
  motor6.setServoState(ON);
  motor6.setSpeed(70);
  motor6.setPosition(position6);
  // cout << "motor6 angle:" << position6 << endl;

  position7 = 139;
  motor7.setServoState(ON);
  motor7.setSpeed(70);
  motor7.setPosition(position7);
  motor7.waitForIdle();
}

void Move::backtoposition()
{
  position1 = 144;
  motor1.setServoState(ON);
  motor1.setSpeed(10);
  motor1.setPosition(position1);
  // cout << "motor1 angle:" << position1 << endl;
  // motor1.setServoState(OFF);

  position2 = 157;
  motor2.setServoState(ON);
  motor2.setSpeed(10);
  motor2.setPosition(position2);
  // cout << "motor2 angle:" << position2 << endl;
  //  motor2.setServoState(OFF);

  position3 = 137;
  motor3.setServoState(ON);
  motor3.setSpeed(7);
  motor3.setPosition(position3);
  // cout << "motor3 angle:" << position3 << endl;
  //   motor3.setServoState(OFF);

  position4 = 161;
  motor4.setServoState(ON);
  motor4.setSpeed(7);
  motor4.setPosition(position4);
  // cout << "motor4 angle:" << position4 << endl;
  //  motor4.setServoState(OFF);

  position5 = 185;
  motor5.setServoState(ON);
  motor5.setSpeed(5);
  motor5.setPosition(position5);
  // cout << "motor5 angle:" << position5 << endl;
  motor5.waitForIdle();

  ros::Duration(1).sleep();

  // position6 = 27;
  position6 = 222;
  motor6.setServoState(ON);
  motor6.setSpeed(70);
  motor6.setPosition(position6);
  // cout << "motor6 angle:" << position6 << endl;

  // position7 = 107;
  position7 = 92;
  motor7.setServoState(ON);
  motor7.setSpeed(70);
  motor7.setPosition(position7);
  motor7.waitForIdle();
  // cout << "motor7 angle:" << position7 << endl;

  // motor5.setServoState(OFF);
}

void Move::fir_subposition()  //地1軸夾爪向下轉動
{
  motor1.setServoState(ON);
  motor2.setServoState(ON);
  motor3.setServoState(ON);
  motor4.setServoState(ON);
  motor5.setServoState(ON);
  position1 = position1 - 10;
  motor1.setSpeed(10);
  motor1.setPosition(position1);
  position2 = position2 + 10;
  motor2.setSpeed(10);
  motor2.setPosition(position2);
}

void Move::fir_addposition() //地1軸夾爪向上轉動
{
  motor1.setServoState(ON);
  motor2.setServoState(ON);
  motor3.setServoState(ON);
  motor4.setServoState(ON);
  motor5.setServoState(ON);
  position1 = position1 + 10;
  motor1.setSpeed(10);
  motor1.setPosition(position1);
  position2 = position2 - 10;
  motor2.setSpeed(10);
  motor2.setPosition(position2);
}

void Move::sec_subposition() //地2軸夾爪向下轉動
{
  motor1.setServoState(ON);
  motor2.setServoState(ON);
  motor3.setServoState(ON);
  motor4.setServoState(ON);
  motor5.setServoState(ON);
  position3 = position3 + 10;
  motor3.setSpeed(10);
  motor3.setPosition(position3);
  position4 = position4 - 10;
  motor4.setSpeed(10);
  motor4.setPosition(position4);
}

void Move::sec_addposition() //地2軸夾爪向上轉動
{
  motor1.setServoState(ON);
  motor2.setServoState(ON);
  motor3.setServoState(ON);
  motor4.setServoState(ON);
  motor5.setServoState(ON);
  position3 = position3 - 10;
  motor3.setSpeed(10);
  motor3.setPosition(position3);
  position4 = position4 + 10;
  motor4.setSpeed(10);
  motor4.setPosition(position4);
}

void Move::thir_subposition() //地3軸夾爪向下轉動
{
  motor1.setServoState(ON);
  motor2.setServoState(ON);
  motor3.setServoState(ON);
  motor4.setServoState(ON);
  motor5.setServoState(ON);
  position5 = position5 - 10;
  motor5.setSpeed(10);
  motor5.setPosition(position5);
}

void Move::thir_addposition() //地3軸夾爪向上轉動
{
  motor1.setServoState(ON);
  motor2.setServoState(ON);
  motor3.setServoState(ON);
  motor4.setServoState(ON);
  motor5.setServoState(ON);
  position5 = position5 + 10;
  motor5.setSpeed(10);
  motor5.setPosition(position5);
}

void Move::fir_sec_subposition() //地1,2軸夾爪向下轉動
{
  motor1.setServoState(ON);
  motor2.setServoState(ON);
  motor3.setServoState(ON);
  motor4.setServoState(ON);
  motor5.setServoState(ON);
  position3 = position3 + 10;
  motor3.setSpeed(10);
  motor3.setPosition(position3);
  position4 = position4 - 10;
  motor4.setSpeed(10);
  motor4.setPosition(position4);
  position1 = position1 - 10;
  motor1.setSpeed(10);
  motor1.setPosition(position1);
  position2 = position2 + 10;
  motor2.setSpeed(10);
  motor2.setPosition(position2);
}

void Move::fir_sec_addposition() //地1,2軸夾爪向上轉動
{
  motor1.setServoState(ON);
  motor2.setServoState(ON);
  motor3.setServoState(ON);
  motor4.setServoState(ON);
  motor5.setServoState(ON);
  position3 = position3 - 10;
  motor3.setSpeed(10);
  motor3.setPosition(position3);
  position4 = position4 + 10;
  motor4.setSpeed(10);
  motor4.setPosition(position4);
  position1 = position1 + 10;
  motor1.setSpeed(10);
  motor1.setPosition(position1);
  position2 = position2 - 10;
  motor2.setSpeed(10);
  motor2.setPosition(position2);
}

void Move::only_gripping_pos() //夾取位置沒夾取動作
{
  // position1 = 70;
  position1 = 100;
  motor1.setServoState(ON);
  motor1.setSpeed(20);
  motor1.setPosition(position1);
  // cout << "motor1 angle:" << position1 << endl;
  // motor1.setServoState(OFF);

  // position2 = 230;
  position2 = 197;
  motor2.setServoState(ON);
  motor2.setSpeed(20);
  motor2.setPosition(position2);

  position3 = 189;
  motor3.setServoState(ON);
  motor3.setSpeed(10);
  motor3.setPosition(position3);
  // cout << "motor3 angle:" << position3 << endl;
  //  motor3.setServoState(OFF);

  // position4 = 80;
  position4 = 105;
  motor4.setServoState(ON);
  motor4.setSpeed(10);
  motor4.setPosition(position4);
  motor4.waitForIdle();
  // cout << "motor4 angle:" << position4 << endl;
  // motor4.setServoState(OFF);

  position5 = 125;
  motor5.setServoState(ON);
  motor5.setSpeed(10);
  motor5.setPosition(position5);
  motor5.waitForIdle();

  position6 = 222;
  motor6.setServoState(ON);
  motor6.setSpeed(70);
  motor6.setPosition(position6);
  // cout << "motor6 angle:" << position6 << endl;

  position7 = 92;
  motor7.setServoState(ON);
  motor7.setSpeed(70);
  motor7.setPosition(position7);
  motor7.waitForIdle();
}

void Move::only_grip() //單純夾取動作
{
  position6 = 180;
  motor6.setServoState(ON);
  motor6.setSpeed(70);
  motor6.setPosition(position6);
  // cout << "motor6 angle:" << position6 << endl;

  position7 = 139;
  motor7.setServoState(ON);
  motor7.setSpeed(70);
  motor7.setPosition(position7);
  motor7.waitForIdle();
}

void Move::only_grip_min() //單純小夾取動作
{
  position6 = 168;
  motor6.setServoState(ON);
  motor6.setSpeed(70);
  motor6.setPosition(position6);
  // cout << "motor6 angle:" << position6 << endl;

  // position7 = 152;
  position7 = 149;
  motor7.setServoState(ON);
  motor7.setSpeed(70);
  motor7.setPosition(position7);
  motor7.waitForIdle();
}

void Move::grip_relex() //單純放鬆動作
{
  position6 = 222;
  motor6.setServoState(ON);
  motor6.setSpeed(70);
  motor6.setPosition(position6);
  // cout << "motor6 angle:" << position6 << endl;

  position7 = 92;
  motor7.setServoState(ON);
  motor7.setSpeed(70);
  motor7.setPosition(position7);
  motor7.waitForIdle();
}

void Move::type2_gripping_pos() //夾取位置沒夾取動作
{
 
  // position1 = 70;
  position1 = 71;
  motor1.setServoState(ON);
  motor1.setSpeed(20);
  motor1.setPosition(position1);
  // cout << "motor1 angle:" << position1 << endl;
  // motor1.setServoState(OFF);

  // position2 = 230;
  position2 = 228;
  motor2.setServoState(ON);
  motor2.setSpeed(20);
  motor2.setPosition(position2);

  position3 = 213;
  motor3.setServoState(ON);
  motor3.setSpeed(10);
  motor3.setPosition(position3);
  // cout << "motor3 angle:" << position3 << endl;
  //  motor3.setServoState(OFF);

  // position4 = 80;
  position4 = 83;
  motor4.setServoState(ON);
  motor4.setSpeed(10);
  motor4.setPosition(position4);
  //motor4.waitForIdle();
  // cout << "motor4 angle:" << position4 << endl;
  // motor4.setServoState(OFF);
  
  position5 = 207;
  motor5.setServoState(ON);
  motor5.setSpeed(10);
  motor5.setPosition(position5);
  motor5.waitForIdle();

  position6 = 222;
  motor6.setServoState(ON);
  motor6.setSpeed(70);
  motor6.setPosition(position6);
  // cout << "motor6 angle:" << position6 << endl;

  position7 = 92;
  motor7.setServoState(ON);
  motor7.setSpeed(70);
  motor7.setPosition(position7);
  motor7.waitForIdle();
}
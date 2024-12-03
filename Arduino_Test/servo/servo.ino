#include <Servo.h>

Servo frisbee_1F_1;
Servo frisbee_1F_2;
Servo frisbee_2F_1;
Servo frisbee_2F_2;
Servo Slide_2F;
Servo cameraY;
Servo launchservo;

int Slide_2F_angle = 10;
int cameraY_angle = 60;

const int pwmPin = 3;         // PWM 腳位
const int sensorPin = 2;      // 紅外線感應器數位輸入腳位
volatile unsigned long lastInterruptTime = 0; // 上次中斷的時間
volatile unsigned long interval = 0;          // 兩次中斷的時間差（微秒）
unsigned int rpm = 0;         // 每分鐘轉速
int pwmValue = 0;             // 預設 PWM 值

void setup() {
  Serial.begin(9600);

  frisbee_1F_1.detach();
  frisbee_1F_2.detach();
  frisbee_2F_1.detach();
  frisbee_2F_2.detach();
  Slide_2F.detach();
  cameraY.detach();
  
  Slide_2F.attach(9);
  cameraY.attach(13);
  launchservo.attach(7);

  Slide_2F.write(Slide_2F_angle);
  cameraY.write(cameraY_angle);
  launchservo.write(120);

  pinMode(pwmPin, OUTPUT);
  pinMode(sensorPin, INPUT_PULLUP);  // 設定紅外線感應器為輸入
  // attachInterrupt(digitalPinToInterrupt(sensorPin), countRpm, FALLING); // 當感應到下降沿時中斷

  delay(100);  // 等待伺服穩定
}

void loop() {
  unsigned long currentTime = millis();
  if (Serial.available() > 0) {
    char received = Serial.read();

    Serial.print("Updated received to: ");
    Serial.println(received);

    //                                  << Recieved Table >>
    //     __________________________________________________________________________________
    //    |   Xbox Button  | Recieved |          Control Servo        |        Command       |
    //    |----------------|----------|-------------------------------|----------------------|
    //    |       LB       |     1    |   frisbee_1F_1 & frisbee_1F_2 |   Turn a full circle |
    //    |       RB       |     2    |   frisbee_2F_1 & frisbee_2F_2 |   Turn a full circle |
    //    |        B       |     3    |                               |                      |
    //    |        X       |     4    |            Slide_2F           |     Open / Close     |
    //    |        Y       |     5    |            CameraY            |      相機向上轉       |
    //    |        A       |     6    |            CameraY            |      相機向下轉       |
    //    |________________|__________|_______________________________|______________________|
    // 
    
    if(received == '1'){
      frisbee_1F_1.attach(4);
      frisbee_1F_2.attach(5);
      frisbee_1F_1.writeMicroseconds(0);
      frisbee_1F_2.writeMicroseconds(0);
      delay(1225);
      frisbee_1F_1.detach();
      frisbee_1F_2.detach();
    } 

    else if(received == '2'){
      frisbee_2F_1.attach(18);
      frisbee_2F_2.attach(17);
      frisbee_2F_1.writeMicroseconds(2500);
      frisbee_2F_2.writeMicroseconds(0);
      delay(1225);
      frisbee_2F_1.detach();
      frisbee_2F_2.detach();
    } 

    else if(received == '3'){
      Slide_2F.write(90);
      Slide_2F_angle = 100;
    }

    else if(received == '4'){
      Slide_2F.write(10);
      Slide_2F_angle = 10;
    }

    else if(received == '5'){
      cameraY_angle -= 10;
      if (cameraY_angle < 0) {
        cameraY_angle = 0;
      }
      cameraY.write(cameraY_angle);
    }

    else if(received == '6'){
      cameraY_angle += 10;
      if (cameraY_angle > 180) {
        cameraY_angle = 180;
      }
      cameraY.write(cameraY_angle);
    }

    else if(received == '7'){
      frisbee_2F_1.attach(18);
      frisbee_2F_1.writeMicroseconds(2500);
      delay(50);
      frisbee_2F_1.detach();
    }

    else if(received == '8'){
      frisbee_1F_1.attach(4);
      frisbee_1F_1.writeMicroseconds(0);
      delay(50);
      frisbee_1F_1.detach();
    }

    else if(received == '9'){
      frisbee_1F_2.attach(5);
      frisbee_1F_2.writeMicroseconds(2500);
      delay(50);
      frisbee_1F_2.detach();
    }

    else if(received == 'a'){
      frisbee_1F_2.attach(5);
      frisbee_1F_2.writeMicroseconds(0);
      delay(50);
      frisbee_1F_2.detach();
    }
    else if(received == 'b'){
      launchservo.write(120);
      delay(150);
      launchservo.write(60);
      delay(500);
      launchservo.write(120);
      delay(500);

    }
    else if(received == 'c'){
      pwmValue += 20;
      if (pwmValue > 255) {
        pwmValue = 255;
      }
      analogWrite(pwmPin, pwmValue);  // 設定 PWM
      delay(2000);
    }
    else if(received == 'd'){
      pwmValue = 0;
      analogWrite(pwmPin, pwmValue);  // 設定 PWM
      delay(2000);
    }
    
  }
}

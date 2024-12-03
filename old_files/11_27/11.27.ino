/*
   輸入　推上層　推下層　發射　　　　上層擋板　鏡頭馬達　上層微調　下層微調
   代號　Ｕ　　　Ｄ　　　Ｌ　　　　　Ｆ　　　　Ｃ　　　　ｕ　　　　ｄ　　　
   備註　　　　　　　　　帶相機角度　　　　　　－１～１　　　　　　　　　　
*/

#include <Servo.h>   // 引入伺服馬達控制庫

/* === 腳位定義 === */

const int IR_Pin = 2;             // 紅外線感測器的腳位
const int pwmPin = 3;                  // PWM 訊號腳位
const int launchServoPin = 7;           // 發射伺服馬達腳位

const int cameraServoPin = 13;          // 相機伺服馬達腳位

const int slideServoPin = 9;     // 上層擋板伺服馬達腳位
const int UF_ServoPin = 18;   // 上層前方伺服馬達控制腳位
const int UB_ServoPin = 17;       // 上後伺服馬達腳位
const int DF_ServoPin = 4;      // 下前伺服馬達腳位
const int DB_ServoPin = 5;       // 下後伺服馬達腳位

/* === 參數定義 === */

const int launchServoInitAngle = 90;   // 發射伺服馬達起始角度
const int launchServoEndAngle = 30;     // 發射伺服馬達終止角度
const int slideServoInitAngle = 110;   // 二樓伺服馬達起始角度
const int slideServoEndAngle = 10;   // 二樓伺服馬達終止角度
const int cameraServoInitAngle = 90;   // 相機伺服馬達初始角度

const int cameraSpeed = 5;   // 相機伺服馬達轉速
const int cameraHigh = 75;  // 設定相機對準目標的高度（cm）
float kp = 0.5, ki = 0.05, kd = 0.1;  // PID 控制參數

/* === 狀態定義 === */

bool launchServoPark = true;      // 發射伺服馬達是否在起始位置
bool slideServoPark = true;  // 上層擋板伺服馬達是否在起始位置
bool launching = false;   // 發射狀態

/* === 全域變數 === */

volatile unsigned long lastInterruptTime = 0; // 上次中斷的時間
volatile unsigned long interruptInterval = 0;          // 兩次中斷的時間差（微秒）
unsigned int rpm = 0;         // 每分鐘轉速
unsigned long cameraLastMoveTime = 0;  // 上次更新時間
const int cameraMoveInterval = 10;  // 設定每次相機轉動的間隔時間（毫秒）
int cameraAngle = 0;  // 相機的角度
float previousError = 0, integral = 0;  // PID 控制中的誤差和積分項
int targetRPM = 0;   // 目標轉速

Servo UF_Servo, UB_Servo, DF_Servo, DB_Servo, slideServo, cameraServo, launchServo;  // 定義各伺服馬達對象

void setup() {
  Serial.begin(9600);  // 初始化串口通信，波特率設定為9600

  pinMode(pwmPin, OUTPUT);  // 設定PWM訊號腳為輸出模式
  pinMode(IR_Pin, INPUT_PULLUP);  // 設定紅外線感測器腳為輸入，並啟用內部上拉電阻

  attachInterrupt(digitalPinToInterrupt(IR_Pin), calculateCurrentRPM, FALLING);  // 設定紅外線腳的中斷觸發方式

  servoInit();  // 初始化所有伺服馬達
}

void loop() {
  unsigned long currentTime = millis();  // 取得當前時間（毫秒）

  if (Serial.available() > 0) {
    String OP = readString(); // 讀取串口輸入的命令字串

    // 處理推上層命令
    if (OP[0] == 'U') {
      UF_Servo.attach(UF_ServoPin);  // 附加上層前方伺服馬達
      UB_Servo.attach(UB_ServoPin);  // 附加上層後方伺服馬達
      UF_Servo.writeMicroseconds(2500);  // 設定上層前方伺服馬達到達指定位置
      UB_Servo.writeMicroseconds(0);    // 設定上層後方伺服馬達到達指定位置
      delay(1225);  // 延遲
      UF_Servo.detach();  // 解除附加
      UB_Servo.detach();  // 解除附加
    }

    // 處理推下層命令
    if (OP[0] == 'D') {
      DF_Servo.attach(DF_ServoPin);  // 附加下層前方伺服馬達
      DB_Servo.attach(DB_ServoPin);  // 附加下層後方伺服馬達
      DF_Servo.writeMicroseconds(0);   // 設定下層前方伺服馬達到達指定位置
      DB_Servo.writeMicroseconds(0);   // 設定下層後方伺服馬達到達指定位置
      delay(1225);  // 延遲
      DF_Servo.detach();  // 解除附加
      DB_Servo.detach();  // 解除附加
    }

    // 上層微調
    if (OP[0] == 'u') {
      UF_Servo.attach(UF_ServoPin);
      UF_Servo.writeMicroseconds(0);  // 設定上層前方伺服馬達微調
      delay(50);  // 延遲
      UF_Servo.detach();  // 解除附加
    }

    // 下層微調
    if (OP[0] == 'd') {
      DF_Servo.attach(DF_ServoPin);
      DF_Servo.writeMicroseconds(2500);  // 設定下層前方伺服馬達微調
      delay(50);  // 延遲
      DF_Servo.detach();  // 解除附加
    }

    // 處理發射命令
    if (OP[0] == 'L') {
      launching = true;  // 設定發射狀態
      cameraAngle = OP.substring(1).toFloat();  // 讀取相機角度
      targetRPM = calculateTargetRPM();  // 計算目標轉速
    }

    // 處理上層擋板控制命令
    if (OP[0] == 'F') {
      if (slideServoPark) {
        slideServo.write(slideServoInitAngle);  // 擋板設置為起始位置
      }
      else {
        slideServo.write(launchServoEndAngle);  // 擋板設置為發射位置
      }
      slideServoPark = !slideServoPark;  // 切換狀態
    }

    // 處理鏡頭控制命令
    if (OP[0] == 'C') {
      static int cameraCtrlAngle = 90;  // 設定相機控制角度的初始值
      static int previousCameraAngle = cameraServoInitAngle;  // 上次的相機角度
      if (currentTime - cameraLastMoveTime >= cameraMoveInterval) {  // 每隔一定時間更新一次相機角度
        cameraCtrlAngle += OP.substring(1).toFloat() * cameraSpeed;  // 根據輸入調整相機角度
        if (cameraCtrlAngle != previousCameraAngle) {
          cameraServo.write(constrain(cameraCtrlAngle, 0, 180));  // 設定相機角度
          previousCameraAngle = cameraCtrlAngle;  // 更新上次相機角度
        }
      }
    }

    // 處理發射控制
    if (launching) {
      // 如果當前RPM接近目標RPM的95%，進行發射
      int TargetRPM = calculateTargetRPM();
      if (rpm - TargetRPM < TargetRPM * 0.05) {
        launchServo.write(launchServoEndAngle);  // 設定發射伺服馬達至發射位置
        delay(500);  // 延遲500毫秒
        launchServo.write(launchServoInitAngle);  // 設定發射伺服馬達回到起始位置
        launching = false;
      }
      else {
        int x = PID();// 否則調用PID控制
        float Y = 112 + (-59.7 * x) + (3.14 * pow(x, 2)) + (-0.0367 * pow(x, 3)) + (0.000199 * pow(x, 4)) + (-0.000000528 * pow(x, 5)) + (0.000000000553 * pow(x, 6));
        if (rpm / Y > 0.75) { //還沒到轉速
          delay(100);
        }
        else {
          analogWrite(pwmPin, TargetRPM);
        }
      }
    }
    printStatus();
  }
}

/* === 副程式 === */

// 初始化伺服馬達
void servoInit() {
  UF_Servo.detach();
  UB_Servo.detach();
  DF_Servo.detach();
  DB_Servo.detach();
  slideServo.detach();
  cameraServo.detach();
  launchServo.detach();

  slideServo.attach(slideServoPin);  // 附加滑動伺服馬達
  cameraServo.attach(cameraServoPin);  // 附加相機伺服馬達
  launchServo.attach(launchServoPin);  // 附加發射伺服馬達

  slideServo.write(slideServoInitAngle);  // 設置伺服馬達初始位置
  cameraServo.write(cameraServoInitAngle);
  launchServo.write(launchServoInitAngle);

  delay(100);  // 初始化後延遲100毫秒
}

// 讀取串口輸入字串
String readString() {
  String result = "";
  while (Serial.available() > 0) {
    char c = Serial.read();  // 逐字讀取
    if (c == '\n') break;  // 碰到換行符結束讀取
    result += c;  // 加入結果字串
  }
  return result;
}

// 計算當前轉速
void calculateCurrentRPM() {
  unsigned long currentInterruptTime = micros();  // 取得當前中斷觸發時間
  interruptInterval = currentInterruptTime - lastInterruptTime;  // 計算兩次中斷間隔
  if (interruptInterval > 0) rpm = 60000000 / interruptInterval;  // 計算轉速
  lastInterruptTime = currentInterruptTime;  // 更新上次中斷時間
}

// 計算目標轉速
int calculateTargetRPM() {
  static int TargetRPM = 0;
  int D = cameraHigh * tan(radians(cameraAngle));  // 計算距離
  TargetRPM = D;
  return constrain(TargetRPM, 0, 255);  // 返回目標轉速（計算邏輯未實作完整）
}

// PID控制演算法
int PID() {
  float error = targetRPM - rpm;  // 計算誤差
  integral += error;  // 累加積分
  integral = constrain(integral, -1000, 1000);
  float derivative = error - previousError;  // 計算微分

  float output = kp * error + ki * integral + kd * derivative;  // 計算PID輸出
  previousError = error;  // 更新上次誤差

  int pwmOutput = map(output, 0, 5500, 0, 255);  // 將輸出值映射到PWM範圍
  pwmOutput = constrain(pwmOutput, 0, 255);  // 限制PWM範圍
  return pwmOutput;
}



/* === 狀態輸出函式 === */
void printStatus() {
  Serial.println("=== 系統狀態 ===");
  Serial.print("發射狀態: ");
  Serial.println(launching ? "發射中" : "閒置");

  Serial.print("上層擋板位置: ");
  Serial.println(slideServoPark ? "起始位置" : "發射位置");

  Serial.print("發射伺服馬達位置: ");
  Serial.println(launchServoPark ? "起始位置" : "發射位置");

  Serial.print("當前RPM: ");
  Serial.println(rpm);

  Serial.print("目標RPM: ");
  Serial.println(targetRPM);

  Serial.print("當前相機角度: ");
  Serial.println(cameraAngle);

  Serial.print("當前相機控制角度: ");
  Serial.println(cameraServo.read());

  Serial.print("PID誤差: ");
  Serial.println(targetRPM - rpm);

  Serial.print("PID積分項: ");
  Serial.println(integral);

  Serial.print("紅外線感測器中斷間隔 (微秒): ");
  Serial.println(interruptInterval);

  Serial.print("PWM輸出: ");
  Serial.println(analogRead(pwmPin));
  Serial.println("================");
}

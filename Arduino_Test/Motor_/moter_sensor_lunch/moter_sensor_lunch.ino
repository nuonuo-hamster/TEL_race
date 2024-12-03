#include <Servo.h>

const int pwmPin = 3;          // PWM 腳位
const int sensorPin = 2;       // 紅外線感應器數位輸入腳位
const int launchServoPin = 7;  // 發射伺服馬達的腳位

volatile unsigned long lastInterruptTime = 0; // 上次中斷的時間
volatile unsigned long interval = 0;          // 兩次中斷的時間差（微秒）
unsigned int rpm = 0;          // 每分鐘轉速
int pwmValue = 0;              // 預設 PWM 值
int distance = 0;              // 儲存輸入的第一位
float angle = 0.0;             // 儲存後方剩下的浮點數

const int launchServoInitAngle = 90;  // 發射伺服馬達起始角度
const int launchServoEndAngle = 30;  // 發射伺服馬達終止角度

const int cameraHigh = 75;  // 設定相機對準目標的高度（cm）
float kp = 0.5, ki = 0.05, kd = 0.1;  // PID 控制參數


int idlePWM = 100;  /* 不要設定出超過100 */// 初始化 PWM 設定
int targetRPM = 0;   // 目標轉速
float previousError = 0, integral = 0;  // PID 控制中的誤差和積分項
int OutPut = 0;


Servo launchServo;

void setup() {
  Serial.begin(9600);           // 啟動 Serial 通訊
  pinMode(pwmPin, OUTPUT);      // 設定 PWM 腳位為輸出
  pinMode(sensorPin, INPUT_PULLUP); // 設定紅外線感應器為輸入
  attachInterrupt(digitalPinToInterrupt(sensorPin), countRpm, FALLING); // 中斷觸發
  launchServo.attach(launchServoPin);  // 附加發射伺服馬達
  launchServo.write(launchServoInitAngle);

  analogWrite(pwmPin, 50);
  delay(5000);
  analogWrite(pwmPin, idlePWM);
}

void loop() {
  calculateRPM();  // 調用副程式計算 RPM

  if (Serial.available() > 0) {
    parseInput(distance, angle);   // 調用副程式解析輸入
    targetRPM = calculateTargetRPM();

    if (rpm < targetRPM) { //未達轉速 加速
      OutPut = PID() * rpm / targetRPM;
      analogWrite(pwmPin,  constrain(OutPut, 0, 255));
    }
    else {
      launchServo.write(launchServoInitAngle);
      delay(15);
      launchServo.write(launchServoEndAngle);
      delay(100);
      launchServo.write(launchServoInitAngle);
    }
    printParsedData(distance, angle);
  }
}

// 中斷處理函式
void countRpm() {
  unsigned long currentInterruptTime = micros(); // 獲取當前時間（微秒）
  interval = currentInterruptTime - lastInterruptTime; // 計算兩次中斷時間差
  lastInterruptTime = currentInterruptTime; // 更新上次中斷時間
}

// 計算 RPM 副程式
void calculateRPM() {
  if (interval > 0) {
    noInterrupts();                      // 暫停中斷，避免讀取時出現競態條件
    unsigned long tempInterval = interval; // 獲取最新的時間間隔
    interrupts();                        // 恢復中斷
    rpm = 60000000 / tempInterval;       // RPM = 每分鐘 (60,000,000 微秒) / 週期 (微秒)
  }
}

// 解析輸入數據
void parseInput(int &distance, float &angle) {
  String input = Serial.readStringUntil('\n');
  int dotIndex = input.indexOf('.'); // 找到小數點位置
  if (dotIndex > 0) {
    distance = input.substring(0, 1).toInt(); // 取第一位
    angle = input.substring(1).toFloat();    // 剩餘部分轉為浮點數
  } else {
    distance = 0;  // 如果格式錯誤，設定默認值
    angle = 0.0;
  }
}
// 計算目標轉速
int calculateTargetRPM() {
  static int TargetRPM = 0;
  const float g = 9.8;       // 重力加速度 (m/s^2)
  const float r = 0.0625;      // 內側滾輪半徑 (m)
  const float theta = 45.0;  // 發射角度 (度數)
  int h;
  if (distance == 1)h = 1.55;
  if (distance == 2)h = 1.95;
  if (distance == 3)h = 2.35;

  int d = cameraHigh * tan(radians(angle));  // 計算距離
  // 將角度轉換為弧度
  float thetaRad = radians(45);

  // 計算飛盤的初速度 v
  float cosTheta = cos(thetaRad);
  float tanTheta = tan(thetaRad);
  float v = sqrt((g * d * d) / (2 * cosTheta * cosTheta * (d * tanTheta - h)));

  // 計算滾輪轉速 (rad/s)
  float omega_r = v / r;

  // 將滾輪轉速轉換為 RPM
  float rpm = omega_r * 60 / (2 * PI);
  return rpm;
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
// 輸出解析數據
void printParsedData(const int &distance, const float &angle) {
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print("targetRPM: ");
  Serial.print(targetRPM);
  Serial.print("RPM: ");
  Serial.println(rpm);
}

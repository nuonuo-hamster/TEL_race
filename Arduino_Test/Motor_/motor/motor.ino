#include <PID_v1.h>

const int hallSensorPin = 2; // 霍爾傳感器的數位輸入
const int pwmOutputPin = 9;  // PWM輸出
const int encoderPPR = 20;   // 霍爾傳感器每轉發出多少脈衝（脈衝數每轉）
volatile unsigned long pulseCount = 0; // 脈衝計數
unsigned long lastTime = 0;
double rpm = 0;   // 實際轉速
double setpoint = 0; // 目標轉速
double input = 0;    // PID的輸入
double output = 0;   // PID的輸出（PWM占空比）

// PID參數
double Kp = 2.0, Ki = 5.0, Kd = 1.0;
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  pinMode(hallSensorPin, INPUT_PULLUP);
  pinMode(pwmOutputPin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), countPulse, RISING);
  
  Serial.begin(9600);
  
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255); // 限制PWM輸出範圍
}

void loop() {
  unsigned long currentTime = millis();
  
  // 計算轉速，每100ms更新一次
  if (currentTime - lastTime >= 100) {
    noInterrupts();
    unsigned long pulses = pulseCount;
    pulseCount = 0;
    interrupts();

    rpm = (pulses * 60000.0) / (encoderPPR * (currentTime - lastTime)); // 計算轉速
    lastTime = currentTime;

    input = rpm; // 更新PID的輸入
    
    // 使用PID計算PWM輸出
    myPID.Compute();
    
    analogWrite(pwmOutputPin, (int)output);
    
    // 顯示目標轉速、實際轉速及PWM輸出
    Serial.print("Setpoint: ");
    Serial.print(setpoint);
    Serial.print(" RPM, Actual: ");
    Serial.print(rpm);
    Serial.print(" RPM, PWM Output: ");
    Serial.println(output);
  }

  // 讀取用戶輸入
  if (Serial.available() > 0) {
    setpoint = Serial.parseFloat();
    Serial.print("New Setpoint: ");
    Serial.println(setpoint);
  }
}

void countPulse() {
  pulseCount++;
}

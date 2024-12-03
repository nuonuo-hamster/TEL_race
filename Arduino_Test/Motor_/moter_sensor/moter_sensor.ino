const int pwmPin = 3;         // PWM 腳位
const int sensorPin = 2;      // 紅外線感應器數位輸入腳位
volatile unsigned long lastInterruptTime = 0; // 上次中斷的時間
volatile unsigned long interval = 0;          // 兩次中斷的時間差（微秒）
unsigned int rpm = 0;         // 每分鐘轉速
int pwmValue = 0;             // 預設 PWM 值

void setup() {
  Serial.begin(9600);         // 啟動 Serial 通訊
  pinMode(pwmPin, OUTPUT);
  pinMode(sensorPin, INPUT_PULLUP);  // 設定紅外線感應器為輸入
  attachInterrupt(digitalPinToInterrupt(sensorPin), countRpm, FALLING); // 當感應到下降沿時中斷
}

void loop() {
  unsigned long currentTime = millis();

  // 計算 RPM
  if (interval > 0) {
    noInterrupts();  // 暫停中斷，避免讀取時出現競態條件
    unsigned long tempInterval = interval; // 獲取最新的時間間隔
    interrupts();       // 恢復中斷

    rpm = 60000000 / tempInterval; // RPM = 每分鐘 (60,000,000 微秒) / 週期 (微秒)
    Serial.print("RPM: ");
    Serial.println(rpm);
  }

  // 非阻塞方式讀取 Serial 輸入
  if (Serial.available() > 0) {
    char input = Serial.read();  // 讀取一個字元
    if (isDigit(input)) {        // 如果是數字字元
      pwmValue = pwmValue * 10 + (input - '0'); // 累加數字（適合多位數 PWM 輸入）
    } else if (input == '\n') {  // 讀到換行符號（輸入結束）
      if (pwmValue >= 0 && pwmValue <= 255) {
        analogWrite(pwmPin, pwmValue);  // 設定 PWM
      }
      pwmValue = 0; // 重置暫存的輸入值
    }
  }
}

// 中斷處理函式
void countRpm() {
  unsigned long currentInterruptTime = micros(); // 獲取當前時間（微秒）
  interval = currentInterruptTime - lastInterruptTime; // 計算兩次中斷時間差
  lastInterruptTime = currentInterruptTime; // 更新上次中斷時間
}

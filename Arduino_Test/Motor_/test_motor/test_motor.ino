// 馬達控制引腳
const int motor1PinA = 10;   // 馬達 1 的 PWM 控制引腳
const int motor1PinB = 11;  // 馬達 1 的方向控制引腳
const int motor2PinA = 12;  // 馬達 2 的 PWM 控制引腳
const int motor2PinB = 13;  // 馬達 2 的方向控制引腳
const int motor3PinA = 2;   // 馬達 3 的 PWM 控制引腳
const int motor3PinB = 3;   // 馬達 3 的方向控制引腳
const int motor4PinA = 4;   // 馬達 4 的 PWM 控制引腳
const int motor4PinB = 5;   // 馬達 4 的方向控制引腳

void setup() {
  // 設定為輸出引腳
  pinMode(motor1PinA, OUTPUT);
  pinMode(motor1PinB, OUTPUT);
  pinMode(motor2PinA, OUTPUT);
  pinMode(motor2PinB, OUTPUT);
  pinMode(motor3PinA, OUTPUT);
  pinMode(motor3PinB, OUTPUT);
  pinMode(motor4PinA, OUTPUT);
  pinMode(motor4PinB, OUTPUT);

  // 初始化串口通信
  Serial.begin(19200);
}

void loop() {
  if (Serial.available() > 0) {
    // 讀取來自 Python 的資料
    String input = Serial.readStringUntil('\n');
    
    // 分割數據 (格式：x_axis, y_axis, rotation)
    int commaIndex1 = input.indexOf(',');
    int commaIndex2 = input.indexOf(',', commaIndex1 + 1);
    
    String xStr = input.substring(0, commaIndex1);
    String yStr = input.substring(commaIndex1 + 1, commaIndex2);
    String rotationStr = input.substring(commaIndex2 + 1);

    float x = xStr.toFloat();       // 左搖桿的 X 軸
    float y = yStr.toFloat();       // 左搖桿的 Y 軸
    float rotation = rotationStr.toFloat(); // 右搖桿的 X 軸

    if x = y = rotation{
      analogWrite(motor1PinA, 255);
      analogWrite(motor2PinA, 255);
      analogWrite(motor3PinA, 255);
      analogWrite(motor4PinA, 255);

      digitalWrite(motor1PinB, motor1Speed < 0 ? HIGH : LOW);
      digitalWrite(motor2PinB, motor2Speed < 0 ? HIGH : LOW);
      digitalWrite(motor3PinB, motor3Speed < 0 ? HIGH : LOW);
      digitalWrite(motor4PinB, motor4Speed < 0 ? HIGH : LOW);
    }
    // 計算每個馬達的速度
    int motor1Speed = map(y + x + rotation, -2, 2, -255, 255);
    int motor2Speed = map(y - x - rotation, -2, 2, -255, 255);
    int motor3Speed = map(y - x + rotation, -2, 2, -255, 255);
    int motor4Speed = map(y + x - rotation, -2, 2, -255, 255);

    // 控制馬達速度 (前進或反向)
    analogWrite(motor1PinA, abs(motor1Speed));
    analogWrite(motor2PinA, abs(motor2Speed));
    analogWrite(motor3PinA, abs(motor3Speed));
    analogWrite(motor4PinA, abs(motor4Speed));

    // 根據速度設定方向 (如果速度為負，則反向)
    digitalWrite(motor1PinB, motor1Speed < 0 ? HIGH : LOW);
    digitalWrite(motor2PinB, motor2Speed < 0 ? HIGH : LOW);
    digitalWrite(motor3PinB, motor3Speed < 0 ? HIGH : LOW);
    digitalWrite(motor4PinB, motor4Speed < 0 ? HIGH : LOW);
  }
}

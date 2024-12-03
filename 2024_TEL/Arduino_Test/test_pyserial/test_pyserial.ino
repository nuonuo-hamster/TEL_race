void setup() {
  Serial.begin(9600); // 设置串口波特率与 Python 脚本中一致
}

void loop() {
  // 从串口接收数据
  if (Serial.available() > 0) {
    String received_data = Serial.readString();
    Serial.print("Received data: ");
    Serial.println(received_data);

    // 向 Python 脚本发送响应数据
    Serial.println("Hello Python!");
  }
}

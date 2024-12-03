// 定義輸入腳位範圍
//const int inputPins[] = {2,3,4,5,6,7,8,9,10,11,12,13};
//const int inputPins[] = {22,23,24,25,26,27,28,29,30,31,
//                         32,33,34,35,36,37,38,39,40,41};
const int inputPins[] = {42,43,44,45,46,47,48,49,50,51,
                         52,53};
const int numInputPins = sizeof(inputPins) / sizeof(inputPins[0]);

void setup() {
  // 設定輸入腳位為輸入模式
  for (int i = 0; i < numInputPins; i++) {
    pinMode(inputPins[i], INPUT);
  }

  // 設定內建LED為輸出模式
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  bool inputHigh = false;
  
  for (int i = 0; i < numInputPins; i++) {
    digitalWrite(inputPins[i], LOW);
  }
  
  // 檢查所有輸入腳位是否有HIGH訊號
  for (int i = 0; i < numInputPins; i++) {
    if (digitalRead(inputPins[i]) == HIGH) {
      inputHigh = true;
      break;
    }
  }

   //如果任意輸入腳位為HIGH，點亮內建LED
  if (inputHigh) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  // 為了防止過度快速的迴圈，加入短暫的延遲
  delay(50);
}

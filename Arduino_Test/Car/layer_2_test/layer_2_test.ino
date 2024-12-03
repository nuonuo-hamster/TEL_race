const int FL_DEC1 = 18;
const int FR_DEC1 = 19;
void setup() {
  
  pinMode(FL_DEC1, INPUT);
  pinMode(FR_DEC1, INPUT);

  attachInterrupt(digitalPinToInterrupt(FL_DEC1), encoderISR_FLA, RISING);
  attachInterrupt(digitalPinToInterrupt(FR_DEC1), encoderISR_FRA, RISING);
  Serial.begin(19200);  //設定通訊速率
  delay(500);  
}

int process_value_1 = 0;
int value_1 = 0;
int process_value_2 = 0;
int value_2 = 0;
void loop() {
  
  send_wheel_1();
  send_wheel_2();
  decoder_calculator();
  Serial.print(process_value_1);
  Serial.print(",");
  Serial.println(process_value_2);
}

unsigned long lastTime = 0; 
int FLa_state = 0, FLa_count = 0;
int FRa_state = 0, FRa_count = 0;
int FLa_old_count = 0;
int FRa_old_count = 0;
void encoderISR_FLA(){
  FLa_count++;
}
void encoderISR_FRA(){
  FRa_count++;
}
// 一段時間紀錄秒數
void decoder_calculator(){
    unsigned long currentTime = millis();
    if (currentTime - lastTime >= 100){
      FLa_old_count = FLa_count;
      FRa_old_count = FRa_count;
      FLa_count= 0;
      FRa_count= 0;
      lastTime = currentTime;
    }
    
}

void send_wheel_1(){
  process_value_1 = FLa_old_count;
}
void send_wheel_2(){
  process_value_2 = FRa_old_count;
}

const int pin_1_256 = 22;
const int pin_1_128 = 23;
const int pin_1_64 = 24;
const int pin_1_32 = 25;
const int pin_1_16 = 26;
const int pin_1_8 = 27;
const int pin_1_4 = 28;
const int pin_1_2 = 29;
const int pin_1_1 = 30;

const int pin_2_256 = 31;
const int pin_2_128 = 32;
const int pin_2_64 = 33;
const int pin_2_32 = 34;
const int pin_2_16 = 35;
const int pin_2_8 = 36;
const int pin_2_4 = 37;
const int pin_2_2 = 38;
const int pin_2_1 = 39;

const int FL_DEC1 = 18;
const int FR_DEC1 = 21;
void setup() {

  pinMode(pin_1_256,OUTPUT);
  pinMode(pin_1_128,OUTPUT);
  pinMode(pin_1_64,OUTPUT);
  pinMode(pin_1_32,OUTPUT);
  pinMode(pin_1_16,OUTPUT);
  pinMode(pin_1_8,OUTPUT);
  pinMode(pin_1_4,OUTPUT);
  pinMode(pin_1_2,OUTPUT);
  pinMode(pin_1_1,OUTPUT);
  pinMode(pin_2_256,OUTPUT);
  pinMode(pin_2_128,OUTPUT);
  pinMode(pin_2_64,OUTPUT);
  pinMode(pin_2_32,OUTPUT);
  pinMode(pin_2_16,OUTPUT);
  pinMode(pin_2_8,OUTPUT);
  pinMode(pin_2_4,OUTPUT);
  pinMode(pin_2_2,OUTPUT); 
  pinMode(pin_2_1,OUTPUT);
  pinMode(FL_DEC1, INPUT);
  pinMode(FR_DEC1, INPUT);
  digitalWrite(pin_1_256, LOW);
  digitalWrite(pin_1_128, LOW);
  digitalWrite(pin_1_64, LOW);
  digitalWrite(pin_1_32, LOW);
  digitalWrite(pin_1_16, LOW);
  digitalWrite(pin_1_8, LOW);
  digitalWrite(pin_1_4, LOW);
  digitalWrite(pin_1_2, LOW);
  digitalWrite(pin_1_1, LOW);

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
//  if(process_value_1==500){
//    process_value_1 = 0;
//   }
//  else process_value_1++;

  value_1 = process_value_1;

  if(value_1>255){
    digitalWrite(pin_1_256, HIGH);
    value_1 -= 256;
  }else digitalWrite(pin_1_256, LOW);
  if(value_1>127){
    digitalWrite(pin_1_128, HIGH);
    value_1 -= 128;
  }else digitalWrite(pin_1_128, LOW);
  if(value_1>63){
    digitalWrite(pin_1_64, HIGH);
    value_1 -= 64;
  }else digitalWrite(pin_1_64, LOW);
  if(value_1>31){
    digitalWrite(pin_1_32, HIGH);
    value_1 -= 32;
  }else digitalWrite(pin_1_32, LOW);
  if(value_1>15){
    digitalWrite(pin_1_16, HIGH);
    value_1 -= 16;
  }else digitalWrite(pin_1_16, LOW);
  if(value_1>7){
    digitalWrite(pin_1_8, HIGH);
    value_1 -= 8;
  }else digitalWrite(pin_1_8, LOW);
  if(value_1>3){
    digitalWrite(pin_1_4, HIGH);
    value_1 -= 4;
  }else digitalWrite(pin_1_4, LOW);
  if(value_1>1){
    digitalWrite(pin_1_2, HIGH);
    value_1 -= 2;
  }else digitalWrite(pin_1_2, LOW);
  if(value_1>0){
    digitalWrite(pin_1_1, HIGH);
    value_1 -= 1;
  }else digitalWrite(pin_1_1, LOW);
}
void send_wheel_2(){
  process_value_2 = FRa_old_count;
//  if(process_value_2==500){
//    process_value_2 = 0;
//   }
//  else process_value_2++;

  value_2 = process_value_2;

  if(value_2>255){
    digitalWrite(pin_2_256, HIGH);
    value_2 -= 256;
  }else digitalWrite(pin_2_256, LOW);
  if(value_2>127){
    digitalWrite(pin_2_128, HIGH);
    value_2 -= 128;
  }else digitalWrite(pin_2_128, LOW);
  if(value_2>63){
    digitalWrite(pin_2_64, HIGH);
    value_2 -= 64;
  }else digitalWrite(pin_2_64, LOW);
  if(value_2>31){
    digitalWrite(pin_2_32, HIGH);
    value_2 -= 32;
  }else digitalWrite(pin_2_32, LOW);
  if(value_2>15){
    digitalWrite(pin_2_16, HIGH);
    value_2 -= 16;
  }else digitalWrite(pin_2_16, LOW);
  if(value_2>7){
    digitalWrite(pin_2_8, HIGH);
    value_2 -= 8;
  }else digitalWrite(pin_2_8, LOW);
  if(value_2>3){
    digitalWrite(pin_2_4, HIGH);
    value_2 -= 4;
  }else digitalWrite(pin_2_4, LOW);
  if(value_2>1){
    digitalWrite(pin_2_2, HIGH);
    value_2 -= 2;
  }else digitalWrite(pin_2_2, LOW);
  if(value_2>0){
    digitalWrite(pin_2_1, HIGH);
    value_2 -= 1;
  }else digitalWrite(pin_2_1, LOW);
}

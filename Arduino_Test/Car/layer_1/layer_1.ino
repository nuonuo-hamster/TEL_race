//4:BR 2:FR 3:BL 1:FL
const int FL_PWM1 = 5;       //Weel_FL
const int FL_PWM2 = 6;
const int FL_DEC1 = 40;      //None
const int FL_DEC2 = 41;      //None
const int FL_ENA = 4;

const int FR_PWM1 = 7;       //Weel_FR 
const int FR_PWM2 = 8;
const int FR_DEC1 = 42;      //None
const int FR_DEC2 = 43;      //None
const int FR_ENA = 9;

const int BL_PWM1 = 11;       //Weel_BL 
const int BL_PWM2 = 12;
const int BL_DEC1 = 21;
const int BL_DEC2 = 44;      //None
const int BL_ENA = 10;
         
const int BR_PWM1 = 49;       //Weel_BR  
const int BR_PWM2 = 51;
const int BR_DEC1 = 2;
const int BR_DEC2 = 45;      //None
const int BR_ENA = 13;

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

void setup() 
{
  pinMode(FL_PWM1,OUTPUT);    
  pinMode(FL_PWM2,OUTPUT);
  pinMode(FR_PWM1,OUTPUT);
  pinMode(FR_PWM2,OUTPUT);
  pinMode(BL_PWM1,OUTPUT);
  pinMode(BL_PWM2,OUTPUT);
  pinMode(BR_PWM1,OUTPUT);
  pinMode(BR_PWM2,OUTPUT);
  pinMode(FL_DEC1, INPUT);
  pinMode(FL_DEC2, INPUT);
  pinMode(FR_DEC1, INPUT);
  pinMode(FR_DEC2, INPUT);
  pinMode(BL_DEC1, INPUT);
  pinMode(BL_DEC2, INPUT);
  pinMode(BR_DEC1, INPUT);
  pinMode(BR_DEC2, INPUT);
  pinMode(FL_ENA, INPUT);
  pinMode(FR_ENA, INPUT);
  pinMode(BL_ENA, INPUT);
  pinMode(BR_ENA, INPUT);
  
  pinMode(pin_1_256,INPUT);
  pinMode(pin_1_128,INPUT);
  pinMode(pin_1_64,INPUT);
  pinMode(pin_1_32,INPUT);
  pinMode(pin_1_16,INPUT);
  pinMode(pin_1_8,INPUT);
  pinMode(pin_1_4,INPUT);
  pinMode(pin_1_2,INPUT);
  pinMode(pin_1_1,INPUT);
  pinMode(pin_2_256,INPUT);
  pinMode(pin_2_128,INPUT);
  pinMode(pin_2_64,INPUT);
  pinMode(pin_2_32,INPUT);
  pinMode(pin_2_16,INPUT);
  pinMode(pin_2_8,INPUT);
  pinMode(pin_2_4,INPUT);
  pinMode(pin_2_2,INPUT);
  pinMode(pin_2_1,INPUT);
  
  digitalWrite(FL_PWM1, LOW);
  digitalWrite(FL_PWM2, LOW);
  digitalWrite(FR_PWM1, LOW);
  digitalWrite(FR_PWM2, LOW);
  digitalWrite(BL_PWM1, LOW);
  digitalWrite(BL_PWM2, LOW);
  digitalWrite(BR_PWM1, LOW);
  digitalWrite(BR_PWM2, LOW);

  // attachInterrupt(digitalPinToInterrupt(FL_DEC1), encoderISR_FLA, RISING);
  // attachInterrupt(digitalPinToInterrupt(FL_DEC2), encoderISR_FLB, RISING);
  // attachInterrupt(digitalPinToInterrupt(FR_DEC1), encoderISR_FRA, RISING);
  // attachInterrupt(digitalPinToInterrupt(FR_DEC2), encoderISR_FRB, RISING);
  attachInterrupt(digitalPinToInterrupt(BL_DEC1), encoderISR_BLA, RISING);
  // attachInterrupt(digitalPinToInterrupt(BL_DEC2), encoderISR_BLB, RISING);
  attachInterrupt(digitalPinToInterrupt(BR_DEC1), encoderISR_BRA, RISING);
  // attachInterrupt(digitalPinToInterrupt(BR_DEC2), encoderISR_BRB, RISING);
  Serial.begin(19200);
  delay(500);  
}

int value_1 = 0;
int value_2 = 0;
void loop() {

    //讀第二層arduino
    read_wheel_1(); //value_1
    read_wheel_2(); //value_2
//    print_layer_2();
    
    //收指令
    serialRecieve();
    movement();
    
    // 計算秒數
    decoder_calculator();
}

unsigned long lastTime = 0; 
int FLa_state = 0, FLb_state = 0, FLa_count = 0, FLb_count = 0;
int FRa_state = 0, FRb_state = 0, FRa_count = 0, FRb_count = 0;
int BLa_state = 0, BLb_state = 0, BLa_count = 0, BLb_count = 0;
int BRa_state = 0, BRb_state = 0, BRa_count = 0, BRb_count = 0;
int FLa_old_count = 0, FLb_old_count = 0;
int FRa_old_count = 0, FRb_old_count = 0;
int BLa_old_count = 0, BLb_old_count = 0;
int BRa_old_count = 0, BRb_old_count = 0;
//轉速interrunpt
void encoderISR_FLA(){
  FLa_count++;
}
void encoderISR_FLB(){
  FLb_count++;
}
void encoderISR_FRA(){
  FRa_count++;
}
void encoderISR_FRB(){
  FRb_count++;
}
void encoderISR_BLA(){
  BLa_count++;
}
void encoderISR_BLB(){
  BLb_count++;
}
void encoderISR_BRA(){
  BRa_count++;
}
void encoderISR_BRB(){
  BRb_count++;
}
// 一段時間紀錄秒數
void decoder_calculator(){
    unsigned long currentTime = millis();
    if (currentTime - lastTime >= 100){
      FLa_old_count = FLa_count;
      FRa_old_count = FRa_count;
      BLa_old_count = BLa_count;
      BRa_old_count = BRa_count;
      FLb_old_count = FLb_count;
      FRb_old_count = FRb_count;
      BLb_old_count = BLb_count;
      BRb_old_count = BRb_count;
      FLa_count = FLb_count = 0;
      FRa_count = FRb_count = 0;
      BLa_count = BLb_count = 0;
      BRa_count = BRb_count = 0;
      lastTime = currentTime;
    }
}
//傳送轉速
void print_RPM(){
    Serial.print(value_1); //
    Serial.print(",");
    Serial.print(FLb_old_count);
    Serial.print(",");
    Serial.print(value_2); //
    Serial.print(",");
    Serial.print(FRb_old_count);
    Serial.print(",");
    Serial.print(BLa_old_count); //
    Serial.print(",");
    Serial.print(BLb_old_count);
    Serial.print(",");
    Serial.print(BRa_old_count); //
    Serial.print(",");
    Serial.println(BRb_old_count);
}

const int BUFFER_SIZE = 5;
int data[BUFFER_SIZE];
int bufferPointer;
int peekByte;
//收指令
void serialRecieve(){
     if (Serial.available()) {

        peekByte = Serial.peek();
        
        if (peekByte == '$'){
            for (int i = 0; i < BUFFER_SIZE; i++){
              data[i] = -1;
            }
            Serial.read(); // delet #
            bufferPointer = 0;
        }
        
        else if (isDigit(peekByte)){
            if(bufferPointer < BUFFER_SIZE){
                data[bufferPointer] = Serial.parseInt();
                bufferPointer ++;
            }
        }
        
        else if (peekByte == 10){
//          Serial.print("Received data ");
//          Serial.print(":");
          for (int i = 0; i < BUFFER_SIZE; i++){
              if (data[i] != -1) {
//                  Serial.print(' ');
//                  Serial.print(data[i]);
              }
          }
          //Serial.println();
          Serial.read(); // delet $
        }
        
        else Serial.read();
    }
}

//pid
class PID {
private:
    double kp;          // 比例增益
    double ki;          // 積分增益
    double kd;          // 微分增益
    double prev_error;  // 前一次誤差
    double integral;    // 積分累積
    double max_output;  // 最大輸出值
    double min_output;  // 最小輸出值

public:
    // 建構函式初始化
    PID(double kp, double ki, double kd, double max_output = 255, double min_output = 0) 
        : kp(kp), ki(ki), kd(kd), max_output(max_output), min_output(min_output), prev_error(0), integral(0) {}

    // 計算 PID 輸出
    double calculate(double setpoint, double current_value) {
        // 計算誤差
        double error = setpoint - current_value;

        // 比例項
        double proportional = kp * error;

        // 積分項
        integral += error;
        double integral_term = ki * integral;

        // 微分項
        double derivative = kd * (error - prev_error);

        // 總輸出
        double output = proportional + integral_term + derivative;

        // 限制輸出範圍
        if (output > max_output) output = max_output;
        if (output < min_output) output = min_output;

        // 更新前一次誤差
        prev_error = error;

        return output;
    }

    // 重置 PID 狀態
    void reset() {
        prev_error = 0;
        integral = 0;
    }
};
PID motor_pid_1(0.2, 0.002, 0, 255, 90); // PID 參數：kp, ki, kd, 最大輸出, 最小輸出
PID motor_pid_2(0.2, 0.002, 0, 255, 90); // PID 參數：kp, ki, kd, 最大輸出, 最小輸出
PID motor_pid_3(0.2, 0.002, 0, 255, 90); // PID 參數：kp, ki, kd, 最大輸出, 最小輸出
PID motor_pid_4(0.2, 0.002, 0, 255, 90); // PID 參數：kp, ki, kd, 最大輸出, 最小輸出
int pid_1_Option = 0;
int pid_2_Option = 0;
int pid_3_Option = 0;
int pid_4_Option = 0;
int motor_1_rpm = 0;
int motor_2_rpm = 0;
int motor_3_rpm = 0;
int motor_4_rpm = 0;
int temp_2_pwm = 0;
//移動or傳送轉速
void movement() 
{
  if(data[0] == 5){
    print_RPM();
    data[0] = -1;
  }
  if(data[0] == 1){
      if(pid_1_Option != data[1]){
        motor_pid_1.reset();
      }
      pid_1_Option = data[1];
      motor_1_rpm = data[2];
  }
  if(data[0] == 2){
      if(pid_2_Option != data[1]){
        motor_pid_2.reset();
      }
      pid_2_Option = data[1];
      motor_2_rpm = data[2];
  }
  if(data[0] == 3){
    if(pid_3_Option != data[1]){
      motor_pid_3.reset();
    }
    pid_3_Option = data[1];
    motor_3_rpm = data[2];
  }
  if(data[0] == 4){
    if(pid_4_Option != data[1]){
      motor_pid_4.reset();
    }
    pid_4_Option = data[1];
    motor_4_rpm = data[2];
  }

  // 編碼器當前RPM == FLa_old_count
  double pwm_1 = motor_pid_1.calculate(motor_1_rpm, value_1); // 計算新的 PWM 值
  // temp_2_pwm = pwm_1; //*********************************** 
//  Serial.println(FLa_old_count);
//     Serial.println(pwm_1);
  // 將 PWM 信號輸出到馬達
  if(pid_1_Option == 1) Forward(FL_PWM1, FL_PWM2, FL_ENA, pwm_1);
  else if(pid_1_Option == 2) Back(FL_PWM1, FL_PWM2, FL_ENA, pwm_1);
  else if(pid_1_Option == 0) Stop(FL_PWM1, FL_PWM2, FL_ENA);
  
  // 編碼器當前RPM == FRa_old_count
  double pwm_2 = motor_pid_2.calculate(motor_2_rpm, value_2); // 計算新的 PWM 值
  // Serial.println(FRa_old_count);
  // 將 PWM 信號輸出到馬達
  // pwm_2 = temp_2_pwm; //***********************************
  if(pid_2_Option == 1) Forward(FR_PWM1, FR_PWM2, FR_ENA, pwm_2);
  else if(pid_2_Option == 2) Back(FR_PWM1, FR_PWM2, FR_ENA, pwm_2);
  else if(pid_2_Option == 0) Stop(FR_PWM1, FR_PWM2, FR_ENA);

  // 編碼器當前RPM == BLa_old_count
  double pwm_3 = motor_pid_3.calculate(motor_3_rpm, BLa_old_count); // 計算新的 PWM 值
  // Serial.println(BLa_old_count);
  // 將 PWM 信號輸出到馬達
  if(pid_3_Option == 1) Forward(BL_PWM1, BL_PWM2, BL_ENA, pwm_3);
  else if(pid_3_Option == 2) Back(BL_PWM1, BL_PWM2, BL_ENA, pwm_3);
  else if(pid_3_Option == 0) Stop(BL_PWM1, BL_PWM2, BL_ENA);

  // 編碼器當前RPM == BRa_old_count
  double pwm_4 = motor_pid_4.calculate(motor_4_rpm, BRa_old_count); // 計算新的 PWM 值
  // Serial.println(BRa_old_count);
  // 將 PWM 信號輸出到馬達
  if(pid_4_Option == 1) Forward(BR_PWM1, BR_PWM2, BR_ENA, pwm_4);
  else if(pid_4_Option == 2) Back(BR_PWM1, BR_PWM2, BR_ENA, pwm_4);
  else if(pid_4_Option == 0) Stop(BR_PWM1, BR_PWM2, BR_ENA);
}
void Forward(int IN1, int IN2, int ENA, int spd)
{   
    analogWrite(IN1, 255);
    analogWrite(IN2, 0);
    analogWrite(ENA, spd);
} 
void Back(int IN1, int IN2, int ENA, int spd)
{
    analogWrite(IN1, 0);
    analogWrite(IN2, 255);
    analogWrite(ENA, spd);
} 
void Stop(int IN1, int IN2, int ENA)
{
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
    analogWrite(ENA, 0);
}

void read_wheel_1(){
  value_1 = 0;
  if(digitalRead(pin_1_256)==HIGH) value_1+=256;
  if(digitalRead(pin_1_128)==HIGH) value_1+=128;
  if(digitalRead(pin_1_64)==HIGH) value_1+=64;
  if(digitalRead(pin_1_32)==HIGH) value_1+=32;
  if(digitalRead(pin_1_16)==HIGH) value_1+=16;
  if(digitalRead(pin_1_8)==HIGH) value_1+=8;
  if(digitalRead(pin_1_4)==HIGH) value_1+=4;
  if(digitalRead(pin_1_2)==HIGH) value_1+=2;
  if(digitalRead(pin_1_1)==HIGH) value_1+=1;
}
void read_wheel_2(){
  value_2 = 0;
  if(digitalRead(pin_2_256)==HIGH) value_2+=256;
  if(digitalRead(pin_2_128)==HIGH) value_2+=128;
  if(digitalRead(pin_2_64)==HIGH) value_2+=64;
  if(digitalRead(pin_2_32)==HIGH) value_2+=32;
  if(digitalRead(pin_2_16)==HIGH) value_2+=16;
  if(digitalRead(pin_2_8)==HIGH) value_2+=8;
  if(digitalRead(pin_2_4)==HIGH) value_2+=4;
  if(digitalRead(pin_2_2)==HIGH) value_2+=2;
  if(digitalRead(pin_2_1)==HIGH) value_2+=1;
}
void print_layer_2(){
  Serial.print(value_1);
  Serial.print(",");
  Serial.println(value_2);
}
    

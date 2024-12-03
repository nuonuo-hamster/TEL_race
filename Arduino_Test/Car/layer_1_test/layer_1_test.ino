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

void setup() {

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
  
  Serial.begin(19200);  //設定通訊速率
}

int value_1 = 0;
int value_2 = 0;
void loop() {

  read_wheel_1();
  read_wheel_2();
  Serial.print(value_1);
  Serial.print(",");
  Serial.println(value_2);
  delay(100); 
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

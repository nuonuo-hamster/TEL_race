const int reset_pin = 52;

const int Weel_FL = 1;
const int Weel_FR = 2;
const int Weel_BL = 3;
const int Weel_BR = 4;
const int Weel_L = 5;
const int Weel_R = 6;

const int IN1_1 = 10;       //Weel_FL
const int IN1_2 = 11;         
const int IN1_3 = 12;       //Weel_FR 
const int IN1_4 = 13;

const int IN2_1 = 2;       //Weel_BL
const int IN2_2 = 3;         
const int IN2_3 = 4;       //Weel_BR  
const int IN2_4 = 5;

const int IN3_1 = 6;      //Weel_L
const int IN3_2 = 7;         
const int IN3_3 = 8;      //Weel_R    
const int IN3_4 = 9;

const int BUFFER_SIZE = 5;
int data[BUFFER_SIZE];
int bufferPointer;
int peekByte;

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
          Serial.print("Received data ");
          Serial.print(":");
          for (int i = 0; i < BUFFER_SIZE; i++){
              if (data[i] != -1) {
                  Serial.print(' ');
                  Serial.print(data[i]);
              }
          }
          Serial.println();
          Serial.read(); // delet $
        }
        
        else Serial.read();
    }
}

void setup() 
{
  Serial.begin(9600); 

  digitalWrite(reset_pin, HIGH);
  pinMode(reset_pin, OUTPUT);  
 
  pinMode(IN1_1,OUTPUT);    
  pinMode(IN1_2,OUTPUT);
  pinMode(IN1_3,OUTPUT);
  pinMode(IN1_4,OUTPUT);
  digitalWrite(IN1_1, LOW);
  digitalWrite(IN1_2, LOW);
  digitalWrite(IN1_3, LOW);
  digitalWrite(IN1_4, LOW);
  
  pinMode(IN2_1,OUTPUT);
  pinMode(IN2_2,OUTPUT);
  pinMode(IN2_3,OUTPUT);
  pinMode(IN2_4,OUTPUT);
  digitalWrite(IN2_1, LOW);
  digitalWrite(IN2_2, LOW);
  digitalWrite(IN2_3, LOW);
  digitalWrite(IN2_4, LOW);
  
  pinMode(IN3_1,OUTPUT);
  pinMode(IN3_2,OUTPUT);
  pinMode(IN3_3,OUTPUT);
  pinMode(IN3_4,OUTPUT);
  digitalWrite(IN3_1, LOW);
  digitalWrite(IN3_2, LOW);
  digitalWrite(IN3_3, LOW);
  digitalWrite(IN3_4, LOW);
  
  delay(500);  
}

void loop() {
    serialRecieve();

    if(data[0] == -2){
      digitalWrite(reset_pin, LOW);
    }
    
    if(data[0] == 1){
        if(data[1] == 1) Forward(IN1_1, IN1_2, data[2]);
        else if(data[1] == 2) Back(IN1_1, IN1_2, data[2]);
        else if(data[1] == 0) Stop(IN1_1, IN1_2);
    }
    if(data[0] == 2){
        if(data[1] == 1) Forward(IN1_3, IN1_4, data[2]);
        else if(data[1] == 2) Back(IN1_3, IN1_4, data[2]);
        else if(data[1] == 0) Stop(IN1_3, IN1_4);
    }
    if(data[0] == 3){
        if(data[1] == 1) Forward(IN2_1, IN2_2, data[2]);
        else if(data[1] == 2) Back(IN2_1, IN2_2, data[2]);
        else if(data[1] == 0) Stop(IN2_1, IN2_2);
    }
    if(data[0] == 4){
        if(data[1] == 1) Forward(IN2_3, IN2_4, data[2]);
        else if(data[1] == 2) Back(IN2_3, IN2_4, data[2]);
        else if(data[1] == 0) Stop(IN2_3, IN2_4);
    }
    if(data[0] == 5){
        if(data[1] == 1) Forward(IN3_1, IN3_2, data[2]);
        else if(data[1] == 2) Back(IN3_1, IN3_2, data[2]);
        else if(data[1] == 0) Stop(IN3_1, IN3_2);
    }
    if(data[0] == 6){
        if(data[1] == 1) Forward(IN3_3, IN3_4, data[2]);
        else if(data[1] == 2) Back(IN3_3, IN3_4, data[2]);
        else if(data[1] == 0) Stop(IN3_3, IN3_4);
    }
}

void Forward(int IN1, int IN2, int spd)
{   
    analogWrite(IN1, spd);
    analogWrite(IN2, 0);
} 

void Back(int IN1, int IN2, int spd)
{
    analogWrite(IN1, 0);
    analogWrite(IN2, spd);
} 

void Stop(int IN1, int IN2)
{
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
}

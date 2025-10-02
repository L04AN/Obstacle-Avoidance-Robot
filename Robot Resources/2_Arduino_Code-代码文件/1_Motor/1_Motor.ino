/*
  ESP8266 car ino v2.00
  Date: 2023.6.31
  Author: Ajay Huajian
  2023 Copyright(c) ZHIYI Technology Inc. All right reserved
*/

//Line order test function of trolley wheel
#define IN_1  0            // L9110S B-1A motors Left       GPIO0 (D8)
#define IN_2  4            // L9110S B-1B motors Left       GPIO4 (D4)
#define IN_3  13           // L9110S A-1A motors Right      GPIO13(D7)
#define IN_4  12           // L9110S A-2A motors Right      GPIO12(D6)

int speedCar =180;
//Function initialization
void setup() 
{
  Serial.begin(115200);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT); 
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
}

//Principal function
void loop()
{
  Forward();            //Car forward
  delay(2000);          
  Backward();           //Car back
  delay(2000);          
  TurnLeft();           //Car turnleft
  delay(2000);          
  TurnRight();          //Car turnright
  delay(2000);          
  Stop();               //Car stop
  delay(1000);          //delayed
}

void Forward(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar+10);//当小车前进或后退走不直时可以修改参数来调节：speedCar+10相比原来的速度增加了10个单位，可以让小车往右调节一些。
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
}

void Backward(){
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speedCar);
}

void TurnLeft(){
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
}

void TurnRight(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speedCar);
}
void Stop()
{
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

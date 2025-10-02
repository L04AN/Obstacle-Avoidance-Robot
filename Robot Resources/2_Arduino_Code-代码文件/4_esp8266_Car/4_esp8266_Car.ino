/*
  ESP8266 car ino v2.00
  Date: 2023.8.31
  Author: Ajay Huajian
  2023 Copyright(c) ZHIYI Technology Inc. All right reserved
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define IN_1  0            // L9110S B-1A motors Left       GPIO0 (D8)
#define IN_2  4            // L9110S B-1B motors Left       GPIO4 (D4)
#define IN_3  13           // L9110S A-1A motors Right      GPIO13(D7)
#define IN_4  12           // L9110S A-2A motors Right      GPIO12(D6)

String command;             //String to store app command state.
int speedCar = 200;         // 0~255.
int speed_low = speedCar/1.5;

const char* ssid = "ZY ESP8266 Car"; //name
ESP8266WebServer server(80);

void setup() { 
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT); 
  Serial.begin(115200);
  
  // Connecting WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.println("AP IP address: ");
  Serial.println(myIP);
 
  // Starting WEB-server 
  server.on ( "/", HTTP_handleRoot );
  server.onNotFound ( HTTP_handleRoot );
  server.begin();    
}

void Forward(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar+10);//当小车前进或后退走不直时可以修改参数来调节：speedCar+10相比原来的速度增加了10个单位，可以让小车往右调节一些。
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
  Serial.println("前进");
}

void Backward(){
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speedCar);
  Serial.println("后退");
}

void TurnLeft(){
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
  Serial.println("左转");
}

void TurnRight(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speedCar);
  Serial.println("右转");
}

void goAheadLeft(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speed_low);
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
  Serial.println("左上");
}

void goAheadRight(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar);
  analogWrite(IN_3, speed_low+10);
  digitalWrite(IN_4, LOW);
  Serial.println("右上");
}

void goBackLeft(){ 
  analogWrite(IN_1, speed_low);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speedCar);
  Serial.println("左下");
}

void goBackRight(){ 
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speed_low+20);
  Serial.println("右下");
}

void Stop(){  
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

void loop() {
  server.handleClient();
  command = server.arg("State");
  if (command == "F") Forward();
  else if (command == "B") Backward();
  else if (command == "L") TurnLeft();
  else if (command == "R") TurnRight();
  else if (command == "I") goAheadRight();
  else if (command == "G") goAheadLeft();
  else if (command == "J") goBackRight();
  else if (command == "H") goBackLeft();
  else if (command == "0") speedCar = 165;
  else if (command == "1") speedCar = 175;
  else if (command == "2") speedCar = 185;
  else if (command == "3") speedCar = 195;
  else if (command == "4") speedCar = 205;
  else if (command == "5") speedCar = 215;
  else if (command == "6") speedCar = 225;
  else if (command == "7") speedCar = 235;
  else if (command == "8") speedCar = 245;
  else if (command == "9") speedCar = 255;
  else if (command == "S") Stop();
}

void HTTP_handleRoot(void) {
  if( server.hasArg("State") ){
    Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}

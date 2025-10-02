//2023.6.7
#define Trig 2   //GPIO2  (D9)
#define Echo 15  //GPIO15 (D10)
float distance;
float cm;

//Line order test function of trolley wheel
#define IN_1 0   // L9110S B-1A motors Left       GPIO0 (D8)
#define IN_2 4   // L9110S B-1B motors Left       GPIO4 (D4)
#define IN_3 13  // L9110S A-1A motors Right      GPIO13(D7)
#define IN_4 12  // L9110S A-2A motors Right      GPIO12(D6)
int speedCar = 180;

#include <Servo.h>
#define ServoPin 5  // ServoPin Input pin         GPIO0(D3)
float leftDis;
float rightDis;
Servo myservo;  // create servo object to control a servo

//Program initialization
void setup() {
  Serial.begin(115200);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  // Define ultrasonic sensor pins
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  // attaches the servo on GPIO5 to the servo object
  myservo.attach(ServoPin, 700, 2400);
  myservo.write(90);
  Stop();
}

//Principal function
void loop() {
  avoidance(20);  //In brackets is the obstacle avoidance distance in cm
}

/*
Function: obtain ultrasonic sensor ranging data
Parameters: Trig, Echo
Parameter description: sensor connected to the motherboard pin port 9,10
Trig -------> pin 9
Echo -------> pin 10
*/

float GetDistance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  distance = pulseIn(Echo, HIGH) / 58.00;
  return distance;  //Return distance
}

void Forward() {
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar + 10);  //当小车前进或后退走不直时可以修改参数来调节：speedCar+10相比原来的速度增加了10个单位，可以让小车往右调节一些。
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
}

void Backward() {
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speedCar);
}

void TurnLeft() {
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
    Serial.println("TurnLeft");
}

void TurnRight() {
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speedCar);
    Serial.println("TurnRight");
}

void Stop() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

/*
* Function: Obstacle avoidance
* Parameter: set_dis sets the obstacle avoidance distance
*/
void avoidance(int set_dis) {
  myservo.write(90);  //Steering engine back to center
  //Obtain the distance between the cart and the obstacle and store it in cm
  cm = GetDistance();
  // Serial.print("cm = ");
  // Serial.println(cm);
  if (cm <= set_dis) {
    Stop();                   //Stop the car
    delay(200);
    myservo.write(140);
    delay(500);
    leftDis = GetDistance();  // Measure the distance between the left obstacle and the car, and store the measurement data in leftDis
    // Serial.print("leftDis = ");
    // Serial.println(leftDis);
    myservo.write(90);
    delay(100);
    myservo.write(40);
    delay(500);
    rightDis = GetDistance();  // Record the range data on the right side of the trolley
    // Serial.print("rightDis = ");
    // Serial.println(rightDis);
    myservo.write(90);

    //The right is more distant from the obstacle than the Left
    if (leftDis < rightDis) {
      if (rightDis < 10) {
        Backward();
        delay(300);
        TurnRight();
        delay(200);
      } else {
        TurnRight();
        delay(200);
      }
    }
    //The left is more distant from the obstacle than the Right
    else if (leftDis > rightDis) {
      if (leftDis < 10) {
        Backward();
        delay(300);
        TurnLeft();
        delay(200);
      } else {
        TurnLeft();
        delay(200);
      }
    }
  } else {
    Forward();
  }
}
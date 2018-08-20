#include "IBT.h"
#include "L298.h"
#include "Sonar.h"

#define DEBUG 2
#define AUTO 0
#define MANUAL 1
#define MANUAL_IK 2


#define BASE 0
#define ACT1 1
#define ACT2 2
#define ROLL 3
#define PITCH 4
#define WRIST 5
#define GRABBER 6


//8 channel receiver
int ch[8];

// for parsing serial data -- autonomous mode
String IncomingData = "";
String Temp = "";
char var;
char dir;
int num1, num2, num3;

IBT base(12, 12);
IBT act1(6, 7);
IBT act2(8, 9);
IBT roll(4, 5);
IBT pitch(10, 11);
IBT wrist(12, 12);
IBT grabber(12, 12);
Sonar sonar_act1(22, 23);
Sonar sonar_act2(24, 25);

// present coordinates of end effector
int x, y, z;

void setup()
{

  Serial.begin(9600);
  //receiver setup
  for (int i = 0; i < 8; i++)
  {
    ch[i] = 39 + 2 * i;
    pinMode(ch[i], INPUT);
  }
  x = 30;
  y = 0;
  z = -50;
}

int mode;
void loop()
{
  //  mode = get_mode();
  // mode = MANUAL;
  // if (mode == AUTO)
  // {
  //   automate();
  // }
  // else {
  //   handle_rf();
  // }

  test();
}

void test()
{
  
  //  delay(100);
//  armtest();
  only_rf_full();
  sonar_test();
  //  display_feedbacks();
}


void display_feedbacks()
{

}

void armtest()
{
  while (Serial.available())
  {
    char c = Serial.read();
    if (c == 'q')
      pitch.rotPos(150);
    if (c == 'z')
      pitch.rotNeg(150);
    if (c == 'a')
      pitch.stop();

    if (c == 'w')
      roll.rotPos(150);
    if (c == 'x')
      roll.rotNeg(150);
    if (c == 's')
      roll.stop();

    if (c == 'e')
      act2.rotPos(250);
    if (c == 'c')
      act2.rotNeg(250);
    if (c == 'd')
      act2.stop();

    if (c == 'r')
      act1.rotPos(250);
    if (c == 'v')
      act1.rotNeg(250);
    if (c == 'f')
      act1.stop();
  }
}

void get_data_from_serial()
{
  if (Serial.available())
  {
    //    delayMicroseconds(10);
    delay(10);
    while (Serial.available())
    {
      var = Serial.read();
      if (var == '\n')
      {
        while (Serial.available())
          var = Serial.read();
        break;
      }
      IncomingData += String(var);
    }
    Serial.println(IncomingData);
    dir = (char)IncomingData[0];
    num1 = IncomingData.substring(0, 4).toInt();
    num2 = IncomingData.substring(4, 8).toInt();
    num3 = IncomingData.substring(8, 12).toInt();
    x = num1;
    y = num2;
    z = num3;
    Serial.print("x : ");
    Serial.print(x);
    Serial.print(" y : ");
    Serial.print(y);
    Serial.print(" z : ");
    Serial.println(z);
    while (Serial.available())
      var = Serial.read();
    IncomingData = "";
  }
}

double get_angle(int angle_num)
{
  double angle;
  switch (angle_num)
  {
    case 1:
      //get angle from the POT
      angle = base_angle();
      break;
    case 2:
      //get angle from the SONAR
      break;
    case 3:
      //get angle from the SONAR
      //return that
      break;
    case 4:
      //get angle using C1 C2
      //return that
      break;
  }
  return angle;
}

double base_angle()
{
  return 0.0;
}










// #define trigPin 22
// #define echoPin 23

// void setup()
// {
//   Serial.begin(9600);
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);
// }
// void loop()
// {
//   sonar();
//   delay(100);
// }
// int sonar()
// {
//   long duration, distance;
//   digitalWrite(trigPin, LOW);  // Added this line
//   delayMicroseconds(2); // Added this line
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10); // Added this line
//   digitalWrite(trigPin, LOW);
//   duration = pulseIn(echoPin, HIGH, 4000);
//   distance = (duration / 2) / 29.1;
//   Serial.println(duration);
//   if (distance >= 200 || distance <= 0)return distance;
//   else return -1;
// }





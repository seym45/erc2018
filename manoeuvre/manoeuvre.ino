#include "IBT.h"
#include "L298.h"

// Macro debug def
#define ARM_DEBUG

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

// 12 v realy pins
#define RELAY_12V_CH1 31
#define RELAY_12V_CH2 33
#define RELAY_12V_CH3 35
#define RELAY_12V_CH4 37

// 24 relay pins
#define RELAY_24V_CH1 23
#define RELAY_24V_CH2 25
#define RELAY_24V_CH3 27
#define RELAY_24V_CH4 29
//8 channel receiver
int ch[8];
// 12 volts
IBT base(12, 13);       // wiper on base
IBT act1wrist360(6, 7); // actuator1 and wrist360
IBT act2(2, 3);         // actuator2
IBT rpg(4, 5);          // roll pitch grabber in a single relay

// for parsing serial data -- autonomous mode
String IncomingData = "";
String Temp = "";
char var;
char dir;
int num1, num2, num3;
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
  setup_relays();
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
  // int del = 1000;
  // rpg.rotPos(150);
  // delay(del);
  // rpg.rotPos(0);
  // delay(del);
  // rpg.rotNeg(150);
  // delay(del);
  // rpg.rotNeg(0);
  //  armtest();
  only_rf_full();
  // reciever_test();
  //  display_feedbacks();
}

void display_feedbacks()
{
}

// void armtest()
// {
//   while (Serial.available())
//   {
//     char c = Serial.read();
//     if (c == 'q')
//       pitch.rotPos(150);
//     if (c == 'z')
//       pitch.rotNeg(150);
//     if (c == 'a')
//       pitch.stop();

//     if (c == 'w')
//       roll.rotPos(150);
//     if (c == 'x')
//       roll.rotNeg(150);
//     if (c == 's')
//       roll.stop();

//     if (c == 'e')
//       act2.rotPos(250);
//     if (c == 'c')
//       act2.rotNeg(250);
//     if (c == 'd')
//       act2.stop();

//     if (c == 'r')
//       act1.rotPos(250);
//     if (c == 'v')
//       act1.rotNeg(250);
//     if (c == 'f')
//       act1.stop();
//   }
// }

void get_data_from_serial()
{
  if (Serial.available())
  {
    //    delayMicroseconds(10);
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
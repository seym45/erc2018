#include "IBT.h"
#include <SBUS.h>
// Macro debug def
#define ARM_DEBUG
#define WHEEL_DEBUG
#define DEBUG

#define AUTO 0
#define MANUAL 1
#define MANUAL_IK 2

#define RC_SENSITIVITY_THRESHOLD 40
#define RC_CHANNEL_FLAG 9

#define BASE 0
#define ACT1 1
#define ACT2 2
#define ROLL 3
#define PITCH 4
#define WRIST 5
#define GRABBER 6
#define FOWARD_BACKWARD 7
#define LEFT_RITGHT 8
#define LEFT_RITGHT 8

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

IBT base(12, 13);         // wiper on base
IBT act1wrist360(10, 11); // actuator1 and wrist360
IBT act2(14, 15);         // actuator2
IBT rpg(8, 9);            // roll pitch grabber in a single relay
IBT left(12, 12);
IBT right(12, 12);

SBUS sbus(Serial3);
int mode;                       // mannual auto semi_auto serial
String inputString = "";        // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete

void setup()
{
  Serial.begin(57600);
  sbus.begin(true);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  //receiver setup
  setup_relays();
}

ISR(TIMER2_COMPA_vect)
{
  sbus.process();
}

void loop()
{
  test();
}

void test()
{
  // only_rf_full();
  // only_serial_full();
  // reciever_test();
// print the string when a newline arrives:
  if (stringComplete)
  {
    Serial.println(inputString);
    handle_serial(inputString)
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

}


/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent()
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }
}

// void serialevent()
// {
//   if (Serial.available())
//   {
//    while (Serial.available())
//     {
//       var = Serial.read();
//       if (var == '\n')
//       {
//         while (Serial.available())
//           var = Serial.read();
//         break;
//       }
//       IncomingData += String(var);
//     }
//     Serial.println(IncomingData);
//     dir = (char)IncomingData[0];
//     num1 = IncomingData.substring(0, 4).toInt();
//     num2 = IncomingData.substring(4, 8).toInt();
//     num3 = IncomingData.substring(8, 12).toInt();
//     x = num1;
//     y = num2;
//     z = num3;
//     Serial.print("x : ");
//     Serial.print(x);
//     Serial.print(" y : ");
//     Serial.print(y);
//     Serial.print(" z : ");
//     Serial.println(z);
//     while (Serial.available())
//       var = Serial.read();
//     IncomingData = "";
//   }
// }

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

//  mode = get_mode();
// mode = MANUAL;
// if (mode == AUTO)
// {
//   automate();
// }
// else {
//   handle_rf();
// }
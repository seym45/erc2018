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
#define RC_CHANNEL_ENABLE 10

#define BASE 0
#define ACT1 1
#define ACT2 2
#define ROLL 3
#define PITCH 4
#define WRIST 5
#define GRABBER 6
#define FOWARD_BACKWARD 7
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

IBT base(6, 7);         // wiper on base
IBT act1wrist360(45, 11); // actuator1 and wrist360
IBT act2(14, 15);         // actuator2
IBT rpg(8, 44);            // roll pitch grabber in a single relay
IBT right(2, 3);
IBT left(4, 5);
//


/////////////////ba, ac1, ac2, roll, pitc, w, g
String arm_names[] = {
  "Base",
  "Act1",
  "Act2",
  "Roll",
  "Pitc",
  "Wrst",
  "Grab",
};





SBUS sbus(Serial1);
int mode;                       // mannual auto semi_auto serial
String inputString = "";        // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete

void setup()
{
  Serial.begin(57600);
  sbus.begin(true);
  delay(2000);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  //receiver setup
  setup_relays();

  pinMode(13, OUTPUT);
  digitalWrite(13, 1);
  //  while (true)
  //  {
  //    if (sbus.getFrameLoss() < 30 && sbus.getFrameLoss() >= 0)
  //    {
  //      Serial.println(sbus.getFrameLoss());
  //      break;
  //    }
  //  //  }
  //  bool flag = true;
  //  while (flag)
  //  {
  //    int cnt = 0;
  //    for (int i = 1; i <= 4; i++)
  //    {
  //      if (abs(sbus.getNormalizedChannel(i)) > 60)cnt++;
  //    }
  //    if (cnt == 4)flag = false;
  //    Serial.println(millis());
  //  }
  //  digitalWrite(13, 0);
  //  delay(1000);
}

ISR(TIMER2_COMPA_vect)
{
  sbus.process();
}

void loop()
{
  //Serial.print('S');
  //  analogWrite(6, 200);
  //  analogWrite(7, 0);// turn  the LED on (HIGH is the voltage level)
  //  delay(1000);                       // wait for a second
  //  analogWrite(6, 0);
  //  analogWrite(7, 200);    // turn the LED off by making the voltage LOW
  //  delay(1000);                       // wait for a second
    test();
  //  Serial.println('E');
}

void test()
{
  only_rf_full();
  // only_serial_full();
  //   reciever_test();
  // print the string when a newline arrives:
   if (stringComplete)
   {
     Serial.println(inputString);
     handle_serial(inputString);
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


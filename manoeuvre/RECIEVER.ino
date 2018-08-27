#define NO_OF_CHANNELS 10

void reciever_test()
{
  for (int channel_id = 1; channel_id <= NO_OF_CHANNELS; channel_id++)
  {
    Serial.print("Ch");
    Serial.print(channel_id);
    Serial.print(' ');
    Serial.print(sbus.getChannel(channel_id));
    Serial.print('\t');
  }
  Serial.println();
}

int temp_ch;
int get_pwm_input_from_rf(byte channel_id)
{
  /* 
  * Method getNormalizedChannel return -100 to +100
  * so to convert into PWM values 2.5 is multiplied 
  * to get a eange of -255 to 255
  */
  return sbus.getNormalizedChannel((int)channel_id) * 2.5;
}

// int temp_ch;
// int get_raw_input_from_rf(byte channel)
// {
//   temp_ch = pulseIn(ch[channel - 1], HIGH, 25000);
//   if (temp_ch == 0)
//   {
//     temp_ch = 1500;
//   }
//   return temp_ch;
// }

// int temp_calc;
// int raw2pwm(int raw_channel_input)
// {
//   // i ranges from 640 to 2100 around
//   float constant = 2;
//   temp_calc = (int)((raw_channel_input - 1500) / constant);

//   if (temp_calc > 250)
//     temp_calc = 250;
//   if (temp_calc < -250)
//     temp_calc = -250;
//   return temp_calc;
// }

// void reciever_test()
// {
// #if DEBUG
//   for (int i = 1; i <= 8; i++)
//   {
//     Serial.print(ch[i-1]);
//     Serial.print(' ');
//     Serial.print(get_raw_input_from_rf(i));
//     Serial.print('\t');
//     //    Serial.print( map( in, 1000, 2000, -255, 255));
//     //    Serial.print(' ');
//   }
//   Serial.println();
// #endif
// }
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
  int pwm = (int)sbus.getNormalizedChannel((int)channel_id) * 2.5;

  if (abs(pwm) < RC_SENSITIVITY_THRESHOLD)
    pwm = 0;
    
  return pwm;
}
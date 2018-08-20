
void reciever_test()
{
#if DEBUG
  for (int i = 1; i <= 8; i++)
  {
    Serial.print(i);
    Serial.print(' ');
    Serial.print(get_raw_pwm_from_rf(i));
    Serial.print('\t');
    //    Serial.print( map( in, 1000, 2000, -255, 255));
    //    Serial.print(' ');
  }
  Serial.println();
#endif
}



int get_mode()
{
 /* ch_val = get_raw_pwm_from_rf(8);
  if( ch_val <> )
  return v...
  else
  return ...
 */
 return 0;
}


 
int temp_ch;
int get_raw_pwm_from_rf(byte channel)
{
  temp_ch = pulseIn(ch[channel-1], HIGH, 25000);

  if (temp_ch == 0)
  {
    temp_ch = 1500;
  }
  return temp_ch;
}


int temp_calc;
int raw2pwm(int raw_channel_input)
{
  // i ranges from 640 to 2100 around
  float constant = 2;
  temp_calc = (int)((raw_channel_input - 1500) / constant);

  if (temp_calc > 250)temp_calc = 250;
  if (temp_calc < -250)temp_calc = -250;
  return temp_calc;
}


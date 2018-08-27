// ---------------------------------- Fully manual control
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
int channel[7] = {
    //channel name index
    7, // base  0
    2, // ac1   1
    3, // ac2   2
    6, // roll  3
    5, //pitch  4
    4, //wrist  5
    1, //grabb  6
};
int available = 10;

void only_rf_full()
{
  if (get_pwm_input_from_rf(flag_channel) > 50)
    drive_wheel();
  else
    driver_arms();
}



void driver_arms()
{
  int speed;
  bool rpg_active = false;
  bool act1wrist_active = false;
  for (byte name = 0; name < available; name++)
  {
    speed = get_pwm_input_from_rf(channel[name]);
    if (abs(speed) < 60)
      speed = 0;

    if (able2move(name) and (speed > 0 || speed < 0))
    {
      move_it(name, speed);
#ifdef ARM_DEBUG
      Serial.print(arm_names[name]);
      Serial.print(":\t");
      Serial.print("Speed ");
      Serial.print(speed);
      Serial.println();
#endif
    }
    else if (name == 0 || name == 2) // base act2
      move_it(name, 0);
    if (!rpg_active && speed && (name == 3 || name == 4 || name == 6)) // r p g
      rpg_active = true;
    if (!act1wrist_active && speed && (name == 1 || name == 5)) // r p g
      act1wrist_active = true;
  }

  if (!rpg_active)
    rpg.stop();
  if (!act1wrist_active)
    act1wrist360.stop();
}
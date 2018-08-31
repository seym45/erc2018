// --------------------------------
void handle_serial(String cmd)
{
  int speed = 130;
  for (int i = 0; i < 2; i++)
  {
    if ( 1 == i)speed = 250;
    Serial.print(cmd[i]);
    if (cmd[i] == '+')
    { 
      if ( 0 == i) speed = 220;
      speed = speed;
    }
    else if (cmd[i] == '-')
      speed = -1 * speed;
    else
      speed = 0;
    move_it(i + 1, speed);
  }
  Serial.println("---------");
}
// ---------------------------------- Fully manual control

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

  if (get_pwm_input_from_rf(RC_CHANNEL_ENABLE) > 50)
  {
    //Serial.println("Off");
    return;
  }

  if (get_pwm_input_from_rf(RC_CHANNEL_FLAG) > 50)
    drive_wheel();
  else
    driver_arms();
}

void driver_arms()
{
  int speed, actwrst_spd, rpg_spd;
  int rpg_count = 0, actwrst_count = 0;
  int actwrst_id, rpg_id;

  for (byte name = 0; name < available; name++)
  {
    speed = get_pwm_input_from_rf(channel[name]);
    if (abs(speed) < 60)
      speed = 0;

    if ((name == 0 || name == 2) && (speed > 0 || speed < 0))
    {
      move_it(name, speed);
#ifdef DEBUG && ARM_DEBUG
      Serial.print(arm_names[name]);
      Serial.print(":\t");
      Serial.print("Speed ");
      Serial.print(speed);
      Serial.println();
#endif
    }
    else if (name == 0 || name == 2) // base act2
      move_it(name, 0);


    if (speed && (name == 3 || name == 4 || name == 6)) // r p g
    {
      rpg_id = name;
      rpg_count++;
      rpg_spd = speed;
    }

    if (speed && (name == 1 || name == 5)) // act wrst
    {

      actwrst_id = name;
      actwrst_count++;
      actwrst_spd = speed;
    }
  }

  if (rpg_count == 1)
    move_it(rpg_id, rpg_spd);
  else
    rpg.stop();

  if (actwrst_count == 1)
    move_it(actwrst_id, actwrst_spd);
  else
    act1wrist360.stop();
}

const int channel_forward_backward = 2;
const int channel_left_right = 4;

void drive_wheel()
{
  int leftspeed, rightspeed, speed, direction;
  speed = get_pwm_input_from_rf(channel_forward_backward);
  direction = get_pwm_input_from_rf(channel_left_right);

  if (speed and direction)
  {
    if (speed > 0)
    {
      if (direction > 0) //assume right bound
      {
        leftspeed = speed;
        rightspeed = map(direction, 0, 250, 250, -250);
        //        rightspeed = middle_out(rightspeed);
      }
      else // assumed left bound
      {
        leftspeed = map(direction, -250, 0, -250, 250);
        //        leftspeed = middle_out(leftspeed);
        rightspeed = speed;
      }
    }
    else
    {
      leftspeed = speed;
      rightspeed = speed;
    }
  }
  else if (speed and !direction)
  {
    leftspeed = speed;
    rightspeed = speed;
  }
  else if (!speed and direction)
  {
    leftspeed = direction;
    rightspeed = (-1) * direction;
  }
  else
  {
    leftspeed = 0;
    rightspeed = 0;
  }

#ifdef DEBUG && WHEEL_DEBUG
  Serial.print("Wheel --- dir raw value: ");
  Serial.print(direction);
  Serial.print("\t");
  Serial.print("left_speed ");
  Serial.print("\t");
  Serial.print(leftspeed);
  Serial.print("\t");
  Serial.print("right_speed ");
  Serial.print(rightspeed);
  Serial.println("");
#endif
  move(left, leftspeed);
  move(right, rightspeed);
}

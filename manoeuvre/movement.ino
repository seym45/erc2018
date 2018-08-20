bool able2move(int arm_name)
{
  bool ans = false;
  switch (arm_name)
  {
    case BASE:
      ans = true;
      break;
    case ACT1:
      ans = true;
      break;
    case ACT2:
      ans = true;
      break;
    case ROLL:
      ans = true;
      break;
    case PITCH:
      ans = true;
      break;
    case WRIST:
      ans = true;
      break;
    case GRABBER:
      ans = true;
      break;
  }

  return ans;
}

void move_it(int name, int pwm)
{
#ifdef ARM_DEBUG
  Serial.print("name ");
  Serial.print(name);
  Serial.print('\t');
  Serial.print("pwm ");
  Serial.print(pwm);
  Serial.println();
#endif
  switch (name)
  {
    case BASE:
      move_arm(base, pwm);
      break;
    case ACT1:
      move_arm(act1, pwm);
      break;
    case ACT2:
      move_arm(act2, pwm);
      break;
    case ROLL:
      move_arm(roll, pwm);
      break;
    case PITCH:
      move_arm(pitch, pwm);
      break;
    case WRIST:
      move_arm(wrist, pwm);
      break;
    case GRABBER:
      move_arm(grabber, pwm);
      break;
  }
}

void move_arm(IBT arm, int pwm)
{
  if (pwm < 0)
  {
    pwm = (-1) * pwm;
    arm.rotNeg(pwm);
  }
  else if (pwm > 0)
  {
    arm.rotPos(pwm);
  }
  else
    arm.stop();
}

void move_arm(L298 arm, int pwm)
{
  if (pwm < 0)
  {
    pwm = (-1) * pwm;
    arm.rotNeg(pwm);
  }
  else if (pwm > 0)
  {
    arm.rotPos(pwm);
  }
  else
    arm.stop();
}

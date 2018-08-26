void setup_relays()
{
  pinMode(RELAY_12V_CH1, OUTPUT);
  pinMode(RELAY_12V_CH2, OUTPUT);
  pinMode(RELAY_12V_CH3, OUTPUT);
  pinMode(RELAY_12V_CH4, OUTPUT);

  pinMode(RELAY_24V_CH1, OUTPUT);
  pinMode(RELAY_24V_CH2, OUTPUT);
  pinMode(RELAY_24V_CH3, OUTPUT);
  pinMode(RELAY_24V_CH4, OUTPUT);

digitalWrite(RELAY_12V_CH1,1);
digitalWrite(RELAY_12V_CH2,1);
digitalWrite(RELAY_12V_CH3,1);
digitalWrite(RELAY_12V_CH4,1);


digitalWrite(RELAY_24V_CH1,1);
digitalWrite(RELAY_24V_CH2,1);
digitalWrite(RELAY_24V_CH3,1);
digitalWrite(RELAY_24V_CH4,1);
}






void select_motor(int arm_name)
{
  switch (arm_name)
  {
    case ACT1:
      digitalWrite(RELAY_12V_CH1, 1);
      digitalWrite(RELAY_12V_CH2, 1);
      break;
    case WRIST:
      digitalWrite(RELAY_12V_CH1, 0);
      digitalWrite(RELAY_12V_CH2, 0);
      break;
    case ROLL:
      digitalWrite(RELAY_24V_CH1, 1);
      digitalWrite(RELAY_24V_CH2, 1);
      digitalWrite(RELAY_24V_CH3, 0);
      digitalWrite(RELAY_24V_CH4, 1);
      break;
    case PITCH:
      digitalWrite(RELAY_24V_CH1, 0);
      digitalWrite(RELAY_24V_CH2, 0);
      digitalWrite(RELAY_24V_CH3, 0);
      digitalWrite(RELAY_24V_CH4, 1);
      break;
    case GRABBER:
      digitalWrite(RELAY_24V_CH1, 1);
      digitalWrite(RELAY_24V_CH2, 0);
      digitalWrite(RELAY_24V_CH3, 1);
      digitalWrite(RELAY_24V_CH4, 1);
      break;
  }
}

void move_it(int name, int pwm)
{
  switch (name)
  {
    case BASE:
      move_arm(base, pwm);
      break;
    case ACT1:
      if(pwm)select_motor(ACT1);
      move_arm(act1wrist360, pwm);
      break;
    case ACT2:
      move_arm(act2, pwm);
      break;
    case ROLL:
      if(pwm)select_motor(ROLL);
      move_arm(rpg, pwm);
      break;
    case PITCH:
      if(pwm)select_motor(PITCH);
      move_arm(rpg, pwm);
      break;
    case WRIST:
      if(pwm)select_motor(WRIST);
      move_arm(act1wrist360, pwm);
      break;
    case GRABBER:
      if(pwm)select_motor(GRABBER);
      move_arm(rpg, pwm);
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
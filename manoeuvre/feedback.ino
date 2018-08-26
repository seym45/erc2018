double base_angle()
{
  return 0.0;
}

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
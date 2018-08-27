bool near(int from, int to, int tolerance)
{
  if (abs(from - to) <= tolerance)
    return true;
  return false;
}

bool near(double from, double to, double tolerance)
{
  if (abs(from - to) <= tolerance)
    return true;
  return false;
}

bool near(double from, double to, int tolerance)
{
  if (abs(from - to) <= tolerance)
    return true;
  return false;
}

double rad2deg(double rad)
{
  return ((rad * 57296) / 1000);
}

int middle_out(int value)
{
  if (value < 0 and abs(value) < RC_SENSITIVITY_THRESHOLD)
    value = (-1) * RC_SENSITIVITY_THRESHOLD;
  else if (value > 0 and abs(value) < RC_SENSITIVITY_THRESHOLD)
    value = RC_SENSITIVITY_THRESHOLD;
  return value;
}

// void sonar_test()
// {
//   Serial.print("Act 1: ");
//   Serial.print(sonar_act1.get_distance());
//   Serial.print('\t');
//   Serial.print("Act 2: ");
//   Serial.print(sonar_act2.get_distance());
//   Serial.println();
// }

bool near(int from, int to, int tolerance)
{
  if (abs(from - to) <= tolerance) return true;
  return false;
}

bool near(double from, double to, double tolerance)
{
  if (abs(from - to) <= tolerance) return true;
  return false;
}

bool near(double from, double to, int tolerance)
{
  if (abs(from - to) <= tolerance) return true;
  return false;
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


double rad2deg(double rad)
{
  return ((rad * 57296)/ 1000);
}
int xyz_channel[3] = {7, 3, 2};
// void handle_rf()
// {
//   int thresh = 40;
//   // X axis
//   int c1 = get_raw_pwm_from_rf(xyz_channel[0]);
//   c1 = raw2pwm(c1);

//   if (abs(c1) > thresh)
//   {
//     if (c1 > 0)
//     {
//       if (inv_kin(x + 1, y, z))
//         x++;
//     }
//     else
//     {
//       if (inv_kin(x - 1, y, z))
//         x--;
//     }
//   }
//   //y axis
//   int c2 = get_raw_pwm_from_rf(xyz_channel[1]);
//   c2 = raw2pwm(c2);

//   if (abs(c2) > thresh)
//   {
//     if (c2 > 0)
//     {
//       if (inv_kin(x, y + 1, z))
//         y++;
//     }
//     else
//     {
//       if (inv_kin(x, y - 1, z))
//         y--;
//     }
//   }
//   //z axis
//   int c3 = get_raw_pwm_from_rf(xyz_channel[2]);
//   c3 = raw2pwm(c3);

//   if (abs(c3) > thresh)
//   {
//     if (c3 > 0)
//     {
//       if (inv_kin(x, y, z + 1))
//         z++;
//     }
//     else
//     {
//       if (inv_kin(x, y, z - 1))
//         z--;
//     }
//   }
//   //x y z values updated
//   move_to_target();
// }

// ---------------------------------- Fully manual control
/////////////////ba, ac1, ac2, roll, pitc
int channel[7] = {3, 4, 2, 1, 5, 7, 8};
int available = 7;
void only_rf_full()
{
  int raw_channel_in, raw_pwm;
  for (byte name = 0; name < available; name++)
  {
    raw_channel_in = get_raw_pwm_from_rf(channel[name]);
    raw_pwm = raw2pwm(raw_channel_in);
    if (abs(raw_pwm) < 40)
    {
      move_it(name, 0);
      continue;
    }
    if (able2move(name))
      move_it(name, raw_pwm);
    else
      move_it(name, 0);
  }
}


// void automate()
// {
//   start_indicator(AUTO);
//   get_data_from_serial();   //x y z updated from serial data
//   calc_target_angles();  //theta1 to theta4 holds target angles now
//   move_to_target();
//   end_indicator(AUTO);
// }

void calc_target_angles()
{
  inv_kin(x, y, z);
}










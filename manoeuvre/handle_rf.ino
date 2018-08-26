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
int available = 7;
#define ZERO 0
void only_rf_full()
{
    int raw_channel_in, raw_pwm;
    bool rpg_active = false;
    bool act1wrist_active = false;
    for (byte name = 0; name < available; name++)
    {
        raw_channel_in = get_raw_input_from_rf(channel[name]);
        raw_pwm = raw2pwm(raw_channel_in);
        if (abs(raw_pwm) < 60)
            raw_pwm = 0;

        if (able2move(name) and (raw_pwm>0 || raw_pwm <0))
        {
            move_it(name, raw_pwm);
#ifdef ARM_DEBUG
            Serial.print(arm_names[name]);
            Serial.print(":\t");
            Serial.print("Speed ");
            Serial.print(raw_pwm);
            Serial.println();
#endif
        }
        else if (name == 0 || name == 2) // base act2
            move_it(name, 0);
        if (!rpg_active && raw_pwm && (name == 3 || name == 4 || name == 6)) // r p g
            rpg_active = true;
        if (!act1wrist_active && raw_pwm  && (name == 1|| name == 5)) // r p g
            act1wrist_active = true;
    }

    if (!rpg_active)
        rpg.stop();
    if (!act1wrist_active)
        act1wrist360.stop();
}
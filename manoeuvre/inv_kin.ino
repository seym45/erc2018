#define NO_OF_DOF 4
#define SPEED_BASE 100
#define SPEED_ACT1 100
#define SPEED_ACT2 100
#define SPEED_ROLL 100
#define SPEED_PITCH 100

int active[NO_OF_DOF];
//angles
double theta1, theta2, theta3, theta4;

// arm lengths
double L1 = 12; // base to shoulder
double L2 = 5;  // wrist to endpoint
double b = 15;  // shoulder to wrist
double a = 10;  // elbow to wrist



// void move_to_target()
// {

//   double angle;
//   while ( true )
//   {
//     // base
//     double cur_angle_base = get_angle(1);
//     if (near(cur_angle_base, theta1, 5))   //(near(current_angle_base, target_angle_base, tolerance))
//       active[0] = 0;
//     else
//     {
//       if (cur_angle_base - theta1 > 0)
//         base.rotPos(SPEED_BASE);
//       else
//         base.rotNeg(SPEED_BASE);
//     }

//     // actuator_1
//     double cur_angle_act1 = get_angle(2);
//     if (near(cur_angle_act1, theta2, 5))
//       active[1] = 0;
//     else
//     {
//       if (cur_angle_act - theta1 > 0)
//         base.rotPos(SPEED_BASE);
//       else
//         base.rotNeg(SPEED_BASE);
//     }

//     // actuator_2
//     if (near(get_angle(2), theta2, 5))
//       active[2] = 0;
//     else
//       move_act2();
//     // encoder
//     if (near(get_angle(3), theta3, 5))
//       active[3] = 0;
//     else
//       move_encoder();

//     //conditions to break the loop
//     int flag = 1;
//     for (int i = 0; i < 4; i++)
//     {
//       if (active[i])flag = 0;
//     }
//     if (flag)break;
//   }
// }

bool inv_kin(int tx, int ty , int tz) {
  // coordinate of the end effector
  double theta1_, theta2_, theta3_, theta4_;
  if (tx == 0) tx = 1;
  if (ty == 0) ty = 1;
  if (tz == 0) tz = 1;
  double px = tx;
  double py = ty;
  double pz = tz;
  theta1_ = atan2(py, px);
  theta1_ = rad2deg(theta1);
  double cc = px * px + (L1 - (pz + L2)) * (L1 - (pz + L2));
  if (cc < 0)return false;
  double c = sqrt (cc);
  double aa = (a * a + b * b - c * c) / (2 * a * b);
  if (abs(aa) > 1)return false;
  double thetaC = acos((a * a + b * b - c * c) / (2 * a * b) );

  thetaC = rad2deg(thetaC);
  theta3_ = 180 - thetaC;
  cc = (a / c) * sin(thetaC);
  if (abs(cc) > 1)return false;
  double thetaA = asin(cc);
  thetaA = rad2deg(thetaA);

  cc = (b / c) * sin(thetaC);
  if (abs(cc) > 1)return false;
  double thetaB = asin(cc);
  thetaB = rad2deg(thetaB);
  double thetaE = atan2(L1, px);
  thetaE = rad2deg(thetaE);
  double thetaD = 90 - thetaE;
  thetaD = rad2deg(thetaD);
  double thetaG = 90 - thetaE;
  thetaG = rad2deg(thetaG);
  double h = sqrt(L1 * L1 + px * px);
  cc = ((pz + L2) / c) * sin(thetaG);
  if (abs(cc) > 1)return false;
  double thetaF = asin(cc);
  double thetaH = 180 - thetaG - thetaF;
  theta2_ = 180 - thetaA  - thetaD - thetaF;
  theta4_ = 180 - thetaB - thetaH;

  //now theta1 to theta4 will be updated
  theta1 = theta1_;
  theta2 = theta2_;
  theta3 = theta3_;
  theta4 = theta4_;
  return true;
}

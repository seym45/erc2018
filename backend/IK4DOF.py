from math import atan2,asin,acos,sin,cos,sqrt,pi
from numpy import isreal

theta1 = 0 
theta2 =0
theta3 = 0
theta4 = 0

L1 = 7 # base to shoudler
L2 = 6 # wrist_start to endpoint
a = 62 # shoulder to elbow 
b = 48 # elbow to wrist_start


def radtodeg(r):
    return 180*r/pi;

def test_code(x,y,z):
    px = x 
    py = y 
    pz = z
    theta1 = atan2(py, px)
    theta1_ = radtodeg(theta1)
    cc = px * px + (L1 - (pz + L2)) * (L1 - (pz + L2))
    if (cc < 0): return False
    c = sqrt (cc)
    aa = (a * a + b * b - c * c) / (2 * a * b)
    if (abs(aa) > 1): return False
    thetaC = acos((a * a + b * b - c * c) / (2 * a * b) )
    thetaC = radtodeg(thetaC)
    theta3_ = 180 - thetaC
    cc = (a / c) * sin(thetaC)
    if (abs(cc) > 1): return False
    thetaA = asin(cc)
    thetaA = radtodeg(thetaA)
    #print("theta A {}".format(thetaA))
    cc = (b / c) * sin(thetaC)
    if (abs(cc) > 1): return False
    thetaB = asin(cc)
    thetaB = radtodeg(thetaB)
    #print("theta B {}".format( thetaB))
    thetaE = atan2(L1, px)
    #print("theta E {}".format(thetaE))
    thetaE = radtodeg(thetaE)
    thetaD = 90 - thetaE
    #print("theta D {}".format(thetaD))
    #print("theta E {}".format(thetaE))
    thetaG = 90 - thetaE
    cc = ((pz + L2) / c) * sin(thetaG)
    if (abs(cc) > 1): return False
    thetaF = asin(cc)
    thetaF = radtodeg(thetaF)
    thetaH =  180-thetaG -thetaF
    #print("==theta H {}".format(thetaH))
    theta2_ = 180 - thetaA  - thetaD - thetaF
    theta4_ = 180 - thetaB - thetaH
    theta1 = theta1_
    theta2 = 180-theta2_
    theta3 = 180-theta3_
    theta4 = 180-theta4_
    if(isreal(theta1) and isreal(theta2) and isreal(theta3) and isreal(theta4)):
        print (theta1)
        print (theta2)
        print (theta3)
        print (theta4)
        return True
    else:
        return False
        
def main():
    if(test_code(30,0,65)):
        print("yes\n")
    else:
        print("no\n")


if __name__=="__main__":
    main()

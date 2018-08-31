from math import atan2, asin, acos, sin, cos, sqrt, pi, radians, degrees
from numpy import isreal
from time import sleep


L1 = 8  # base to shoulder
b = 46  # shoulder to elbow
a = 62  # elbow to wrist


def xyz2theta(x, y, z):
    angle1 = atan2(y, x)
    angle1 = degrees(angle1)
    c = (x * x + (z - L1) * (z - L1))
    if c < 0:
        return None
    c = sqrt(c)
    aa = (a * a + b * b - c * c) / (2 * a * b)
    if abs(aa) > 1:
        return None
    angle3 = acos(aa)
    cc = (a / c) * sin(radians(angle3))
    if (abs(cc) > 1):
        return None
    A = asin(cc)
    angle3 = degrees(angle3)
    A = degrees(A)
    E = atan2(L1, x)
    E = degrees(E)
    D = 90 - E
    cc = (z / c) * sin(radians(D))
    if (abs(cc) > 1):
        return None
    F = asin(cc)
    F = degrees(F)
    angle2 = A + F + D
    if(isreal(angle1) and isreal(angle2) and isreal(angle3)):
        #print (angle1)
        #print (angle2)
        #print (angle3)
        angle1 = round(angle1, 1)
        angle2 = round(angle2, 1)
        angle3 = round(angle3, 1)
        return [angle1, angle2, angle3]


def main():
    pass
    f = open("file.txt", 'w')
    if xyz2theta(5000, 0, 35):
        print("yes\n")
    else:
        print("no\n")

    print("-----------\n")
    for x in range(0, 100):
        for y in range(0, 100):
            for z in range(0, 100):
                if(xyz2theta(x, y, z)):
                    [angle1, angle2, angle3] = xyz2theta(x, y, z)
                    if(angle3 in range(70, 170)):
                        if(angle2 in range(45, 170)):
                            print(angle1)
                            print(angle2)
                            print(angle3)
                            print(x, y, z)
                            print("------")
                            f.write("------\n")
                            f.write("{} {} {} || {} {} {}".format(
                                x, y, z, angle1, angle2, angle3))
                            f.write("------\n--------\n")
                            # sleep(.50)
                        else:
                            print("angle1 out of range")
                    else:
                        print("angle3 out of range")


if __name__ == "__main__":
    main()

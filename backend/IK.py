from sympy import *
from time import time
from mpmath import radians
import math

def xyz2theta(xyz,roll_pitch_yaw):
    ## Set up code
    ## Do not modify!
    x = 0
    class Position:
        def __init__(self,EE_pos):
            self.x = EE_pos[0]
            self.y = EE_pos[1]
            self.z = EE_pos[2]
    class Orientation:
        def __init__(self,EE_ori):
            self.rr = EE_ori[0]
            self.pp = EE_ori[1]
            self.yy = EE_ori[2]

    position = Position(xyz)
    orientation = Orientation(roll_pitch_yaw)

    class Combine:
        def __init__(self,position,orientation):
            self.position = position
            self.orientation = orientation

    comb = Combine(position,orientation)

    class Pose:
        def __init__(self,comb):
            self.poses = [comb]

    req = Pose(comb)
    start_time = time()

    ########################################################################################
    ##

    ## Insert IK code here! starting at: Define DH parameter symbols

    # Define DH param symbols

    #print ('assigning DH parameters')

    d1, d2, d3, d4, d5, d6, d7 = symbols('d1:8') # link offset

    a0, a1, a2, a3, a4, a5, a6 = symbols('a0:7') # link length

    alpha0, alpha1, alpha2, alpha3, alpha4, alpha5, alpha6 = symbols('alpha0:7') # twist angle

    # joint angle symbols

    q1, q2, q3, q4, q5, q6, q7 = symbols('q1:8')

    #print( 'DH parameters assigned')

    #print ('Created DH Table')

    # Modified DH params

    DH_Table = {alpha0: 0,     a0: 0,         d1: 16,     q1: q1,
        alpha1: -pi/2., a1: 7,    d2: 0,         q2: -pi/2. + q2,
        alpha2: 0,     a2: 50,     d3: 0,         q3: q3,
        alpha3: -pi/2., a3: 7,     d4: 62,     q4: q4,
        alpha4: pi/2,     a4: 0,         d5: 0,         q5: q5,
        alpha5: -pi/2., a5: 0,         d6: 0,         q6: q6,
        alpha6: 0,     a6: 0,         d7: 10,     q7: 0}

    #print ('DH Table Created')

    # define modified DH transformation matrix

    #print ('Creating TF Matrix')

    def TF_Matrix(alpha, a, d, q):
         TF = Matrix([[cos(q),         -sin(q),         0,         a],[sin(q)*cos(alpha),     cos(q)*cos(alpha),     -sin(alpha),     -sin(alpha)*d],[sin(q)* sin(alpha),     cos(q)*sin(alpha),     cos(alpha),     cos(alpha)*d],[0,            0,            0,        1]])
         return TF

    #print ('applying transforms')

    T0_1 = TF_Matrix(alpha0, a0, d1, q1).subs(DH_Table)
    T1_2 = TF_Matrix(alpha1, a1, d2, q2).subs(DH_Table)
    T2_3 = TF_Matrix(alpha2, a2, d3, q3).subs(DH_Table)
    T3_4 = TF_Matrix(alpha3, a3, d4, q4).subs(DH_Table)
    T4_5 = TF_Matrix(alpha4, a4, d5, q5).subs(DH_Table)
    T5_6 = TF_Matrix(alpha5, a5, d6, q6).subs(DH_Table)
    T6_EE = TF_Matrix(alpha6, a6, d7, q7).subs(DH_Table)

    T0_EE = T0_1 * T1_2 * T2_3 * T3_4 * T4_5 * T5_6 * T6_EE

    #print ('transforms applied')
    # Extract end-effector position and orientation from request
    # px, py, pz = end-effector position
    # roll, pitch, yaw = end-effector orientation

    #print ('applying end effector position and orientation')

    px = req.poses[x].position.x
    py = req.poses[x].position.y
    pz = req.poses[x].position.z

    (roll, pitch, yaw) =(req.poses[x].orientation.rr, req.poses[x].orientation.pp,req.poses[x].orientation.yy)

    #print ('end effector position and orientation applied')

    # Find EE rotation matrix
    # Define RPY roation matrices
    # http://planning.cs.uiuc.edu/node102.html

    #print ('applying EE rotation matrix')

    r, p , y = symbols('r p y')

    ROT_x = Matrix([
        [1,     0 ,         0],
        [0,     cos(r),     -sin(r)],
           [0,     sin(r),     cos(r)]]) # ROLL

    ROT_y = Matrix([
        [cos(p),     0 ,     sin(p)],
        [0,         1,     0],
           [-sin(p),     0,     cos(p)]]) # PITCH (CHANGED!)

    ROT_z = Matrix([
        [cos(y),     -sin(y),     0],
        [sin(y),     cos(y),     0],
        [0,         0,         1]]) # YAW

    ROT_EE = ROT_z * ROT_y * ROT_x

    Rot_Error = ROT_z.subs(y, radians(180)) * ROT_y.subs(p, radians(-90))


    ROT_EE = ROT_EE * Rot_Error
    ROT_EE = ROT_EE.subs({'r': roll, 'p': pitch, 'y': yaw})

    EE = Matrix([[px], [py], [pz]])

    #print ('EE rotation matrix applied')

    WC = EE - (0.303) * ROT_EE[:,2]
    theta1 = atan2(WC[1], WC[0])

    #print ('theta 1 calculated')

    # SSS triangle for theta2 and theta3

    side_a = 1.501
    side_b = sqrt(pow(sqrt(WC[0] * WC[0] + WC[1] * WC[1]) - 0.35, 2) + pow((WC[2] - 0.75), 2)) #CHANGED!!!

    side_c = 1.25

    angle_a = acos((side_b * side_b + side_c * side_c - side_a * side_a) / (2 * side_b * side_c))
    angle_b = acos((side_a * side_a + side_c * side_c - side_b * side_b) / (2 * side_a * side_c))
    angle_c = acos((side_a * side_a + side_b * side_b - side_c * side_c ) / (2 * side_a * side_b))

    theta2 = pi/2. - angle_a - atan2(WC[2] - 0.75, sqrt(WC[0] * WC[0] + WC[1] * WC[1]) - 0.35) #(CHANGED!!!)
    theta3 = pi/2. - (angle_b + 0.036) # 0.036 accounts for sag in link4 of -0.054m
 
    #print ('theta 2 and 3 calculated')

    R0_3 = T0_1[0:3,0:3] * T1_2[0:3,0:3] * T2_3[0:3,0:3]
    R0_3 = R0_3.evalf(subs={q1: theta1, q2:theta2, q3: theta3})

    R3_6 = R0_3.transpose() * ROT_EE

    # Euler angles from rotation matrix

    theta4 = atan2(R3_6[2,2], -R3_6[0,2])
    theta5 = atan2(sqrt(R3_6[0,2]*R3_6[0,2] + R3_6[2,2]*R3_6[2,2]), R3_6[1,2])
    theta6 = atan2(-R3_6[1,1], R3_6[1,0]) 
    try:
        theta1=round(float(theta1*180/(math.pi)),1)
        theta2=round(float(theta2*180/(math.pi)),1)
        theta3=round(float(theta3*180/(math.pi)),1)
        theta4=round(float(theta4*180/(math.pi)),1)
        theta5=round(float(theta5*180/(math.pi)),1)
        theta6=round(float(theta6*180/(math.pi)),1)
    except TypeError as e:
        print(str(e))
        return None
    except Exception as e:
        print(str(e))
        return None

    print (theta1)
    print (theta2)
    print (theta3)
    print (theta4)
    print (theta5)
    print (theta6)
    return [theta1,theta2,theta3,theta4,theta5,theta6]


if __name__=="__main__":
    #FORMAT: xyz2theta([x,y,z],[roll,pitch,yaw])
    xyz2theta([2.16135,-1.42635,1.55109],[  1.6445982, 0.0229017, -0.493058 ])
	#this function above sets theta 1 to theta 6

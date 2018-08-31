import arduino
import constants
from time import sleep, time
import threading
import angle_master

feedback_ard = arduino.Arduino(constants.ID_FEEDBACK_ARDUINO, 57600)
movement_ard = arduino.Arduino(constants.ID_MOVEMENT_ARDUINO, 57600)
sleep(2)
present_angles = [0, 0, 0, 0, 0, 0]


def handle_interrupts(data):
    pass

a1 = 0
a2 = 0
def get_feedbacks():
    global a1
    global a2
    while True:
        data = feedback_ard.readline()
        # print(data)
        if data and 'F' in data and len:
            raw_values = data.strip().split(',')[1:]
            # print(raw_values)
            try:
                a1 = angle_master.get_angle(constants.ACTUATOR_1, float(raw_values[constants.ACTUATOR_1]))
                a2 = angle_master.get_angle(constants.ACTUATOR_2, float(raw_values[constants.ACTUATOR_2]))
                # print(present_angles[constants.ACTUATOR_2])
            except Exception as e:
                print(str(e)) 
        if data and 'I' in data:
            handle_interrupts(data)
        # print('p ',a1,a2)
        # sleep(1)

import math
def generate_command(t1,t2):
    cmd = ''
    
    if abs(t1-a1) < 10:
        temp = 'X'
    elif t1 > a1:
        temp = '+'
    elif t1 < a1:
        temp = '-'
    cmd = cmd + temp


    if abs(t2-a2) < 10:    
        temp = 'X'
    elif t2 > a2:
        temp = '+'
    elif t2 < a2:
        temp = '-'
    
    cmd = cmd + temp + '\n'       
    
    return cmd
    # cmd = ''
    # for arm_name in range(0, 6):
    #     if present_angles[arm_name] == new_angles[arm_name]:
    #         temp = 'X'
    #     elif present_angles[arm_name] > new_angles[arm_name]:
    #         temp = '+'
    #     elif present_angles[arm_name] < new_angles[arm_name]:
    #         temp = '-'
    #     cmd = cmd + temp
    #     print('generate cmd :', cmd)
    # return cmd


arm_moving = False
# 6 new_angles in a array


def arm_move_to(new_angles):
    arm_moving = True
    feedback_thread = threading.Thread(target=get_feedbacks)
    feedback_thread.start()
    while arm_moving:
        cmd = generate_command(new_angles)
        print(cmd)
        # movement_ard.write(cmd)
        if '+' not in cmd and '-' not in cmd:
            arm_moving = False


import IK
if __name__ == '__main__':
    feedback_thread = threading.Thread(target=get_feedbacks)
    feedback_thread.start()
    
    # arm_move_to(thetas)
    ta1 = 110
    ta2 = 200
    arm_moving = True
    while arm_moving:
        cmd = generate_command(ta1, ta2)
        print(cmd)
        movement_ard.write(cmd)
        if '+' not in cmd and '-' not in cmd:
            arm_moving = False

    # cmd = 'XX+' + '\n'
    # movement_ard.write(cmd)
    # print(movement_ard.readline())
    # sleep(3)

    # cmd = 'XX+' + '\n'
    # movement_ard.write(cmd)
    # print(movement_ard.readline())
    # sleep(3)


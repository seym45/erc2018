import arduino
import constants
from time import sleep, time
import threading
import angle_master

feedback_ard = arduino.Arduino(constants.ID_FEEDBACK_ARDUINO, 9600)
movement_ard = arduino.Arduino(constants.ID_FEEDBACK_ARDUINO, 9600)
sleep(2)
present_angles = [0, 0, 0, 0, 0, 0]


def handle_interrupts(data):
    pass


def get_feedbacks():

    while True:
        data = feedback_ard.readline()
        if 'F' in data:
            raw_values = data.strip().split(',')
            for arm_name in range(0, 7):
                present_angles[arm_name] = angle_master.get_angle(
                    arm_name, raw_values[arm_name])
        if 'I' in data:
            handle_interrupts(data)


def generate_command(new_angles):
    cmd = ''
    for arm_name in range(0, 7):
        if present_angles[arm_name] == new_angles[arm_name]:
            temp = str(arm_name) + 'X'
        elif present_angles[arm_name] > new_angles[arm_name]:
            temp = str(arm_name) + '+'
        elif present_angles[arm_name] < new_angles[arm_name]:
            temp = str(arm_name) + '-'
        cmd = cmd + temp
        print('generate cmd :', cmd)
    return cmd


arm_moving = False
# 6 new_angles in a array


def arm_move_to(new_angles):
    arm_moving = True
    feedback_thread = threading.Thread(target=get_feedbacks)
    feedback_thread.start()
    while arm_moving:
        cmd = generate_command(new_angles)
        movement_ard.write(cmd)
        if '+' not in cmd and '-' not in cmd:
            arm_moving = False


import IK
if __name__ == '__main__':
    x, y, z, roll, pitch, yaw = [
        x, 0, z, 0, 0, 0
    ]
    thetas = IK.xyz2theta([x, y, z, roll, pitch, yaw])
    arm_move_to(thetas)
import arduino
import constants
from time import sleep, time
import threading
import angle_master

feedback_ard = arduino.Arduino(constants.ID_FEEDBACK_ARDUINO, 57600)
# movement_ard = arduino.Arduino(constants.ID_MOVEMENT_ARDUINO, 57600)
sleep(2)
present_angles = [0, 0, 0, 0, 0, 0]


def handle_interrupts(data):
    pass


def get_feedbacks():

    while True:
        data = feedback_ard.readline()
        print(data)
        if data and 'F' in data and len:
            raw_values = data.strip().split(',')[1:]
            print(raw_values)
            try:
                present_angles[constants.ACTUATOR_1] = angle_master.get_angle(constants.ACTUATOR_1, float(raw_values[constants.ACTUATOR_1]))
                present_angles[constants.ACTUATOR_2] = angle_master.get_angle(constants.ACTUATOR_2, float(raw_values[constants.ACTUATOR_2]))
                # print(present_angles[constants.ACTUATOR_2])
            except Exception as e:
                print(str(e)) 
        if data and 'I' in data:
            handle_interrupts(data)
        print('p ', end='')        
        print(present_angles)
        # sleep(1)


def generate_command(new_angles):
    cmd = ''
    for arm_name in range(0, 6):
        if present_angles[arm_name] == new_angles[arm_name]:
            temp = 'X'
        elif present_angles[arm_name] > new_angles[arm_name]:
            temp = '+'
        elif present_angles[arm_name] < new_angles[arm_name]:
            temp = '-'
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
        print(cmd)
        # movement_ard.write(cmd)
        if '+' not in cmd and '-' not in cmd:
            arm_moving = False


import IK
if __name__ == '__main__':
    feedback_thread = threading.Thread(target=get_feedbacks)
    feedback_thread.start()

    # x, y, z, roll, pitch, yaw = [
    #  60, 1, 5,1 , 2, 5
    # ]
    # thetas = IK.xyz2theta([x, y, z], [roll, pitch, yaw])
    # thetas = [
    #     2, 2, 2,
    #     2, 2, 2
    # ]
    # arm_move_to(thetas)
# while True:
    # cmd = 'XX+' + '\n'
    # movement_ard.write(cmd)
    # print(movement_ard.readline())
    # sleep(3)

    # cmd = 'XX+' + '\n'
    # movement_ard.write(cmd)
    # print(movement_ard.readline())
    # sleep(3)

    # cmd = 'XXX' + '\n'
    # movement_ard.write(cmd)
    # print(movement_ard.readline())
    # sleep(3)

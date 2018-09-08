import arduino
import constants
from time import sleep, time
import threading
import angle_master
import db_conn


def handle_interrupts(data):
    pass


def get_feedbacks():
    while True:
        data = feedback_ard.readline()
        # print(data)
        if data and 'F' in data and len:
            raw_values = data.strip().split(',')[1:]
            # print(raw_values)
            try:
                a1 = angle_master.get_angle(constants.BASE, float(raw_values[constants.BASE]))
                a2 = angle_master.get_angle(constants.ACTUATOR_1, float(raw_values[constants.ACTUATOR_1]))
                a3 = angle_master.get_angle(constants.ACTUATOR_2, float(raw_values[constants.ACTUATOR_2]))
                # print(present_angles[constants.ACTUATOR_2])
                db_conn.store_angles(a1,a2,a3)
            except Exception as e:
                print(str(e)) 
        if data and 'I' in data:
            handle_interrupts(data)
        # print('p ',a1,a2)
        # sleep(1)

def update_movement_ard():
    cmd = db_conn.read_command()
    if cmd:
        cmd = cmd.strip()
    else:
        return
    movement_ard.write(cmd)
    

if __name__ == '__main__':
    feedback_ard = arduino.Arduino(constants.ID_FEEDBACK_ARDUINO, 57600)
    movement_ard = arduino.Arduino(constants.ID_MOVEMENT_ARDUINO, 57600)
    sleep(2)

    while True:
        get_feedbacks() #  feedback arduino
        update_movement_ard()

    
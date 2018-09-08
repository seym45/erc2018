import db_conn
import arduino
import constants
from time import sleep, time
import threading
import angle_master
import db_conn
import math


def handle_interrupts(data):
    pass


def generate_command(a1, a2, a3, t1, t2, t3):
    cmd = ''
    if abs(t1-a1) < 5:
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
    cmd = cmd + temp

    if abs(t3-a3) < 10:
        temp = 'X'
    elif t3 > a3:
        temp = '+'
    elif t3 < a3:
        temp = '-'

    cmd = cmd + temp + '\n'

    return cmd


def handle_ik():
    # Target fetch from db
    try:
        t1, t2, t3 = db_conn.read_targets()
    except Exception as e:
        # print(handle_ik.__name__+ ': ' + str(e))
        return


    if t1 == None or t2 == None or t3 == None:
        return

    # check if we need to move arm
    arm_moving = True
    prev_cmd = ''
    while arm_moving:
        a1, a2, a3 = db_conn.read_angles()
        if a1 == None or a2 == None or a3 == None:
            continue
        cmd = generate_command(a1, a2, a3, t1, t2, t3)
        if cmd != prev_cmd:
            print(cmd)
            db_conn.store_command(cmd)
            prev_cmd = cmd
            print(time(), end=" ")            
            print(t1,t2,t3) 
        else:
            print(time(), end=" ")            
            print(t1,t2,t3)            
            sleep(.1)

        if '+' not in cmd and '-' not in cmd:
            arm_moving = False

    # delete target angels
        db_conn.delete_target()
    




if __name__ == '__main__':
    while True:
        handle_ik()

    # cmd = 'XX+' + '\n'
    # movement_ard.write(cmd)
    # print(movement_ard.readline())
    # sleep(3)

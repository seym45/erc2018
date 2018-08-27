import serial,time

def send_recv(arduinoOut, in_):
    arduinoOut.write(in_.encode())
    try_count = 0
    feedback = None

    while True:
        feedback = arduinoOut.readline()
        if feedback:
            break
        else:
            try_count = try_count + 1
            print(try_count)

        if 4 == try_count:
            print('mara')
            break


    return feedback


if __name__ == '__main__':
    a = '023.2123.1098.000000000.0090.0023.2123.1098.000000000.0090.0X'
    arduinoOut = serial.Serial('COM17', 9600, timeout=1)
    time.sleep(2)
    feedback =send_recv(arduinoOut, a)
    print(feedback)
    arduinoOut.close()

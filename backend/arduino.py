import serial
import time
from utils_ import current_milli_time
import serial.tools.list_ports


class Arduino:
    connected = False
    port = ""
    baudrate = ""
    timeout = 1000  # milisec
    ser = ''

    def __init__(self, id, baudrate=9600, timeout=0):
        self.id = id
        self.baudrate = baudrate
        self.timeout = timeout
        self.getPort()
        self.connect()
    
    def getPort(self):
        comlist = serial.tools.list_ports.comports()
        print(comlist)
        for comport, address in comlist:
            if self.id in address:
                self.port = comport

    def connect(self):
        try:
            self.serial = serial.Serial(
                port=self.port, baudrate=self.baudrate, timeout=1)
            self.connected = True
        except:
            self.connected = False
            print(("Failed to connect on ", self.port))

    def readline(self):
        try:
            return self.serial.readline().decode().strip()
        except Exception as e:
            print(str(e))
            self.connected = False


    def write(self, data2write):
        try:
            self.serial.write(data2write.encode())
        except Exception as e:
            print(str(e))
            self.connected = False


if __name__ == '__main__':
    feedback = Arduino('123',96600)
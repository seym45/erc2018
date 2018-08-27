import serial
import serial.tools.list_ports
import time


def current_milli_time(): return int(round(time.time() * 1000))


class Connector:
    connected = False
    port = ""
    baudrate = ""
    timeout = 1000  # milisec
    ser = ""

    def __init__(self, port, baudrate=9600, timeout=1):
        self.port = port
        self.baudrate = baudrate
        self.timeout = timeout
        try:
            self.ser = serial.Serial(self.port, self.baudrate, timeout=self.timeout)
            self.connected = True
        except:
            self.connected = False
            print("Failed to connect on ", self.port)

    def sendandread(self, data):
        data = self.serialize(data)
        try:
            print('sending..')
            self.ser.write(data.encode())
            print('Recving..')
            response = ''
            while True:
                latest = self.ser.readline();
                response = response + latest.decode()
                print(response)
                if '\n' in latest.decode():
                    print(response)

                if '#' in response:
                    print(response)
                    break

            return response
        except Exception as e:
            print(str(e))
            self.connected = False
        

    def serialize(self, angles):
        temp = ''
        for angle in angles:
            angle = round(angle, 1)
            temp = temp + str(angle).zfill(5)
        temp = temp+'X'+'\r\n'
        print(temp)
        return temp


if __name__ == '__main__':

    try:
        ports = list(serial.tools.list_ports.comports())
        PORT = ""
        for port_no, description, address in ports:
            if '756383032373514102E0' in address:
                PORT = port_no
            break
        if not PORT:
            raise ValueError('No port Found')
    except ValueError:
        print('No port Found')
        exit

    conn = Connector(PORT, 9600)
    print(conn.connected)
    arr = [123.231, 123.1, 098.0, 0, 0.0, 90.1]
    arr = arr + arr
    print(conn.sendandread(arr))
            

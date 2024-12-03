import serial
import time
def serOpen(port = 'COM5', rate = 9600):

    ser = serial.Serial(port, rate)

    return ser

def serClose(ser):
    ser.close()

def stop(ser):

    data_to_send_1 = f'$1 0 200\n'
    data_to_send_2 = f'$2 0 200\n'
    data_to_send_3 = f'$3 0 200\n'
    data_to_send_4 = f'$4 0 200\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())

def forward(ser):
    
    data_to_send_1 = f'$1 1 200\n'
    data_to_send_2 = f'$2 1 200\n'
    data_to_send_3 = f'$3 1 200\n'
    data_to_send_4 = f'$4 1 200\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())

def backward(ser):
    
    data_to_send_1 = f'$1 2 200\n'
    data_to_send_2 = f'$2 2 200\n'
    data_to_send_3 = f'$3 2 200\n'
    data_to_send_4 = f'$4 2 200\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())

def turnLeft(ser):

    data_to_send_1 = f'$1 2 200\n'
    data_to_send_2 = f'$2 1 200\n'
    data_to_send_3 = f'$3 1 200\n'
    data_to_send_4 = f'$4 2 200\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())

def turnRight(ser):

    data_to_send_1 = f'$1 1 200\n'
    data_to_send_2 = f'$2 2 200\n'
    data_to_send_3 = f'$3 2 200\n'
    data_to_send_4 = f'$4 1 200\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())

def shiftLeft(ser):

    data_to_send_1 = f'$1 2 200\n'
    data_to_send_2 = f'$2 1 200\n'
    data_to_send_3 = f'$3 2 200\n'
    data_to_send_4 = f'$4 1 200\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())

def shiftRight(ser):

    data_to_send_1 = f'$1 1 200\n'
    data_to_send_2 = f'$2 2 200\n'
    data_to_send_3 = f'$3 1 200\n'
    data_to_send_4 = f'$4 2 200\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())

def recieveMessage(ser):

    received_data = ser.readline().decode().strip()
    print(received_data, type(received_data))

def main():

    pass

if __name__ == '__main__':

    main()
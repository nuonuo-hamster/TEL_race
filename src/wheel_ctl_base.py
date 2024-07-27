import serial

def serOpen(port = 'COM5', rate = 9600):

    ser = serial.Serial(port, rate)

    return ser

def serClose(ser):
    ser.close()

def reset(ser):

    data_to_send = f'$-2 0 0\n'
    ser.write(data_to_send.encode())

def stop(ser):

    data_to_send_1 = f'$1 0 150\n'
    data_to_send_2 = f'$2 0 150\n'
    data_to_send_3 = f'$3 0 150\n'
    data_to_send_4 = f'$4 0 150\n'
    data_to_send_5 = f'$5 0 150\n'
    data_to_send_6 = f'$6 0 150\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())
    ser.write(data_to_send_5.encode())
    ser.write(data_to_send_6.encode())

def forward(ser):

    data_to_send_1 = f'$1 1 150\n'
    data_to_send_2 = f'$2 1 150\n'
    data_to_send_3 = f'$3 1 150\n'
    data_to_send_4 = f'$4 1 150\n'
    data_to_send_5 = f'$5 1 150\n'
    data_to_send_6 = f'$6 1 150\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())
    ser.write(data_to_send_5.encode())
    ser.write(data_to_send_6.encode())

def backward(ser):

    data_to_send_1 = f'$1 2 150\n'
    data_to_send_2 = f'$2 2 150\n'
    data_to_send_3 = f'$3 2 150\n'
    data_to_send_4 = f'$4 2 150\n'
    data_to_send_5 = f'$5 2 150\n'
    data_to_send_6 = f'$6 2 150\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())
    ser.write(data_to_send_5.encode())
    ser.write(data_to_send_6.encode())

def turnLeft(ser):

    data_to_send_1 = f'$1 1 200\n'
    data_to_send_2 = f'$2 2 200\n'
    data_to_send_3 = f'$3 1 200\n'
    data_to_send_4 = f'$4 2 200\n'
    data_to_send_5 = f'$5 2 200\n'
    data_to_send_6 = f'$6 1 200\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())
    ser.write(data_to_send_5.encode())
    ser.write(data_to_send_6.encode())

def turnRight(ser):

    data_to_send_1 = f'$1 2 200\n'
    data_to_send_2 = f'$2 1 200\n'
    data_to_send_3 = f'$3 2 200\n'
    data_to_send_4 = f'$4 1 200\n'
    data_to_send_5 = f'$5 1 200\n'
    data_to_send_6 = f'$6 2 200\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())
    ser.write(data_to_send_5.encode())
    ser.write(data_to_send_6.encode())

def shiftLeft(ser):

    data_to_send_1 = f'$1 2 100\n'
    data_to_send_2 = f'$2 1 100\n'
    data_to_send_3 = f'$3 1 250\n'
    data_to_send_4 = f'$4 2 250\n'
    data_to_send_5 = f'$5 1 180\n'
    data_to_send_6 = f'$6 2 180\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())
    ser.write(data_to_send_5.encode())
    ser.write(data_to_send_6.encode())

def shiftRight(ser):

    data_to_send_1 = f'$1 1 90\n'
    data_to_send_2 = f'$2 2 90\n'
    data_to_send_3 = f'$3 2 255\n'
    data_to_send_4 = f'$4 1 255\n'
    data_to_send_5 = f'$5 2 180\n'
    data_to_send_6 = f'$6 1 180\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())
    ser.write(data_to_send_5.encode())
    ser.write(data_to_send_6.encode())

def recieveMessage(ser):

    received_data = ser.readline().decode().strip()
    print(received_data, type(received_data))

def main():

    pass

if __name__ == '__main__':

    main()
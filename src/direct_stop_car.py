import serial
import time

def serOpen(port = 'COM5', rate = 9600):

    ser = serial.Serial(port, rate)

    return ser

def stop(ser):

    data_to_send_1 = f'$1 0 230\n'
    data_to_send_2 = f'$2 0 230\n'
    data_to_send_3 = f'$3 0 230\n'
    data_to_send_4 = f'$4 0 230\n'
    data_to_send_5 = f'$5 0 230\n'
    data_to_send_6 = f'$6 0 230\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())
    ser.write(data_to_send_5.encode())
    ser.write(data_to_send_6.encode())

arduino2 = serOpen(port = 'COM12', rate = 19200)
time.sleep(1)

stop(arduino2)
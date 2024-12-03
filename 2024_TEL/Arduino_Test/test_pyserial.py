# pipenv install pyserial
import serial
import time

def main():
    # 串口初始化
    ser = serial.Serial('COM5', 9600)

    # 等待串口初始化完成
    time.sleep(1)

    # 向 Arduino 發送數據
    data_to_send = f'$5 0 100\n'
    print(data_to_send)
    ser.write(data_to_send.encode()) 

    # 等待一點時間以確保 Arduino 有足够的時間處理數據
    # time.sleep(0.25)

    # 從 Arduino 接收數據
    received_data = ser.readline().decode().strip()
    print(received_data, type(received_data))
    
    # data = ser.read(20) #是讀20個字元
    # data = ser.readline() #是讀一行，以/n結束，要是沒有/n就一直讀，阻塞。

    # 关闭串口
    ser.close()

if __name__ == '__main__':

    main()
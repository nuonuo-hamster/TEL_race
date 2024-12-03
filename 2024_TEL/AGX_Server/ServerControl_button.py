import socket
import serial
import time
import threading
import os
import sys

# 設定 Arduino 的串口
try:
    arduino1 = serial.Serial('/dev/ttyACM1', 9600, timeout=1)  
    # arduino2 = serial.Serial('/dev/ttyACM0', 19200, timeout=1)  
    # arduino2  = 0
    time.sleep(1)  # 等待串口初始化
except serial.SerialException as e:
    print(f"Failed to connect to Arduino: {e}") 

# 設定接收端 UDP 的 IP 和端口
UDP_IP = "0.0.0.0"  # 接收來自任何 IP 的訊號
UDP_PORT1 = 8888      
# UDP_PORT2 = 9999

# 創建一個 UDP socket
sock1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock1.bind((UDP_IP, UDP_PORT1))  # 綁定接收端 IP 和端口
# sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# sock2.bind((UDP_IP, UDP_PORT2))  # 綁定接收端 IP 和端口

print(f"Listening for messages on {UDP_IP}:{UDP_PORT1}")
# print(f"Listening for messages on {UDP_IP}:{UDP_PORT2}")

def restart_program():
    """重新啟動 Python 程式"""
    print("正在重新啟動程式...")
    time.sleep(1)  # 等待 1 秒鐘
    python = sys.executable  # 取得當前 Python 解釋器
    os.execl(python, python, *sys.argv)  # 重新啟動當前程式
    print("System restart...")

def control_arduino1(signal):
    print(f"Sending message to Arduino 1: {signal}")
    """根據接收到的訊號控制 Arduino"""
    if signal == "1":
        print("Received command 1: Rotate 1F Servo")
        arduino1.write(f"1\n".encode())  # 控制 1F Servo
    elif signal == "2":
        print("Received command 2: Rotate 2F Servo")
        arduino1.write(f"2\n".encode())  # 控制 2F Servo
    elif signal == "3":
        print("Received command 3: 2F slide open")
        arduino1.write(f"3\n".encode())  # 控制2F slide open
    elif signal == "4":
        print("Received command 4: 2F slide close")
        arduino1.write(f"4\n".encode())  # 控制2F slide close
    elif signal == "5":
        print("Received command 5: Camera Y angle +10")
        arduino1.write(f"5\n".encode())  # 控制相機 Y 角度 +10
    elif signal == "6":
        print("Received command 6: Camera Y angle -10")
        arduino1.write(f"6\n".encode())  # 控制相機 Y 角度 -10
    elif signal == "7":
        print("Received command 7: 2F servo adjust forward")
        arduino1.write(f"7\n".encode())  # 微調2F servo 往前
    elif signal == "8":
        print("Received command 8: 2F servo adjust back")
        arduino1.write(f"8\n".encode())  # 微調2F servo 往後
    elif signal == "9":
        print("Received command 9: 1F servo adjust back")
        arduino1.write(f"9\n".encode())  # 微調1F servo 往後
    elif signal == "a":
        print("Received command a: 1F servo adjust forward")
        arduino1.write(f"a\n".encode())  # 微調1F servo 往前
    elif signal == "b":
        print("Received command b: Frisbee launch")
        arduino1.write(f"b\n".encode())  # 微調1F servo 往前
    elif signal == "c":
        print("Received command c: 1F servo adjust forward")
        arduino1.write(f"c\n".encode())  # 微調1F servo 往前
    elif signal == "d":
        print("Received command d: 1F servo adjust forward")
        arduino1.write(f"d\n".encode())  # 微調1F servo 往前
    elif signal == "L":
        print("Received command L: Launch")
        arduino1.write(f"L\n".encode()) 
    elif signal == "exit":
        print("Received command: Exit program")
        restart_program()
        # arduino1.close()  # 關閉 Arduino 串口
        # sock1.close()  # 關閉 UDP socket
        # sock2.close()                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               .close()  # 關閉 UDP socket
        # exit()  # 終止程序

# def control_arduino2(msg):
#     print(f"Sending message to Arduino 2: {msg}")
#     arduino2.write(msg.encode())

import os
# 接收訊號並處理
while True:
    # wheel_data, wheel_addr = sock2.recvfrom(1024)  # 接收資料，最大長度為 1024 bytes
    button_data, button_addr = sock1.recvfrom(1024)  # 接收資料，最大長度為 1024 bytes
    # print(f"Received message: {wheel_data.decode()} from {wheel_addr}")
    print(f"Received message: {button_data.decode()} from {button_addr}")

    # 處理接收到的訊號並控制 Arduino
    thread1 = threading.Thread(target=control_arduino1, args=(button_data.decode(),))
    # thread2 = threading.Thread(target=control_arduino2, args=(wheel_data.decode(),))

    os.system("clear")

    thread1.start()
    # thread2.start()

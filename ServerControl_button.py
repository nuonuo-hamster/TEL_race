import socket
import serial
import time
import threading
import os
import sys
import cv2
from src import d435i

button_msg = None
current_pwm = 0
target_rpm = 0

# 設定 arduino_servo 的串口
try:
    arduino_servo = serial.Serial('/dev/ttyACM0', 9600, timeout=1)  
    arduino_launch = 0 #serial.Serial('/dev/ttyACM0', 28800, timeout=1)
    print("Arduino_servo successfully connected")
    print("Arduino_launch successfully connected")
    time.sleep(1)  # 等待串口初始化
except serial.SerialException as e:
    print(f"Failed to connect to arduino_servo: {e}") 
    exit(1)

# 設定接收端 UDP 的 IP 和端口
UDP_IP = "0.0.0.0"  # 接收來自任何 IP 的訊號
UDP_PORT = 8888      

# 創建一個 UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))  # 綁定接收端 IP 和端口

def connectD435i(width=640, height=480, device_number=None):
    pipe1 = d435i.realsense_init(width, height, device_number)
    return pipe1

def restart_program(pipe1):
    """重新啟動 Python 程式"""
    cv2.destroyAllWindows()
    pipe1.stop()
    print("正在重新啟動程式...")
    time.sleep(1)  # 等待 1 秒鐘
    python = sys.executable  # 取得當前 Python 解釋器
    print("程式重啟完畢...")
    os.execl(python, python, *sys.argv)  # 重新啟動當前程式

def control_arduino_servo(signal, pipe1):
    global button_msg, current_pwm
    print(f"Sending message to Servo: {signal}")
    """根據接收到的訊號控制 arduino_servo"""
    if signal == "1":
        # print("Received command 1: Rotate 1F Servo")
        button_msg = "Received command 1: Rotate 1F Servo"
        arduino_servo.write(f"1\n".encode())  # 控制 1F Servo
    elif signal == "2":
        # print("Received command 2: Rotate 2F Servo")
        button_msg = "Received command 2: Rotate 2F Servo"
        arduino_servo.write(f"2\n".encode())  # 控制 2F Servo
    elif signal == "3":
        # print("Received command 3: 2F slide open")
        button_msg = "Received command 3: 2F slide open"
        arduino_servo.write(f"3\n".encode())  # 控制2F slide open
    elif signal == "4":
        # print("Received command 4: 2F slide close")
        button_msg = "Received command 4: 2F slide close"
        arduino_servo.write(f"4\n".encode())  # 控制2F slide close
    elif signal == "5":
        # print("Received command 5: Camera Y angle +10")
        button_msg = "Received command 5: Camera Y angle +10"
        arduino_servo.write(f"5\n".encode())  # 控制相機 Y 角度 +10
    elif signal == "6":
        # print("Received command 6: Camera Y angle -10")
        button_msg = "Received command 6: Camera Y angle -10"
        arduino_servo.write(f"6\n".encode())  # 控制相機 Y 角度 -10
    elif signal == "7":
        # print("Received command 7: 2F servo adjust forward")
        button_msg = "Received command 7: 2F servo adjust forward"
        arduino_servo.write(f"7\n".encode())  # 微調2F servo 往前
    elif signal == "8":
        # print("Received command 8: 2F servo adjust back")
        button_msg = "Received command 8: 2F servo adjust forward"
        arduino_servo.write(f"8\n".encode())  # 微調2F servo 往後
    elif signal == "9":
        # print("Received command 9: 1F servo adjust back")
        button_msg = "Received command 9: 1F servo adjust back"
        arduino_servo.write(f"9\n".encode())  # 微調1F servo 往後
    elif signal == "a":
        # print("Received command a: 1F servo adjust forward")
        button_msg = "Received command a: 1F servo adjust forward"
        arduino_servo.write(f"a\n".encode())  # 微調1F servo 往前
    elif signal == "b":
        # print("Received command b: Frisbee launch")
        button_msg = "Received command b: Frisbee launch"
        arduino_servo.write(f"b\n".encode())  # 微調1F servo 往前
    elif signal == "c":
        # print("Received command c: Center motor RPM +20")
        button_msg = "Received command c: Center motor RPM +20"
        current_pwm += 20
        arduino_servo.write(f"c\n".encode())  # 微調1F servo 往前
    elif signal == "d":
        # print("Received command d: Center motor RPM is set to ZERO")
        button_msg = "Received command d: Center motor RPM is set to ZERO"
        current_pwm = 0
        arduino_servo.write(f"d\n".encode())  # 微調1F servo 往前
    elif signal == 'e':
        _, _, _, yaw, _ = d435i.realsense_run(pipe1)
        # print("Received command e: 設定最近距離目標, Yaw= "f"{yaw}")
        button_msg = "Received command e: 設定最近距離目標, Yaw= "f"{yaw}"
        arduino_launch.write(f"1"f"{yaw}""\n".encode())  # 調整目標在最近位置
    elif signal == 'f':
        # print("Received command e: 設定中等距離目標, Yaw= "f"{yaw}")
        button_msg = "Received command e: 設定中等距離目標, Yaw= "f"{yaw}"
        _, _, _, yaw, _ = d435i.realsense_run(pipe1)
        arduino_launch.write(f"2"f"{yaw}""\n".encode()) # 調整目標在中等位置
    elif signal == "L":
        # print("Received command L: Launch")
        button_msg = "Received command L: Launch"
        arduino_servo.write(f"L\n".encode()) 
    elif signal == "restart":
        # print("Received command: Restart program ")
        button_msg = "Received command: Restart program"
        restart_program(pipe1)   
        

def d435i_framing(pipe1, device_number):
    while True:
        _, color_image, _, yaw, pitch = d435i.realsense_run(pipe1)
           
        d435i.put_text(color_image, 1, yaw, 10, 30)
        d435i.put_text(color_image, 2, pitch, 10, 60)

        if device_number == 1:  
            cv2.imshow('843112070310', color_image)
            if cv2.waitKey(1) == 27: # esc
                break
        if device_number == 2:  
            cv2.imshow('923322072763', color_image)
            if cv2.waitKey(1) == 27: # esc
                break

    cv2.destroyAllWindows()
    pipe1.stop()

def target_rpm_list():
    global current_pwm
    global target_rpm
    if current_pwm == 0:
        target_rpm = 0
    elif current_pwm == 20:
        target_rpm = 0
    elif current_pwm == 40:
        target_rpm = 780
    elif current_pwm == 60:
        target_rpm = 2190
    elif current_pwm == 80:
        target_rpm = 3100
    elif current_pwm == 100:
        target_rpm = 4070
    elif current_pwm == 120:
        target_rpm = 4530
    elif current_pwm == 140:
        target_rpm = 4830
    elif current_pwm == 160:
        target_rpm = 5040
    elif current_pwm == 180:
        target_rpm = 5250
    elif current_pwm == 200:
        target_rpm = 5410
    elif current_pwm == 220:
        target_rpm = 5470
    elif current_pwm == 240:
        target_rpm = 5650

def receive_arduino_msg():
    global button_msg, current_pwm, target_rpm
    while True:
        try:
            received_data = arduino_servo.readline().decode('utf-8').strip() 
            target_rpm_list()
            print("Current PWM is: "f"{current_pwm}"", be sure RPM is above: "f'{target_rpm}')
            if received_data:
                os.system("clear")
                print("RPM: ", received_data)
                print(f"{button_msg}")
        except:
            pass

def start():                                                                   
    
    print(f"Listening for messages on {UDP_IP}:{UDP_PORT}")
    # pipe1 = connectD435i(width=640, height=480, device_number=843112070310)
    pipe2 = connectD435i(width=640, height=480, device_number=923322072763)
    # print("pipe1 created")
    print("pipe2 created")

    # thread1 = threading.Thread(target=d435i_framing, args=(pipe1, 1))
    thread2 = threading.Thread(target=d435i_framing, args=(pipe2, 2))
    thread4 = threading.Thread(target=receive_arduino_msg)
    # thread1.start()
    thread2.start()
    thread4.start()

    # 接收訊號並處理
    while True:
        button_data, button_addr = sock.recvfrom(1024)  # 接收資料，最大長度為 1024 bytes
        
        os.system("clear")
        # print(f"Received message: {button_data.decode()} from {button_addr}")

        # 處理接收到的訊號並控制 arduino_servo
        thread3 = threading.Thread(target=control_arduino_servo, args=(button_data.decode(), pipe2))
        thread3.start()

if __name__ == "__main__":
    start()

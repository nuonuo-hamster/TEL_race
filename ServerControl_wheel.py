import socket
import serial
import time
import threading
import os

# 設定 Arduino 的串口
try:
    arduino = serial.Serial('/dev/ttyACM0', 19200, timeout=1)  
    time.sleep(1)  # 等待串口初始化
except serial.SerialException as e:
    try:
        arduino = serial.Serial('/dev/ttyACM1', 19200, timeout=1)  
        time.sleep(1)  # 等待串口初始化
    except serial.SerialException as e:
        print(f"Failed to connect to Arduino: {e}")
        exit(1)

# 設定接收端 UDP 的 IP 和端口
UDP_IP = "0.0.0.0"  # 接收來自任何 IP 的訊號
UDP_PORT = 9999

# 創建一個 UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))  # 綁定接收端 IP 和端口

def control_arduino(msg):
    # print(f"Sending message to Wheels: {msg}")
    arduino.write(msg.encode())

def start():

    print(f"Listening for messages on {UDP_IP}:{UDP_PORT}")

    # 接收訊號並處理
    while True:
        wheel_data, wheel_addr = sock.recvfrom(1024)  # 接收資料，最大長度為 1024 bytes

        os.system("clear")
        print(f"Received message: {wheel_data.decode()}from {wheel_addr}")
        print(f"Sending message to Wheels: {wheel_data.decode()}")

        # 處理接收到的訊號並控制 Arduino
        thread = threading.Thread(target=control_arduino, args=(wheel_data.decode(),))
        thread.start()

if __name__ == "__main__":
    start()
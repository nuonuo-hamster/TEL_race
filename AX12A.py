import Jetson.GPIO as GPIO
import serial
import time

# 設置 GPIO 模式
#GPIO.setmode(GPIO.BOARD)
GPIO.setmode(GPIO.BCM)  # 使用 BCM 編號模式
GPIO.setup(17, GPIO.OUT)  # 這裡的 17 是 BCM 編號

# 假設我們使用 GPIO17 作為 Data 引腳來控制 TX/RX 的方向
DATA_PIN = 17  # 這裡假設用 GPIO 17 來控制數據方向

# 設定 GPIO 引腳為輸入或輸出
GPIO.setup(DATA_PIN, GPIO.OUT)

# UART 設置，假設我們使用 /dev/ttyTHS1 作為串口
ser = serial.Serial('/dev/ttyTHS1', 57600, timeout=1)  # 設定為 57600 波特率

# 控制方向：設定為輸出模式，將數據傳送到 AX-12A
def set_tx():
    GPIO.setup(DATA_PIN, GPIO.OUT)  # 設定 DATA_PIN 為輸出，傳送數據
    print("Set direction: TX")

# 控制方向：設定為輸入模式，從 AX-12A 讀取數據
def set_rx():
    GPIO.setup(DATA_PIN, GPIO.IN)   # 設定 DATA_PIN 為輸入，接收數據
    print("Set direction: RX")

# 發送數據到 AX-12A 馬達
def send_data(data):
    set_tx()  # 設定為發送模式
    ser.write(data)  # 寫入數據
    time.sleep(0.1)  # 等待發送完成

# 讀取來自 AX-12A 馬達的數據
def read_data():
    set_rx()  # 設定為接收模式
    response = ser.read(5)  # 假設我們期望收到 5 個字節的回應
    print(f"Received data: {response}")
    return response

def main():
    try:
        # 發送指令給 AX-12A
        send_data(b'\xFF\xFF\x01\x03\x02')  # 這是一個範例的指令
        time.sleep(0.1)
        
        # 讀取來自 AX-12A 的回應
        read_data()

    except KeyboardInterrupt:
        print("Program interrupted.")
    
    finally:
        ser.close()  # 關閉串口
        GPIO.cleanup()  # 清理 GPIO

if __name__ == "__main__":
    main()


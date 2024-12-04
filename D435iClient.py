import cv2
import socket
import pickle
import struct
import numpy as np

def connectServer(ip, port):
    # 連接到 server
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((ip, port))
    return client_socket

def GetFrame(tunnel):
    try:
        # 讀取數據大小並解包
        size = struct.unpack('!I', tunnel.read(struct.calcsize('!I')))[0]
        data = tunnel.read(size)

        # 使用 pickle 解包數據字典
        data_dict = pickle.loads(data)

        color_image_bytes = data_dict["color_image_bytes"]
        color_image_shape = data_dict["color_image_shape"]
        color_image = np.frombuffer(color_image_bytes, dtype=np.uint8).reshape(color_image_shape)
        yaw = data_dict["yaw"]
        pitch = data_dict["pitch"]

        return color_image, yaw, pitch

    except Exception as e:
        print("Error unpacking frame:", e)
        return None, None, None

def clientClose(client_socket):
    # 關閉 socket 連接
    client_socket.close()

def test(ip=None, port=7777):
    # 從ip.txt拿ip
    with open("./ip.txt", 'r') as file:
        line = file.readline().strip()
        if line.startswith("ip="):
            ip = line.split('=')[1].strip("'")
    if ip is None: return

    try:
        print(f"Connecting to server at {ip}:{port}...")
        client_socket = connectServer(ip, port)
        print(f"Successfully connected to {ip}:{port}.")

        try:
            print("Getting frame from server...")
            tunnel = client_socket.makefile('rb')

            while True:
                # 從 server 接收並解包影像數據
                color_image, yaw, pitch = GetFrame(tunnel)

                if color_image is None:
                    print("Failed to receive valid frame.")
                    break

                # 顯示接收到的影像
                print(f"Yaw: {yaw:.2f}, Pitch: {pitch:.2f}")
                cv2.imshow('Client', color_image)

                # 按 ESC 鍵退出
                if cv2.waitKey(1) == 27:  # esc
                    break

            cv2.destroyAllWindows()
            tunnel.close()

        except Exception as e:
            print(f"Error while receiving frames: {e}")

        clientClose(client_socket)

    except Exception as e:
        print(f"Error connecting to server: {e}")

if __name__ == '__main__':

    test()

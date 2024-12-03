import cv2
import socket
import pickle
import struct
import numpy as np
from cam import d435i  # 假設 d435i 是你自定義的模組

def connectD435i(width=640, height=480):
    pipe = d435i.realsense_init(width, height)
    return pipe

def serverOpen(port):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('0.0.0.0', port))
    server_socket.listen(5)
    return server_socket

def loopSendFrame(tunnel, pipe):
    connection = tunnel.makefile('wb')

    while True:
        # 獲取深度圖像和顏色圖像以及 yaw 和 pitch
        depth_frame, color_image, depth_cm, yaw, pitch = d435i.realsense_run(pipe)

        # 轉換 color_image 為 bytes
        color_image_bytes = color_image.tobytes()
        color_image_shape = color_image.shape

        # 轉換 depth_frame 為 bytes（將深度數據轉換為 numpy 陣列）
        depth_data = np.asanyarray(depth_frame.get_data())
        depth_bytes = depth_data.tobytes()

        # 包裝數據
        data_dict = {
            "color_image_bytes": color_image_bytes,
            "color_image_shape": color_image_shape,
            "yaw": yaw,
            "pitch": pitch,
            "depth_bytes": depth_bytes,  # 加入深度數據
            "depth_shape": depth_data.shape
        }

        # 序列化並打包數據
        data = pickle.dumps(data_dict)
        size = struct.pack('!I', len(data))  # 打包數據大小

        # 發送數據：先發送數據大小，然後發送數據本身
        connection.write(size)
        connection.write(data)

        if cv2.waitKey(1) == 27:  # 按 ESC 退出
            break

    connection.close()

def main():
    print("connect D435i...")
    pipe = connectD435i(width=640, height=480)

    print("open server...")
    server_socket = serverOpen(port=7777)

    while True:
        try:
            print("Wait for client...")
            tunnel, addr = server_socket.accept()
            print(f"Client connected: {addr}")

            print("send frame...")
            loopSendFrame(tunnel, pipe)

            tunnel.close()
            print("client offline")
        except Exception as e:
            print(f"Server error: {e}")

    pipe.stop()

if __name__ == '__main__':
    main()


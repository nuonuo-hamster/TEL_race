import cv2
import socket
import pickle
import struct
import numpy as np
from src import d435i

def connectD435i(width=640, height=480):

    pipe = d435i.realsense_init(width, height)
    return pipe

def serverOpen(port):

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('0.0.0.0', port))
    server_socket.listen(5)
    return server_socket

def loopSendFrame(tunnel, pipe):
    try:
        connection = tunnel.makefile('wb')
        while True:
            depth_frame, color_image, depth_cm, yaw, pitch = d435i.realsense_run(pipe)

            color_image_bytes = color_image.tobytes()
            color_image_shape = color_image.shape

            # 打包數據並發送
            data_dict = {
                "color_image_bytes": color_image_bytes,
                "color_image_shape": color_image_shape,
                "yaw": yaw,
                "pitch": pitch
            }
            data = pickle.dumps(color_image)
            size = struct.pack('!I', len(data))

            # 發送數據
            connection.write(size)
            connection.write(data)
            connection.flush()

            if cv2.waitKey(1) == 27:  # esc
                break

    except (BrokenPipeError, ConnectionResetError) as e:
        print("Connection error:", e)

    finally:
        connection.close()

def main():

    print("Connect D435i...")
    pipe = connectD435i(width=640, height=480)

    print("Open server...")
    server_socket = serverOpen(port=8888)

    while(True):
        try:
            print("Wait for client...")
            tunnel, addr = server_socket.accept()
            
            print(f"Sending frame to client {addr} ...")
            loopSendFrame(tunnel, pipe)
            
            tunnel.close()
            print("Client offline")

        except Exception as e:
            print("Server error:", e)
            
    pipe.stop()

if __name__ == '__main__':

    main()
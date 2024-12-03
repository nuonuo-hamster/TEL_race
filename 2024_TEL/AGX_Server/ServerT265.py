import socket
import pickle

from cam import t265

def connectT265():

    pipe = t265.cam_init()
    return pipe

def serverOpen(port):

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('0.0.0.0', port))
    server_socket.listen(5)
    return server_socket

def SendPose(tunnel, pipe):

    frame_number, position, rpy_rad = t265.poseProcess(pipe)
    array = [frame_number, position, rpy_rad]

    data = pickle.dumps(array)
    tunnel.send(data)

    recv_data = tunnel.recv(1024) # 同步 "data has been received."


def main():

    print("connect T265...")
    pipe = connectT265()

    print("open server...")
    server_socket = serverOpen(port=8889)

    while(True):
        print("Wait for client...")
        tunnel, addr = server_socket.accept()
        
        try:
            print("send frame...")
            while(True):
                SendPose(tunnel, pipe)
        except:
            print("send frame ended.")

        tunnel.close()
        print("client offline")

    t265.cam_close(pipe)

if __name__ == '__main__':

    main()
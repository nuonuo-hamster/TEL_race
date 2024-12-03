import socket
import pickle
import math
import numpy as np

def connectServer(ip, port):

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((ip, port))

    return client_socket

def getPose(client_socket):

    data = client_socket.recv(1024)
    poseArray = pickle.loads(data)
    client_socket.send("data has been received.".encode('gbk')) # 同步

    return poseArray

# while 死鎖直到移動一定距離
def streamUntilDistance(ip, port, cm):

    client_socket = connectServer(ip, port)
    
    poseArray = getPose(client_socket)
    originPosition = np.array([poseArray[1][0], poseArray[1][2]])

    while(True):

        poseArray = getPose(client_socket)
        currentPosition = np.array([poseArray[1][0], poseArray[1][2]])

        distance = 100*np.linalg.norm(currentPosition - originPosition)
        print('{:.2f} cm'.format(distance))

        if(distance >= cm): break

    client_socket.close()

# while 死鎖直到移動一定角度
def streamUntilDegree(ip, port, degree):

    client_socket = connectServer(ip, port)
    
    poseArray = getPose(client_socket)
    originDegree = poseArray[2][2]

    while(True):

        poseArray = getPose(client_socket)
        currentDegree = poseArray[2][2]

        angle = abs(currentDegree - originDegree) *180/math.pi
        print('{:.2f} degree'.format(angle))

        if(angle >= degree): break

    client_socket.close()

def test(ip='192.168.137.103', port=8889):

    client_socket = connectServer(ip, port)
    
    for _ in range(500):
        poseArray = getPose(client_socket)
        print(poseArray) # (frame number, (x, y, z), (row, pitch, yaw))
        # 相機的(x, y, z) -> 實際的(x, z, -y)

    client_socket.close()

if __name__ == '__main__':

    test(ip='192.168.137.103', port=8889)
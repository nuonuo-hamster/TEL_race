import socket

def connectWheelServer(ip, port):
  
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((ip, port))
    return client_socket

def sendText(client_socket, text):
    client_socket.send(text.encode())

def clientClose(client_socket):
    client_socket.close()

# 用這個發送
def sendToServer(sendingText, ip, port):

    try:
        client_socket = connectWheelServer(ip, port)
        
        try:
            sendText(client_socket, text=sendingText)
            print('send access.')
        except:
            print('failed to send.')

        clientClose(client_socket)
    except:
        print("failed to send.")

def test(ip='192.168.137.103', port=8899):
    
    try:
        print("connect Wheel server...")
        client_socket = connectWheelServer(ip, port)
        print("connect success.")
        
        try:
            sendText(client_socket, text='$1 1 150\n')
        except:
            print('send text failed.')

        clientClose(client_socket)
    except:
        print("connect err.")

if __name__ == '__main__':

    test(ip='192.168.137.103', port=8899)

    # # sendingText: f'$(wheel number) (forword 1 backward 2) (speed 0~255))\n'
    # sendToServer(sendingText=f'$1 1 150\n', ip='192.168.137.103', port=8899)
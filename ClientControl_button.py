import threading
import time
import socket
from src.controller_config import*

def create_socket(server_ip, server_port):

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return client_socket, (server_ip, server_port)

def send_control_message(client_socket, server_address, message=''):
    try:
        client_socket.sendto(message.encode(), server_address)
    except Exception as e:
        print(f"Error sending message: {e}")

# thread loop
def control_buttom(controller, client_socket, server_address):
    flag_X = False
    layer = 0
    while True:
        if layer==0: ##搖桿操作的第一層
            buttons = controller.get_buttons()
            up, right, down, left = controller.get_pad()
            if buttons[LEFT_BUMP]:
                print("LB pressed, rotating 1F servo")
                send_control_message(client_socket, server_address, message="1")
                time.sleep(0.1)

            elif buttons[RIGHT_BUMP]:
                print("RB pressed, rotating 2F servo")
                send_control_message(client_socket, server_address, message="2")
                time.sleep(0.1)

            elif buttons[X] and flag_X == False:
                print("X pressed, 2F silde move")
                send_control_message(client_socket, server_address, message="3")
                flag_X = True
                time.sleep(0.1)

            elif buttons[X] and flag_X == True:
                print("X pressed, close")
                send_control_message(client_socket, server_address, message="4")
                flag_X = False
                time.sleep(0.1)

            elif buttons[A]:
                print("A pressed")
                send_control_message(client_socket, server_address, message="6")
                time.sleep(0.1)

            elif buttons[B]:
                print("B pressed, launching frisbee")
                send_control_message(client_socket, server_address, message="b")
                time.sleep(0.1)
                
            elif buttons[Y]:
                print("Y pressed")
                send_control_message(client_socket, server_address, message="5")
                time.sleep(0.1)
            
            elif up == 1:
                print("Pad Up")
                send_control_message(client_socket, server_address, message="7")
                time.sleep(0.1)

            elif down == 1:
                print("Pad Down")
                send_control_message(client_socket, server_address, message="8")
                time.sleep(0.1)

            elif right == 1:
                print("Pad Right")
                send_control_message(client_socket, server_address, message="c")
                time.sleep(0.1)

            elif left == 1:
                print("Pad Left")
                send_control_message(client_socket, server_address, message="d")
                time.sleep(0.1)

            elif buttons[RIGHT_STICK_BTN]:
                print("Right stick pressed")
                send_control_message(client_socket, server_address, message="exit")
                time.sleep(0.1)
                break

            elif buttons[LEFT_STICK_BTN]:
                print("Left stick pressed")
                layer = 1
                print("現在在第二層半自動操作")
                time.sleep(0.1)
            time.sleep(0.1)
            
        while layer==1: ##搖桿操作的第二層
            buttons = controller.get_buttons()
            up, right, down, left = controller.get_pad()
            if buttons[LEFT_BUMP]:
                print("LB pressed, rotating 1F servo")
                send_control_message(client_socket, server_address, message="1")
                time.sleep(0.1)

            elif buttons[RIGHT_BUMP]:
                print("RB pressed, rotating 2F servo")
                send_control_message(client_socket, server_address, message="2")
                time.sleep(0.1)

            elif buttons[X] and flag_X == False:
                print("X pressed, 2F silde move")
                send_control_message(client_socket, server_address, message="3")
                flag_X = True
                time.sleep(0.1)

            elif buttons[X] and flag_X == True:
                print("X pressed, close")
                send_control_message(client_socket, server_address, message="4")
                flag_X = False
                time.sleep(0.1)

            elif buttons[A]:
                print("A pressed")
                send_control_message(client_socket, server_address, message="6")
                time.sleep(0.1)

            elif buttons[B]:
                print("B pressed, launching frisbee")
                send_control_message(client_socket, server_address, message="b")
                time.sleep(0.1)
                
            elif buttons[Y]:
                print("Y pressed")
                send_control_message(client_socket, server_address, message="5")
                time.sleep(0.1)
            
            elif up == 1:
                print("Pad Up")
                send_control_message(client_socket, server_address, message="7")
                time.sleep(0.1)

            elif down == 1:
                print("Pad Down")
                send_control_message(client_socket, server_address, message="8")
                time.sleep(0.1)

            elif right == 1:
                print("Pad Right")
                send_control_message(client_socket, server_address, message="c")
                time.sleep(0.1)

            elif left == 1:
                print("Pad Left")
                send_control_message(client_socket, server_address, message="d")
                time.sleep(0.1)

            elif buttons[RIGHT_STICK_BTN]:
                print("Right stick pressed")
                send_control_message(client_socket, server_address, message="exit")
                time.sleep(0.1)
                break

            elif buttons[LEFT_STICK_BTN]:
                print("Left stick pressed")
                layer = 0
                print("現在在第一層手動操作")
                time.sleep(0.1)

            time.sleep(0.1)

            # if buttons[A]:
            #     arduino1.write(b'1')  # Move Servo 1
            # if buttons[B]:
            #     arduino1.write(b'2')  # Move Servo 2
            # if buttons[LEFT_BUMP]:
            #     arduino1.write(b'3')  # Move Servo 3

def start():
    # 從ip.txt拿ip
    server_ip = None
    with open("./ip.txt", 'r') as file:
        line = file.readline().strip()
        if line.startswith("ip="):
            server_ip = line.split('=')[1].strip("'")
    if server_ip is None: return

    controller_start()
    print("---------------------------")

    controller = Controller(dead_zone=0.15)
    client_socket, server_address = create_socket(server_ip, server_port=8888)

    thread = threading.Thread(target=control_buttom, args=(controller, client_socket, server_address))
    thread.start()

    controller_loop()

if __name__ == "__main__":
    start()

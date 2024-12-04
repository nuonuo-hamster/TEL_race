import threading
import time
import socket
import os
from src.controller_config import*
from src.three_dimension_movement import car_move_wrap

def create_socket(server_ip, server_port):
    
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return client_socket, (server_ip, server_port)

# thread loop
def control_rooler(controller, client_socket, server_address):
    map_controller = [-1, 1]
    map_Movement = [-200, 200]
    car_move = car_move_wrap(map_controller, map_Movement, client_socket, server_address)
    old_key = None
    car_instruct = ''

    while True:
        pygame.event.pump()

        left_stick_x, left_stick_y = controller.get_left_stick()
        right_stick_x, right_stick_y = controller.get_right_stick()

        if left_stick_x > 0.2: 
            left_stick_x = 1
        elif left_stick_x < -0.2:
            left_stick_x = -1
        else:
            left_stick_x = 0

        if left_stick_y > 0.2: 
            left_stick_y = 1
        elif left_stick_y < -0.2:
            left_stick_y = -1
        else:
            left_stick_y = 0

        if right_stick_x > 0.2: 
            right_stick_x = 1
        elif right_stick_x < -0.2:
            right_stick_x = -1
        else:
            right_stick_x = 0
        
        os.system('cls')
        print(f"Left joystick: X = {left_stick_x}, Y = {-left_stick_y} || Right joystick: X = {right_stick_x}, Y = {right_stick_y}")
        print(car_instruct)
        key = left_stick_y,left_stick_x,right_stick_x
        if old_key!=key:
            car_instruct = car_move(-left_stick_y, left_stick_x, right_stick_x)
        old_key = key 

        time.sleep(0.1)

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
    client_socket, server_address = create_socket(server_ip, server_port=9999)

    thread = threading.Thread(target=control_rooler, args=(controller, client_socket, server_address))
    thread.start()

    controller_loop()

if __name__ == "__main__":
    start()

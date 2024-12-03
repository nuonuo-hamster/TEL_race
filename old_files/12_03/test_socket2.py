import threading
import serial
import pygame
import sys
import time
import socket
import wheel_ctl_base
from three_dimension_movement import car_move, car_move_wrap

LINUX = 0
MAC = 1
WINDOWS = 2

platform = sys.platform
version = int(pygame.version.ver[0])

if platform.startswith("lin"):
    platform_id = LINUX
elif platform.startswith("darwin"):
    platform_id = MAC
elif platform.startswith("win"):
    platform_id = WINDOWS

if platform_id == LINUX:
    print("Linux")
    A = 0
    B = 1
    X = 2
    Y = 3
    LEFT_BUMP = 4
    RIGHT_BUMP = 5
    BACK = 6
    START = 7
    LEFT_STICK_BTN = 9
    RIGHT_STICK_BTN = 10
    LEFT_STICK_X = 0
    LEFT_STICK_Y = 1
    RIGHT_STICK_X = 3
    RIGHT_STICK_Y = 4
    LEFT_TRIGGER = 2
    RIGHT_TRIGGER = 5

elif platform_id == WINDOWS:
    print("Windows")
    A = 0
    B = 1
    X = 2
    Y = 3
    LEFT_BUMP = 4
    RIGHT_BUMP = 5
    BACK = 6
    START = 7
    LEFT_STICK_BTN = 8
    RIGHT_STICK_BTN = 9
    LEFT_STICK_X = 0
    LEFT_STICK_Y = 1
    if version == 2:
        RIGHT_STICK_X = 2
        RIGHT_STICK_Y = 3
        LEFT_TRIGGER = 4
        RIGHT_TRIGGER = 5
    else:
        RIGHT_STICK_X = 4
        RIGHT_STICK_Y = 3
        TRIGGERS = 2

elif platform_id == MAC:
    print("Mac")
    A = 11
    B = 12
    X = 13
    Y = 14
    LEFT_BUMP = 8
    RIGHT_BUMP = 9
    BACK = 5
    START = 4
    LEFT_STICK_BTN = 6
    RIGHT_STICK_BTN = 7
    PAD_UP = 0
    PAD_DOWN = 1
    PAD_LEFT = 2
    PAD_RIGHT = 3
    LEFT_STICK_X = 0
    LEFT_STICK_Y = 1
    RIGHT_STICK_X = 2
    RIGHT_STICK_Y = 3
    LEFT_TRIGGER = 4
    RIGHT_TRIGGER = 5


class Controller:

    id_num = 0

    def __init__(self, dead_zone=0.15):
        self.joystick = pygame.joystick.Joystick(Controller.id_num)
        self.joystick.init()
        self.dead_zone = dead_zone
        self.left_trigger_used = False
        self.right_trigger_used = False
        Controller.id_num += 1

    def get_id(self):
        return self.joystick.get_id()

    def dead_zone_adjustment(self, value):
        if value > self.dead_zone:
            return (value - self.dead_zone) / (1 - self.dead_zone)
        elif value < -self.dead_zone:
            return (value + self.dead_zone) / (1 - self.dead_zone)
        else:
            return 0

    def get_buttons(self):
        if platform_id == LINUX:
            return (self.joystick.get_button(A),
                    self.joystick.get_button(B),
                    self.joystick.get_button(X),
                    self.joystick.get_button(Y),
                    self.joystick.get_button(LEFT_BUMP),
                    self.joystick.get_button(RIGHT_BUMP),
                    self.joystick.get_button(BACK),
                    self.joystick.get_button(START),
                    0, # Unused, since Guide only works on Linux
                    self.joystick.get_button(LEFT_STICK_BTN),
                    self.joystick.get_button(RIGHT_STICK_BTN))

        elif platform_id == WINDOWS:
            return (self.joystick.get_button(A),
                    self.joystick.get_button(B),
                    self.joystick.get_button(X),
                    self.joystick.get_button(Y),
                    self.joystick.get_button(LEFT_BUMP),
                    self.joystick.get_button(RIGHT_BUMP),
                    self.joystick.get_button(BACK),
                    self.joystick.get_button(START),
                    self.joystick.get_button(LEFT_STICK_BTN),
                    self.joystick.get_button(RIGHT_STICK_BTN))

        elif platform_id == MAC:
            return (0, # Unused
                    0, # Unused
                    0, # Unused
                    0, # Unused
                    self.joystick.get_button(START),
                    self.joystick.get_button(BACK),
                    self.joystick.get_button(LEFT_STICK_BTN),
                    self.joystick.get_button(RIGHT_STICK_BTN),
                    self.joystick.get_button(LEFT_BUMP),
                    self.joystick.get_button(RIGHT_BUMP),
                    0, # Unused
                    self.joystick.get_button(A),
                    self.joystick.get_button(B),
                    self.joystick.get_button(X),
                    self.joystick.get_button(Y))

    def get_left_stick(self):
        left_stick_x = self.dead_zone_adjustment(self.joystick.get_axis(LEFT_STICK_X))
        left_stick_y = self.dead_zone_adjustment(self.joystick.get_axis(LEFT_STICK_Y))
        return (left_stick_x, left_stick_y)

    def get_right_stick(self):
        right_stick_x = self.dead_zone_adjustment(self.joystick.get_axis(RIGHT_STICK_X))
        right_stick_y = self.dead_zone_adjustment(self.joystick.get_axis(RIGHT_STICK_Y))
        return (right_stick_x, right_stick_y)

    def get_triggers(self):
        trigger_axis = 0.0
        if platform_id == LINUX or platform_id == MAC:
            left = self.joystick.get_axis(LEFT_TRIGGER)
            right = self.joystick.get_axis(RIGHT_TRIGGER)

            if left != 0:
                self.left_trigger_used = True
            if right != 0:
                self.right_trigger_used = True

            if not self.left_trigger_used:
                left = -1
            if not self.right_trigger_used:
                right = -1

            trigger_axis = (-1 * left + right) / 2

        elif platform_id == WINDOWS:
            if version == 2:
                left = self.joystick.get_axis(LEFT_TRIGGER)
                right = self.joystick.get_axis(RIGHT_TRIGGER)
                trigger_axis = (-1 * left + right) / 2
            else:
                trigger_axis = -1 * self.joystick.get_axis(TRIGGERS)

        return trigger_axis

    def get_pad(self):
        if platform_id == LINUX or platform_id == WINDOWS:
            hat_x, hat_y = self.joystick.get_hat(0)
            up = int(hat_y == 1)
            right = int(hat_x == 1)
            down = int(hat_y == -1)
            left = int(hat_x == -1)
        elif platform_id == MAC:
            up = self.joystick.get_button(PAD_UP)
            right = self.joystick.get_button(PAD_RIGHT)
            down = self.joystick.get_button(PAD_DOWN)
            left = self.joystick.get_button(PAD_LEFT)
        return up, right, down, left


TIME_THRESHOLD = 20
last_update_time = time.time()

def clear_joystick_cache():
    print("Clearing joystick cache (reinitializing joystick)...")
    pygame.joystick.quit()
    pygame.joystick.init()
    print("Joystick cache cleared!")
    controller = Controller(dead_zone=0.15)
    return controller

def check_joystick_cleanup():
    global last_update_time
    current_time = time.time()
    if current_time - last_update_time > TIME_THRESHOLD:
        clear_joystick_cache()
        last_update_time = current_time

def create_socket():
    server_ip = "192.168.0.222"
    server_port1 = 8888
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return client_socket, (server_ip, server_port1)

def create_socket2():
    server_ip = "192.168.0.222"
    server_port1 = 9999
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return client_socket, (server_ip, server_port1)

def send_control_message(client_socket, server_address, message1='', message2=''):
    try:
        # client_socket.sendto(message1.encode(), server_address)
        client_socket.sendto(message2.encode(), server_address)
    except Exception as e:
        print(f"Error sending message: {e}")

def control_arduino1(controller, client_socket, server_address):
    flag_X = False
    while True:
        buttons = controller.get_buttons()
        up, right, down, left = controller.get_pad()

        if buttons[LEFT_BUMP]:
            print("LB pressed, rotating 1F servo")
            send_control_message(client_socket, server_address, message2="1")
            time.sleep(0.1)

        elif buttons[RIGHT_BUMP]:
            print("RB pressed, rotating 2F servo")
            send_control_message(client_socket, server_address, message2="2")
            time.sleep(0.1)

        elif buttons[X] and flag_X == False:
            print("X pressed, 2F silde move")
            send_control_message(client_socket, server_address, message2="3")
            flag_X = True
            time.sleep(0.1)

        elif buttons[X] and flag_X == True:
            print("X pressed, close")
            send_control_message(client_socket, server_address, message2="4")
            flag_X = False
            time.sleep(0.1)

        elif buttons[A]:
            print("A pressed")
            send_control_message(client_socket, server_address, message2="6")
            time.sleep(0.1)

        elif buttons[B]:
            print("B pressed, launching frisbee")
            send_control_message(client_socket, server_address, message2="b")
            time.sleep(0.1)
            
        elif buttons[Y]:
            print("Y pressed")
            send_control_message(client_socket, server_address, message2="5")
            time.sleep(0.1)
        
        elif up == 1:
            print("Pad Up")
            send_control_message(client_socket, server_address, message2="7")
            time.sleep(0.1)

        elif down == 1:
            print("Pad Down")
            send_control_message(client_socket, server_address, message2="8")
            time.sleep(0.1)

        elif right == 1:
            print("Pad Right")
            send_control_message(client_socket, server_address, message2="c")
            time.sleep(0.1)

        elif left == 1:
            print("Pad Left")
            send_control_message(client_socket, server_address, message2="d")
            time.sleep(0.1)

        elif buttons[RIGHT_STICK_BTN]:
            print("Right stick pressed")
            send_control_message(client_socket, server_address, message2="exit")
            time.sleep(0.1)

        time.sleep(0.1)

        # if buttons[A]:
        #     arduino1.write(b'1')  # Move Servo 1
        # if buttons[B]:
        #     arduino1.write(b'2')  # Move Servo 2
        # if buttons[LEFT_BUMP]:
        #     arduino1.write(b'3')  # Move Servo 3


def control_arduino2(controller, client_socket, server_address):
    map_controller = [-1, 1]
    map_Movement = [-200, 200]
    car_move = car_move_wrap(map_controller, map_Movement, client_socket, server_address)
    
    while True:
        pygame.event.pump()

        left_stick_x, left_stick_y = controller.get_left_stick()
        right_stick_x, right_stick_y = controller.get_right_stick()

        # arduino2.write(f'{left_stick_x},{left_stick_y},{right_stick_x}\n'.encode())
        print(f"Left joystick: X = {left_stick_x}, Y = {left_stick_y} || Right joystick: X = {right_stick_x}, Y = {right_stick_y}")

        car_move(-left_stick_y, left_stick_x, right_stick_x)

        time.sleep(0.1)


def start():
    pygame.init()
    
    # 確保有控制器被檢測到
    joystick_count = pygame.joystick.get_count()
    print(f"Number of joysticks: {joystick_count}")
    
    if joystick_count == 0:
        print("No joystick found!")
        return

    controller = Controller(dead_zone=0.15)
    client_socket, server_address = create_socket()
    # client_socket2, server_address = create_socket2()

    thread1 = threading.Thread(target=control_arduino1, args=(controller, client_socket, server_address))
    # thread2 = threading.Thread(target=control_arduino2, args=(controller, client_socket2, server_address))

    thread1.start()
    # thread2.start()

    while True:
        pygame.event.pump()  # This keeps pygame's event system updated
        time.sleep(0.1)

        


if __name__ == "__main__":
    start()

import pygame
import time
import sys

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

def controller_start():
    pygame.init()
    
    # 確保有控制器被檢測到
    joystick_count = pygame.joystick.get_count()
    print(f"Number of joysticks: {joystick_count}")
    
    if joystick_count == 0:
        print("No joystick found!")
        return

def controller_loop():
    while True:
        pygame.event.pump()  # This keeps pygame's event system updated
        time.sleep(0.1)

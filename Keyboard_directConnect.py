import time
from src import keyboard_detect
from src import three_dimension_movement
from src.three_dimension_movement import car_move_wrap

old_key = None

def Wheels_keyboard_trigger(key, car_move):
    
    global old_key

    if (key == None and key != old_key):
        print('stop')
        car_move(0, 0, 0)

    elif (key == 'w' and key != old_key):
        print('forward')
        car_move(250, 0, 0)

    elif (key == 's' and key != old_key):
        print('backward')
        car_move(-250, 0, 0)
    
    elif (key == 'q' and key != old_key):
        print('turnLeft')
        car_move(0, 0, -250)
    
    elif (key == 'e' and key != old_key):
        print('turnRight')
        car_move(0, 0, 250)

    elif (key == 'a' and key != old_key):
        print('shiftLeft')
        car_move(0, -250, 0)

    elif (key == 'd' and key != old_key):
        print('shiftRight')
        car_move(0, 250, 0)

    time.sleep(0.1)
    old_key = key

def test():

    map_controller = [-100, 100]
    map_Movement = [-250, 250]

    three_dimension_movement.serOpen(port = 'COM12', rate = 19200)
    car_move = car_move_wrap(map_controller, map_Movement)

    KBConfig = keyboard_detect.keyboard_config()
    KBConfig.CreateKBDetectTask()

    time.sleep(1)
    while(True):
        key = KBConfig.currntKey[0]
        Wheels_keyboard_trigger(key, car_move)
        if (key == 'esc'): break

    three_dimension_movement.serClose()

if __name__ == '__main__':
    
    test() #沒有連server 直連Arduino控制
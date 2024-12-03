import time
from src import keyboard_detect
from src import wheel_ctl_base

old_key = None

def Wheels_keyboard_trigger(ser, key):
    
    global old_key

    if (key == None and key != old_key):
        print('stop')
        wheel_ctl_base.stop(ser)

    elif (key == 'w' and key != old_key):
        print('forward')
        wheel_ctl_base.forward(ser)

    elif (key == 's' and key != old_key):
        print('backward')
        wheel_ctl_base.backward(ser)
    
    elif (key == 'q' and key != old_key):
        print('turnLeft')
        wheel_ctl_base.turnLeft(ser)
    
    elif (key == 'e' and key != old_key):
        print('turnRight')
        wheel_ctl_base.turnRight(ser)

    elif (key == 'a' and key != old_key):
        print('shiftLeft')
        wheel_ctl_base.shiftLeft(ser)

    elif (key == 'd' and key != old_key):
        print('shiftRight')
        wheel_ctl_base.shiftRight(ser)

    time.sleep(0.1)
    old_key = key

def test():

    ser = wheel_ctl_base.serOpen(port = 'COM12', rate = 19200)
    
    KBConfig = keyboard_detect.keyboard_config()
    KBConfig.CreateKBDetectTask()
    time.sleep(1)
    while(True):
        key = KBConfig.currntKey[0]
        Wheels_keyboard_trigger(ser, key)
        if (key == 'esc'): break

    wheel_ctl_base.serClose(ser)

if __name__ == '__main__':
    
    test() #沒有連server 直連Arduino控制
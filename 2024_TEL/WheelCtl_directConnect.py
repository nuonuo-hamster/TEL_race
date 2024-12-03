import time
from src import keyboard_detect
from src import wheel_ctl_base

old_key = None

def Wheels_keyboard_trigger(ser, key):
    
    global old_key

    if (key == None and key != old_key):
        wheel_ctl_base.stop(ser)
        print('stop')
        time.sleep(0.1)

    if (key == 'w' and key != old_key):
        wheel_ctl_base.forward(ser)
        print('forward')
        time.sleep(0.1)

    if (key == 's' and key != old_key):
        wheel_ctl_base.backward(ser)
        print('backward')
        time.sleep(0.1)
    
    if (key == 'q' and key != old_key):
        wheel_ctl_base.turnLeft(ser)
        print('turnLeft')
        time.sleep(0.1)
    
    if (key == 'e' and key != old_key):
        wheel_ctl_base.turnRight(ser)
        print('turnRight')
        time.sleep(0.1)

    if (key == 'a' and key != old_key):
        wheel_ctl_base.shiftLeft(ser)
        print('shiftLeft')
        time.sleep(0.1)

    if (key == 'd' and key != old_key):
        wheel_ctl_base.shiftRight(ser)
        print('shiftRight')
        time.sleep(0.1)

    if (key == 'r' and key != old_key):
        wheel_ctl_base.reset(ser)
        print('reset')
        time.sleep(0.1)
        
    old_key = key

def test():

    ser = wheel_ctl_base.serOpen(port = 'COM5', rate = 9600)
    KBConfig = keyboard_detect.keyboard_config()
    KBConfig.CreateKBDetectTask()

    while(True):
        key = KBConfig.currntKey[0]
        Wheels_keyboard_trigger(ser, key)
        if (key == 'esc'): break

    wheel_ctl_base.serClose(ser)

if __name__ == '__main__':
    
    test() #沒有連server 直連Arduino控制
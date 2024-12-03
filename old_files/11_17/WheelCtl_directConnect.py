import time
from src import keyboard_detect
from src import wheel_ctl_base

old_key = None
car_state = "stop"
pid_array = None

def Wheels_keyboard_trigger(ser, key):
    
    global old_key
    global car_state
    global pid_array

    if (key == None and key != old_key):
        car_state = 'stop'
        print('stop')
        if pid_array is not None:
            wheel_ctl_base.delete_PID(pid_array)

    elif (key == 'w' and key != old_key):
        car_state = 'forward'
        print('forward')
        pid_array = wheel_ctl_base.create_PID()

    elif (key == 's' and key != old_key):
        car_state = 'backward'
        print('backward')
        pid_array = wheel_ctl_base.create_PID()
    
    elif (key == 'q' and key != old_key):
        car_state = 'turnLeft'
        print('turnLeft')
        pid_array = wheel_ctl_base.create_PID()
    
    elif (key == 'e' and key != old_key):
        car_state = 'turnRight'
        print('turnRight')
        pid_array = wheel_ctl_base.create_PID()

    elif (key == 'a' and key != old_key):
        car_state = 'shiftLeft'
        print('shiftLeft')
        pid_array = wheel_ctl_base.create_PID()

    elif (key == 'd' and key != old_key):
        car_state = 'shiftRight'
        print('shiftRight')
        pid_array = wheel_ctl_base.create_PID()
####################
    if(car_state == 'stop'):
        wheel_ctl_base.stop(ser)
        
    elif(car_state == 'forward'):
        wheel_ctl_base.forward(ser, pid_array)

    elif(car_state == 'backward'):
        wheel_ctl_base.backward(ser, pid_array)

    elif(car_state == 'turnLeft'):
        wheel_ctl_base.turnLeft(ser, pid_array)

    elif(car_state == 'turnRight'):
        wheel_ctl_base.turnRight(ser, pid_array)

    elif(car_state == 'shiftLeft'):
        wheel_ctl_base.shiftLeft(ser, pid_array)

    elif(car_state == 'shiftRight'):
        wheel_ctl_base.shiftRight(ser, pid_array)

    time.sleep(0.15)

    old_key = key

def test():

    ser = wheel_ctl_base.serOpen(port = 'COM5', rate = 19200)
    
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
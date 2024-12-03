import keyboard
from multiprocessing import Process
from multiprocessing import Manager
from multiprocessing import Lock

def getCurrentKey():

    allKeys = keyboard.get_hotkey_name().split('+')
        
    if (len(allKeys) == 1 and len(allKeys[0]) == 0):
        return None
    elif (len(allKeys) == 1 and len(allKeys[0]) != 0):
        pressedKey = allKeys[0]
        return pressedKey
    else:
        pressedKey = keyboard.read_key()
        return pressedKey

def KBDetectLoop(currntKey, lock):

    with lock:
        while(currntKey[0] != 'esc'):
            currntKey[0] = getCurrentKey()    

class keyboard_config:

    def __init__(self):
        self.currntKey = Manager().list([None])
        self.lock = Lock()

    def CreateKBDetectTask(self):

        keyboard_detect = Process(target=KBDetectLoop, args=(self.currntKey, self.lock))
        keyboard_detect.start()
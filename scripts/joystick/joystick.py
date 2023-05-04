import evdev
from enum import IntEnum

class CodeAxisGamepad(IntEnum):
    LEFT_X_STICK  = 0
    LEFT_Y_STICK  = 1
    RIGHT_X_STICK = 3
    RIGHT_Y_STICK = 4

class CodeButtonsGamepad(IntEnum):
    A_BUTTON = 304
    B_BUTTON = 305
    X_BUTTON = 307
    Y_BUTTON = 308
    
class Joystick():

    def __init__(self):
        self.name = None
        devices = [evdev.InputDevice(path) for path in evdev.list_devices()]
        for i in devices:
            if ("Xbox" in i.name) or ("X-Box" in i.name):
                self.gamepad = i
                self.name = self.gamepad.name
                break
            if self.name is None:
                print("No gamepad found")
        self.stick_value = {CodeAxisGamepad.LEFT_X_STICK:0, CodeAxisGamepad.LEFT_Y_STICK:0, CodeAxisGamepad.RIGHT_X_STICK:0, CodeAxisGamepad.RIGHT_Y_STICK:0}
        self.max_value_sticks = self.gamepad.absinfo(CodeAxisGamepad.LEFT_X_STICK).max
        self.status_button = {CodeButtonsGamepad.A_BUTTON:False, CodeButtonsGamepad.B_BUTTON:False, CodeButtonsGamepad.X_BUTTON:False, CodeButtonsGamepad.Y_BUTTON:False}
        
    def readButtonsState(self, button_name:int):
        if button_name in self.gamepad.active_keys():
            if not self.status_button[button_name]:
                self.status_button[button_name] = True
        elif self.status_button[button_name]:
            self.status_button[button_name] = False
        
    def readStickValue(self):
        self.stick_value[CodeAxisGamepad.LEFT_X_STICK]  = self.gamepad.absinfo(CodeAxisGamepad.LEFT_X_STICK).value
        self.stick_value[CodeAxisGamepad.LEFT_Y_STICK]  = self.gamepad.absinfo(CodeAxisGamepad.LEFT_Y_STICK).value
        self.stick_value[CodeAxisGamepad.RIGHT_X_STICK] = self.gamepad.absinfo(CodeAxisGamepad.RIGHT_X_STICK).value
        self.stick_value[CodeAxisGamepad.RIGHT_Y_STICK] = self.gamepad.absinfo(CodeAxisGamepad.RIGHT_Y_STICK).value

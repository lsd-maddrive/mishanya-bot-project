import time
from calculationSpeed import CalculationSpeed
from joystick import (CodeAxisGamepad, CodeButtonsGamepad, Joystick)
from USB import SerialUsb
import serial

if __name__ == "__main__":
    joystick = Joystick()
    serial_port = SerialUsb("/dev/ttyAMA0", 115200)
    calculate_speed = CalculationSpeed(0.5, 1, 10000, joystick.max_value_sticks)
    while(True):
        start = False
        joystick.readButtonsState(CodeButtonsGamepad.A_BUTTON)
        if joystick.status_button[CodeButtonsGamepad.A_BUTTON]:
            start = True
            #serial_port.send_start()
        
        while(start):
            joystick.readStickValue()
            v_x, v_y      = calculate_speed.calculationSpeedAxis(joystick.stick_value.get(CodeAxisGamepad.RIGHT_X_STICK), joystick.stick_value.get(CodeAxisGamepad.RIGHT_Y_STICK))
            angular_speed = calculate_speed.calculationAngularSpeed(joystick.stick_value.get(CodeAxisGamepad.LEFT_X_STICK))
            serial_port.send_data(v_x, v_y, angular_speed)
            joystick.readButtonsState(CodeButtonsGamepad.X_BUTTON)
            if joystick.status_button[CodeButtonsGamepad.X_BUTTON]:
                start = False
                #serial_port.close_serial()
            #print("Vx = ", v_x, "Vy = ", v_y, "Angular speed = ", angular_speed)
            time.sleep(0.01)
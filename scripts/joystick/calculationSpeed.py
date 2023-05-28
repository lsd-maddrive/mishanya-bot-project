import math

class CalculationSpeed:

    def __init__(self, v_max: float, angular_speed_max: float, dead_zone: int, max_value_stick: int):
        self.v_max             = v_max
        self.dead_zone         = dead_zone
        self.angular_speed_max = angular_speed_max
        self.max_value_stick   = max_value_stick
        self.v_x               = 0
        self.v_y               = 0
           
    def deadZone(self, value_x: int, value_y: int):
        if abs(value_x) < self.dead_zone:
            value_x = 0
        if abs(value_y) < self.dead_zone:
            value_y = 0
        return value_x, value_y

    def calculationSpeedAxis(self, raw_x: int, raw_y: int):
        raw_y = (-1) * raw_y 
        raw_x, raw_y = self.deadZone(raw_x, raw_y)

        if raw_x == 0:
            if raw_y == 0:
                self.v_x = 0
                self.v_y = 0
                return self.v_x, self.v_y
            elif raw_y > 0:
                alpha = math.pi / 2
            elif raw_y < 0:
                alpha = - math.pi / 2
        elif raw_y == 0:
            if raw_x > 0:
                alpha = 0
            elif raw_x < 0:
                alpha = math.pi
        else:
            alpha = math.atan(raw_y / raw_x)
            if raw_x < 0:
                alpha = alpha + math.pi
        
        v_x = math.cos(alpha) * self.v_max
        v_y = math.sin(alpha) * self.v_max
        return (round(v_x, 3), round(v_y, 3))
    
    def calculationAngularSpeed(self,  raw_x: int) -> float:
        raw_x, raw_y = self.deadZone(raw_x, 0)
        ang_speed = (self.angular_speed_max * raw_x) / self.max_value_stick
        return round(ang_speed, 3)
        
    
        
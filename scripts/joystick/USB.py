import serial
import struct

class  SerialUsb:
    """   
    This class is designed to work with Usb Serial
    """
    def __init__(self, com_port:str, baudrate:int):
        self.port = serial.Serial(com_port, baudrate) 
        self.port.isOpen()
        self.magic = b'1f2d3d'
        self.opcode = {'start': 0x1a, 'data': 0x2b, 'stop': 0x3c}

    def send_data(self, v_x:float, v_y:float, angular_speed:float): 
        """   
        This method sends the data by usb serial
        @param arc: angle of rotation of the servo
        @type arc: int
        """
        self.port.write(struct.pack("<fff", v_x, v_y, angular_speed))
        print(struct.pack("<fff", float(v_x), float(v_y), float(angular_speed)))
        
    def send_start(self):
        self.port.write(struct.pack('<6sh', self.magic, self.opcode['start']))

    def close_serial(self):
        """   
        This method closes usb serial
        """
        self.port.write(struct.pack('<6sh', self.magic, self.opcode['stop']))
        self.port.close() 

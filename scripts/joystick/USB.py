import serial
import struct
from crc import Calculator, Configuration

class  SerialUsb:
    """   
    This class is designed to work with Usb Serial
    """
    def __init__(self, com_port:str, baudrate:int):
        self.port = serial.Serial(com_port, baudrate) 
        self.port.isOpen()
        self.magic = [0x1f, 0x2b, 0x3b]
        self.opcode = {'start': 0x1a, 'data': 0x2b, 'stop': 0x3c}
        self.config = Configuration(
            width = 8,
            polynomial = 0x31,
            init_value = 0xff,
            final_xor_value = 0x00,
            reverse_input = False,
            reverse_output = False,
            )

    def send_data(self, v_x:float, v_y:float, angular_speed:float): 
        """   
        This method sends the data by usb serial
        @param arc: angle of rotation of the servo
        @type arc: int
        """
        self.data = struct.pack("<fff", float(v_x), float(v_y), float(angular_speed))
        self.calculator = Calculator(self.config)
        self.crc = self.calculator.checksum(self.data)
        self.port.write(struct.pack("<BBBfffB", self.magic[0], self.magic[1], self.magic[2], float(v_x), float(v_y), float(angular_speed), self.crc))
        #print(struct.pack("<fff", float(v_x), float(v_y), float(angular_speed)))
        
    def send_start(self):
        self.port.write(struct.pack('<6sh', self.magic, self.opcode['start']))

    def close_serial(self):
        """   
        This method closes usb serial
        """
        self.port.write(struct.pack('<6sh', self.magic, self.opcode['stop']))
        self.port.close() 

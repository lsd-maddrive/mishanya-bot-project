
from crc import Calculator, Configuration
import struct

config = Configuration(
    width=8,
    polynomial=0x31,
    init_value=0xff,
    final_xor_value=0x00,
    reverse_input=False,
    reverse_output=False,
)

data =  struct.pack("<fff", float(0), float(0), float(0))

calculator = Calculator(config)
crc = calculator.checksum(data)
print(hex(crc))

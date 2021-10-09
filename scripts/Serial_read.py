import serial
import codecs


num_data = 100 # number of measurements 

name_port = input('Port name: ') # port name
baudrate = int(input('Baud speed: ')) # baud speed

sensor_data=serial.Serial(name_port, baudrate) # open serial
data_file = open("sensor_data.txt", "a") # open file


data=sensor_data.readline() # read serial
while(codecs.decode(data, 'UTF-8')!="start\n"): #check start data
    data=sensor_data.readline()
print("START\n")
data_file.write("start new data\n")
while num_data!=0:
    data=sensor_data.readline()
    data_file.write(codecs.decode(data, 'UTF-8')) # writing to a file
    num_data -= 1 

data_file.close() # close file
sensor_data.close() # clise serial

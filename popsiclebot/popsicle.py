import serial
ser = serial.Serial('/dev/ttyUSB0', 9600)
ser.write('s$\n')
#ser.write('lu 96$\n')
print "Command sent, waiting for reply"
while True:
	print ser.readline()


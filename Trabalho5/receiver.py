
import serial
from time import sleep
ser = serial.Serial('/dev/ttyACM0',9600)
sleep(2)
print "Connected" 
L = ('9','8','7')
for i in L:
  ser.write(i)
  print ser.read()
print "Fim"  

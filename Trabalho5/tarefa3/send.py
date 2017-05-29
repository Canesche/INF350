import base64
import serial
from time import sleep
ser = serial.Serial('/dev/ttyACM0',9600)
sleep(2)
print "Connected" 

#x = ser.read()

#if x == '1':
#	print "Conectado"

recstr = ""
#i = 0

with open("imagem.png", "rb") as imageFile:
    str = base64.b64encode(imageFile.read())
    print len(str)
    for letter in str:
    	print letter
    	ser.write(letter)
    	
print "terminado"

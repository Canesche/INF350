import serial
import base64
import time
from time import sleep

def decodeImage(data):
    with open("newImage2.jpg", "wb") as f:
        f.write(data.decode("base64"))

imagem = ""
#serialArduino = serial.Serial('COM8', 115200)  # para windows
serialArduino = serial.Serial('/dev/cu.usbmodem1411',115200) # linux

sleep(2)
print "Connected"

while True:
    line = serialArduino.read()
    imagem = imagem + line
    print line
    if line == '=':
        break



decodeImage(imagem)



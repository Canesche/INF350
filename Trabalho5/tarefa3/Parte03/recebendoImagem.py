import serial
import base64

concatena = ""
#serialArduino = serial.Serial('COM8', 115200)  # para windows
ser = serial.Serial('/dev/ttyACM0',9600) # linux
while True:
    
    line = serialArduino.readline()
    concatena = concatena + line
    print(line)
    #serialArduino.write(nome.encode())
print concatena

fh = open("novaImagem.png", "wb")
fh.write(concatena.decode('base64'))
fh.close()

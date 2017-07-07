import serial
import base64
from time import sleep

def encodeImage():
    with open("iconeSair.png", "rb") as f:
        data = f.read()
        return data.encode("base64")

data = encodeImage()
lista = []
lista.append("")
cont = 0
for x in data:
    lista[cont] = lista[cont] + x
    if x == '\n':
        cont = cont + 1
        lista.append("")


serialArduino = serial.Serial('/dev/cu.usbmodem1421', 115200)  # para Mac :-)
sleep(2)
print "Connected"


pacote = int(len(data) / 60)

'''for x in range(0, pacote):
    sub = data[x*60: (x + 1) * 60]
    cont = 0
    while cont < len(sub):
        serialArduino.write(sub[cont])
        print(sub[cont])
        cont = cont + 1
    serialArduino.write(sub)
    print sub'''
    


for x in data:
    serialArduino.write(x);
    print x
    sleep(0.15)



    


    
    

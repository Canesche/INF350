import serial
import base64

with open("icono.png", "rb") as imageFile:
    str = base64.b64encode(imageFile.read())
    print str

tamanho = len(str)
pacotes = tamanho/50
concatena = ""
print tamanho
print pacotes

serialArduino = serial.Serial('COM6', 115200)  # para windows

for x in range(0, pacotes+1):
        substring = str [x*50:(x+1)*50]
        while True:
            #nome = raw_input("Digite textos: ")
            #print(nome)
            serialArduino.write(substring.encode())
		    print substring
        concatena = concatena + substring

print concatena
#line = serialArduino.readline()
#serialArduino.write(str.encode())
#for i in xrange(1,10):
#print(str)
    
    

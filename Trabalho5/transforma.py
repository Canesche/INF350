import base64
 
with open("imagem.png", "rb") as imageFile:
    str = base64.b64encode(imageFile.read())
    #print str
fh = open("teste.txt", "wb")
fh.write(str)
fh.close()

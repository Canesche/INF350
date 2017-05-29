import base64
 
with open("imagem.png", "rb") as imageFile:
    str = base64.b64encode(imageFile.read())
    print str
fh = open("imageToSave.png", "wb")
fh.write(str.decode('base64'))
fh.close()

from PIL import Image,ImageOps

im = Image.open('dog.jpg')

# im = ImageOps.flip(im)
im = ImageOps.mirror(im)
# im = im.rotate(30)
im.save('dog_flip.jpg')
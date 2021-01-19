from PIL import Image
import numpy as np

img = Image.open("tree.png")
img = np.array(img)
img = Image.fromarray(img)
img.save("np2png.png")

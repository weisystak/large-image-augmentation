from PIL import Image

png = Image.open("a.png")

png.load() # required for png.split()

background = Image.new("RGB", png.size, (255, 255, 255))
background.paste(png, mask=png.split()[3]) # 3 is the alpha channel
background.save("rgb_a.png")
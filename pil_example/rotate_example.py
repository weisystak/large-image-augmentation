from PIL import Image
import time

t = []
t.append(time.time())

# img = Image.open("tree.png")

img = Image.open("tree_l.png")
t.append(time.time())
print(f'Total Image OPEN time {t[-1]-t[-2]}')

augment_angle = 30
augment_translate = (10, 5)


img = img.rotate(
                    augment_angle, 
                    resample=Image.BILINEAR, 
                    translate=augment_translate,
                    fillcolor=(255, 255, 255),
)
t.append(time.time())
print(f'Total Image Rotate Elapsed: {t[-1]-t[-2]}')
# img.save("simd_r_tree.png")
# img.save("simd_r_tree_l.png")










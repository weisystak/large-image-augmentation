import slideio
import openslide
import time
import cv2
import numpy as np
slide_path = "/home/jylin/aetherAI/slides/4098031e-e0dd-4c75-8023-47601e773aca/TCGA-85-8049-01Z-00-DX1.59554c0f-d04a-41f2-b152-654a848b0443.svs"


a = []


a.append(time.time())

slide = openslide.open_slide(slide_path)

target_level = 2

# for level in range(len(slide.level_downsamples)):
#     w,h = slide.level_dimensions[level]
#     l = slide.level_downsamples[level]
#     print(f'{level}, {w}, {h}, {l}')
#     if slide.level_downsamples[level] <= 1.0 / 0.2:
#         target_level = level
        
target_width, target_height = slide.level_dimensions[target_level]
print(f'{len(slide.level_downsamples)} \n target: {target_level}, {target_width}, {target_height}')


# Read the image
img_rgba = slide.read_region(
    location=(0, 0),
    level=target_level,
    size=(target_width, target_height),
)
img_rgba.save("custom_level2.png")
# img = np.array(img_rgba)
# img = cv2.cvtColor(img_rgba, cv2.COLOR_BGRA2RGB)
# # Resize the image
# width, height = target_width, target_height
# if slide.level_downsamples[target_level] < 1.0 / 0.2:
#     ratio = slide.level_downsamples[target_level] * 0.2
#     width, height = int(target_width * ratio), int(target_height * ratio)
#     img = cv2.resize(img, (width, height))
# size = 4096*3
# img = img[:size, :size]
# img = cv2.resize(img, (512,512))
# cv2.imwrite('block_3.jpg', img)

    
a.append(time.time())
print(f'openslide load image elapsed: {a[-1] - a[-2]}')


# 53.24 s
# 51.72 s (after warm up)
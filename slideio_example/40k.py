import slideio
import openslide
import time
import cv2
import psutil
slide_path = "/home/u8136408/aetherAI/slides/4098031e-e0dd-4c75-8023-47601e773aca/TCGA-85-8049-01Z-00-DX1.59554c0f-d04a-41f2-b152-654a848b0443.svs"
resize_ratio = 0.2

a = []
a.append(time.time())
slide = slideio.open_slide(slide_path, "SVS")
print(f"raw_metadata {slide.raw_metadata}")
num_scenes = slide.num_scenes
print(f"num_scenes: {num_scenes}")
for index in range(0, num_scenes):
    print(slide.get_scene(index).name, slide.get_scene(index).size)
scene = slide.get_scene(0)
print( scene.num_t_frames, scene.num_z_slices, scene.compression)
w,h = scene.size
image = scene.read_block(size=(int(w*resize_ratio),int(h*resize_ratio)))
print(f'shape: {image.shape}')
image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
print(f'{type(image)}, {image.shape}')
a.append(time.time())
print(f'slideio load image elapsed: {a[-1] - a[-2]}')


# cv2.resize(image, (int(h/50), int(w/50)))
# cv2.imwrite("slideio_40k.jpg", image)

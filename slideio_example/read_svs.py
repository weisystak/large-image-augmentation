import slideio
import openslide
import time

slide_path = "/home/u8136408/aetherAI/slides/4098031e-e0dd-4c75-8023-47601e773aca/TCGA-85-8049-01Z-00-DX1.59554c0f-d04a-41f2-b152-654a848b0443.svs"


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
# image = scene.read_block()
# print(f'{type(image)}, {image.shape}')
a.append(time.time())
print(f'slideio load image elapsed: {a[-1] - a[-2]}')








a.append(time.time())

slide = openslide.open_slide(slide_path)

target_level = 0

for level in range(len(slide.level_downsamples)):
    w,h = slide.level_dimensions[level]
    l = slide.level_downsamples[level]
    print(f'{level}, {w}, {h}, {l}')
    if slide.level_downsamples[level] <= 1.0 / 0.2:
        target_level = level
        
target_width, target_height = slide.level_dimensions[target_level]
print(f'{len(slide.level_downsamples)} \n {target_level}, {target_width}, {target_height}')


# Read the image
img_rgba = slide.read_region(
    location=(0, 0),
    level=target_level,
    size=(target_width, target_height),
)

a.append(time.time())
print(f'openslide load image elapsed: {a[-1] - a[-2]}')
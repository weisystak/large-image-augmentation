import slideio
import time
import cv2
import albumentations as A
slide_path = "/home/u8136408/aetherAI/slides/4098031e-e0dd-4c75-8023-47601e773aca/TCGA-85-8049-01Z-00-DX1.59554c0f-d04a-41f2-b152-654a848b0443.svs"
resize_ratio = 0.2
# resize_ratio = 0.02
img_size = 40000
# img_size = 2000


transform = A.Compose([
    A.HorizontalFlip(p=1.0),
    A.Rotate(limit=30, border_mode=cv2.BORDER_CONSTANT, value=(255, 255, 255), p=1.0)
])


a = []
a.append(time.time())

slide = slideio.open_slide(slide_path, "SVS")
scene = slide.get_scene(0)
w, h = scene.size
w, h = int(w * resize_ratio), int(h * resize_ratio)
# image = scene.read_block(size=(1247,1535))
img = scene.read_block(size=(w, h))
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
print(img.shape)
a.append(time.time())
print(f'slideio load image elapsed: {a[-1] - a[-2]}')

img =  transform(image=img)["image"]


a.append(time.time())
print(f'albumentation rotate image elapsed: {a[-1] - a[-2]}')

# Pad and/or crop to the desired size
delta_w = max(0, img_size - w)
delta_h = max(0, img_size - h)
left, right = delta_w // 2, delta_w - (delta_w // 2)
top, bottom = delta_h // 2, delta_h - (delta_h // 2)
img = cv2.copyMakeBorder(
    img,
    top,
    bottom,
    left,
    right,
    cv2.BORDER_CONSTANT,
    value=(255, 255, 255),
)
img = img[: img_size, : img_size, :]


a.append(time.time())
print(f'cv2 MakeBorder image elapsed: {a[-1] - a[-2]}')




# cv2.imwrite("albumentation_border.jpg", img)


import cv2

size = 40000

img = cv2.imread("tree.png")
img = cv2.resize(img, (size, size))
cv2.imwrite("tree.png", img)
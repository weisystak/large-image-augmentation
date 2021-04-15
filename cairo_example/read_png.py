import cv2 
  

img = cv2.imread('source_operator.png') 
print(img.shape)
n = 20
for i in range(8+n, 13+n):
    for j in range(8+n, 13+n):
    # for j in range(len(img[0])):
    
        print(img[i][j], end=" ") 
    print()
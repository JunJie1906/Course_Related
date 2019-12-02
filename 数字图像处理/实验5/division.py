import numpy as np
import cv2

img = cv2.imread('yaogan.jpg')
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

cv2.imshow('gray',gray)
# ret, dst = cv2.threshold(cell_gray,0, 255, cv2.THRESH_BINARY_INV,cv2.THRESH_OTSU)
dst = cv2.adaptiveThreshold(gray,255,cv2.ADAPTIVE_THRESH_MEAN_C,cv2.THRESH_BINARY,11,2)

cv2.imshow('dst',dst)

kernel=np.ones((3,3),np.uint8)
Open=cv2.morphologyEx(dst,cv2.MORPH_OPEN,kernel,iterations=2)

cv2.imshow('Open',Open)

dilate=cv2.dilate(Open,kernel,iterations=3)
cv2.imshow('dilate',dilate)

dis=cv2.distanceTransform(Open,cv2.DIST_L2 ,5)
cv2.imshow('dis',dis)

ret,f=cv2.threshold(dis,10,255,cv2.THRESH_BINARY)
cv2.imshow('f',f)
f=np.uint8(f)

u=dilate-f

_,Components=cv2.connectedComponents(f)

cv2.imshow('u',u)
watershed = cv2.watershed(img,Components)

img[watershed == -1] = [255,255,255]

cv2.imshow('pro',img)
cv2.waitKey(0)

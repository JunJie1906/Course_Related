import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('p1.jpg',0)

sobel = np.array([[-1,0,1],[-2,0,2],[-1,0,1]])

roberts = np.array([[1,0],[0,-1]])

kernel1 = np.array([[-1, -1, -1],[-1, 8, -1],[-1, -1, -1]])

kernel2 = np.array([[2,0,2],[0,-8,0],[2,0,2]])

kernel3 = np.array([[1,3,1],[3,-16,3],[1,3,1]])


def img_filter(img,filter1,filter2,size):
    L = len(img)
    W = len(img[0])
    img_after = img.copy()
    for i in range(1,L-1):
        for j in range(1,W-1):
            conv1 = np.multiply(img[i-1:i+size-1,j-1:j+size-1],filter1)
            conv2 = np.multiply(img[i-1:i+size-1,j-1:j+size-1],filter2)
            # print(sum(sum(conv)))
            SUM = max(sum(sum(conv1)),sum(sum(conv2)))
            if SUM<0:
                SUM = 0
            if SUM>255:
                SUM = 255
            img_after[i][j] = SUM
    return img_after



# img_after1 = img_filter(img,sobel,sobel.T,3)
# img_after2 = img_filter(img,roberts,roberts.T,2)
img_after3 = img_filter(img,kernel2,kernel2.T,3)
cv2.imshow('before1',img)
# cv2.imshow('after1_sobel',img_after1)
# cv2.imshow('after1_roberts',img_after2)
cv2.imshow('after1_kernel',img_after3)
cv2.waitKey(0)



# f = np.fft.fft2(img)
# fshift = np.fft.fftshift(f)
#
# rows, cols = img.shape
# crow,ccol = int(rows/2), int(cols/2)
# fshift[crow-40:crow+40, ccol-40:ccol+40] = 0
#
# ishift = np.fft.ifftshift(fshift)
# img_fft = np.fft.ifft2(ishift)
# img_fft = np.abs(img_fft)
#
# img_back_int = img_fft.astype(np.uint8)
# cv2.imshow('fft',img_back_int)
# cv2.waitKey(0)



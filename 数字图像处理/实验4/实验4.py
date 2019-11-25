import matplotlib.pyplot as graph
import numpy as np
from numpy import fft
import math
import cv2


def get_H(image_size, angle, motion_dis=10):
    H = np.zeros(image_size)
    x_center = (image_size[0] - 1) / 2
    y_center = (image_size[1] - 1) / 2
    sin_val = math.sin(angle * math.pi / 180)
    cos_val = math.cos(angle * math.pi / 180)
    for i in range(motion_dis):
        x_offset = int(sin_val * i)
        y_offset = int(cos_val * i)
        H[int(x_center - x_offset)][int(y_center + y_offset)] = 1
    return H / H.sum()


def blurred(input, H):
    input_fft = fft.fft2(input)
    H_fft = fft.fft2(H)
    blurred = fft.ifft2(input_fft * H_fft)
    blurred = np.abs(fft.fftshift(blurred))
    return blurred

def wiener(input, H, K):
    input_fft = fft.fft2(input)
    H_fft = fft.fft2(H)
    H_fft = np.conj(H_fft) / (np.abs(H_fft) ** 2 + K)
    result = fft.ifft2(input_fft * H_fft)
    result = np.abs(fft.fftshift(result))
    return result


#image = cv2.imread('p1.jpg',0)
image = cv2.imread('p2.jpg',0)
H = get_H(image.shape, 30,20)
blurred = np.abs(blurred(image, H))
result2 = wiener(blurred, H,0.001)  # 维纳滤波
result2 = result2.astype(np.uint8)
blurred = blurred.astype(np.uint8)
cv2.imshow('img',image)
cv2.imshow('blurred_img',blurred)
cv2.imshow('wiener_process_img',result2)
cv2.waitKey(0)


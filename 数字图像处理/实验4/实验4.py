import matplotlib.pyplot as graph
import numpy
from numpy import fft
import math
import cv2

# 仿真运动模糊
def motion_process(len, sx,sy):

    PSF = numpy.zeros((sy, sx))
    PSF[int(sy / 2):int(sy /2 + 1), int(sx / 2 - len / 2):int(sx / 2 + len / 2)] = 1
    return (PSF / PSF.sum()) # 归一化亮度


def make_blurred(input, PSF, eps):
    input_fft = numpy.fft.fft2(input)
    PSF_fft = numpy.fft.fft2(PSF) + eps
    blurred = numpy.fft.ifft2(input_fft * PSF_fft)
    blurred = numpy.abs(numpy.fft.fftshift(blurred))
    return blurred

def wiener(input, PSF, eps):
    input_fft = numpy.fft.fft2(input)
    PSF_fft = numpy.fft.fft2(PSF) + eps #噪声功率，这是已知的，考虑epsilon
    result = numpy.fft.ifft2(input_fft / PSF_fft) #计算F(u,v)的傅里叶反变换
    result = numpy.abs(numpy.fft.fftshift(result))
    return result


image = cv2.imread('D://a.jpg',0)
img_h=image.shape[0]
img_w=image.shape[1]

PSF = motion_process(10,img_w,img_h)
print(image.shape)
print(PSF.shape)
print()
# blurred = numpy.abs(make_blurred(image, PSF, 1e-3))
#
# blurred = blurred.astype(numpy.uint8)
result = wiener(image, PSF, 1e-1)

result = result.astype(numpy.uint8)

cv2.imshow('a',result)
# cv2.imshow('blur',blurred)
cv2.waitKey(0)
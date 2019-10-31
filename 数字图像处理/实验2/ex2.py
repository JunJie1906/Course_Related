import cv2
import numpy as np
from matplotlib import pyplot as plt
import math

# path
def get_dist(img_path):
    img_gray = cv2.imread(img_path, 0)
    plt.hist(img_gray.ravel(), 16, [0, 256])  # 宽度为16
    plt.show()


# 线性变换
def LinerTrans(pix,a,b,c,d):
    if pix < a:
        return pix
    elif pix<=b:
        return ((d-c)/(b-a))*(pix-a)+c
    else:
        return pix

def img_liner_trans(img_path, a, b, c, d):
    img_gray = cv2.imread(img_path, 0)
    cv2.imshow('before', img_gray)
    cv2.waitKey(0)
    for i in range(len(img_gray)):
        for j in range(len(img_gray[0])):
            img_gray[i][j] = LinerTrans(img_gray[i][j], a, b, c, d)
    cv2.imshow('after', img_gray)
    cv2.waitKey(0)

# 分段线性变换
def LinerTrans_(pix,a,b,c,d):
    if pix < a:
        return (c/a)*pix
    elif pix<=b:
        return ((d-c)/(b-a))*(pix-a)+c
    else:
        return ((255-d)/(256-b))*(pix-b)+d

def img_liner_trans_(img_path,a,b,c,d):
    img_gray = cv2.imread(img_path,0)
    cv2.imshow('before',img_gray)
    cv2.waitKey(0)
    for i in range(len(img_gray)):
        for j in range(len(img_gray[0])):
            img_gray[i][j] = LinerTrans_(img_gray[i][j],a,b,c,d)
    cv2.imshow('after',img_gray)
    cv2.waitKey(0)

def exp_trans(pix,a,b,c):
    return b**(c*(pix-a))-1

def img_exp_trans(img_path,a,b,c):
    img_gray = cv2.imread(img_path,0)
    cv2.imshow('before',img_gray)
    cv2.waitKey(0)
    for i in range(len(img_gray)):
        for j in range(len(img_gray[0])):
            img_gray[i][j] = exp_trans(img_gray[i][j],a,b,c)
    cv2.imshow('after',img_gray)
    cv2.waitKey(0)

p1 = 'D://p1.png'
p2 = 'D://p2.png'
p3 = 'D://p3.png'
p4 = 'D://p4.png'
# get_dist(p2)
# get_dist(p3)
# get_dist(p4)



img_gray = cv2.imread(p4,0)
g = cv2.equalizeHist(img_gray)
cv2.imshow('after',g)
cv2.waitKey(0)
# img_exp_trans(p4,0,1.4,0.1)

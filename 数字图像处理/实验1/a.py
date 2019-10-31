import cv2
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt



img = Image.open("E:/s2.png")

arr = np.array(img)

l = arr.shape[0]
w = arr.shape[1]
d = arr.shape[2]

f = open('D://test.txt','w')
# f.write('')
r = 0
g = 0
b = 0

lr = []
lg = []
lb = []

print(l,w,d)
for i in range(int(l)):
    for j in range(int(w)):
        f.write('[')
        r+=arr[i][j][0]
        lr.append(arr[i][j][0])
        g+=arr[i][j][1]
        lg.append(arr[i][j][1])
        b+=arr[i][j][2]
        lb.append(arr[i][j][2])
        for k in range(d):
            if k==2:
                f.write(str(arr[i][j][k])+']')
                # print(str(arr[i][j][k]))
            else:
                f.write(str(arr[i][j][k])+',')
        f.write(',')
    # f.write('\n')
    f.write('\n')
f.close()
s = arr.size/3




print(int(r/s),int(g/s),int(b/s))

plt.hist(lr,100)
plt.xlabel('R')
plt.ylabel('Frequency')
plt.show()

plt.hist(lg,100)
plt.xlabel('G')
plt.ylabel('Frequency')
plt.show()

plt.hist(lb,100)
plt.xlabel('B')
plt.ylabel('Frequency')

plt.show()


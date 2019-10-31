import os
f = open('E:/python_homework/copy.txt','r')
ft = open('E:/python_homework/new.txt','w')
l = f.readlines()
for i in l:
    ft.writelines(i)
f.close()
ft.close()
l = []
for i in range(1,5):
    f = open('E:/python_homework/folder/file%d.txt'%i,'r')
    l1 = f.readlines()
    for j in l1:
        l.append(j)
    f.close()
f = open('E:/python_homework/folder/merge.txt','w')
for i in l:
    f.writelines(i)
f.close()
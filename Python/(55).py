f = open('E:/python_homework/numbers.txt','r')
l = f.readlines()
f.close()
f1 = open('E:/python_homework/Sort.txt','w')
for i in range(len(l)):
    l[i] = float(l[i])
l.sort()
aver = sum(l)/len(l)
fc = 0
for i in l:
    fc += (i-aver)**2
for i in l :
    f1.write('%5.1f\n'%i)
f1.write('aver : %5.2f\n'%aver)
f1.write('fangcha : %5.2f\n'%fc)
f1.close()
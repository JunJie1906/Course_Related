def is_meisen(x):
    x1 = x
    x += 1
    while x > 1:
        x /= 2
    if x == 1:
        return x1
    else:
        return -1

l = []
for i in range(1,1001):
    if is_meisen(i) == -1:
        continue
    l.append(i)
for i in range(len(l)):
    print('%3d%4d'%(i,l[i]),end='\n')
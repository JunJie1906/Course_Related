def is_huiwen(x):
    x = str(x)
    i = 0
    while True:
        if i >= int(len(x)/2):
            return True
        else:
            if x[i] != x[-1-i]:
                return False
            else:
                i += 1

def is_prim(x):
    i = 2
    while i < x/2:
        if x % i == 0:
            return False
        i += 1
    if i >= x/2:
        return True

def is_fansushu(x):
    if is_huiwen(x) == False:
        if is_prim(x) == True:
            return True
    return False

i = 2
l = []
while True :
    if len(l) == 30:
        break
    if i<10:
        if is_prim(i) == True:
            l.append(i)
    else:
        if is_fansushu(i) == True:
            l.append(i)
    i += 1
for i in range(len(l)):
    if i!= 0 and i % 8 ==0:
        print()
    print('%5d'%l[i],end=' ')
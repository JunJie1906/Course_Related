import random
def foo(x):
    x = int(x)
    l = []
    for i in range(1,int(x/2)+1):
        if x % i == 0:
            l.append(i)
    return sum(l)
random = random.randint(2,1000)
print(random)
print(foo(random))
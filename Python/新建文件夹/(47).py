import random
def foo(x):
    x1 = str(x)
    l = list(x1)
    l.reverse()
    s = ''
    for i in l:
        s += i
    return int(s)

x = random.randint(10,1000)
print(x)
print(foo(x))
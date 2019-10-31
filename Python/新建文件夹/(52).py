def foo(x):
    s = input()
    l = list(s)
    l1 = []
    l2 = []
    l1.append(l[x].lower())
    l1.append(l[x].upper())
    for i in l:
        if i in l1:
            l2.append(i)
    return l[x],len(l2)
x = int(input('please input a number'))
print(foo(x))
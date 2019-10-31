def fibonacii(x):
    l1 = [1,1]
    for i in range(2,x+1):
        l1.append(l1[i-1]+l1[i-2])
    print(l1)

x = int(input())
fibonacii(x)
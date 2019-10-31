x = input('please input a number: ')
x = int(x)
i = 1
while i <= x:
    if i == 1:
        print(str.center('三轮',x*4))
    if 1 < i <x:
        m =  ('三轮' ,'   '*(i-2),6)
        m = str(m)
        print(str.center(m,x*4))
    else:
        print(str.center('三轮'*i,x*4))
    i += 1

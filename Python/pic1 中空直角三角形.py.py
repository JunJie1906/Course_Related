x = int(input('please input a number'))
i = 1
while i <= x:
    if i == 1:
        print('* ')
    if i >= 2:
        print('*','  '*(i-2),'*')
    if i == x:
        print('*','* '* x )
    i += 1


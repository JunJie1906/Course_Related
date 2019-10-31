x = 'What a wonderful day'
def reverse(x):
    s = x.split(' ')
    s1 = ''
    for i in s:
        s1 = i + ' ' + s1
    return s1
print(reverse(x))

f = open('E:/python_homework/word.txt','r')
l = f.readlines()
l1 = []
for i in l:
    if i[0] in ['a','e','i','o','u']:
        l1.append(i)
f.close()
f = open('E:/python_homework/new_word.txt','w')
for i in l1:
    f.writelines(i)
f.close()
f = open('E:/python_homework/names.txt','r')
l = f.readlines()
name = input()
if name not in l:
    name = name+'\n'
    l.append(name)
l.sort()
f.close()
f = open('E:/python_homework/new_word.txt','w')
for i in l:
    f.writelines(i)
f.close()
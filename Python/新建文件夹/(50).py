def encode(num):
    l11 = [chr(i) for i in range(97, 123)]
    l22 = [chr(i) for i in range(65, 91)]
    l1 = [chr(i) for i in range(97, 123)] + [chr(i) for i in range(65, 91)]
    l2 = [str(i) for i in range(10)]
    l = []
    l3 = list(x)
    for i in range(len(x) - 1):
        if x[i] in l1 and x[i + 1] in l2 or x[i] in l2 and x[i + 1] in l1:
            l.append(i)
    for i in range(len(l)):
        l3.insert(i + l[i] + 1, '#')
    s = ''
    for i in l3:
        s += i
    s = s.split('#')  # s 是列表 【‘123’，‘asd’】
    if x[0] in l1:
        for i in range(len(s)):
            if i % 2 == 0:
                li = list(s[i])
                for j in range(len(li)):
                    if li[j] in l11:
                        li[j] = chr(ord(li[j]) + num) if chr(ord(li[j]) + num) in l11 else chr(ord(li[j]) + num - 26)
                    if li[j] in l22:
                        li[j] = chr(ord(li[j]) + num) if chr(ord(li[j]) + num) in l22 else chr(ord(li[j]) + num - 26)
                p = ''
                for j in li:
                    p += j
                s[i] = p
            else:
                s[i] = str(int(s[i]) * num)
        string = ''
        for i in s:
            string = string + i
        return string
    if x[0] in l2:
        for i in range(len(s)):
            if i % 2 == 0:
                s[i] = str(int(s[i]) * num)
            else:
                lq = list(s[i])
                for j in range(len(lq)):
                    if lq[j] in l11:
                        lq[j] = chr(ord(lq[j]) + num) if chr(ord(lq[j]) + num) in l11 else chr(ord(lq[j]) + num - 26)
                    if lq[j] in l22:
                        lq[j] = chr(ord(lq[j]) + num) if chr(ord(lq[j]) + num) in l22 else chr(ord(lq[j]) + num - 26)
                p = ''
                for j in lq:
                    p += j
                s[i] = p
        string = ''
        for i in s:
            string = string + i
        return string

def decode(num):
    l11 = [chr(i) for i in range(97, 123)]
    l22 = [chr(i) for i in range(65, 91)]
    l1 = [chr(i) for i in range(97, 123)] + [chr(i) for i in range(65, 91)]
    l2 = [str(i) for i in range(10)]
    l = []
    l3 = list(x)
    for i in range(len(x) - 1):
        if x[i] in l1 and x[i + 1] in l2 or x[i] in l2 and x[i + 1] in l1:
            l.append(i)
    for i in range(len(l)):
        l3.insert(i + l[i] + 1, '#')
    s = ''
    for i in l3:
        s += i
    s = s.split('#')  # s 是列表 【‘123’，‘asd’】
    if x[0] in l1:
        for i in range(len(s)):
            if i % 2 == 0:
                li = list(s[i])
                for j in range(len(li)):
                    if li[j] in l11:
                        li[j] = chr(ord(li[j]) - num) if chr(ord(li[j]) - num) in l11 else chr(ord(li[j]) - num + 26)
                    if li[j] in l22:
                        li[j] = chr(ord(li[j]) - num) if chr(ord(li[j]) - num) in l22 else chr(ord(li[j]) - num + 26)
                p = ''
                for j in li:
                    p += j
                s[i] = p
            else:
                s[i] = str(int(int(s[i]) / num))
        string = ''
        for i in s:
            string = string + i
        return string
    if x[0] in l2:
        for i in range(len(s)):
            if i % 2 == 0:
                s[i] = str(int(int(s[i]) / num))
            else:
                lq = list(s[i])
                for j in range(len(lq)):
                    if lq[j] in l11:
                        lq[j] = chr(ord(lq[j]) - num) if chr(ord(lq[j]) - num) in l11 else chr(ord(lq[j]) - num + 26)
                    if lq[j] in l22:
                        lq[j] = chr(ord(lq[j]) - num) if chr(ord(lq[j]) - num) in l22 else chr(ord(lq[j]) - num + 26)
                p = ''
                for j in lq:
                    p += j
                s[i] = p
        string = ''
        for i in s:
            string = string + i
        return string

x = input('please input the str')
num = int(input('please in put the num'))
print(encode(num))
x = encode(num)
print(decode(num))
import re



stack = '(a)|(b)*'



ans = []

status = 0
last = []
smbl = 0
last_ = []

for i in range(len(stack)):
    if stack[i].isalpha():
        ans.append([status,stack[i],status+1])
        status+=1
        continue

    if stack[i]=='(':
        last.append(status)
        continue

    if stack[i]==')':
        if i+1<len(stack) and stack[i+1]=='*':
            if smbl ==0:
                ans.append([last[-1],'ep',status])
                ans.append([status, 'ep', last[-1]])
                last_ = [status,last[-1]]
                last = last[:-1]
                continue
            else:
                ans.append([last[-1],'ep',last_[-1]])
                ans.append([last_[-1], 'ep', last[-1]])
                if last_==[]:
                    smbl = 0

    if stack[i]=='*':
        if i>0:
            if stack[i-1]!=')':
                ans.append([status,'ep',status])
                if status>0:
                    ans.append([status-1,'ep',status])

    if stack[i]=='|':
        smbl = 1


ans = sorted(ans)
print(ans)


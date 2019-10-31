
p = 'a(b*|c)*d'
# 中缀转后缀
def chg(p):
    stack = []
    # bkt = ['(',')','|','*']
    str = ''
    for i in range(len(p)):
        str += p[i]
        if p[i]==')':
            if i+1<len(p):
                if p[i+1].isalpha():
                    str+='&'
        if p[i].isalpha():
            if i+1<len(p):
                if p[i+1]=='(':
                    str+='&'
                if p[i+1].isalpha():
                    str+='&'
        if p[i]=='*':
            if i+1<len(p):
                if p[i+1].isalpha():
                    str+='&'


    preority = ['|','&']

    bk = ''

    for i in range(len(str)):
        if str[i] == '*':
            bk+=str[i]
            continue
        if str[i].isalpha():
            bk+=str[i]
            continue
        if str[i]=='(':
            stack.append('(')
            continue

        if str[i] == ')':
            while stack!=[]:
                if stack[-1]=='(':
                    stack = stack[:-1]
                    break
                bk+=stack[-1]
                stack = stack[:-1]
            continue
        ptr = preority.index(str[i])
        crt = preority[:ptr+1]
        while stack!=[]:
            if stack[-1] == '(':
                break
            if stack[-1] not in crt:
                break

            if stack[-1] in crt:
                bk+=stack[-1]
                stack = stack[:-1]
        stack.append(str[i])

    while stack!=[]:
        bk+=stack[-1]
        stack = stack[:-1]
    return bk




# 后缀表达式转NFA
def getNFA(p):
    obj = chg(p)

    node = []

    class nfa:
        def __init__(self,begin,end,ans):
            self.begin = begin
            self.end = end
            self.ans = ans

    operator = ['*','|','&']

    def mkNode(s):
        if node==[]:
            p = nfa(0,1,[[0,s,1]])
        else:
            state = node[-1].end
            p = nfa(state,state+1,[[state,s,state+1]])
        return p

    def mkStar(n):
        n.ans.append([n.begin,'ep',n.end])
        n.ans.append([n.end,'ep',n.begin])
        return n

    def mkUnion(a1,a2):
        begin = a1.begin
        end = a2.end
        ans = []
        for i in a1.ans:
            ans.append(i)
        for i in a2.ans:
            ans.append(i)
        p = nfa(begin,end,ans)
        return p

    def mkor(a1,a2):
        begin = a1.begin
        end = a2.end

        ans = []
        for i in a1.ans:
            ans.append(i)
        for j in range(len(a2.ans)):
            if a2.ans[j][0] == end:
                a2.ans[j][0] = begin
            if a2.ans[j][2] == end:
                a2.ans[j][2] = begin
            c = a2.ans[j][0]
            a2.ans[j][0] = a2.ans[j][2]
            a2.ans[j][2] = c
            ans.append(a2.ans[j])

        ans.append([a1.end,'ep',a2.end])
        p = nfa(begin,end,ans)
        return p

    for i in obj:
        if i not in operator:
            node.append(mkNode(i))
            continue
        if i=='*':
            crt = node[-1]
            node = node[:-1]
            node.append(mkStar(crt))
            continue
        if i=='&':
            crt2 = node[-1]
            crt1 = node[-2]
            node = node[:-2]
            node.append(mkUnion(crt1,crt2))
            continue
        if i=='|':
            crt2 = node[-1]
            crt1 = node[-2]
            node = node[:-2]
            node.append(mkor(crt1,crt2))
    return sorted(node[0].ans)

ans = getNFA(p)
# for i in ans:
#     print(i)

def e_closure(s,nfa):
    sym = s
    l = []
    for i in sym:
        l.append(i)
    for i in nfa:
        if i[1]=='ep':
            if i[0] in sym and i[2] not in sym:
                l.append(i[2])
    return l

def move(p,s,nfa):
    sym = []
    for i in s:
        sym.append(i)

    flag = True
    while flag == True:
        sym1 = []
        for i in sym:
            sym1.append(i)
        for i in nfa:
            if i[1] == 'ep' or i[1] == p:
                if i[0] in sym1 and i[2] not in sym1:
                    sym1.append(i[2])
                    break
        if sym1==sym:
            flag = False
        else:
            sym.clear()
            for i in sym1:
                sym.append(i)
    return sym

def Eql(a,b):
    if len(a)!=len(b):
        return False
    for i in a:
        if i not in b:
            return False
    return True

state = [[0]]
n = 0
alp = []

DFA = []


print(move('a',e_closure([0],ans),ans))


for i in p:
    if i.isalpha():
        alp.append(i)
# print(alp)
while n<len(state):

    for i in alp:
        mv = move(i,state[n],ans)
        # print(i,mv)
        In2 = False
        for k in range(len(state)):
            if Eql(state[k],mv)==True:
                In2 = True
                break
        print(i,state[n])
        if In2==False:
            state.append(mv)
            DFA.append([n,i,len(state)-1])



    # print(n,len(state))
    n+=1


print(state)

print(DFA)



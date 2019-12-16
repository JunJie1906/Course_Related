
class node:
    def __init__(self,ans,gen,prob,child=None):
        '''
            for S-> NP VP prob :
        :param ans:  S
        :param gen: NP VP, a list where stored String NP and VP
        :param prob: probability
        :param child: last node
        '''
        self.ans = ans
        self.gen = gen
        self.prob = prob
        self.child = child

    def show(self):
        print(self.ans,'->',end=' ')
        for i in self.gen:
            print(i,end=' ')
        print(self.prob)
    def dfs(self,perx = 1):
        child = self.child
        if child==None:
            print('-' * perx + self.ans)
            print('-' * (perx + 1)+self.gen[0])
            return
        else:
            print('-'*perx+self.ans)
            for c in child:
                c.dfs(perx+1)

    def __eq__(self, other):
        return self.ans==other.ans

# generate table
def getInitTable(n):
    return [[[]for j in range(i+1)] for i in range(n)]

# load
def loadData(data):
    dic = []
    data = data.strip()
    data = data.split('\n')
    for i in data:
        s = i.split()
        dic.append(node(s[0],s[1:-1],float(s[-1])))
    return dic


def expand(lst,dic):
    crt = [i for i in lst]
    ans = []
    for i in lst:
        ans.append(i)
    while crt != []:
        p = crt[0]
        crt = crt[1:]
        for k in dic:
            if len(k.gen)==1 and k.gen[0]==p.ans:
                m = node(k.ans,k.gen,k.prob*p.prob,[p])
                if m not in ans:
                    ans.append(m)
                    crt.append(m)
                elif ans[ans.index(m)].prob<m.prob:
                    ans[ans.index(m)] = m
    return ans

def merge(t1,t2,dic):
    ans = []
    for i in t1:
        for j in t2:
            for p in dic:
                p1 = [i.ans,j.ans]
                if p.gen==p1:
                    crt = node(p.ans,p.gen,p.prob*i.prob*j.prob,[i,j])
                    if crt not in ans:
                        ans.append(crt)
                    elif crt.prob>ans[ans.index(crt)].prob:
                        ans[ans.index(crt)] = crt
    return ans

def add(a1,a2):
    ans = []
    for i in a1:
        ans.append(i)
    for j in a2:
        if j in ans:
            if j.prob>ans[ans.index(j)].prob:
                ans[ans.index(j)] = j
        else:
            ans.append(j)
    return ans


data = '''
S NP VP 0.9
S VP 0.1
VP V NP 0.5
VP V 0.1
VP V @VP_V 0.3
VP V PP 0.1
@VP_V NP PP 1
NP NP NP 0.1
NP NP PP 0.2
NP N 0.7
PP P NP 1
N people 0.5
N fish 0.2
N tanks 0.2
N rods 0.1
V people 0.1
V fish 0.6
V tanks 0.3
P with 1.0
'''

dic = loadData(data)

text = 'fish people fish tanks'
text = text.strip().split()

#init table[i][i]
table = getInitTable(len(text))

for i in table:
    print(i)

for i in range(len(text)):
    for p in dic:
        if text[i] in p.gen:
            table[i][i].append(p)
    table[i][i] = expand(table[i][i],dic)

n = len(text)
for i in range(1,n):
    for j in range(n-i):
        ans = []
        print(j,i+j)
        for k in range(i):
            ans = add(ans, expand(merge(table[j+k][j], table[i+j][j+k+1], dic), dic))
        for an in ans:
            an.show()
        table[i+j][j] = ans

# print tree
for k in table[n-1][0]:
    if k.ans=='S':
        k.dfs()
        break

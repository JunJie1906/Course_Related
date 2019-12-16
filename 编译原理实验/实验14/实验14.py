
class node:
    def __init__(self,left,point_left,point_right):
        self.left = left
        self.point_left = point_left
        self.point_right = point_right
    def show(self):
        print(self.left,end=' -> ')
        for i in self.point_left:
            print(i,end=' ')
        print('.',end=' ')
        for i in self.point_right:
            print(i,end=' ')
        print()
    def __eq__(self, other):
        return self.left==other.left and self.point_left==other.point_left and self.point_right==other.point_right
    def __hash__(self):
        return hash(str(self.left)+ str(self.point_right) + str(self.point_left))

class state:
    def __init__(self,data,next_state):
        self.data = e_closure(data,dic)
        self.next = next_state
    def show(self):
        for i in self.data:
            i.show()
    def show_next(self,index):
        for i in self.next:
            print('move('+str(index)+",'"+str(i[0])+"') =",i[1])
    def e_closure(self):
        self.data = e_closure(self.data,dic)
    def add(self,p):
        self.data.append(p)
        self.data = e_closure(self.data,dic)
    def accept(self):
        return self.next==[]
    def getNext(self,c):
        for i in self.next:
            if i[0]==c:
                return i[1]
        return
    def empty(self):
        return self.data==[]
    def __eq__(self, other):
        return set(self.data)==set(other.data)

def load_data(data):
    start_stu = []
    data = data.strip().split('\n')
    for d in data:
        left = d.split()[0]
        d = d.replace(left,'',1).strip().split('|')
        for i in range(len(d)):
            d[i] = d[i].strip().split()
            start_stu.append(node(left,[],d[i]))
    return start_stu

def e_closure(S,dic):
    crt = [i for i in S]
    added = set()
    while crt!=[]:
        cur = []
        for i in crt:
            if i.point_right!=[] and i.point_right[0] not in added:
                for j in dic:
                    if i.point_right!=[] and i.point_right[0] == j.left:
                        added.add(j.left)
                        cur.append(j)
                        S.append(j)
        crt = cur
    return list(set(S))


def move(S,t):
    ans = []
    for i in S:
        if i.point_right!=[] and i.point_right[0]==t:
            cur = node(i.left,i.point_left.copy(),i.point_right.copy())
            cur.point_left.append(cur.point_right[0])
            cur.point_right = cur.point_right[1:]
            ans.append(cur)
    return list(set(ans))


data = '''
E' E
E  E + T | T
T  T * F | F
F ( E ) | id
'''

load_data(data)
dic = load_data(data)

start = state([node("E'",[],['E'])],[])
states = [start]

index = 0
while index<len(states):
    Next = []
    cur = states[index]
    for i in cur.data:
        if i.point_right!=[] and i.point_right[0] not in Next:
            Next.append(i.point_right[0])
    n = 0
    while n<len(Next):
        new_state = state(e_closure(move(states[index].data,Next[n]),dic),[])
        if new_state.empty() == False and new_state not in states:
            states.append(new_state)
            states[index].next.append((Next[n], index + n + 1))
        else:
            states[index].next.append((Next[n],states.index(new_state)))
        n += 1
    index+=1


for i in range(len(states)):
    print('state', i)
    if states[i].accept():
        print("Accept State")
    else:
        states[i].show_next(i)
    states[i].show()
    print()


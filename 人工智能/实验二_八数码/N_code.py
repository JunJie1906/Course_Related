import heapq
import time

class node:
    def __init__(self,state,father,fx,hash_val,steps=0):
        '''
        :param state:      current State, a String
        :param father:     last State
        :param fx:         distance
        :param hash_val:   hash(state)
        :param steps:      steps to begin
        '''
        self.father = father
        self.state = state
        self.fx = fx
        self.hash_val = hash_val
        self.steps = steps
    # less
    def __lt__(self, other):
        return (self.fx+self.steps) < (other.fx+other.steps)
    # equal
    def __eq__(self, other):
        return self.hash_val==other.hash_val


class NCode:
    def __init__(self,begin,size = 3,ans='123804765'):
        '''

        :param begin:   begin State
        :param size:    3*3 or 4*4 ......
        :param ans:     final State
        '''
        self.ans = ans
        self.begin = begin
        self.OPEN = []
        self.CLOSE = []
        self.size = size
    def f_manhattan(self,state):
        dis = 0
        for i in range(len(state)):
            pos = self.ans.find(state[i])
            dis += abs(pos - i) % self.size
            dis += abs(pos - i) // self.size
        return dis

    def f_notInPos(self,state):
        dis = 0
        for i in range(len(state)):
            if self.ans[i] != state[i]:
                dis+=1
        return dis

    def move_left(self,state):
        pos = state.find('0')
        state = list(state)
        if pos%self.size==0:
            return
        else:
            state[pos],state[pos-1]=state[pos-1],state[pos]
        s = ''
        for i in state:
            s += i
        return s

    def move_right(self, state):
        pos = state.find('0')
        state = list(state)
        if pos%self.size==self.size-1:
            return
        else:
            state[pos],state[pos+1]=state[pos+1],state[pos]
        s = ''
        for i in state:
            s += i
        return s

    def move_up(self, state):
        pos = state.find('0')
        state = list(state)
        if pos //self.size == 0:
            return
        else:
            state[pos], state[pos-self.size] = state[pos-self.size], state[pos]
        s = ''
        for i in state:
            s += i
        return s

    def move_down(self, state):
        pos = state.find('0')
        state = list(state)
        if pos // self.size == self.size-1:
            return
        else:
            state[pos], state[pos + self.size] = state[pos + self.size], state[pos]
        s = ''
        for i in state:
            s += i
        return s

    def run_manhattan(self):
        heapq.heappush(self.OPEN,node(self.begin,None,self.f_manhattan(self.begin),hash(self.begin),0))
        move = [self.move_up,self.move_down,self.move_left,self.move_right]
        while self.OPEN!=[]:
            Node = heapq.heappop(self.OPEN)
            if Node not in self.CLOSE:
                self.CLOSE.append(Node)
            if Node.fx==0:
                return Node
            for f in move:
                moveState = f(Node.state)
                if moveState != None:
                    moveNode = node(moveState,Node.hash_val,self.f_manhattan(moveState),hash(moveState),Node.steps+1)
                    if moveNode not in self.CLOSE:
                        heapq.heappush(self.OPEN,moveNode)
        print('Not Found')
        return False

    def run_notInPos(self):
        heapq.heappush(self.OPEN,node(self.begin,None,self.f_notInPos(self.begin),hash(self.begin),0))
        move = [self.move_up,self.move_down,self.move_left,self.move_right]
        while self.OPEN!=[]:
            Node = heapq.heappop(self.OPEN)
            if Node not in self.CLOSE:
                self.CLOSE.append(Node)
            if Node.fx==0:
                return Node
            for f in move:
                moveState = f(Node.state)
                if moveState != None:
                    moveNode = node(moveState,Node.hash_val,self.f_notInPos(moveState),hash(moveState),Node.steps+1)
                    if moveNode not in self.CLOSE:
                        heapq.heappush(self.OPEN,moveNode)
        print('Not Found')
        return False

    def print_road_manhattan(self):
        self.__init__(self.begin, self.size, self.ans)
        Node = self.run_manhattan()
        print('h(x) = manhattan')
        print('OPEN状态数：', len(self.OPEN))
        print('CLOSE状态数：',len(self.CLOSE))
        print('步数：',Node.steps)
        lst = []
        lst.append(Node)
        father = Node.father
        while father!=None:
            father = self.CLOSE[self.CLOSE.index(node(0,0,0,father))]
            lst.append(father)
            father = father.father
        for i in range(len(lst)):
            print('第',i,'步：')
            self.show_board(lst[len(lst)-i-1].state)

    def print_road_notInPos(self):
        self.__init__(self.begin,self.size,self.ans)
        Node = self.run_notInPos()
        print('h(x) = notInPos')
        print('OPEN状态数：', len(self.OPEN))
        print('CLOSE状态数：',len(self.CLOSE))
        print('步数：',Node.steps)
        lst = []
        lst.append(Node)
        father = Node.father
        while father!=None:
            father = self.CLOSE[self.CLOSE.index(node(0,0,0,father))]
            lst.append(father)
            father = father.father
        for i in range(len(lst)):
            print('第',i,'步：')
            self.show_board(lst[len(lst)-i-1].state)

    def show_board(self,s):
        for i in range(len(s)):
            if (i+self.size)%self.size==0:
                if i!=0:
                    print()
            print(s[i],end=' ')
        print()

# 3*3
code = NCode('123456780',3,'012345678')

# 4*4
# code = NCode('023416785qwe9rty',4,'123456789qwerty0')

t1=time.perf_counter()
code.print_road_manhattan()
t2 = time.perf_counter()
print('h(x) = manhattan, sum time is ',t2-t1,'s')
print()
t1=time.perf_counter()
code.print_road_notInPos()
t2 = time.perf_counter()
print('h(x) = notInPos, sum time is ',t2-t1,'s')



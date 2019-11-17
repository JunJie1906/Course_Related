import datetime
import heapq

Shift = [[0,1],[0,-1],[1,0],[-1,0]]

Final_state = []

InitState = []

class State():
    def __init__(self,gx,hx,state,val,father):
        self.gx = gx
        self.hx = hx
        self.state = state
        self.val = val
        self.father = father
        self.fx = gx+hx
    #定义优先队列的比较
    def __lt__(self, other):
        return self.fn < other.fn

    def __eq__(self, other):
        return self.hash_value == other.hash_value

    def __ne__(self, other):
        return not self.__eq__(other)

def hx_not_pos(cur_state,Final_state):
    ans = 0
    for i in range(len(Final_state)):
        for j in range(len(Final_state[i])):
            if cur_state[i][j]!=Final_state[i][j]:
                ans+=1
    return ans

def A_star(initState,FinalState,hx,open_table,close_table):
    s0 = State(0,hx(initState,FinalState),initState,hash(str(initState)),None)
    for i in Shift:
        open_table.append(State(0,hx(initState,FinalState),initState,hash(str(initState)),None))

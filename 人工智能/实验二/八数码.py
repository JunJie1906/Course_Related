

depth = 1

final_state = [[1,2,3],[8,0,4],[7,6,5]]

begin_state = [[6,3,4],[7,1,2],[5,8,0]]

ans = []
ans.append([[6,3,4],[7,1,2],[5,8,0]])
shifts = []

def left_shift(begin_state):
    for i in range(3):
        if begin_state[i][0]==0:
            return False
        for j in range(2):
            if begin_state[i][j+1]==0:
                crt = begin_state[i][j]
                begin_state[i][j+1] = crt
                begin_state[i][j] = 0
                return begin_state
    return False

def right_shift(begin_state):
    for i in range(3):
        if begin_state[i][2]==0:
            return False
        for j in range(2):
            if begin_state[i][j]==0:
                crt = begin_state[i][j+1]
                begin_state[i][j] = crt
                begin_state[i][j+1] = 0
                return begin_state
    return False

def up_shift(begin_state):
    for i in range(3):
        if begin_state[0][i]==0:
            return False
        for j in range(2):
            if begin_state[j+1][i]==0:
                crt = begin_state[j][i]
                begin_state[j+1][i] = crt
                begin_state[j][i] = 0
                return begin_state
    return False

def down_shift(begin_state):
    for i in range(3):
        if begin_state[2][i]==0:
            return False
        for j in range(2):
            if begin_state[j][i]==0:
                crt = begin_state[j+1][i]
                begin_state[j][i] = crt
                begin_state[j+1][i] = 0
                return begin_state
    return False

def d():
    return depth

def h(crt_state,final_state):
    p = 0
    for i in range(3):
        for j in range(3):
            if crt_state[i][j]!=final_state[i][j]:
                p+=1
    return p

def f(crt_state,final_state):
    return d()+h(crt_state,final_state)




MinVal = 321312
MinMatrix = -1

def solve(begin_state):
    print(1)
    MinVal = 321312
    if left_shift(begin_state)!=False:
        if MinVal > f(begin_state, final_state):
            MinVal = f(begin_state,final_state)
            MinMatrix =1
        right_shift(begin_state)
    if right_shift(begin_state)!=False:
        if MinVal>f(begin_state,final_state):
            MinVal = f(begin_state,final_state)
            MinMatrix = 2
        left_shift(begin_state)
    if up_shift(begin_state)!=False:
        if MinVal > f(begin_state, final_state):
            MinVal = f(begin_state,final_state)
            MinMatrix = 3
        down_shift(begin_state)
    if down_shift(begin_state)!=False:
        if MinVal > f(begin_state, final_state):
            MinVal = f(begin_state,final_state)
            MinMatrix = 4
        up_shift(begin_state)

    if MinMatrix==1:
        print(begin_state)
        left_shift(begin_state)
        print(begin_state)
        print(ans)
        if begin_state in ans:
            return
        shifts.append('left')
        ans.append(begin_state)
        solve(begin_state)
    elif MinMatrix==2:
        right_shift(begin_state)
        if begin_state in ans:
            return
        shifts.append('rightt')
        ans.append(begin_state)
        solve(begin_state)
    elif MinMatrix==3:
        up_shift(begin_state)
        if begin_state in ans:
            return
        shifts.append('up')
        ans.append(begin_state)
        solve(begin_state)
    elif MinMatrix==4:
        down_shift(begin_state)
        if begin_state in ans:
            return
        shifts.append('down')
        ans.append(begin_state)
        solve(begin_state)
    print(ans)
    print(shifts)
    print()
    print()
solve(begin_state)
print(ans)
print(shifts)


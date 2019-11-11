
class eight_code():

    def __init__(self):
        self.ans = '123804765'
        self.open = []
        self.close = []
        self.depth = 0

    def h(self,x):
        return self.depth

    def g_not_in_pos(self,x):
        p = 0
        for i in range(len(x)):
            if self.ans[i]!=x[i]:
                p+=1
        return p

    def f(self,x):
        return self.h(x)+self.g_not_in_pos(x)

    def swap(self,p,a,b):
        p = list(p)
        temp = p[a]
        p[a] = p[b]
        p[b] = temp
        q = ''
        for i in p:
            q+=i
        return q

    def left_shift(self,x):
        for j in range(len(x)):
            if x[j]=='0':
                if j%3==0:
                    return False
                return self.swap(x,j-1,j)

    def right_shift(self,x):
        for j in range(len(x)):
            if x[j]=='0':
                if (j+1)%3==0:
                    return False
                return self.swap(x,j,j+1)

    def up_shift(self, x):
        for j in range(len(x)):
            if x[j] == '0':
                if j<3:
                    return False
                return self.swap(x, j, j - 3)

    def down_shift(self, x):
        for j in range(len(x)):
            if x[j] == '0':
                if j>5:
                    return False
                return self.swap(x, j, j + 3)

    def Update_open(self,x):
        for i in range(len(self.open)):
            if self.open[i][0] == x[0]:
                if self.open[i][1] > x[1]:
                    self.open = self.open.replace(self.open[i],x)
                    return
                return
        self.open.append(x)

    def Update_close(self,x):
        for i in range(len(self.close)):
            if self.close[i][0] == x[0]:
                if self.close[i][1] > x[1]:
                    self.close = self.close.replace(self.close[i],x)
                    return True
                return True
        return False


    def solve(self,begin):
        while begin!=self.ans:
            next_state = [self.left_shift(begin),self.right_shift(begin),self.up_shift(begin),self.down_shift(begin)]
            for j in next_state:
                if j!=False:
                    in_close = self.Update_close((j, self.f(j),begin))
                    if in_close == False:
                        self.Update_open((j,self.f(j),begin))

            min_steps = 99999
            add_state = ''
            father = ''
            for j in range(len(self.open)):
                if self.open[j][1]<min_steps:
                    min_steps=self.open[j][1]
                    add_state=self.open[j][0]
                    father = self.open[j][2]
            self.open.remove((add_state,min_steps,father))
            self.close.append((add_state,min_steps,father))
            begin = add_state
            self.depth += 1

    def show_board(self,s):
        for i in range(len(s)):
            if (i+3)%3==0:
                print()
            print(s[i],end=' ')
        print()

    def show_road(self,x):
        road = []
        end = self.close[-1]
        road.append(end[0])
        while end[-1]!=x:
            road.append(end[-1])
            for i in self.close:
                if i[0]==end[-1]:
                    end = i
                    break
        for i in range(len(road)):
            self.show_board(road[len(road)-i-1])

    def play(self,s):
        str = '123804765'
        for i in s:
            if i=='w':
                if self.up_shift(str) != False:
                    str = self.up_shift(str)
            if i=='a':
                if self.left_shift(str) != False:
                    str = self.left_shift(str)
            if i=='s':
                if self.down_shift(str) != False:
                    str = self.down_shift(str)
            if i=='d':
                if self.right_shift(str) != False:
                    str = self.right_shift(str)
        print(str)
        self.show_board(str)

    def run(self,s):
        self.solve(s)
        self.show_road(s)

m = eight_code()

# m.show_board('682103754')
# m.play('awdwddsawsdawdsadwdsaasddwadasdawsaaaaadawsdawdasdaawdwwdssadwasdwawsdasdwasadawsadawawsdawdawdadawdsadawawsd')
board = '841203576'
m.show_board(board)
m.run(board)

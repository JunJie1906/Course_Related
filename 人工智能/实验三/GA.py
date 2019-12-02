import math
import heapq
import random
import time

class node:
    def __init__(self,val,adapt):
        self.val = val
        self.adapt = adapt
    # adapt lager, better
    def __lt__(self, other):
        return self.adapt > other.adapt
    def __eq__(self, other):
        return self.adapt == other.adapt

class GA:
    def __init__(self,size,low,high):
        '''
        :param size: 种群规模
        :param low:  取值下界
        :param high: 取值上界
        '''
        self.size = size
        self.population = []
        self.low = low
        self.high = high
        sz = (high-low)
        for _ in range(self.size):
            x = random.random()*sz+low
            self.Update(node(x,self.f(x)))

    def f(self,x):
        return x*math.sin(10*math.pi*x)+2.0

    def Encode(self,x):
        '''
        double to str
        :param x:
        :return:
        '''
        x-=self.low
        if x<1:
            return '0'+str(int(x*1e15))
        return str(int(x*1e15))

    def Decode(self,x):
        '''
        str to double
        :param x:
        :return:
        '''
        x = int(x)/1e15
        x +=self.low
        return x

    def Update(self,node):
        heapq.heappush(self.population, node)
        if len(self.population) > self.size:
            heapq.heappop(self.population)

    def cross(self,node1,node2):
        index = int(random.random()*16)
        x1 = list(self.Encode(node1.val))
        x2 = list(self.Encode(node2.val))
        try:
            x1[index],x2[index] = x2[index],x1[index]
        except:
            return node1,node2
        x1 = self.Decode(''.join(x1))
        x2 = self.Decode(''.join(x2))
        return node(x1,self.f(x1)),node(x2,self.f(x2))

    def vari(self,node1):
        index = int(random.random() * 16)
        # index = 15
        x1 = list(self.Encode(node1.val))

        # print(node1.val,len(x1),x1,index)
        try:
            x1[index] = str(int(random.random()*10))
        except:
            return node1
        x1 = self.Decode(''.join(x1))
        return node(x1,self.f(x1))

    def Select_maxN(self,n=1):
        l = []
        for i in range(n):
            l.append(heapq.heappop(self.population))
        for i in range(n):
            heapq.heappush(self.population, l[i])
        return l

    def Select_randomN(self,n=1):
        l = []
        size = len(self.population)
        for i in range(n):
            selected = self.population[int(random.random() * size)]
            l.append(selected)
        return l

    def Select_maxN_Cross_update(self):
        N = int(random.random()*self.size/2)*2
        selected = self.Select_maxN(N)
        for i in range(len(selected)//2):
            crt = self.cross(selected[i],selected[i+1])
            if crt[0].val in range(self.low,self.high):
                self.Update(crt[0])
            if crt[1].val in range(self.low, self.high):
                self.Update(crt[1])

    def Select_maxN_Vari_update(self):
        N = int(random.random()*self.size)
        selected = self.Select_maxN(N)
        for i in range(len(selected)):
            if selected[i].val in range(self.low, self.high):
                self.Update(self.vari(selected[i]))

    def run_MaxN(self,t=1):
        print('种群大小：',self.size)
        print('选择个体方法：随机选择N，选择N个最大个体')
        print('训练时间为：',t,'s')
        t1 = time.perf_counter()
        t2 = time.perf_counter()
        while t2-t1<t:
            if random.random()*2>1:
                self.Select_maxN_Cross_update()
            else:
                self.Select_maxN_Vari_update()
            t2 = time.perf_counter()

    def Select_randomN_Cross_update(self):
        N = int(random.random()*self.size/2)*2
        selected = self.Select_randomN(N)
        for i in range(len(selected)//2):
            crt = self.cross(selected[i],selected[i+1])
            if crt[0].val in range(self.low,self.high):
                self.Update(crt[0])
            if crt[1].val in range(self.low, self.high):
                self.Update(crt[1])

    def Select_randomN_Vari_update(self):
        N = int(random.random()*self.size)
        selected = self.Select_randomN(N)
        for i in range(len(selected)):
            if selected[i].val in range(self.low, self.high):
                self.Update(self.vari(selected[i]))

    def run_random(self,t=1):
        print('种群大小：',self.size)
        print('选择个体方法：随机选择N，随机选择N个个体')
        print('训练时间为：', t, 's')
        t1 = time.perf_counter()
        t2 = time.perf_counter()
        while t2-t1<t:
            if random.random()*2>1:
                self.Select_randomN_Cross_update()
            else:
                self.Select_randomN_Vari_update()
            t2 = time.perf_counter()

    def show(self,n):
        print('适应值前',n,'个个体的x和f(x)值：')
        ans = []
        while self.population!=[]:
            ans.append(heapq.heappop(self.population))
        for i in range(len(ans)):
            if i<n:
                self.show_node(ans[i])
            else:
                break
        print()


    def show_node(self,node):
        print(node.val, node.adapt)

# ga = GA(100,-1,2)
# ga.run_random(3)
# ga.show(5)
#
# ga = GA(50,-1,2)
# ga.run_random(3)
# ga.show(5)
#
# ga = GA(20,-1,2)
# ga.run_random(3)
# ga.show(5)
#
# ga = GA(100,-1,2)
# ga.run_MaxN(3)
# ga.show(5)
#
# ga = GA(50,-1,2)
# ga.run_MaxN(3)
# ga.show(5)
#
# ga = GA(20,-1,2)
# ga.run_MaxN(3)
# ga.show(5)



ga = GA(100,-1,2)
ga.run_MaxN(30)
ga.show(5)

ga = GA(50,-1,2)
ga.run_MaxN(30)
ga.show(5)

ga = GA(20,-1,2)
ga.run_MaxN(30)
ga.show(5)

ga = GA(100,-1,2)
ga.run_random(30)
ga.show(5)

ga = GA(50,-1,2)
ga.run_random(30)
ga.show(5)

ga = GA(20,-1,2)
ga.run_random(30)
ga.show(5)



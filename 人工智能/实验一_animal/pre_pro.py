src = ['有毛发','有奶','有羽毛','会飞', '下蛋','吃肉','有犬齿','有爪','眼盯着前方','有蹄','黄褐色','暗斑点','黑条纹','长腿','长脖子','黑色','不会飞','会游泳','善飞']
mid = ['食肉动物','哺乳动物','鸟','有蹄动物']
result = ['豹','虎','长颈鹿','斑马','鸵鸟','企鹅','信天翁']

def Addsrc(src,str):
    src.append(str)
def Addmid(src,str):
    src.append(str)

def Addresult(src,str):
    src.append(str)


rules = []
# rule[3] == 0: 生成mid 1，生成result
def AddRules(ru,rules,src,mid,result):
    a = ru.split("\n")
    for i in a:
        rule = [[],[],[],0]
        for j in range(len(src)):
            if i.find(src[j]) != -1:
                rule[0].append(j)
        for k in range(len(mid)):
            if i.find(mid[k]) != -1:
                rule[1].append(k)
        for p in range(len(result)):
            if i.find(result[p]) != -1:
                rule[2].append(p)
                rule[3] = 1
        if rule !=[[],[],[],0]:
            rules.append(rule)
    return rules

#展示所有的规则
def show(rule,src,mid,result):
    i = rule
    if i[3] == 0:
        print("中间结论：",end=' ')
    else:
        print("结果：",end=' ')
    for j in i[0]:
        print('src: ',src[j],end=' ')
    for k in i[1]:
        print('mid: ',mid[k],end=' ')
    for p in i[2]:
        print('result: ',result[p],end=' ')
    print()

def show_all(rules,src,mid,result):
    ans = ''
    for i in rules:
        if i[3] == 0:
            ans +="条件：";
            for j in i[0]:
                ans = ans + src[j] + ' '
            ans+='结论：'
            for k in i[1]:
                ans = ans + mid[k] + ' '
        else:
            ans+="条件：";
            for j in i[0]:
                ans = ans +src[j]+' '
            for k in i[1]:
                ans = ans +mid[k]+' '
            ans+='结论：'
            for p in i[2]:
                ans = ans + result[p]
        ans += '\n'
    return ans
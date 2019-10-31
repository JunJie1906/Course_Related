import easygui as gui
import pre_pro
import sys

src = ['有毛发','有奶','有羽毛','会飞', '下蛋','吃肉','有犬齿','有爪','眼盯前方','有蹄','黄褐色','暗斑点','黑条纹','长腿','长脖子','黑色','不会飞','会游泳','善飞']
mid = ['食肉动物','哺乳动物','鸟','有蹄动物','反刍动物']
result = ['豹','虎','长颈鹿','斑马','鸵鸟','企鹅','信天翁']
ru = """
规则1：如果：动物有毛发 则  ：该动物是哺乳动物
规则2：如果：动物有奶 则  ：该单位是哺乳动物
规则3：如果：该动物有羽毛 则  ：该动物是鸟
规则4：如果：动物会飞，且会下蛋 则  ：该动物是鸟
规则5：如果：动物吃肉 则  ：该动物是食肉动物
规则6：如果：动物有犬齿，且有爪，且眼盯前方 则  ：该动物是食肉动物
规则7：如果：动物是哺乳动物，且有蹄 则  ：该动物是有蹄动物
规则8：如果：动物是哺乳动物，且是反刍动物 则  ：该动物是有蹄动物
规则9：如果：动物是哺乳动物，且是食肉动物，且是黄褐色的，且有暗斑点 则  ：该动物是豹
规则10：如果：如果：动物是黄褐色的，且是哺乳动物，且是食肉，且有黑条纹则 ：该动物是虎
规则11：如果：动物有暗斑点，且有长腿，且有长脖子，且是有蹄类 则  ：该动物是长颈鹿
规则12：如果：动物有黑条纹，且是有蹄类动物  则  ：该动物是斑马
规则13：如果：动物有长腿，且有长脖子，且是黑色的，且是鸟，且不会飞 则  ：该动物是鸵鸟
规则14：如果：动物是鸟，且不会飞，且会游泳，且是黑色的 则  ：该动物是企鹅
规则15：如果：动物是鸟，且善飞 则  ：该动物是信天翁
"""


rules = []

def init():
    pre_pro.AddRules(ru, rules, src, mid, result)


# a是b的子数组
def IsSub(a,b):
    for i in a:
        if i not in b:
            return False
    return True

def predict(str,rules,src,mid,result):
    crt = [[],[],[],0]
    # 把字符串里面出现的初始条件加进去
    for i in range(len(src)):
        if str.find(src[i])!=-1:
            crt[0].append(i)
    for j in range(len(mid)):
        if str.find(mid[j])!=-1:
            crt[1].append(j)
    # 由初始条件推出中间条件
    for p in rules:
        if IsSub(p[0],crt[0]) and p[3]==0:
            for k in p[1]:
                crt[1].append(k)
    for q in rules:
        if IsSub(q[0],crt[0]) and q[3]==1 and IsSub(q[1],crt[1]):
            #能预测到结果
            for k in q[2]:
                crt[2].append(k)
            crt[3] = 1
    if crt[3]==1:
        s='预测结果：'
        for i in crt[2]:
            s+=result[i]
            s+=' '
        return s
    q = '预测结果：'
    for i in crt[1]:
        q+=mid[i]
    return q

init()

def GUI():
    a = gui.multchoicebox(msg="选择您需要的服务\nTips:先点击 Clear All,然后选择需要的功能，点OK， 否则容易点不到。。",choices=('预测','添加新的特征和规则','显示已有的规则','退出'))
    if a == ['退出']:
        exit()
    elif a ==['预测']:
        inp = gui.enterbox(msg="请输入相应的特征:\n输入格式：\n只要输入包含特征字符串就行\n如果输入更多特征则会预测所有可能结果")
        if inp ==None:
            inp = ''
        ans = predict(inp, rules, src, mid, result)
        if ans =='预测结果：':
            ans = "预测结果：未预测到~~"
        if gui.ccbox("预测结果："+ans+"\n还要继续吗?",choices=("还要继续","算了吧")):
            GUI()
        else:
             sys.exit(0)
    elif a == ['显示已有的规则']:
        ans = pre_pro.show_all(rules,src,mid,result)
        if gui.ccbox(ans+"\n还要继续吗?",choices=("还要继续","算了吧")):
            GUI()
        else:
             sys.exit(0)

    elif a== ['添加新的特征和规则']:
        msg = "请输入对应的特征：\n每种特征以空格分隔输入\nrules以字符串形式输入，不同的rules用换行符\\n分隔，每条rule只要包含相应特征字符串就行"
        title = "添加特征及规则"
        Names = ["src", "mid", "result", "rules"]
        values = []
        values = gui.multenterbox(msg, title, Names)
        if values == []:
            values = ['','','']
        for i in values[0].split():
            if i not in src:
                src.append(i)
        for i in values[1].split():
            if i not in mid:
                mid.append(i)
        for i in values[2].split():
            if i not in result:
                result.append(i)
        pre_pro.AddRules(values[3],rules,src,mid,result)
        pre_pro.show_all(rules,src,mid,result)
        if gui.ccbox("输入完成！！\n还要继续吗?",choices=("还要继续","算了吧")):
            GUI()
        else:
             sys.exit(0)
    else:
        GUI()
GUI()



